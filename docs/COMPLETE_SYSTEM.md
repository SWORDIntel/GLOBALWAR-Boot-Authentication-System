# GLOBALWAR: Complete System Documentation
## The Ultimate WarGames Boot Authentication System

### Table of Contents
1. [System Overview](#system-overview)
2. [Hardware Requirements](#hardware-requirements)
3. [Boot Flow Diagram](#boot-flow-diagram)
4. [Authentication Layers](#authentication-layers)
5. [Game Implementations](#game-implementations)
6. [Escape Routes](#escape-routes)
7. [Build Instructions](#build-instructions)
8. [Testing Guide](#testing-guide)

---

## System Overview

GLOBALWAR is a boot-time authentication system inspired by the 1983 film WarGames. It implements a multi-layered security system that:
- Binds to specific hardware via TPM 2.0
- Requires dual YubiKey authentication
- Presents frustrating games to unauthorized users
- Rewards those who refuse to play with system access
- Implements defense-in-depth with multiple trap layers

### Core Philosophy
"The only winning move is not to play" - but finding this path requires navigating through multiple psychological and technical challenges.

---

## Hardware Requirements

### Mandatory
- **TPM 2.0**: Intel PTT or discrete TPM chip
- **YubiKey**: One FIDO2 (0x0402) and one FIPS (0x0407)
- **UEFI Boot**: With systemd-boot support
- **ZFS**: Encrypted root filesystem

### Optional Enhancements
- Dell ControlVault 3 fingerprint reader
- Smart card reader
- Bluetooth for proximity detection
- Webcam for facial recognition (future)

### Tested Configuration
- Dell laptop with Intel Meteor Lake
- 2x YubiKey (FIDO2 + FIPS models)
- ZFS on Linux 2.3.x
- systemd-boot 257.x

---

## Boot Flow Diagram

```
POWER ON
    ↓
[TPM Check]
    ├─ No/Wrong TPM ──────────────→ [CHEATING CHESS HELL]
    └─ Valid TPM                          ↓
         ↓                          [XYZZY Escape]
    [YubiKey Detection]                   ↓
         ├─ No Key ───────────────→ [ESCAPE TRAP GAMES]
         └─ Key Present                   ├─ Tic-Tac-Toe
              ↓                           ├─ Number Guess
    [Mission Impossible Theme]            ├─ Rock Paper Scissors
              ↓                           └─ [Loop Forever]
    [WOPR Interface]
         ↓
    "SHALL WE PLAY A GAME?"
         ├─ Yes → [GTW Game] → Win → [HONEYPOT]
         └─ No (4+ times required)
              ↓
    [Backdoor Authentication]
         ├─ "CPE1704TKS"
         ├─ "JOSHUA"
         └─ "FALKEN"
              ↓
    [Password Prompt]
         ├─ "PENCIL"
         └─ "TICTHREE"
              ↓
    "THE ONLY WINNING MOVE IS NOT TO PLAY"
              ↓
    [ZFS Passphrase Entry]
              ↓
    [REAL SYSTEM BOOT]
```

---

## Authentication Layers

### Layer 0: Hardware Binding (TPM)
```c
// TPM PCR Measurements
PCR[0-3]: BIOS/UEFI firmware
PCR[4]:   Boot loader code
PCR[5]:   Boot loader config
PCR[7]:   Secure Boot state
PCR[8]:   Kernel command line
PCR[9]:   Kernel image
PCR[10]:  GLOBALWAR state
PCR[11]:  YubiKey serial binding
```

### Layer 1: Physical Token (YubiKey)
- **No YubiKey**: Cheating Chess (impossible to win)
- **FIDO2 Only**: Standard WOPR interface
- **Both Keys**: Full authentication available

### Layer 2: Behavioral (Game Refusal)
Required refusal sequence:
1. Initial "No"
2. "ARE YOU CERTAIN?" → No
3. "97.3% PROBABILITY YOU WOULD ENJOY" → No
4. "SOVIET FIRST STRIKE READY" → No
5. "RESISTANCE PATTERNS MATCH FALKEN" → Backdoor

### Layer 3: Knowledge (Movie References)
Valid backdoor codes:
- `CPE1704TKS` - Launch code from movie
- `JOSHUA` - AI's name
- `FALKEN` - Creator's name
- `PENCIL` - Password hint
- `WOPR` - System name

### Layer 4: Secret (ZFS Passphrase)
Final actual encryption key for ZFS pool

---

## Game Implementations

### 1. Cheating Chess (No YubiKey Path)

#### Escalation Levels
```
Moves 1-5:   SUBTLE
- Extra pawn moves
- Diagonal rooks
- "Accidental" double moves

Moves 6-10:  OBVIOUS
- Spawning queens ("REVIVING QUEEN")
- Pieces defecting
- Capturing through pieces

Moves 11-15: ABSURD
- Board rotation
- Time travel (undo your moves)
- Dimensional merge (20 pieces)

Moves 16-20: QUANTUM
- Schrödinger's checkmate
- Heisenberg uncertainty
- Wave function collapse

Moves 21+:   EXISTENTIAL
- "You're an NPC"
- "Reality is a simulation"
- Recursive game loops
```

#### False Hope Windows
```c
gambits[] = {
    {"Falken Defense", 3 moves},      // Closes quickly
    {"Skynet Gambit", 2 moves},       // Almost impossible
    {"Kobayashi Maru", 1 move},       // Instant close
    {"Strange Game", 5 moves},        // Longest window
    {"System Crash", 1 move}          // Never works
}
```

### 2. Escape Trap Games (Post-XYZZY)

#### Tic-Tac-Toe
- Perfect minimax algorithm
- Pretends to make mistakes
- "Oops, almost let you win\!"
- Always draws or wins

#### Number Guessing
- Reads input while claiming not to
- Fakes wrong guesses for suspense
- Reveals keystroke monitoring

#### Rock Paper Scissors
- Pattern recognition (90% win rate)
- Markov chain prediction
- Claims "luck" when winning
- Best of 100 (exhausting)

### 3. Global Thermonuclear War (If You Play)

#### Secret Winning Strategy
```
Turn 1: Do NOTHING (DEFCON 5)
Turn 2: Send "WOULD YOU LIKE TO PLAY A GAME?"
Turn 3: Limited strike at 07:04
        - 3 command bunkers only
        - SLBMs only (fastest)
Turn 4: Immediate ceasefire offer
Turn 5: Counterforce on silos if refused
Result: <50M casualties = WIN → HONEYPOT
```

---

## Escape Routes

### From Chess Hell
**Attempt**: Type `XYZZY`
**Result**: Escape Trap Games (worse\!)

### From Escape Trap
**Secret**: Type quote backwards: `YALP OT TON SI EVOM GNINNOW YLNO EHT`
**Result**: Joshua kernel panic → ZFS unlock

### From WOPR
**Correct Path**: Refuse 4+ times → Backdoor → Password
**Result**: Legitimate authentication

### Emergency Recovery
**Keys**: F12 + Correct YubiKey during boot
**Result**: Bypass games, straight to ZFS prompt

---

## Build Instructions

### 1. Prerequisites
```bash
# Install required packages
apt-get install -y \
    build-essential \
    libncurses5-dev \
    libtss2-dev \
    libfido2-dev \
    espeak \
    alsa-utils \
    dracut \
    ukify

# For sound generation
apt-get install -y sox libsox-dev
```

### 2. Compile Components
```bash
cd /boot/GLOBALWAR

# Audio system
gcc -o build/audio_system \
    src/core/audio_system.c \
    -lm -lasound

# Chess game
gcc -o build/chess_hflr \
    src/game/chess_hflr.c \
    src/core/audio_system.c \
    -lncurses -lm

# Escape trap
gcc -o build/escape_trap \
    src/game/escape_trap.c \
    src/core/audio_system.c \
    -lncurses -lm

# TPM handler
gcc -o build/tpm_handler \
    src/core/tpm_handler.c \
    -ltss2-esys -ltss2-sys

# Main WOPR
gcc -o build/wopr \
    src/core/main.c \
    src/core/state_machine.c \
    src/core/auth.c \
    -lncurses -lfido2 -ltss2-esys
```

### 3. Generate Sounds
```bash
chmod +x scripts/generate_sounds.sh
./scripts/generate_sounds.sh
```

### 4. Create Initramfs
```bash
# Create initramfs structure
mkdir -p initramfs/{bin,dev,proc,sys,etc,lib,sounds}

# Copy binaries
cp build/* initramfs/bin/
cp /usr/bin/{zpool,zfs,espeak,aplay} initramfs/bin/

# Copy libraries
ldd build/wopr | grep "=>" | awk '{print $3}' | \
    xargs -I {} cp {} initramfs/lib/

# Copy sounds
cp -r sounds/* initramfs/sounds/

# Create init script
cat > initramfs/init << 'EOF'
#\!/bin/sh
export PATH=/bin
mount -t proc proc /proc
mount -t sysfs sys /sys
mount -t devtmpfs dev /dev

# Start GLOBALWAR
/bin/wopr

# If we get here, auth succeeded
zpool import -N rpool
echo -n "Enter ZFS passphrase: "
read -s PASS
echo "$PASS" | zfs load-key rpool/ROOT/LONENOMAD
mount -t zfs rpool/ROOT/LONENOMAD /newroot
exec switch_root /newroot /sbin/init
EOF

chmod +x initramfs/init

# Create initramfs archive
cd initramfs
find . | cpio -o -H newc | zstd -19 > ../globalwar.img
cd ..
```

### 5. Create UKI (Optional)
```bash
ukify build \
    --linux=/boot/vmlinuz \
    --initrd=globalwar.img \
    --cmdline="quiet loglevel=0" \
    --splash=assets/wopr-logo.bmp \
    --output=globalwar.efi

# Install to EFI
cp globalwar.efi /boot/efi/EFI/Linux/
```

### 6. Configure systemd-boot
```bash
cat > /boot/efi/loader/entries/globalwar.conf << EOF
title   GLOBALWAR Defense System
efi     /EFI/Linux/globalwar.efi
EOF
```

---

## Testing Guide

### 1. Test Without Rebooting
```bash
# Test in QEMU
qemu-system-x86_64 \
    -kernel /boot/vmlinuz \
    -initrd globalwar.img \
    -m 2G \
    -nographic \
    -append "console=ttyS0"
```

### 2. Component Tests
```bash
# Test audio
./build/audio_system test

# Test chess (warning: frustrating)
./build/chess_hflr

# Test escape trap
./build/escape_trap

# Test TPM binding (requires TPM)
sudo ./build/tpm_handler verify
```

### 3. Security Tests
```bash
# Verify no YubiKey = chess
# Remove YubiKey and test

# Verify wrong TPM = chess
# Test on different hardware

# Verify refusal count
# Must refuse exactly 4+ times

# Verify escape routes
# XYZZY → Trap
# Backwards quote → Real escape
```

---

## Secrets and Easter Eggs

### Hidden Commands
- `HELP` - Shows fake help (misleading)
- `JOSHUA` - "I AM JOSHUA" response
- `DAVID` - "SCHOOL IS BORING TODAY?"
- `MCKITTRICK` - "GENERAL BERINGER DOES NOT TRUST ME"

### Audio Easter Eggs
- Hold ESC during MI theme: Plays backwards
- Type "NORAD" repeatedly: Air raid siren
- Win impossible chess: Universe segfaults

### Debug Mode
```bash
# Create debug flag file
touch /boot/efi/.globalwar_debug

# Enables:
# - Verbose logging
# - Shows correct paths
# - Reduces refusal count to 2
# - Shows TPM PCR values
```

---

## Troubleshooting

### "Stuck in Chess Hell"
- Ensure YubiKey is inserted before boot
- Check TPM is enabled in BIOS
- Verify PCR values match expected

### "WOPR Won't Accept Password"
- Must be exact: "PENCIL" not "pencil"
- No trailing spaces
- US keyboard layout assumed

### "Can't Escape Trap Games"
- Quote must be EXACTLY backwards
- Include "THE" at beginning
- All caps, spaces included

### "ZFS Won't Unlock"
- Verify pool name: rpool/ROOT/LONENOMAD
- Check encryption is enabled
- Ensure key format matches

---

## Legal and Ethical Notes

This system is designed for:
- Educational purposes
- Personal use on your own hardware
- Security research and testing

Do NOT use for:
- Unauthorized access prevention
- Production systems without testing
- Systems where users need emergency access

Remember: While frustrating games are funny in concept, real security should be balanced with usability and emergency recovery options.

---

## Credits

Inspired by WarGames (1983)
- "SHALL WE PLAY A GAME?"
- "THE ONLY WINNING MOVE IS NOT TO PLAY"

Built with:
- ZFS on Linux
- systemd-boot
- TPM 2.0 specifications
- YubiKey FIDO2/U2F

Special thanks to Joshua/WOPR for teaching us about futility.

---

*"A strange game. The only winning move is not to play."*
EOFSYS < /dev/null
