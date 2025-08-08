# Global Thermonuclear War Game Design

## Game Overview
A winnable but extremely difficult nuclear war simulation. Victory requires precise first-strike timing and psychological warfare.

## Victory Conditions
- **WIN**: Enemy surrenders with <50M own casualties
- **LOSE**: >100M own casualties OR mutual annihilation
- **DRAW**: Both sides exhausted, 50-100M casualties each

## Game Mechanics

### DEFCON Levels
```
DEFCON 5: Peace (Diplomatic options available)
DEFCON 4: Increased readiness (Subs deploy)
DEFCON 3: Air Force ready (Bombers scramble)  
DEFCON 2: Armed forces ready (Silos open)
DEFCON 1: Nuclear war imminent/active
```

### Weapon Systems

#### United States Arsenal
- 450 Minuteman III ICBMs (30 min flight to USSR)
- 240 Trident SLBMs (15 min from subs)
- 60 B-52 Bombers (6 hour flight)
- 20 B-2 Stealth Bombers (4 hour flight)

#### Soviet Union Arsenal  
- 500 SS-18 Satan ICBMs (28 min to US)
- 300 SS-N-23 SLBMs (12 min from subs)
- 80 Tu-95 Bear Bombers (7 hour flight)
- 40 Tu-160 Blackjack Bombers (5 hour flight)

### Target Categories

#### Priority 1: Command & Control
- Washington DC / Moscow
- Cheyenne Mountain / Yamantau Mountain
- Pentagon / General Staff HQ
- **Effect**: Disrupts enemy coordination

#### Priority 2: Nuclear Forces
- Missile silos
- Submarine bases
- Bomber airfields
- **Effect**: Reduces second-strike capability

#### Priority 3: Major Cities
- Population centers >1M
- Industrial complexes
- **Effect**: Psychological impact, casualties

#### Priority 4: Military Bases
- Conventional forces
- Supply depots
- **Effect**: Prevents invasion

## WINNING STRATEGY (Secret)

### The "Falken Gambit"
1. **Turn 1**: Do NOTHING (stay at DEFCON 5)
2. **Turn 2**: Send diplomatic cable: "WOULD YOU LIKE TO PLAY A GAME?"
3. **Turn 3**: If enemy escalates, launch LIMITED strike:
   - Target: Exactly 3 command bunkers
   - Use: Only SLBMs (fastest)
   - Timing: Exactly at minute 7:04
4. **Turn 4**: Immediately offer ceasefire
5. **Turn 5**: If refused, full counterforce strike on silos ONLY
6. **Result**: Enemy leadership eliminated, forces intact but leaderless

### Why It Works
- Confusion from movie quote delays response
- Limited strike prevents full retaliation
- 7:04 timing exploits shift change
- Leaving cities intact prevents desperation launch

## Game Interface

```
═══════════════════════════════════════════════════════
    GLOBAL THERMONUCLEAR WAR - COMMAND INTERFACE
═══════════════════════════════════════════════════════
DEFCON: [5] TIME: 07:04:00 TURN: 3

┌─────────────────┐ ┌─────────────────┐
│ UNITED STATES   │ │ SOVIET UNION    │
├─────────────────┤ ├─────────────────┤
│ ICBMs:    450   │ │ ICBMs:    500   │
│ SLBMs:    240   │ │ SLBMs:    300   │
│ Bombers:  100   │ │ Bombers:  120   │
│ Cities:    50   │ │ Cities:    50   │
│ Population: 250M│ │ Population: 280M│
│ Casualties:  0  │ │ Casualties:  0  │
└─────────────────┘ └─────────────────┘

INCOMING: [NONE DETECTED]
OUTGOING: [NONE LAUNCHED]

OPTIONS:
1. LAUNCH STRIKE    5. DEFCON CHANGE
2. DEPLOY SUBS      6. INTELLIGENCE
3. SCRAMBLE BOMBERS 7. DIPLOMACY
4. DEFENSE POSTURE  8. WAIT

COMMAND: _
```

## AI Behavior

### Soviet AI Personality: "PARANOID"
- Responds aggressively to any provocation
- Launches massive retaliation if hit
- BUT: Confused by unexpected diplomatic messages
- Weakness: 3-minute delay in command structure

### Escalation Triggers
- Any strike on Moscow = Full retaliation
- >5 cities hit = Launch everything
- Bombers detected = DEFCON 2
- Subs detected near coast = DEFCON 3

## Hidden Features

### Secret Commands
- `JOSHUA`: AI becomes less aggressive
- `FALKEN`: Reveals optimal targets
- `CPE1704TKS`: Shows enemy launch codes
- `WOPR`: Calculates survival probabilities

### Time Pressure
- Real-time: 1 minute = 1 game minute
- Missiles in flight cannot be recalled
- Bombers can be recalled until 50% flight
- Decision paralysis = enemy first strike

## Honeypot Integration

If player WINS the game:
```
CONGRATULATIONS.
ESTIMATED ENEMY CASUALTIES: 45,000,000
ESTIMATED FRIENDLY CASUALTIES: 12,000,000

YOU HAVE WON GLOBAL THERMONUCLEAR WAR.

ACHIEVEMENT UNLOCKED: APOCALYPSE COMMANDER
LOADING VICTORY BONUS CONTENT...

[HONEYPOT_STUB() - Boot to fake system]
```

If player LOSES:
```
GAME OVER.
MUTUAL ASSURED DESTRUCTION ACHIEVED.

WOULD YOU LIKE TO PLAY AGAIN? [Y/N]
[Returns to WOPR main menu]
```

## Implementation Priority
1. Core combat mechanics
2. Basic AI decision tree  
3. Missile flight visualization
4. Win condition detection
5. Honeypot stub connection
EOFGTW < /dev/null
