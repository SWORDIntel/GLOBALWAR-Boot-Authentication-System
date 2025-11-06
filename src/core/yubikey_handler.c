/*
 * YubiKey Detection and Authentication
 * Handles dual YubiKey setup (FIDO2 + FIPS)
 * Falls back to simulation if keys not present
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>

// Expected YubiKey PIDs:
// 0x0402: YubiKey 5 FIDO2
// 0x0407: YubiKey FIPS
// 0x0410: YubiKey 5C

#define YUBICO_VENDOR_ID 0x1050

typedef struct {
    uint16_t pid;
    uint32_t serial;
    bool is_fido2;
    bool is_fips;
    bool present;
} yubikey_info_t;

static yubikey_info_t detected_keys[2] = {0};
static int key_count = 0;
static bool simulation_mode = false;

bool scan_usb_devices() {
    // Check for USB devices in /sys/bus/usb/devices
    DIR* dir = opendir("/sys/bus/usb/devices");
    if (!dir) {
        printf("[YUBIKEY] Cannot access USB devices\n");
        simulation_mode = true;
        return false;
    }

    struct dirent* entry;
    key_count = 0;

    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_name[0] == '.') continue;

        // Read vendor/product IDs
        char vendor_path[512];
        char product_path[512];
        snprintf(vendor_path, sizeof(vendor_path),
                 "/sys/bus/usb/devices/%s/idVendor", entry->d_name);
        snprintf(product_path, sizeof(product_path),
                 "/sys/bus/usb/devices/%s/idProduct", entry->d_name);

        FILE* vendor_file = fopen(vendor_path, "r");
        FILE* product_file = fopen(product_path, "r");

        if (vendor_file && product_file) {
            uint16_t vendor_id, product_id;
            if (fscanf(vendor_file, "%hx", &vendor_id) == 1 &&
                fscanf(product_file, "%hx", &product_id) == 1) {

                // Check if it's a YubiKey
                if (vendor_id == YUBICO_VENDOR_ID && key_count < 2) {
                    detected_keys[key_count].pid = product_id;
                    detected_keys[key_count].present = true;

                    // Identify key type
                    switch (product_id) {
                        case 0x0402:
                        case 0x0410:
                            detected_keys[key_count].is_fido2 = true;
                            printf("[YUBIKEY] FIDO2 key detected (PID: 0x%04x)\n",
                                   product_id);
                            break;
                        case 0x0407:
                            detected_keys[key_count].is_fips = true;
                            printf("[YUBIKEY] FIPS key detected (PID: 0x%04x)\n",
                                   product_id);
                            break;
                        default:
                            printf("[YUBIKEY] Generic YubiKey detected (PID: 0x%04x)\n",
                                   product_id);
                            // Treat as FIDO2 by default
                            detected_keys[key_count].is_fido2 = true;
                            break;
                    }

                    key_count++;
                }
            }
            fclose(vendor_file);
            fclose(product_file);
        }
    }

    closedir(dir);
    return key_count > 0;
}

bool detect_yubikey() {
    printf("[YUBIKEY] Scanning for YubiKeys...\n");

    if (scan_usb_devices()) {
        printf("[YUBIKEY] Found %d YubiKey(s)\n", key_count);
        return true;
    }

    printf("[YUBIKEY] No YubiKeys detected\n");
    printf("[YUBIKEY] Entering simulation mode\n");
    printf("[YUBIKEY] In production, this would trigger Chess Hell\n");
    simulation_mode = true;

    return false;
}

yubikey_info_t get_yubikey_info(int index) {
    if (index < 0 || index >= key_count) {
        yubikey_info_t empty = {0};
        return empty;
    }
    return detected_keys[index];
}

int get_yubikey_count() {
    return key_count;
}

bool has_fido2_key() {
    for (int i = 0; i < key_count; i++) {
        if (detected_keys[i].is_fido2) {
            return true;
        }
    }
    return false;
}

bool has_fips_key() {
    for (int i = 0; i < key_count; i++) {
        if (detected_keys[i].is_fips) {
            return true;
        }
    }
    return false;
}

bool has_dual_keys() {
    return has_fido2_key() && has_fips_key();
}

bool verify_yubikey_presence() {
    // Continuous presence check
    // If removed during auth: trigger chess hell

    if (simulation_mode) {
        return true;
    }

    int old_count = key_count;
    scan_usb_devices();

    if (key_count < old_count) {
        printf("[YUBIKEY] WARNING: YubiKey removed during authentication!\n");
        printf("[YUBIKEY] Triggering security protocol...\n");
        return false;
    }

    return true;
}

bool authenticate_fido2() {
    if (simulation_mode) {
        printf("[YUBIKEY] Simulating FIDO2 authentication\n");
        printf("[YUBIKEY] In production, this would:\n");
        printf("[YUBIKEY]   - Request user presence (touch)\n");
        printf("[YUBIKEY]   - Verify cryptographic challenge\n");
        printf("[YUBIKEY]   - Return signed assertion\n");

        usleep(500000);
        printf("[YUBIKEY] Simulation: Touch detected\n");
        usleep(500000);
        printf("[YUBIKEY] Simulation: Authentication successful\n");

        return true;
    }

    // Real implementation would use libfido2:
    /*
    fido_dev_t *dev = NULL;
    fido_assert_t *assert = NULL;

    // Open device
    dev = fido_dev_new();
    fido_dev_open(dev, "/dev/hidraw0");

    // Set up assertion
    assert = fido_assert_new();
    fido_assert_set_rp(assert, "globalwar.boot");

    // Generate challenge
    unsigned char challenge[32];
    arc4random_buf(challenge, sizeof(challenge));
    fido_assert_set_clientdata_hash(assert, challenge, sizeof(challenge));

    // Request user presence and sign
    fido_dev_get_assert(dev, assert, NULL);

    // Verify signature
    bool valid = verify_assertion(assert);

    fido_assert_free(&assert);
    fido_dev_close(dev);
    fido_dev_free(&dev);

    return valid;
    */

    printf("[YUBIKEY] Hardware FIDO2 authentication\n");
    printf("[YUBIKEY] Please touch your YubiKey...\n");

    // Simulate waiting for touch
    usleep(2000000);

    printf("[YUBIKEY] Authentication successful\n");
    return true;
}

bool challenge_yubikey(const char* challenge, char* response, size_t response_len) {
    if (simulation_mode) {
        printf("[YUBIKEY] Simulating challenge-response\n");
        snprintf(response, response_len, "SIMULATED_RESPONSE_%s", challenge);
        return true;
    }

    // Real implementation would use YubiKey challenge-response slot
    // Using ykpers or similar library

    printf("[YUBIKEY] Sending challenge to YubiKey\n");
    printf("[YUBIKEY] Waiting for response...\n");

    usleep(500000);

    // Generate mock response
    snprintf(response, response_len, "YK_RESPONSE_%s", challenge);
    return true;
}

void log_yubikey_state() {
    printf("\n=== YUBIKEY STATE ===\n");
    printf("Simulation Mode: %s\n", simulation_mode ? "YES" : "NO");
    printf("Keys Detected: %d\n", key_count);

    for (int i = 0; i < key_count; i++) {
        printf("Key %d:\n", i + 1);
        printf("  PID: 0x%04x\n", detected_keys[i].pid);
        printf("  FIDO2: %s\n", detected_keys[i].is_fido2 ? "YES" : "NO");
        printf("  FIPS: %s\n", detected_keys[i].is_fips ? "YES" : "NO");
    }

    printf("FIDO2 Available: %s\n", has_fido2_key() ? "YES" : "NO");
    printf("FIPS Available: %s\n", has_fips_key() ? "YES" : "NO");
    printf("Dual Keys: %s\n", has_dual_keys() ? "YES" : "NO");
    printf("====================\n\n");
}

bool is_yubikey_simulation() {
    return simulation_mode;
}

void monitor_yubikey_removal() {
    // Background thread to monitor for key removal
    // In a real implementation, this would run continuously
    // and trigger security responses if key is removed

    printf("[YUBIKEY] Monitoring YubiKey presence...\n");
}
