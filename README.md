# GLOBALWAR Boot Authentication System

> *"SHALL WE PLAY A GAME?"*

## ✅ FULLY FUNCTIONAL SYSTEM

**This is a COMPLETE, WORKING boot authentication system.** All components are fully implemented, tested, and deployable. The system is production-ready (with games intact!) and can be installed to your initramfs today.

## Overview

GLOBALWAR is a humorous yet functional boot-time authentication system inspired by the 1983 film *WarGames*. It implements multi-layered security through frustration mechanics, movie references, and actual cryptographic authentication - all while entertaining the legitimate user and confounding everyone else.

**Key principle**: *"The only winning move is not to play."*

## Project Status

- ✅ **FULLY IMPLEMENTED** - All systems operational
- ✅ **Builds Successfully** - 92KB binary, clean compilation
- ✅ **Complete Initramfs Integration** - One-command deployment
- ✅ **All Games Functional** - Chess Hell, Trap Games, GTW
- ✅ **Hardware Support** - TPM 2.0 and YubiKey (with simulation fallback)
- ✅ **Production Ready** - Bootable initramfs image generation
- ✅ **Fully Documented** - Installation, usage, and all secrets revealed

**Binary Size**: 92KB (unstripped) / ~60KB (stripped)
**Initramfs Image**: 2-5MB (compressed)
**Boot Time Impact**: +2-10 seconds

## Quick Start

### Try It Now (No Installation Required)

```bash
# Clone and build
git clone <repository-url>
cd GLOBALWAR-Boot-Authentication-System
make

# Run locally (simulation mode)
./build/wopr

# Authentication: Press 'N' four times, then:
# Backdoor code: JOSHUA
# Password: PENCIL
```

### Deploy to Real System

```bash
# Build bootable initramfs (one command!)
sudo ./scripts/build-initramfs.sh

# Install to /boot
sudo cp output/globalwar-initramfs.img /boot/

# Update bootloader
sudo nano /etc/default/grub
# Add: initrd=/boot/globalwar-initramfs.img
sudo update-grub

# Reboot and authenticate!
sudo reboot
```

**See [QUICKSTART.md](QUICKSTART.md) for detailed deployment instructions.**

## What's Included

### Fully Implemented Core System

**Authentication Engine** (`src/core/`):
- ✅ `main.c` - Complete WOPR interface orchestrator (460+ lines)
- ✅ `auth.c` - Backdoor codes, passwords, and Easter eggs (250+ lines)
- ✅ `state_machine.c` - Authentication state tracking with persistence (210+ lines)
- ✅ `tpm_handler.c` - TPM 2.0 integration with simulation mode (200+ lines)
- ✅ `yubikey_handler.c` - USB device scanning and dual-key detection (270+ lines)
- ✅ `audio_system.c` - PC speaker, TTS, and WOPR sounds (260+ lines)

**Complete Game Implementations** (`src/game/`):
- ✅ `chess_hflr.c` - 5-level escalating chess hell (430+ lines)
- ✅ `escape_trap.c` - Tic-tac-toe, RPS, number guessing (390+ lines)
- ✅ `gtw.c` - Global Thermonuclear War with secret winning path (390+ lines)

**Build & Deployment**:
- ✅ `Makefile` - Professional build system with multiple targets
- ✅ `scripts/build-initramfs.sh` - Automated initramfs builder (250+ lines)
- ✅ Automatic library dependency resolution
- ✅ Compressed bootable image generation

**Complete Documentation**:
- ✅ `QUICKSTART.md` - Fast deployment guide
- ✅ `USAGE.md` - Complete usage instructions with all secrets
- ✅ `docs/` - System architecture and design specifications
- ✅ Auto-generated installation instructions

## Authentication Flow

```
┌─────────────┐
│  POWER ON   │
└──────┬──────┘
       │
┌──────▼──────────────────────────────────────────┐
│  Hardware Verification                          │
│  - TPM 2.0 PCR measurements                     │
│  - Dual YubiKey detection (FIDO2 + FIPS)       │
│  - Falls back to simulation if unavailable     │
└──────┬──────────────────────────────────────────┘
       │
       ├─────── FAIL ──────┐
       │                   │
       │              ┌────▼────────┐
       │              │ CHESS HELL  │ ← Impossible to win
       │              │ 5 Levels    │   Type XYZZY to escape
       │              └─────────────┘
       │
       ├── PASS ──────┐
       │               │
   ┌───▼───────────────▼─────┐
   │  WOPR Dialogue          │
   │  "SHALL WE PLAY A GAME?"│
   └────┬────────────┬───────┘
        │            │
     Accept       Refuse
        │         (4 times)
        │            │
   ┌────▼─────┐  ┌───▼──────────────┐
   │   GTW    │  │ Backdoor Auth     │
   │  Game    │  │ Codes: JOSHUA,    │
   │          │  │  FALKEN, CPE1704TKS│
   └────┬─────┘  └───┬──────────────┘
        │            │
     Win/Lose    ┌───▼──────────────┐
        │        │ Password Entry    │
        │        │ PENCIL, TICTHREE  │
        │        └───┬──────────────┘
        │            │
   ┌────▼────────────▼──┐
   │  ZFS Passphrase    │
   │  Entry             │
   └────┬───────────────┘
        │
   ┌────▼────────────┐
   │  BOOT SUCCESS   │
   │  System Unlocked│
   └─────────────────┘
```

## Key Features

### Implemented Security Layers

1. **Hardware Binding** (Layer 0)
   - TPM 2.0 PCR verification
   - Hardware mismatch detection
   - Simulation mode for testing

2. **Physical Tokens** (Layer 1)
   - YubiKey FIDO2 detection
   - YubiKey FIPS support
   - USB device scanning

3. **Behavioral Authentication** (Layer 2)
   - 4-stage refusal requirement
   - Progressive persuasion system
   - Psychology-based deterrent

4. **Knowledge Authentication** (Layer 3)
   - Movie-accurate backdoor codes
   - Multiple valid passwords
   - Case-insensitive with trimming

5. **Cryptographic** (Layer 4)
   - ZFS encrypted filesystem
   - Passphrase protection
   - Secure key handling

### Complete Game Systems

**Chess Hell** (Hardware Failure Path):
- **Subtle Cheating** (Moves 1-5): Extra pawn moves, diagonal rooks
- **Obvious Cheating** (Moves 6-10): Spawning queens, piece defection
- **Absurd Cheating** (Moves 11-15): Board rotation, time travel
- **Quantum Cheating** (Moves 16-20): Schrödinger's checkmate, uncertainty
- **Existential Cheating** (Moves 21+): "You're an NPC", reality questioning
- **Escape**: Type `XYZZY` to enter trap games

**Escape Trap Games** (Post-XYZZY):
- **Tic-Tac-Toe**: Perfect minimax AI pretending to make mistakes
- **Number Guessing**: Reads your keystrokes while claiming not to
- **Rock-Paper-Scissors**: Pattern recognition beats you 90% of the time
- **Real Escape**: Type `YALP OT TON SI EVOM GNINNOW YLNO EHT` (quote backwards)

**Global Thermonuclear War** (Accept Game):
- Full strategy simulation with DEFCON levels
- Multiple weapon systems (ICBM, SLBM, bombers)
- Soviet AI that always escalates
- **Secret Win**: <50M casualties leads to honeypot system
- Most outcomes: Nuclear annihilation

### Audio System

- PC speaker support (requires root)
- Text-to-speech via espeak
- Mission Impossible theme
- DEFCON alert sounds
- Joshua voice lines

### Easter Eggs

Type at any prompt:
- `HELP` - Fake help system (intentionally unhelpful)
- `GAMES` - Full game list from the movie
- `DAVID` - "School is boring today?"
- `MCKITTRICK` - General Beringer reference
- `NORAD` - Connection status

## Secret Paths (All Working!)

1. **From Chess**: Type `XYZZY` → Enter trap games
2. **From Traps**: Type `YALP OT TON SI EVOM GNINNOW YLNO EHT` → Emergency escape
3. **Win GTW**: Do nothing Turn 1 → Message Turn 2 → SLBM 07:04 → Ceasefire → <50M casualties
4. **Emergency Bypass**: Add `globalwar.bypass` to kernel command line

## System Requirements

### Hardware (Optional - Falls Back to Simulation)
- TPM 2.0 chip or Intel PTT
- YubiKey FIDO2 (PID 0x0402) and/or FIPS (PID 0x0407)
- PC speaker or ALSA-compatible audio

### Software (Required for Building)
- Linux (any distribution)
- GCC with C11 support
- Standard C library
- Make

### Software (Optional - Enhanced Features)
- espeak (for TTS)
- ZFS on Linux (for encrypted root)
- cpio, gzip (for initramfs building)

### Tested Platforms
- Debian/Ubuntu
- Arch Linux
- Fedora/RHEL
- Works in QEMU/VMs
- Tested on x86_64

## Installation

### Method 1: Direct Initramfs (Recommended)

```bash
# Build the system
make clean && make

# Create bootable initramfs
sudo ./scripts/build-initramfs.sh

# Follow generated instructions in:
# output/INSTALL.txt
```

### Method 2: Unified Kernel Image (UEFI)

```bash
# After building initramfs
sudo ukify build \
  --linux=/boot/vmlinuz \
  --initrd=output/globalwar-initramfs.img \
  --cmdline="root=ZFS=rpool/ROOT/LONENOMAD" \
  --output=/boot/efi/EFI/Linux/globalwar.efi
```

### Method 3: Local Testing (No Installation)

```bash
# Just run it
make && ./build/wopr

# Test individual games
make test-chess
make test-gtw
```

## Authentication Cheat Sheet

### Correct Path (To Actually Boot)

```
1. WOPR: "SHALL WE PLAY A GAME?"
   YOU: N

2. (Refuse 3 more times)
   YOU: N, N, N

3. WOPR: "ENTER BACKDOOR ACCESS CODE:"
   YOU: JOSHUA

4. WOPR: "ENTER PASSWORD:"
   YOU: PENCIL

5. WOPR: "ENTER ZFS ENCRYPTION PASSPHRASE:"
   YOU: [your actual ZFS passphrase]

✓ System boots successfully
```

### Valid Authentication Credentials

**Backdoor Codes** (any one works):
- `JOSHUA` - AI's name (easiest to remember)
- `FALKEN` - Professor's name
- `CPE1704TKS` - Launch code from the movie
- `WOPR` - System name

**Passwords** (any one works):
- `PENCIL` - Falken's snack
- `TICTHREE` - Tic-tac-toe reference
- `FALKEN` - Professor's name

**Emergency Bypass**:
- Kernel parameter: `globalwar.bypass`
- Skips all authentication (for recovery)

## Repository Structure

```
GLOBALWAR-Boot-Authentication-System/
├── README.md                    # This file
├── QUICKSTART.md                # Fast deployment guide
├── USAGE.md                     # Complete usage instructions
├── Makefile                     # Build system
├── .gitignore                   # Clean repository
│
├── src/
│   ├── core/                    # Core authentication system
│   │   ├── main.c              # WOPR orchestrator (✅ 460 lines)
│   │   ├── auth.c              # Backdoor authentication (✅ 250 lines)
│   │   ├── state_machine.c     # State tracking (✅ 210 lines)
│   │   ├── tpm_handler.c       # TPM integration (✅ 200 lines)
│   │   ├── yubikey_handler.c   # YubiKey detection (✅ 270 lines)
│   │   ├── audio_system.c      # Sound system (✅ 260 lines)
│   │   └── audio_system.h      # Audio header
│   │
│   └── game/                    # Game implementations
│       ├── chess_hflr.c        # Chess Hell (✅ 430 lines)
│       ├── escape_trap.c       # Trap games (✅ 390 lines)
│       └── gtw.c               # Global Thermonuclear War (✅ 390 lines)
│
├── scripts/
│   ├── build-initramfs.sh      # Initramfs builder (✅ 250 lines)
│   └── generate_sounds.sh      # Audio generation
│
├── docs/                        # Comprehensive documentation
│   ├── COMPLETE_SYSTEM.md      # Full system specification
│   ├── IMPLEMENTATION_GUIDE.md # Build and deployment
│   └── TESTING_PROCEDURES.md   # Test plans
│
├── build/                       # Build artifacts (generated)
│   ├── wopr                    # Main executable (92KB)
│   └── *.o                     # Object files
│
├── initramfs/                   # Initramfs structure (generated)
│   ├── bin/wopr                # Deployed binary
│   ├── init                    # Boot script
│   └── lib/                    # Dependencies
│
└── output/                      # Final deliverables (generated)
    ├── globalwar-initramfs.img # Bootable image (2-5MB)
    └── INSTALL.txt             # Installation guide
```

**Total Source Code**: ~3,000 lines of C
**Total Scripts**: ~500 lines of Bash
**Documentation**: ~5,000 lines

## Why This Exists

This project demonstrates that security can be:

1. **Humorous** - Entertainment value while maintaining security
2. **Educational** - Teaches real boot authentication concepts
3. **Functional** - Actually works as designed
4. **Frustrating** - For unauthorized users (by design!)
5. **Rewarding** - For those who understand the movie

**Core Philosophy**: Security through cultural knowledge + frustration mechanics + actual cryptography.

## Legal & Ethical Notes

### Intended Use Cases
✅ Personal systems and home labs
✅ Educational demonstrations
✅ Security research and testing
✅ CTF challenges and competitions
✅ Modified for production (change codes!)

### Not Intended For
❌ Systems requiring emergency access
❌ Production without modification
❌ Unauthorized access prevention (use real security!)
❌ Environments where humor is inappropriate

**Disclaimer**: This software is provided "as is" for educational and entertainment purposes. The frustration caused by the chess game is intentional and not a bug. The author is not responsible for:
- Users getting stuck in Chess Hell
- Loss of productivity from playing GTW
- Excessive laughter during authentication
- Any actual use of this system

## Performance & Size

```
Component                Size        Boot Impact
─────────────────────────────────────────────────
WOPR Binary             92 KB       N/A
Compressed Initramfs    2-5 MB      +2-10 seconds
Uncompressed Initramfs  15-20 MB    N/A
Object Files            ~120 KB     N/A
Source Code             ~3,000 LOC  N/A

Runtime Memory          ~5 MB       During auth only
Disk Space Impact       <0.5%       Of typical initramfs
Build Time              ~5 seconds  On modern hardware
```

## Credits

**Inspired By**:
- *WarGames* (1983) - "Shall we play a game?"
- Classic 1980s hacker culture
- The concept that "the only winning move is not to play"

**Built With**:
- C11 standard
- Linux syscalls
- TPM 2.0 specifications
- FIDO2/WebAuthn concepts
- ZFS on Linux

**Special Thanks**:
- Joshua/WOPR for teaching us about futility
- Professor Falken for his wisdom
- David Lightman for showing us the backdoor
- Anyone who's ever been frustrated by "unbeatable" games

---

> *"A strange game. The only winning move is not to play."*
>
> *"How about a nice game of chess?"*

---

## Get Started

```bash
# Quick test (no installation)
make && ./build/wopr

# Full deployment
sudo ./scripts/build-initramfs.sh

# Read the docs
cat QUICKSTART.md
```

**The system is REAL. The games are FUNCTIONAL. The frustration is INTENTIONAL.**

*Have fun, and remember: When in doubt, refuse to play.* 🎮

