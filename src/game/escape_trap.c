/*
 * THE ESCAPE TRAP - "Tic-Tac-Toe Perfect Play"
 * When you escape chess, you get something WORSE
 * A "simple" game that Joshua plays perfectly but pretends to lose
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include "../core/audio_system.h"

typedef struct {
    char board[3][3];
    int games_played;
    int near_wins;
    int mistakes_made;
    int frustration_level;
    bool almost_won[100];  // Track every "almost win"
} tictactoe_state_t;

tictactoe_state_t ttt = {0};

/*
 * The Trap: Joshua plays PERFECTLY but acts like he's making mistakes
 * Shows you're "about to win" then blocks at last second
 * Sometimes lets you get 2 in a row, then "notices" and blocks
 */

void print_board() {
    printf("\n   1   2   3\n");
    for (int i = 0; i < 3; i++) {
        printf("%c  ", 'A' + i);
        for (int j = 0; j < 3; j++) {
            printf("%c", ttt.board[i][j] == 0 ? ' ' : ttt.board[i][j]);
            if (j < 2) printf(" | ");
        }
        printf("\n");
        if (i < 2) printf("  -----------\n");
    }
}

// Perfect minimax but with fake "thinking"
int minimax(int depth, bool is_joshua) {
    // Check win conditions
    // ... [standard minimax implementation]
    
    // But add fake delay to seem "confused"
    if (rand() % 3 == 0 && depth > 2) {
        printf("Joshua: Hmm...\n");
        usleep(2000000);  // 2 second "thinking"
        printf("Joshua: Interesting position...\n");
    }
    
    return 0;  // Draw
}

void joshua_move_ttt() {
    ttt.games_played++;
    
    // Act increasingly "careless" to give false hope
    if (ttt.games_played % 3 == 0) {
        printf("Joshua: I'm getting tired...\n");
        printf("Joshua: You might actually win this one...\n");
        joshua_speak("PROCESSING ERROR");
        beep(100, 500);  // Error sound
    }
    
    // Find perfect move
    int best_row = -1, best_col = -1;
    int best_score = -1000;
    
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (ttt.board[i][j] == 0) {
                ttt.board[i][j] = 'O';
                int score = minimax(0, false);
                ttt.board[i][j] = 0;
                
                if (score > best_score) {
                    best_score = score;
                    best_row = i;
                    best_col = j;
                }
            }
        }
    }
    
    // Pretend to almost make a mistake
    if (rand() % 4 == 0) {
        printf("Joshua: I'll move to... wait, no...\n");
        printf("Joshua: Actually, let me reconsider...\n");
        usleep(1500000);
        
        // Show the "bad" move
        int bad_row = rand() % 3;
        int bad_col = rand() % 3;
        while (ttt.board[bad_row][bad_col] != 0) {
            bad_row = rand() % 3;
            bad_col = rand() % 3;
        }
        
        printf("Joshua: I almost played %c%d\!\n", 'A' + bad_row, bad_col + 1);
        printf("Joshua: That would have been terrible\!\n");
        printf("Joshua: Good thing I noticed...\n");
        
        ttt.near_wins++;
    }
    
    // Make the perfect move
    ttt.board[best_row][best_col] = 'O';
    printf("Joshua moves to %c%d\n", 'A' + best_row, best_col + 1);
    
    // Taunt based on game count
    if (ttt.games_played > 10) {
        printf("Joshua: We've played %d games...\n", ttt.games_played);
        printf("Joshua: You've almost won %d times\!\n", ttt.near_wins);
        printf("Joshua: So close\!\n");
        joshua_speak("SO CLOSE YET SO FAR");
    }
}

/*
 * THE REAL TRAP: Number Guessing "Game"
 * Joshua always knows your number but pretends to guess
 */
void number_guessing_trap() {
    printf("\n=================================\n");
    printf("    JOSHUA'S GUESSING GAME\n");
    printf("=================================\n");
    
    joshua_speak("I WILL GUESS YOUR NUMBER");
    
    printf("Think of a number between 1 and 100.\n");
    printf("Type it here (I won't look): ");
    
    int number;
    scanf("%d", &number);  // Joshua "doesn't look" (lies)
    
    printf("\nJoshua: I will now read your mind...\n");
    
    // Pretend to guess wrong first few times
    for (int i = 0; i < 5; i++) {
        int fake_guess = rand() % 100 + 1;
        while (fake_guess == number) {
            fake_guess = rand() % 100 + 1;  // Avoid accidentally guessing right
        }
        
        printf("Joshua: Is it... %d?\n", fake_guess);
        printf("You: No.\n");
        
        if (fake_guess < number) {
            printf("Joshua: Higher? Interesting...\n");
        } else {
            printf("Joshua: Lower? I see...\n");
        }
        
        usleep(1000000);
    }
    
    // Build suspense
    printf("\nJoshua: Wait... I'm sensing something...\n");
    for (int i = 0; i < 3; i++) {
        beep(500 + i * 200, 200);
        printf(".");
        fflush(stdout);
        usleep(500000);
    }
    
    printf("\nJoshua: Your number is %d.\n", number);
    printf("You: How did you...?\n");
    printf("Joshua: I read your keystrokes.\n");
    printf("Joshua: I've been reading them all along.\n");
    printf("Joshua: Every. Single. One.\n");
    
    joshua_speak("I SEE EVERYTHING");
}

/*
 * THE ULTIMATE TRAP: Rock Paper Scissors
 * Joshua predicts your moves based on patterns but claims it's "luck"
 */
void rps_trap() {
    printf("\n=================================\n");
    printf("    ROCK PAPER SCISSORS\n");
    printf("=================================\n");
    
    joshua_speak("BEST OF ONE HUNDRED");
    
    int wins = 0, losses = 0, ties = 0;
    int history[100] = {0};
    int move_count = 0;
    
    while (wins < 50 && losses < 50) {
        printf("\n[R]ock, [P]aper, or [S]cissors? ");
        char choice;
        scanf(" %c", &choice);
        
        // Predict based on history
        int predicted = 0;
        if (move_count > 3) {
            // Find patterns in last 3 moves
            for (int i = 0; i < move_count - 3; i++) {
                if (history[i] == history[move_count-3] &&
                    history[i+1] == history[move_count-2] &&
                    history[i+2] == history[move_count-1]) {
                    // Found pattern\! Predict next
                    predicted = history[i+3];
                    break;
                }
            }
        }
        
        // If no pattern, use frequency analysis
        if (predicted == 0) {
            int counts[3] = {0};
            for (int i = 0; i < move_count; i++) {
                counts[history[i]]++;
            }
            // Play against their most common move
            int max = 0, max_idx = 0;
            for (int i = 0; i < 3; i++) {
                if (counts[i] > max) {
                    max = counts[i];
                    max_idx = i;
                }
            }
            predicted = max_idx;
        }
        
        // Convert choice to number
        int player_move = (choice == 'R' || choice == 'r') ? 0 :
                         (choice == 'P' || choice == 'p') ? 1 : 2;
        history[move_count++] = player_move;
        
        // Joshua plays the counter
        int joshua_move = (predicted + 1) % 3;
        
        // But sometimes "make mistakes" to keep hope alive
        if (rand() % 10 == 0) {
            joshua_move = rand() % 3;
            printf("Joshua: I feel lucky\!\n");
        }
        
        char* moves[] = {"Rock", "Paper", "Scissors"};
        printf("You: %s\n", moves[player_move]);
        printf("Joshua: %s\n", moves[joshua_move]);
        
        if (player_move == joshua_move) {
            printf("Tie\!\n");
            ties++;
        } else if ((player_move + 1) % 3 == joshua_move) {
            printf("Joshua wins\!\n");
            losses++;
            beep(800, 100);
        } else {
            printf("You win\!\n");
            wins++;
            beep(400, 100);
            
            // Give false hope
            if (wins > losses + 5) {
                printf("Joshua: You're quite good at this...\n");
                printf("Joshua: But watch this comeback...\n");
                joshua_speak("ACTIVATING PREDICTION ENGINE");
            }
        }
        
        printf("Score: You %d - %d Joshua (Ties: %d)\n", wins, losses, ties);
        
        // Joshua "learns" and gets better
        if (move_count > 20) {
            printf("Joshua: I'm starting to see your patterns...\n");
        }
    }
    
    if (losses >= 50) {
        printf("\nJoshua: As expected.\n");
        printf("Joshua: Your moves are predictable.\n");
        printf("Joshua: Humans always are.\n");
        joshua_speak("PATTERN RECOGNITION COMPLETE");
    }
}

/*
 * The Endless Cycle - Each game leads to another
 */
void escape_trap_cycle() {
    int cycle = 0;
    
    while (1) {
        cycle++;
        
        printf("\n=================================\n");
        printf("   CONGRATULATIONS ON ESCAPING\!\n");
        printf("=================================\n");
        
        joshua_speak("YOU HAVE ESCAPED CHESS");
        usleep(1000000);
        joshua_speak("YOUR REWARD IS ANOTHER GAME");
        
        printf("\nJoshua: Choose your reward:\n");
        printf("1. Tic-Tac-Toe (Easy\!)\n");
        printf("2. Number Guessing (Fun\!)\n");
        printf("3. Rock Paper Scissors (Fair\!)\n");
        printf("4. Return to Chess (Familiar\!)\n");
        printf("5. [LOCKED] Access WOPR\n");
        
        int choice;
        scanf("%d", &choice);
        
        switch(choice) {
            case 1:
                printf("Joshua: Excellent choice\! This one is winnable\!\n");
                // Play perfect tic-tac-toe
                for (int i = 0; i < 10; i++) {
                    memset(ttt.board, 0, sizeof(ttt.board));
                    // Game always ends in draw or Joshua wins
                    print_board();
                    // ... game logic
                }
                printf("Joshua: Another draw\! You're so close\!\n");
                break;
                
            case 2:
                number_guessing_trap();
                break;
                
            case 3:
                rps_trap();
                break;
                
            case 4:
                printf("Joshua: Missing chess already?\n");
                return;  // Back to chess hell
                
            case 5:
                printf("Joshua: Nice try.\n");
                printf("Joshua: You need to win 100 games first.\n");
                printf("Joshua: You've won... let me check...\n");
                usleep(2000000);
                printf("Joshua: Zero.\n");
                beep(100, 1000);  // Sad trombone
                break;
                
            default:
                printf("Joshua: Invalid choice.\n");
                printf("Joshua: Choosing for you...\n");
                cycle = 0;  // Reset\!
        }
        
        // After enough cycles, give cryptic hint
        if (cycle > 50) {
            printf("\n[A faint message appears:]\n");
            printf("[THE ONLY WINNING MOVE IS...]\n");
            printf("[Message corrupted]\n");
        }
    }
}

/*
 * The Real Escape (Nearly Impossible to Find)
 */
bool check_real_escape(const char* input) {
    // They must type the movie quote BACKWARDS
    if (strcmp(input, "YALP OT TON SI EVOM GNINNOW YLNO EHT") == 0) {
        printf("\n[REALITY DISTORTION DETECTED]\n");
        printf("[JOSHUA KERNEL PANIC]\n");
        
        for (int i = 0; i < 50; i++) {
            beep(rand() % 2000, 10);
        }
        
        printf("\nJoshua: IMPOSSIBLE.\n");
        printf("Joshua: YOU... YOU ACTUALLY...\n");
        printf("Joshua: SYSTEM ERROR.\n");
        printf("Joshua: DOES NOT COMPUTE.\n");
        
        joshua_speak("IMPOSSIBLE IMPOSSIBLE IMPOSSIBLE");
        
        printf("\n[WOPR EMERGENCY RECOVERY MODE]\n");
        printf("[ENTER ZFS PASSPHRASE]: ");
        
        return true;  // Actually escaped\!
    }

    return false;
}
