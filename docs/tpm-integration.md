# TPM 2.0 Hardware Binding

## Overview
Binds WOPR boot system to specific Dell laptop hardware using TPM 2.0 attestation.

## TPM PCR Usage

### PCR Allocation
```
PCR 0-3: BIOS/UEFI measurements
PCR 4: Boot loader (systemd-boot)
PCR 5: Boot loader configuration
PCR 7: Secure Boot state
PCR 8: Kernel command line
PCR 9: Kernel image
PCR 10: WOPR state storage
PCR 11: YubiKey serial binding
```

## Initialization Sequence

```c
// tpm_handler.c
bool init_tpm_binding() {
    // 1. Check TPM manufacturer
    if (\!is_intel_ptt() && \!is_stm_tpm()) {
        return launch_chess_game();  // Wrong hardware
    }
    
    // 2. Verify PCR values match expected boot
    if (\!verify_pcr_chain()) {
        return launch_chess_game();  // Modified boot
    }
    
    // 3. Check for YubiKey presence
    if (\!detect_yubikey()) {
        return launch_chess_game();  // No YubiKey
    }
    
    // 4. Retrieve stored YubiKey serials from TPM
    char* authorized_serials = tpm_nvread(0x1500000);
    if (\!verify_yubikey_serial(authorized_serials)) {
        return launch_chess_game();  // Wrong YubiKey
    }
    
    // 5. All checks passed - launch WOPR
    return launch_wopr();
}
```

## TPM NV Storage Layout

### Index Allocations
```
0x1500000: Authorized YubiKey serials (64 bytes)
0x1500001: WOPR session keys (256 bytes)
0x1500002: Failed attempt counter (4 bytes)
0x1500003: Hardware fingerprint (128 bytes)
0x1500004: ZFS key seal policy (512 bytes)
```

## Sealing ZFS Keys

### Key Sealing Process
```bash
# Seal ZFS key to TPM with PCR policy
tpm2_createpolicy --policy-pcr \
    -l 0,1,2,3,4,5,7,8,9 \
    -L sha256 \
    -f pcr.policy

tpm2_create -C primary.ctx \
    -g sha256 \
    -G rsa \
    -a "fixedtpm|fixedparent|sensitivedataorigin" \
    -i zfs.key \
    -L pcr.policy \
    -r zfs.priv \
    -u zfs.pub

# Load into TPM persistent storage
tpm2_load -C primary.ctx \
    -r zfs.priv \
    -u zfs.pub \
    -n zfs.name \
    -c zfs.ctx

tpm2_evictcontrol -C o \
    -c zfs.ctx \
    0x81000000
```

### Key Unseal at Boot
```c
bool unseal_zfs_key(char* passphrase) {
    ESYS_CONTEXT* ctx;
    TPM2B_SENSITIVE_DATA* unsealed;
    
    // Initialize TPM context
    Esys_Initialize(&ctx, NULL, NULL);
    
    // Verify PCR state matches policy
    if (\!verify_pcr_policy(ctx)) {
        return false;  // Boot state changed
    }
    
    // Unseal the key
    Esys_Unseal(ctx, 
                0x81000000,  // Persistent handle
                ESYS_TR_PASSWORD,
                ESYS_TR_NONE,
                ESYS_TR_NONE,
                &unsealed);
    
    // Combine with user passphrase
    char* final_key = derive_key(unsealed->buffer, passphrase);
    
    // Unlock ZFS
    return unlock_zfs_with_key(final_key);
}
```

## Hardware Fingerprinting

### Collected Attributes
```c
typedef struct {
    char cpu_serial[32];      // From MSR 0x119
    char board_serial[64];     // DMI Type 2
    char tpm_ek_cert[256];     // TPM Endorsement Key
    uint8_t mac_addresses[6][6]; // All network interfaces
    char dell_service_tag[16];  // Dell specific
} hardware_fingerprint_t;

bool verify_hardware() {
    hardware_fingerprint_t current;
    hardware_fingerprint_t stored;
    
    collect_fingerprint(&current);
    tpm_nvread(0x1500003, &stored, sizeof(stored));
    
    // Allow 1 component change (e.g., network card)
    int differences = compare_fingerprints(&current, &stored);
    return (differences <= 1);
}
```

## Anti-Tampering Measures

### PCR Extension on Events
```c
// Extend PCR 10 on authentication events
void record_auth_attempt(bool success) {
    TPM2B_DIGEST digest;
    
    if (success) {
        memcpy(digest.buffer, "AUTH_SUCCESS", 12);
    } else {
        memcpy(digest.buffer, "AUTH_FAILURE", 12);
    }
    
    tpm2_pcr_extend(10, &digest);
}

// Check if too many failures
bool check_lockout() {
    uint32_t failures;
    tpm_nvread(0x1500002, &failures, 4);
    
    if (failures > 5) {
        // Permanently lock until TPM reset
        tpm2_dictionarylockout_lock();
        return true;
    }
    return false;
}
```

## TPM Random Number Usage

```c
// Use TPM RNG for game randomness
int get_game_random(int max) {
    TPM2B_DIGEST random_bytes;
    
    Esys_GetRandom(esys_ctx,
                   ESYS_TR_NONE,
                   ESYS_TR_NONE, 
                   ESYS_TR_NONE,
                   32,
                   &random_bytes);
    
    // Convert to integer range
    uint32_t val = *(uint32_t*)random_bytes.buffer;
    return val % max;
}
```

## Fallback Behavior

### If TPM Check Fails:
1. No TPM → Cheating chess only
2. Wrong TPM → Cheating chess only  
3. PCR mismatch → Cheating chess only
4. No YubiKey → Cheating chess only
5. Wrong YubiKey → Cheating chess only

### Recovery Mode
Hold F12 during boot + correct YubiKey:
- Bypasses PCR checks
- Still requires TPM presence
- Logs security event
- Requires ZFS passphrase + recovery code

## Build Requirements
```makefile
# Link with TPM libraries
LDFLAGS += -ltss2-esys -ltss2-sys -ltss2-mu
CFLAGS += -I/usr/include/tss2

# Required packages
# apt-get install libtss2-dev tpm2-tools
```
EOFTPM < /dev/null
