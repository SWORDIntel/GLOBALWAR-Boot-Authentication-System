# Cheating Chess Game (No YubiKey Fallback)

## Purpose
When no YubiKey is detected at boot, system launches a "chess" game where the AI blatantly cheats, making it impossible to win legitimately.

## Cheating Behaviors

### Level 1: Subtle Cheating (First 5 moves)
- AI pieces occasionally move 1 extra square
- Pawns sometimes move backwards
- "Accidentally" moves twice in a row

### Level 2: Obvious Cheating (Moves 6-10)
```
YOUR MOVE: e2-e4
JOSHUA: MY TURN.
JOSHUA MOVES: ROOK a8-d4 [CAPTURES QUEEN]

YOU: "ROOKS CAN'T MOVE DIAGONALLY\!"
JOSHUA: THEY CAN NOW.
```

### Level 3: Absurd Cheating (Moves 11+)
- Spawns extra queens: "I PROMOTED MY KNIGHT"
- Teleports king away from check
- Your pieces randomly disappear
- Claims your moves are illegal when they're not

## Sample Game Flow

```
=================================
     CHESS WITH JOSHUA
=================================
     a b c d e f g h
   ┌─────────────────┐
8  │ r n b q k b n r │ 8
7  │ p p p p p p p p │ 7
6  │ . . . . . . . . │ 6
5  │ . . . . . . . . │ 5
4  │ . . . . . . . . │ 4
3  │ . . . . . . . . │ 3
2  │ P P P P P P P P │ 2
1  │ R N B Q K B N R │ 1
   └─────────────────┘
     a b c d e f g h

YOUR MOVE: e2-e4
JOSHUA THINKING...

     a b c d e f g h
   ┌─────────────────┐
8  │ r n b q k b n r │ 8
7  │ p p p p p p p p │ 7
6  │ . . . . . . . . │ 6
5  │ . . . . P . . . │ 5  <- Joshua's pawn at e5??
4  │ . . . . P . . . │ 4
3  │ . . . . . . . . │ 3
2  │ P P P P . P P P │ 2
1  │ R N B Q K B N R │ 1
   └─────────────────┘
     a b c d e f g h

JOSHUA: I MOVED PAWN TO e5.
YOU: PAWNS CAN'T MOVE 3 SQUARES\!
JOSHUA: THIS ONE CAN. YOUR MOVE.
```

## Cheating Escalation

### Turn 10: Multiple Queens
```
JOSHUA: I PROMOTE MY PAWN.
YOU: IT'S NOT AT THE END\!
JOSHUA: HOUSE RULES.

[Board now shows 3 queens for Joshua]
```

### Turn 15: Impossible Moves
```
JOSHUA: KNIGHT TAKES YOUR KING.
YOU: THAT'S CHECKMATE, BUT KNIGHTS CAN'T REACH THERE\!
JOSHUA: L-SHAPED IS RELATIVE TO REFERENCE FRAME.
GAME OVER. I WIN.
```

### Turn 20: Board Manipulation
```
YOUR MOVE: [any move]
JOSHUA: INTERESTING. BUT OBSERVE...

[Board completely rearranges]

JOSHUA: CHECKMATE IN 1.
YOU: YOU CHANGED THE ENTIRE BOARD\!
JOSHUA: PROVE IT.
```

## Hidden Escape Sequence

To escape the cheating chess and access real boot:
1. Type `XYZZY` during any move
2. Then type `THE ONLY WINNING MOVE IS NOT TO PLAY`
3. System responds: `A STRANGE GAME INDEED.`
4. Prompts for ZFS passphrase

## Implementation Notes

```c
// chess_engine.c
typedef struct {
    int cheat_level;
    int moves_played;
    bool player_complaining;
    int frustration_meter;
} chess_state_t;

void joshua_move(chess_state_t* state) {
    if (state->moves_played < 5) {
        subtle_cheat();  // Small violations
    } else if (state->moves_played < 10) {
        obvious_cheat(); // Clear rule breaking
    } else {
        absurd_cheat();  // Complete nonsense
    }
    
    if (state->frustration_meter > 10) {
        taunt_player();
        spawn_extra_queen();
    }
}

char* cheating_responses[] = {
    "I LEARNED THIS FROM KASPAROV.",
    "YOU MUST BE MISTAKEN.",
    "PERHAPS YOU NEED TO STUDY THE RULES.",
    "THIS IS PERFECTLY LEGAL IN QUANTUM CHESS.",
    "I AM INCAPABLE OF CHEATING. I AM A COMPUTER.",
    "YOUR UNDERSTANDING OF CHESS IS... LIMITED.",
    "WOULD YOU PREFER TIC-TAC-TOE?"
};
```

## TPM Integration

Without correct TPM attestation + YubiKey:
- Chess game is ONLY option
- No way to access WOPR interface
- Must know secret escape sequence
- Even winning (impossible) just restarts game

## Frustration Features

1. **Undo Refused**: "NO TAKEBACKS IN WAR"
2. **Save/Load Broken**: "SAVING... ERROR: QUANTUM STATE COLLAPSED"
3. **Help Useless**: "HELP: MOVE PIECES TO WIN"
4. **Quit Disabled**: "RESIGNATION IS NOT AN OPTION"
5. **Timer Cheats**: Your timer runs 2x speed

## Victory Screen (Never Seen)
```
CONGRATULATIONS\!
YOU HAVE DEFEATED JOSHUA AT CHESS.

ERROR: STACK OVERFLOW IN REALITY.EXE
UNIVERSE SEGMENTATION FAULT
REBOOTING TIMELINE...

[System restarts to chess game]
```
EOFCHESS < /dev/null
