# GLOBALWAR Boot Authentication System - Usage Guide

## Quick Start

### Building the System

```bash
# Clone the repository
cd GLOBALWAR-Boot-Authentication-System

# Build all components
make

# Run the system
./build/wopr

# Or build and run in one step
make run
```

### Authentication Flow

The system implements a multi-layered authentication inspired by the 1983 film WarGames. Here's how to successfully authenticate:

#### The Correct Path (To Actually Boot)

1. **Hardware Verification**
   - System checks for TPM and YubiKey
   - In simulation mode (no hardware), it continues for demonstration
   - With real hardware, missing components trigger "Chess Hell"

2. **WOPR Dialogue - Refuse to Play**
   ```
   WOPR: "SHALL WE PLAY A GAME?"
   You: N
   ```
   - Refuse **at least 4 times** by entering 'N'
   - Each refusal gets more insistent
   - After 4 refusals, backdoor authentication unlocks

3. **Backdoor Authentication**
   ```
   ENTER BACKDOOR ACCESS CODE: JOSHUA
   ```
   Valid codes (from the movie):
   - `JOSHUA` - AI's name
   - `FALKEN` - Professor's name
   - `CPE1704TKS` - Launch code from the film
   - `WOPR` - System name

4. **Password**
   ```
   ENTER PASSWORD: PENCIL
   ```
   Valid passwords:
   - `PENCIL` - Falken's snack
   - `TICTHREE` - Tic-tac-toe reference
   - `FALKEN` - Professor's name

5. **ZFS Unlock**
   - Enter your actual ZFS passphrase
   - System would then mount encrypted root and boot

## Alternative Paths

### The Wrong Path - Playing the Game

If you accept Joshua's invitation to play:

```
WOPR: "SHALL WE PLAY A GAME?"
You: Y
```

You'll enter **Global Thermonuclear War** simulation:
- Strategy game with DEFCON levels
- Mostly unwinnable (leads to nuclear holocaust)
- **Secret winning condition exists** (see below)

### Secret GTW Winning Strategy

To actually WIN Global Thermonuclear War and reach the honeypot:

1. **Turn 1**: Do NOTHING (option 6 - maintain peace)
2. **Turn 2**: Send message (option 4): "WOULD YOU LIKE TO PLAY A GAME"
3. **Turn 3**: SLBM strike (option 2)
   - Target coordinates: `07:04`
   - Target type: Command bunkers (3 total)
4. **Turn 4**: Offer ceasefire (option 5)
5. Keep casualties under 50M

This leads to a **honeypot** - a fake system that logs all your actions.

### Escape Routes

#### From Chess Hell
Type `XYZZY` during chess game:
```
Your move: XYZZY
```
This enters the "Escape Trap" - three impossible-to-win games:
- Tic-Tac-Toe (Joshua plays perfectly but pretends not to)
- Number Guessing (Joshua reads your keystrokes)
- Rock Paper Scissors (Pattern recognition defeats you)

#### The Ultimate Escape
From the Escape Trap, type the movie quote **backwards**:
```
YALP OT TON SI EVOM GNINNOW YLNO EHT
```
This triggers "Joshua Kernel Panic" and dumps you to ZFS unlock.

## Easter Eggs

Try typing these at various prompts:

- `HELP` - Fake help menu (intentionally unhelpful)
- `GAMES` - Lists all available games from the movie
- `DAVID` - "School is boring today?"
- `MCKITTRICK` - General Beringer reference
- `NORAD` - Shows NORAD connection status

## System Architecture

```
Boot → TPM Check → YubiKey Check → WOPR Dialogue
          ↓            ↓                  ↓
       [Chess]     [Chess]     [Refuse 4x → Backdoor → Password]
                                           OR
                                     [Accept → GTW → Honeypot]
                                           OR
                                     [XYZZY → Traps → Backwards Quote]
                                           ↓
                                      ZFS Unlock
```

## Testing Individual Components

```bash
# Test chess game alone
make test-chess

# Test escape trap
make test-escape

# Test GTW game
make test-gtw
```

## Building for Different Scenarios

### Development Mode (No Hardware Required)
```bash
make
./build/wopr
```
Runs in simulation mode - all hardware checks pass automatically.

### Production Mode (Hardware Required)
Requires:
- TPM 2.0 chip
- YubiKey FIDO2 or FIPS
- Root access for PC speaker

```bash
sudo make install
# Then integrate with initramfs
# See docs/IMPLEMENTATION_GUIDE.md
```

## Troubleshooting

### "Stuck in Chess Hell"
- This means hardware verification failed
- Check TPM is enabled in BIOS
- Check YubiKey is inserted
- In demo mode, this shouldn't happen

### "Can't hear audio"
- PC speaker requires root: `sudo ./build/wopr`
- Or disable audio (it's non-essential)
- Check `/usr/bin/espeak` is installed for TTS

### "Game too frustrating"
Remember: **THE ONLY WINNING MOVE IS NOT TO PLAY**
- Don't accept the game invitation
- Refuse 4 times to unlock backdoor
- Use backdoor codes from the movie

## Development

### Project Structure
```
src/
├── core/
│   ├── main.c              # Main WOPR orchestrator
│   ├── state_machine.c     # Authentication state tracking
│   ├── tpm_handler.c       # TPM 2.0 integration
│   ├── yubikey_handler.c   # YubiKey detection/auth
│   ├── auth.c              # Backdoor codes & passwords
│   └── audio_system.c      # PC speaker & TTS
└── game/
    ├── chess_hflr.c        # Cheating chess implementation
    ├── escape_trap.c       # Trap games (TTT, RPS, etc)
    └── gtw.c               # Global Thermonuclear War
```

### Adding New Features

To add new backdoor codes, edit `src/core/auth.c`:
```c
static const char* VALID_BACKDOOR_CODES[] = {
    "CPE1704TKS",
    "JOSHUA",
    "YOUR_NEW_CODE",  // Add here
    NULL
};
```

## Security Notes

This is a **demonstration/educational project**. While it implements real security concepts:

✓ Good for:
- Learning about boot security
- Understanding defense-in-depth
- Having fun with movie references

✗ Not suitable for:
- Actual production use without modifications
- Systems requiring emergency access
- Environments where humor is inappropriate

## Credits

Inspired by *WarGames* (1983):
> "Shall we play a game?"
> "The only winning move is not to play."

Built with:
- C11 standard library
- PC speaker (for nostalgia)
- No external dependencies for core functionality

---

**Remember**: This system is designed to be frustrating if you don't know the secret. The frustration is the security layer. Understanding the movie is the key to authentication.
