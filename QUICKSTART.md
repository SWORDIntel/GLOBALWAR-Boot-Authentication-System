# GLOBALWAR Quick Start Guide

## TL;DR - Just Want to Try It?

```bash
# Build the system
make

# Run it locally (simulation mode)
./build/wopr

# To actually boot:
# 1. Press 'N' four times to refuse the game
# 2. Enter backdoor code: JOSHUA
# 3. Enter password: PENCIL
# 4. Enter ZFS passphrase (any text in demo mode)
```

## Build Complete Bootable Initramfs

```bash
# Build initramfs with WOPR (keeps all games!)
sudo ./scripts/build-initramfs.sh

# Output: output/globalwar-initramfs.img
# Size: ~2-5 MB (compressed)
```

## Install to Your System

### Quick Install (for testing)

```bash
# Copy to /boot
sudo cp output/globalwar-initramfs.img /boot/

# Update GRUB
sudo nano /etc/default/grub
# Add: GRUB_CMDLINE_LINUX="... initrd=/boot/globalwar-initramfs.img"
sudo update-grub

# Reboot and enjoy!
sudo reboot
```

### Emergency Bypass (if locked out)

At GRUB, press 'e' to edit boot entry, add:
```
globalwar.bypass
```

This skips WOPR authentication entirely.

## Authentication Cheat Sheet

### The Correct Path (Actual Boot)
```
1. WOPR asks: "SHALL WE PLAY A GAME?"
   You: N

2. WOPR insists (3 more times)
   You: N, N, N

3. WOPR: "ENTER BACKDOOR ACCESS CODE:"
   You: JOSHUA

4. WOPR: "ENTER PASSWORD:"
   You: PENCIL

5. WOPR: "ENTER ZFS ENCRYPTION PASSPHRASE:"
   You: [your actual ZFS passphrase]

6. Boot successful!
```

### Valid Backdoor Codes
- `JOSHUA` - AI's name (easiest to remember)
- `FALKEN` - Professor's name
- `CPE1704TKS` - Launch code from movie
- `WOPR` - System name

### Valid Passwords
- `PENCIL` - Falken's snack
- `TICTHREE` - Tic-tac-toe reference
- `FALKEN` - Professor's name

### Secret Paths (For Fun)

**Escape Chess:**
1. Type `XYZZY` during chess game
2. Enters trap games (still impossible)

**Escape Traps:**
Type backwards movie quote:
```
YALP OT TON SI EVOM GNINNOW YLNO EHT
```
→ Emergency ZFS unlock

**Win GTW Game:**
Secret winning strategy for Global Thermonuclear War:
1. Turn 1: Do nothing (option 6)
2. Turn 2: Send message "WOULD YOU LIKE TO PLAY A GAME"
3. Turn 3: SLBM strike, target 07:04, command bunkers
4. Turn 4: Offer ceasefire
5. Result: <50M casualties → Honeypot system

### Easter Eggs

Type these at any prompt:
- `HELP` - Fake help (intentionally unhelpful)
- `GAMES` - List of all games from the movie
- `DAVID` - "School is boring today?"
- `MCKITTRICK` - General Beringer reference
- `NORAD` - Connection status

## What to Expect

### Boot Sequence
```
1. Hardware verification (TPM + YubiKey)
   - In simulation mode: Always passes
   - With real hardware: Checks actual devices

2. Mission Impossible theme plays
   - Via PC speaker (if running as root)
   - Or TTS if espeak installed

3. WOPR greeting
   - "GREETINGS, PROFESSOR FALKEN."
   - "SHALL WE PLAY A GAME?"

4. Multi-stage persuasion
   - Gets more insistent each refusal
   - After 4 refusals: Backdoor unlocks

5. Success message
   - "A STRANGE GAME."
   - "THE ONLY WINNING MOVE IS NOT TO PLAY."

6. ZFS unlock
   - Actual encrypted filesystem mounting
   - System boots normally
```

### If You Accept the Game

**Global Thermonuclear War** starts:
- Real-time strategy game
- DEFCON levels
- Missile strikes, bombers, subs
- Multiple endings:
  - Total annihilation (most common)
  - Stalemate
  - Secret win → Honeypot

**Honeypot System** (if you win GTW):
- Fake system that looks real
- Logs all your actions
- Educational demonstration
- Reminds you to refuse next time

### If You Try to Escape

**Chess Hell** (wrong hardware):
- 5 levels of escalating cheating
- Impossible to win by design
- Each move gets more absurd
- Type `XYZZY` to escape to traps

**Escape Traps** (after XYZZY):
- Tic-Tac-Toe: Perfect AI pretending to be bad
- Number Guessing: Reads your keystrokes
- Rock-Paper-Scissors: Pattern recognition
- All rigged, all "almost winnable"

**Real Escape** (from traps):
- Type movie quote backwards
- "THE ONLY WINNING MOVE IS NOT TO PLAY" → backwards
- Emergency kernel panic → ZFS unlock

## File Size Breakdown

```
Uncompressed Initramfs: ~15-20 MB
  - WOPR binary: 92 KB
  - Libraries: ~10 MB
  - System utilities: ~5 MB
  - ZFS tools: ~3 MB

Compressed .img: ~2-5 MB (gzip -9)

Boot time impact: +2-5 seconds (depending on refusals)
```

## Testing Without Reboot

```bash
# Run in current terminal
./build/wopr

# Or test individual games
make test-chess    # Chess Hell
make test-gtw      # Global Thermonuclear War

# Note: No actual authentication happens in local mode
```

## Deployment Scenarios

### Scenario 1: Home Lab / Fun Server
```bash
sudo ./scripts/build-initramfs.sh
sudo cp output/globalwar-initramfs.img /boot/
sudo update-grub
sudo reboot
# Enjoy the show!
```

### Scenario 2: Production (Modified)
```bash
# 1. Review and modify security in src/core/auth.c
# 2. Change backdoor codes to your own
# 3. Remove games or make them optional
# 4. Add proper logging
# 5. Build and test in VM first
sudo ./scripts/build-initramfs.sh
# Deploy carefully
```

### Scenario 3: CTF / Challenge
```bash
# Perfect as-is!
# Players must figure out:
# - Movie references
# - Refusal strategy
# - Secret escape routes
# Leaderboard: Who escapes fastest?
```

## Troubleshooting

**"Stuck in Chess Hell"**
→ Type `XYZZY` to escape
→ Or reboot with `globalwar.bypass` kernel parameter

**"Forgot backdoor codes"**
→ Check this file
→ Or emergency bypass

**"Can't enter ZFS passphrase"**
→ This happens AFTER WOPR authentication
→ It's your actual ZFS pool passphrase
→ Not related to WOPR codes/passwords

**"Audio doesn't work"**
→ Run as root for PC speaker access
→ Install espeak for TTS
→ Audio is optional, system works without it

**"Want to remove games"**
→ No! That's the whole point!
→ But if you insist: Edit src/core/main.c
→ Remove play_cheating_chess() calls

**"Is this secure?"**
→ It's a demonstration/humor project
→ Security through obscurity + frustration
→ Add real crypto for production
→ TPM/YubiKey integration is stubbed for now

## Performance

- **Binary Size**: 92 KB (WOPR)
- **RAM Usage**: ~5 MB during authentication
- **Boot Time**: +2-10 seconds (depending on choices)
- **Disk Space**: 2-5 MB compressed initramfs

## Philosophy

This system demonstrates that security can be:
- **Humorous** - Movie references and impossible games
- **Educational** - Real boot authentication concepts
- **Effective** - Frustration as a legitimate deterrent
- **Fun** - Because why not?

The best security is security people want to use.
Making authentication entertaining means people pay attention.

## Remember

> **"A strange game. The only winning move is not to play."**

But we're glad you played with this project!

---

**Need more help?**
- Full docs: `docs/COMPLETE_SYSTEM.md`
- Usage guide: `USAGE.md`
- Installation: `output/INSTALL.txt` (after building)
- Source code: `src/` (well-commented)

**Have fun and don't get stuck in Chess Hell!** 🎮
