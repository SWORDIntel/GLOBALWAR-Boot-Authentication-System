# GLOBALWAR Boot Authentication System

> *"SHALL WE PLAY A GAME?"*

## ⚠️ IMPORTANT NOTICE

**This is a DOCUMENTATION AND STUB PROJECT ONLY.** The code provided consists of comprehensive documentation, design specifications, and stub implementations. This is NOT production-ready code and should be treated as a detailed blueprint for potential future implementation.

## Overview

GLOBALWAR is a comprehensive design for a boot-time authentication system inspired by the 1983 film WarGames. It presents a multi-layered security system that frustrates unauthorized users while rewarding those who understand that "the only winning move is not to play."

## Project Status

- ✅ **Complete Documentation** - Full system architecture and design
- ✅ **Stub Implementations** - All major components stubbed out
- ✅ **Game Logic** - Chess and trap games fully documented
- ✅ **Audio System** - Complete implementation provided
- ⚠️ **NOT FUNCTIONAL** - Requires actual implementation
- ⚠️ **FOR REFERENCE ONLY** - Educational and planning purposes

## What's Included

### Documentation (`/docs`)
- `COMPLETE_SYSTEM.md` - Full system specification with all secrets
- `IMPLEMENTATION_GUIDE.md` - Detailed build and deployment instructions
- `TESTING_PROCEDURES.md` - Comprehensive test plans
- Game design documents for chess, GTW, and traps
- TPM integration and hardware binding specs

### Source Code (`/src`)
- **Core Components** (stubs)
  - `main.c` - WOPR interface entry point
  - `tpm_handler.c` - TPM 2.0 hardware binding
  - `yubikey_handler.c` - Dual YubiKey authentication
  - `state_machine.c` - Authentication state tracking

- **Implemented Components**
  - `audio_system.c` - Complete PC speaker and TTS implementation
  - `chess_hflr.c` - Full cheating chess with 5 escalation levels
  - `escape_trap.c` - Complete trap games implementation

- **Game Systems** (stubs)
  - `gtw.c` - Global Thermonuclear War game design

### Scripts (`/scripts`)
- `generate_sounds.sh` - Creates Joshua voice lines and system sounds

## System Design Highlights

### Authentication Flow
```
TPM Check → YubiKey Check → WOPR Dialogue → Refusal Path → Backdoor → Password → ZFS Unlock
     ↓           ↓                ↓
[Chess Hell] [Chess Hell]  [Accept → GTW → Honeypot]
```

### Key Features
- **Hardware Binding**: TPM 2.0 PCR measurements
- **Physical Tokens**: Dual YubiKey requirement (FIDO2 + FIPS)
- **Psychological Deterrent**: Impossibly frustrating chess game
- **Movie Authenticity**: Exact dialogue from WarGames
- **Multiple Trap Layers**: Escape attempts lead to worse situations
- **Hidden Win Conditions**: Secret paths for legitimate users

### Secret Escape Routes (Documented)
1. **From Chess**: Type `XYZZY` (leads to trap games)
2. **From Trap**: Type quote backwards: `YALP OT TON SI EVOM GNINNOW YLNO EHT`
3. **Emergency**: F12 + correct YubiKey during boot
4. **GTW Win**: Specific 5-turn sequence with <50M casualties

## Implementation Requirements

If you decide to build this system, you'll need:

### Hardware
- TPM 2.0 chip or Intel PTT
- YubiKey FIDO2 (PID 0x0402)
- YubiKey FIPS (PID 0x0407)
- PC speaker or ALSA support

### Software
- Linux with systemd-boot
- ZFS on Linux with encryption
- Libraries: `libncurses5-dev`, `libtss2-dev`, `libfido2-dev`
- Tools: `espeak`, `alsa-utils`

## Why This Exists

This project serves as:
1. **Educational Reference** - Learn about boot-time authentication
2. **Security Research** - Explore defense-in-depth concepts
3. **Creative Project** - Tribute to WarGames and classic hacker culture
4. **Design Document** - Blueprint for similar security systems
5. **Entertainment** - The frustration mechanics are hilarious in concept

## Repository Structure

```
/boot/GLOBALWAR/
├── README.md              # This file
├── docs/                  # Comprehensive documentation
│   ├── COMPLETE_SYSTEM.md
│   ├── IMPLEMENTATION_GUIDE.md
│   └── TESTING_PROCEDURES.md
├── src/                   # Source code (stubs + implementations)
│   ├── core/             # Core system components
│   ├── game/             # Game implementations
│   └── honeypot/         # Honeypot system
└── scripts/              # Build and setup scripts
```

## Legal Disclaimer

This software is provided "as is" for educational and entertainment purposes only. The authors are not responsible for any use, misuse, or implementation of these concepts. The frustration caused by the chess game is intentional and not a bug.

## Credits

- Inspired by WarGames (1983)
- Uses concepts from TPM 2.0 specifications
- FIDO2/WebAuthn for modern authentication
- ZFS on Linux for encrypted filesystems

---

> *"A strange game. The only winning move is not to play."*
> 
> *"How about a nice game of chess?"*

---

**Remember**: This is a comprehensive DESIGN DOCUMENT with stub implementations. It is NOT functional code. The chess game, if implemented as designed, would be genuinely impossible to win. You have been warned.
EOF < /dev/null
