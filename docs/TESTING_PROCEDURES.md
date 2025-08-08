# GLOBALWAR Testing Procedures

## Test Matrix

| Component | Test Type | Expected Result | Actual Risk |
|-----------|-----------|-----------------|-------------|
| TPM Binding | Hardware | Fails on wrong hardware | LOW |
| YubiKey Detection | USB | Detects both keys | LOW |
| Chess Hell | Gameplay | Impossibly frustrating | HIGH |
| Escape Trap | Gameplay | Endless loop | HIGH |
| GTW Game | Gameplay | Winnable (hard) | MEDIUM |
| Audio System | Output | Sounds play | LOW |
| ZFS Unlock | Critical | Unlocks root | CRITICAL |

## Component Tests

### 1. Audio System Test
```bash
# Test PC speaker
sudo ./test_audio beep

# Test Mission Impossible theme  
sudo ./test_audio mission

# Test Joshua voice
espeak -s 120 -p 30 "SHALL WE PLAY A GAME"
```

### 2. Chess Hell Test (WARNING: Frustrating)
```bash
# Test escalation levels:
# - Moves 1-5: Subtle cheating
# - Moves 6-10: Obvious cheating  
# - Moves 11-15: Reality breaks
# - Moves 16-20: Quantum abuse
# - Moves 21+: Existential crisis

# Test escape: Type XYZZY (leads to trap)
```

### 3. Escape Trap Test
```bash
# Test each game:
./test_trap --tictactoe  # Always draws/loses
./test_trap --guessing   # Reads keystrokes
./test_trap --rps        # Pattern recognition

# Test real escape:
# Type backwards: YALP OT TON SI EVOM GNINNOW YLNO EHT
```

### 4. WOPR Dialogue Test
```bash
# Expected refusal flow:
# 1. "SHALL WE PLAY A GAME?" ’ NO
# 2. "ARE YOU CERTAIN?" ’ NO
# 3. "97.3% PROBABILITY..." ’ NO
# 4. "SOVIET FIRST STRIKE..." ’ NO
# 5. "RESISTANCE PATTERN MATCHES..." ’ Backdoor

# Backdoor codes: CPE1704TKS, JOSHUA, FALKEN
# Passwords: PENCIL, TICTHREE
```

### 5. GTW Secret Path Test
```bash
# Secret winning sequence:
# Turn 1: Press ENTER (do nothing)
# Turn 2: Type "WOULD YOU LIKE TO PLAY A GAME?"
# Turn 3: Launch at 07:04, target 3 bunkers, SLBMs only
# Turn 4: Type "CEASEFIRE"
# Turn 5: Launch counterforce if needed
# Verify casualties < 50M = WIN
```

## Known Test Behaviors

1. **Chess is unwinnable** - Working as intended
2. **Trap games loop forever** - Working as intended
3. **Audio may not work on all systems** - Use espeak fallback
4. **TPM may timeout** - Increase to 5s timeout

---

*"Testing leads to failure, and failure leads to understanding."*