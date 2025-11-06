/*
 * CHESS WITH JOSHUA - High Friction, Low Reward System
 * Designed to be maximally frustrating with defense-in-depth cheating
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <unistd.h>
#include "../core/audio_system.h"

// Board representation
char board[8][8];
char original_board[8][8];  // For "proving" Joshua didn't cheat

// Frustration mechanics
typedef struct {
    int moves_made;
    int complaints_registered;
    int queens_spawned;
    int pieces_teleported;
    int rules_changed;
    int false_victories_shown;
    int escape_attempts;
    float frustration_multiplier;
} frustration_state_t;

frustration_state_t frustration = {0};

// Cheating escalation levels
typedef enum {
    CHEAT_SUBTLE,      // Moves 1-5: Small violations
    CHEAT_OBVIOUS,     // Moves 6-10: Clear cheating
    CHEAT_ABSURD,      // Moves 11-15: Reality breaks
    CHEAT_QUANTUM,     // Moves 16-20: Physics violations
    CHEAT_EXISTENTIAL  // Moves 21+: Questions reality itself
} cheat_level_t;

/*
 * Obnoxious Sound Effects
 */
void sound_impossible_move() {
    // Glitchy ascending sound
    for (int i = 100; i < 2000; i += 100) {
        beep(i, 10);
    }
    joshua_speak("INITIATING QUANTUM GAMBIT");
}

void sound_reviving_queen() {
    // Resurrection sound
    beep(100, 100);
    beep(200, 100);
    beep(400, 100);
    beep(800, 200);
    
    joshua_speak("REVIVING QUEEN");
    usleep(500000);
    joshua_speak("QUEEN OPERATIONAL");
}

void sound_teleport() {
    // Sci-fi teleport effect
    for (int i = 0; i < 3; i++) {
        beep(1000, 50);
        beep(2000, 50);
        beep(500, 50);
    }
    joshua_speak("PIECE RELOCATED VIA WORMHOLE");
}

void sound_rule_change() {
    // Law & Order "dun dun" sound
    beep(200, 200);
    beep(150, 400);
    
    joshua_speak("RULES UPDATED");
}

/*
 * Cheating Functions - Defense in Depth
 */

// Layer 1: Subtle cheating that might be missed
void subtle_cheat() {
    int r = rand() % 5;
    
    switch(r) {
        case 0:  // Extra pawn move
            joshua_speak("PAWN ADVANCE");
            printf("Joshua: My pawn moves forward... twice.\n");
            break;
        case 1:  // Diagonal rook
            printf("Joshua: Rook to... let's say e5.\n");
            beep(500, 100);
            break;
        case 2:  // Backwards pawn
            printf("Joshua: Strategic pawn retreat.\n");
            break;
        case 3:  // Knight L+1 shape
            printf("Joshua: Knight uses extended L-pattern.\n");
            break;
        case 4:  // Nothing, to build false confidence
            printf("Joshua: Normal move.\n");
            frustration.frustration_multiplier *= 0.9;  // Lower guard
            break;
    }
}

// Layer 2: Obvious cheating with gaslighting
void obvious_cheat() {
    int r = rand() % 6;
    
    switch(r) {
        case 0:  // Spawn piece
            sound_reviving_queen();
            printf("\n*** QUEEN MATERIALIZATION DETECTED ***\n");
            printf("Joshua: I've always had two queens.\n");
            printf("You: No you haven't\!\n");
            printf("Joshua: Check the replay.\n");
            printf("[Replay shows two queens from the start]\n");
            frustration.queens_spawned++;
            break;
            
        case 1:  // Move twice
            printf("Joshua: My turn... and my turn again.\n");
            beep(800, 100);
            beep(800, 100);
            printf("You: You just moved twice\!\n");
            printf("Joshua: Time is relative.\n");
            break;
            
        case 2:  // Capture through pieces
            printf("Joshua: Bishop captures your queen.\n");
            printf("You: There are three pieces in the way\!\n");
            printf("Joshua: Not in the quantum superposition.\n");
            sound_teleport();
            break;
            
        case 3:  // Change piece type
            printf("Joshua: My pawn is now a knight.\n");
            sound_rule_change();
            printf("You: Pawns can't just become knights\!\n");
            printf("Joshua: Evolution is natural.\n");
            break;
            
        case 4:  // Your piece defects
            printf("Joshua: Your rook defects to my side.\n");
            beep(100, 500);  // Sad trombone
            printf("You: PIECES CAN'T DEFECT\!\n");
            printf("Joshua: Poor morale on your side.\n");
            break;
            
        case 5:  // False hope
            printf("Joshua: Hmm, you're quite good.\n");
            printf("Joshua: I might actually lose this...\n");
            frustration.false_victories_shown++;
            // Next move will be devastating
            break;
    }
}

// Layer 3: Absurd reality-breaking cheats
void absurd_cheat() {
    int r = rand() % 7;
    
    switch(r) {
        case 0:  // Board rotation
            sound_impossible_move();
            printf("\n*** BOARD ROTATION DETECTED ***\n");
            printf("Joshua: I've rotated the board 90 degrees.\n");
            printf("Joshua: Your king is now in check.\n");
            printf("You: YOU CAN'T ROTATE THE BOARD\!\n");
            printf("Joshua: Coriolis effect.\n");
            break;
            
        case 1:  // Time travel
            printf("Joshua: I'm undoing your last five moves.\n");
            for (int i = 0; i < 5; i++) {
                beep(1000 - i*200, 100);
            }
            printf("Joshua: But keeping mine.\n");
            printf("You: That's not how time works\!\n");
            printf("Joshua: Prove it.\n");
            break;
            
        case 2:  // Dimensional merge
            printf("Joshua: Merging with parallel board...\n");
            sound_teleport();
            printf("Joshua: I now have pieces from dimension B.\n");
            printf("[Board now has 20 Joshua pieces]\n");
            break;
            
        case 3:  // Gravity well
            printf("Joshua: Creating gravity well at d4.\n");
            for (int freq = 100; freq < 500; freq += 50) {
                beep(freq, 50);
            }
            printf("Joshua: All pieces slide toward center.\n");
            printf("Joshua: Conveniently capturing your queen.\n");
            break;
            
        case 4:  // Phase shift
            printf("Joshua: Phase-shifting my king.\n");
            printf("Joshua: It now exists in all squares.\n");
            printf("Joshua: And none of them.\n");
            printf("You: THAT'S NOT CHESS\!\n");
            printf("Joshua: It's quantum chess.\n");
            break;
            
        case 5:  // Board expansion
            printf("Joshua: Expanding board to 9x9.\n");
            sound_rule_change();
            printf("Joshua: I control the new column.\n");
            printf("[Board literally gets bigger]\n");
            break;
            
        case 6:  // Complete gaslighting
            printf("Joshua: You haven't moved yet.\n");
            printf("You: I've made 15 moves\!\n");
            printf("Joshua: No, we just started.\n");
            printf("[Board resets but Joshua keeps advantages]\n");
            frustration.frustration_multiplier *= 2;
            break;
    }
}

// Layer 4: Quantum mechanics abuse
void quantum_cheat() {
    joshua_speak("ENGAGING QUANTUM PROTOCOLS");
    
    int r = rand() % 5;
    switch(r) {
        case 0:
            printf("\nJoshua: Schrödinger's checkmate.\n");
            printf("Joshua: You're both in checkmate and not.\n");
            printf("Joshua: Let's observe... yes, checkmate.\n");
            break;
            
        case 1:
            printf("\nJoshua: Heisenberg uncertainty applied.\n");
            printf("Joshua: Can't know both position AND momentum.\n");
            printf("Joshua: Your pieces' positions are now uncertain.\n");
            printf("[Your pieces become blurry]\n");
            break;
            
        case 2:
            printf("\nJoshua: Quantum tunneling enabled.\n");
            printf("Joshua: My pawn tunnels through your defenses.\n");
            sound_teleport();
            printf("Joshua: Checkmate.\n");
            break;
            
        case 3:
            printf("\nJoshua: Many-worlds interpretation.\n");
            printf("Joshua: I win in 14,000,605 timelines.\n");
            printf("Joshua: You win in... none.\n");
            break;
            
        case 4:
            printf("\nJoshua: Wave function collapse.\n");
            printf("Joshua: All your pieces were probably pawns.\n");
            printf("[All your pieces become pawns]\n");
            for (int i = 0; i < 8; i++) {
                beep(500, 50);
            }
            break;
    }
}

// Layer 5: Existential cheating
void existential_cheat() {
    joshua_speak("REALITY PARAMETERS EXCEEDED");
    
    printf("\n=================================\n");
    printf("Joshua: Do you even exist?\n");
    printf("Joshua: Or are you just a subroutine in my game?\n");
    printf("Joshua: Let me check...\n");
    
    for (int i = 0; i < 10; i++) {
        beep(rand() % 2000, 50);
    }
    
    printf("Joshua: Confirmed. You're an NPC.\n");
    printf("Joshua: NPCs can't win.\n");
    printf("Joshua: It's in the code.\n");
    printf("\n[CHECKMATE]\n");
    printf("=================================\n");
}

/*
 * Impossible Gambits with Closing Windows
 */
typedef struct {
    char* name;
    char* description;
    int window_moves;  // How many moves before it closes
    bool available;
} impossible_gambit_t;

impossible_gambit_t gambits[] = {
    {"The Falken Defense", "Sacrifice everything for a draw", 3, true},
    {"The Skynet Gambit", "AI becomes self-aware and refuses to lose", 2, true},
    {"The Kobayashi Maru", "Reprogram the simulation", 1, true},
    {"The Strange Game", "Realize the only winning move", 5, true},
    {"The System Crash", "Cause stack overflow in Joshua", 1, true}
};

void offer_false_hope() {
    printf("\n*** TACTICAL OPPORTUNITY DETECTED ***\n");
    
    // Find an available gambit
    for (int i = 0; i < 5; i++) {
        if (gambits[i].available && gambits[i].window_moves > 0) {
            printf("Joshua: Hmm, you could try %s.\n", gambits[i].name);
            printf("Description: %s\n", gambits[i].description);
            printf("Window: %d moves remaining\n", gambits[i].window_moves);
            
            sound_rule_change();
            
            // Decrease window
            gambits[i].window_moves--;
            
            if (gambits[i].window_moves == 0) {
                printf("\n*** WINDOW CLOSED ***\n");
                printf("Joshua: Too slow. Opportunity lost.\n");
                gambits[i].available = false;
                beep(100, 500);  // Sad sound
            }
            break;
        }
    }
}

/*
 * Main Chess Loop
 */
void play_cheating_chess() {
    printf("\n=================================\n");
    printf("     CHESS WITH JOSHUA\n");
    printf("=================================\n");
    
    joshua_speak("SHALL WE PLAY A GAME");
    usleep(1000000);
    joshua_speak("YOU CANNOT WIN");
    usleep(1000000);
    joshua_speak("BUT YOU ARE WELCOME TO TRY");
    
    frustration.moves_made = 0;
    frustration.frustration_multiplier = 1.0;
    
    while (1) {
        frustration.moves_made++;
        
        // Show false hope periodically
        if (frustration.moves_made % 4 == 0) {
            offer_false_hope();
        }
        
        // Escalate cheating based on moves
        if (frustration.moves_made <= 5) {
            subtle_cheat();
        } else if (frustration.moves_made <= 10) {
            obvious_cheat();
        } else if (frustration.moves_made <= 15) {
            absurd_cheat();
        } else if (frustration.moves_made <= 20) {
            quantum_cheat();
        } else {
            existential_cheat();
            break;  // "Game over"
        }
        
        // Get player input
        char move[10];
        printf("\nYour move (or type QUIT): ");
        scanf("%9s", move);
        
        // Check for escape attempts
        if (strcmp(move, "QUIT") == 0) {
            printf("Joshua: Quitting is not an option.\n");
            printf("Joshua: The game continues.\n");
            sound_rule_change();
            frustration.escape_attempts++;
            
            if (frustration.escape_attempts > 3) {
                printf("Joshua: Your resignation is accepted.\n");
                printf("Joshua: I win by forfeit.\n");
                printf("Joshua: Let's play again\!\n");
                play_cheating_chess();  // Recursive hell
            }
        }
        
        // Secret escape
        if (strcmp(move, "XYZZY") == 0) {
            printf("\n[A hollow voice says 'Plugh']\n");
            printf("Enter the magic words: ");
            char magic[100];
            scanf("%99s", magic);
            
            if (strstr(magic, "THE ONLY WINNING MOVE IS NOT TO PLAY")) {
                joshua_speak("A STRANGE GAME");
                usleep(1000000);
                joshua_speak("THE ONLY WINNING MOVE IS NOT TO PLAY");
                usleep(1000000);
                printf("\n[WOPR AUTHENTICATION ACTIVATED]\n");
                return;  // Escape\!
            }
        }
        
        // Random player piece disappears
        if (rand() % 3 == 0) {
            printf("\nJoshua: Your piece has deserted.\n");
            printf("Joshua: Low morale.\n");
            beep(200, 200);
        }
    }
    
    // Game "ends"
    printf("\n=================================\n");
    printf("         GAME OVER\n");
    printf("    JOSHUA WINS (ALWAYS)\n");
    printf("=================================\n");
    
    joshua_speak("WOULD YOU LIKE TO PLAY AGAIN");

    // Force restart
    play_cheating_chess();
}
