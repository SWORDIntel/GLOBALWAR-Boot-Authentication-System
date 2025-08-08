# GLOBALWAR System Architecture

## Overview
Multi-layered authentication system using WarGames WOPR interface with hardware-bound security.

## Boot Flow

### Stage 1: Initial Hardware Check
1. Check for TPM 2.0 presence
2. Verify TPM PCR values match expected boot chain
3. Check if YubiKey FIDO2 is inserted
   - If NO YubiKey: Launch CHEATING CHESS (see chess-game.md)
   - If YubiKey present: Continue to WOPR

### Stage 2: WOPR Authentication
1. Display WOPR greeting ("GREETINGS PROFESSOR FALKEN")
2. Insistently suggest playing Global Thermonuclear War (4+ times)
3. Track user responses:
   - If user plays GTW → Launch game (see gtw-game.md)
   - If user wins GTW → HONEYPOT_STUB() [future implementation]
   - If user refuses 4+ times → Proceed to Stage 3

### Stage 3: True Authentication
1. After sufficient refusals, prompt for backdoor code
2. Valid codes: "CPE1704TKS", "JOSHUA", "FALKEN"
3. Prompt for password: "PENCIL", "TICTHREE"
4. On success → Stage 4

### Stage 4: ZFS Unlock
1. Display: "THE ONLY WINNING MOVE IS NOT TO PLAY"
2. Prompt: "ENTER ZFS ENCRYPTION PASSPHRASE:"
3. Use entered passphrase to unlock:
   ```bash
   echo "$PASSPHRASE" | zfs load-key rpool/ROOT/LONENOMAD
   ```
4. Mount and switch_root to real system

## Module Structure

```
/boot/GLOBALWAR/
├── src/
│   ├── core/
│   │   ├── main.c          # Main entry point
│   │   ├── state_machine.c # WOPR state management
│   │   ├── tpm_handler.c   # TPM operations
│   │   └── auth.c          # Authentication logic
│   ├── game/
│   │   ├── gtw_engine.c    # Global Thermonuclear War
│   │   ├── chess_engine.c  # Cheating chess
│   │   └── ai_opponent.c   # Game AI
│   ├── honeypot/
│   │   └── stub.c          # Placeholder for honeypot OS
│   └── assets/
│       ├── ascii_art.h     # WOPR screens
│       └── dialogues.h     # Movie quotes
└── initramfs/
    └── init                # Boot script
```

## Hardware Requirements
- TPM 2.0 (Intel PTT or STM)
- YubiKey 4/5 with FIDO2
- Dell ControlVault 3 (optional enhancement)

## Security Layers
1. **TPM Binding**: Locks to specific hardware
2. **YubiKey Presence**: Determines chess vs WOPR
3. **Behavioral Analysis**: Refusing to play = legitimate user
4. **Knowledge Factor**: Movie references as passwords
5. **Final Secret**: Actual ZFS passphrase

## Stubs for Future Development
- `honeypot_boot()`: Currently just reboots
- `fingerprint_auth()`: Placeholder for ControlVault 3
- `network_unlock()`: Remote attestation option
EOF < /dev/null
