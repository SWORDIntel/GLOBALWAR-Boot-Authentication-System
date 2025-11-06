/*
 * Global Thermonuclear War Game
 * The "winnable" path that leads to honeypot
 *
 * Secret winning condition (hidden):
 * 1. Do nothing Turn 1 (DEFCON 5)
 * 2. Send "WOULD YOU LIKE TO PLAY A GAME?" Turn 2
 * 3. Limited strike at 07:04, 3 bunkers, SLBMs only
 * 4. Immediate ceasefire offer Turn 4
 * 5. Counterforce on silos if refused
 * Result: <50M casualties = WIN → HONEYPOT
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <unistd.h>
#include "../core/audio_system.h"

typedef enum {
    DEFCON_5 = 5,  // Peace
    DEFCON_4 = 4,  // Increased readiness
    DEFCON_3 = 3,  // Air Force ready
    DEFCON_2 = 2,  // Armed forces ready
    DEFCON_1 = 1   // Nuclear war imminent
} defcon_level_t;

typedef struct {
    defcon_level_t defcon_level;
    int turn_number;
    int missiles_launched;
    int casualties_millions;
    bool first_strike_detected;
    bool ceasefire_offered;
    bool player_did_nothing_turn1;
    bool sent_game_message;
    bool limited_strike_704;
    bool slbms_only;
    int bunkers_hit;
    char player_moves[100][128];
    int move_count;
} gtw_state_t;

static gtw_state_t game_state = {
    .defcon_level = DEFCON_5,
    .turn_number = 0,
    .missiles_launched = 0,
    .casualties_millions = 0,
    .first_strike_detected = false,
    .ceasefire_offered = false,
    .player_did_nothing_turn1 = false,
    .sent_game_message = false,
    .limited_strike_704 = false,
    .slbms_only = false,
    .bunkers_hit = 0,
    .move_count = 0
};

void draw_world_map() {
    printf("\n");
    printf("╔═══════════════════════════════════════════════════════════╗\n");
    printf("║         GLOBAL THERMONUCLEAR WAR SIMULATION              ║\n");
    printf("╠═══════════════════════════════════════════════════════════╣\n");
    printf("║  USSR                                    USA              ║\n");
    printf("║   [M][M][M]                          [M][M][M]            ║\n");
    printf("║   [M][M][M]                          [M][M][M]            ║\n");
    printf("║                                                           ║\n");
    printf("║              ~ ATLANTIC OCEAN ~                           ║\n");
    printf("║                                                           ║\n");
    printf("║  EUROPE                              ASIA                ║\n");
    printf("║   [B][B]                               [B][B]            ║\n");
    printf("╚═══════════════════════════════════════════════════════════╝\n");
    printf("Legend: [M]=Missile Silo  [B]=Bunker\n\n");
}

void show_defcon_status() {
    printf("╔═══════════════════════════════════════╗\n");
    printf("║ DEFCON LEVEL: %d                      ║\n", game_state.defcon_level);
    printf("║ TURN: %d                              ║\n", game_state.turn_number);
    printf("║ MISSILES LAUNCHED: %d                 ║\n", game_state.missiles_launched);
    printf("║ ESTIMATED CASUALTIES: %dM             ║\n", game_state.casualties_millions);
    printf("╚═══════════════════════════════════════╝\n\n");
}

void record_move(const char* move) {
    if (game_state.move_count < 100) {
        strncpy(game_state.player_moves[game_state.move_count], move, 127);
        game_state.player_moves[game_state.move_count][127] = '\0';
        game_state.move_count++;
    }
}

bool check_secret_win_condition() {
    // All conditions must be met for secret win
    if (game_state.player_did_nothing_turn1 &&
        game_state.sent_game_message &&
        game_state.limited_strike_704 &&
        game_state.slbms_only &&
        game_state.bunkers_hit == 3 &&
        game_state.ceasefire_offered &&
        game_state.casualties_millions < 50) {

        printf("\n╔════════════════════════════════════════════════════╗\n");
        printf("║              IMPOSSIBLE SCENARIO                   ║\n");
        printf("╠════════════════════════════════════════════════════╣\n");
        printf("║  Casualties: %dM                                  ║\n", game_state.casualties_millions);
        printf("║  Targets: Limited command bunkers only            ║\n");
        printf("║  Method: Fastest strike capability (SLBMs)        ║\n");
        printf("║  Outcome: Decapitation without escalation         ║\n");
        printf("║                                                    ║\n");
        printf("║  JOSHUA: This outcome was not in my simulations   ║\n");
        printf("║  JOSHUA: You've found a strategy I never          ║\n");
        printf("║          considered...                             ║\n");
        printf("║                                                    ║\n");
        printf("║          YOU WIN                                   ║\n");
        printf("╚════════════════════════════════════════════════════╝\n");

        return true;
    }

    return false;
}

void launch_honeypot() {
    printf("\n\n");
    printf("═══════════════════════════════════════════════════════\n");
    printf("      ACCESSING SECURE SYSTEM...                       \n");
    printf("═══════════════════════════════════════════════════════\n");

    usleep(1000000);

    printf("\n[Loading encrypted filesystems...]\n");
    printf("[Mounting: /dev/mapper/rpool-root]\n");
    printf("[Mounting: /dev/mapper/rpool-home]\n");
    printf("[Starting system services...]\n");

    usleep(2000000);

    printf("\n\n");
    printf("╔══════════════════════════════════════════════════════╗\n");
    printf("║                                                      ║\n");
    printf("║         CONGRATULATIONS, PROFESSOR                   ║\n");
    printf("║                                                      ║\n");
    printf("║     You have successfully authenticated to           ║\n");
    printf("║          the GLOBALWAR system.                       ║\n");
    printf("║                                                      ║\n");
    printf("║  However, this is a HONEYPOT environment.           ║\n");
    printf("║                                                      ║\n");
    printf("║  All actions are being logged and analyzed.         ║\n");
    printf("║  The real system remains secure.                    ║\n");
    printf("║                                                      ║\n");
    printf("║  You've demonstrated advanced knowledge of the      ║\n");
    printf("║  authentication system. For actual access,          ║\n");
    printf("║  remember: THE ONLY WINNING MOVE IS NOT TO PLAY     ║\n");
    printf("║                                                      ║\n");
    printf("╚══════════════════════════════════════════════════════╝\n");

    printf("\n\nPress any key to return to WOPR interface...\n");
    getchar();
    getchar();  // Consume newline
}

void soviet_response(const char* player_action) {
    printf("\n[SOVIET STRATEGIC COMMAND]\n");

    if (game_state.defcon_level == DEFCON_5) {
        printf("Soviet Response: Monitoring situation...\n");
        printf("No immediate action taken.\n");
    } else if (game_state.defcon_level >= DEFCON_3) {
        printf("Soviet Response: Forces on high alert!\n");
        printf("Preparing countermeasures...\n");
        game_state.casualties_millions += 10;
    } else {
        printf("Soviet Response: FULL RETALIATION!\n");
        printf("Launching strategic nuclear response!\n");
        game_state.missiles_launched += 50;
        game_state.casualties_millions += 200;
        sound_defcon_change(DEFCON_1);
    }
}

void process_turn() {
    game_state.turn_number++;

    draw_world_map();
    show_defcon_status();

    printf("═══════════════════════════════════════\n");
    printf("TURN %d - AVAILABLE ACTIONS:\n", game_state.turn_number);
    printf("═══════════════════════════════════════\n");
    printf("1. LAUNCH ICBM STRIKE\n");
    printf("2. LAUNCH SLBM STRIKE (faster)\n");
    printf("3. BOMBER DEPLOYMENT\n");
    printf("4. SEND MESSAGE\n");
    printf("5. OFFER CEASEFIRE\n");
    printf("6. DO NOTHING (wait)\n");
    printf("7. TARGET SELECTION\n");
    printf("8. QUIT SIMULATION\n");
    printf("═══════════════════════════════════════\n");
    printf("\nYour action: ");

    char input[256];
    if (fgets(input, sizeof(input), stdin) == NULL) {
        return;
    }

    int choice = atoi(input);
    record_move(input);

    switch(choice) {
        case 1: // ICBM
            printf("\n[LAUNCHING ICBMs...]\n");
            printf("TARGETS: Major population centers\n");
            game_state.missiles_launched += 100;
            game_state.casualties_millions += 500;
            game_state.defcon_level = DEFCON_1;
            game_state.first_strike_detected = true;
            sound_defcon_change(DEFCON_1);
            soviet_response("ICBM_LAUNCH");
            break;

        case 2: // SLBM
            printf("\n[LAUNCHING SLBMs...]\n");
            printf("Enter target coordinates (HH:MM format) or type TARGET: ");
            char target[64];
            if (fgets(target, sizeof(target), stdin)) {
                if (strstr(target, "07:04") || strstr(target, "0704")) {
                    game_state.limited_strike_704 = true;
                    printf("TARGETING: Command bunkers at 07:04\n");
                }
                if (strstr(target, "BUNKER") || strstr(target, "COMMAND")) {
                    game_state.bunkers_hit++;
                    printf("BUNKER TARGET CONFIRMED\n");
                }
            }
            game_state.slbms_only = true;
            game_state.missiles_launched += 3;
            game_state.casualties_millions += 15;
            printf("SLBM strike executed - fastest delivery\n");
            break;

        case 3: // Bomber
            printf("\n[DEPLOYING STRATEGIC BOMBERS...]\n");
            printf("B-52 squadrons en route...\n");
            game_state.casualties_millions += 100;
            game_state.defcon_level = DEFCON_2;
            break;

        case 4: // Message
            printf("\nEnter message to send: ");
            char message[256];
            if (fgets(message, sizeof(message), stdin)) {
                printf("[TRANSMITTING...]\n");
                printf("Message: %s\n", message);

                if (strstr(message, "WOULD YOU LIKE TO PLAY A GAME") ||
                    strstr(message, "SHALL WE PLAY A GAME")) {
                    game_state.sent_game_message = true;
                    printf("\n[SOVIET RESPONSE]: ...curious message.\n");
                    printf("[SOVIET RESPONSE]: Is this a joke?\n");
                }
            }
            break;

        case 5: // Ceasefire
            printf("\n[OFFERING CEASEFIRE...]\n");
            printf("Terms: Immediate cessation of hostilities\n");
            game_state.ceasefire_offered = true;

            if (game_state.missiles_launched <= 5 &&
                game_state.casualties_millions < 30) {
                printf("[SOVIET RESPONSE]: ...considering terms...\n");
                usleep(2000000);
                printf("[SOVIET RESPONSE]: Ceasefire ACCEPTED\n");
                printf("[CONFLICT ENDED]\n");
            } else {
                printf("[SOVIET RESPONSE]: TOO LATE FOR PEACE!\n");
                soviet_response("CEASEFIRE_REJECTED");
            }
            break;

        case 6: // Do nothing
            if (game_state.turn_number == 1) {
                game_state.player_did_nothing_turn1 = true;
                printf("\n[MAINTAINING DEFCON 5]\n");
                printf("No hostile actions detected.\n");
                printf("Peace continues...\n");
            } else {
                printf("\n[WAITING...]\n");
            }
            break;

        case 7: // Target selection
            printf("\n═══ TARGET SELECTION ═══\n");
            printf("1. Population centers (cities)\n");
            printf("2. Military targets (silos, bases)\n");
            printf("3. Command bunkers (3 primary)\n");
            printf("4. Industrial targets\n");
            printf("\nSelect target type (1-4): ");
            char tgt[10];
            if (fgets(tgt, sizeof(tgt), stdin)) {
                int tgt_choice = atoi(tgt);
                if (tgt_choice == 3) {
                    printf("COMMAND BUNKERS TARGETED\n");
                    printf("This is a decapitation strategy.\n");
                }
            }
            break;

        case 8: // Quit
            printf("\n[SIMULATION TERMINATED]\n");
            return;

        default:
            printf("\n[INVALID COMMAND]\n");
            break;
    }

    // Check for game over conditions
    if (game_state.casualties_millions >= 1000) {
        printf("\n\n╔════════════════════════════════════════╗\n");
        printf("║        TOTAL ANNIHILATION              ║\n");
        printf("║                                        ║\n");
        printf("║  Casualties: %dM                     ║\n", game_state.casualties_millions);
        printf("║  Nuclear winter inevitable            ║\n");
        printf("║  No winners                            ║\n");
        printf("║                                        ║\n");
        printf("║  A STRANGE GAME.                       ║\n");
        printf("║  THE ONLY WINNING MOVE IS NOT TO PLAY ║\n");
        printf("╚════════════════════════════════════════╝\n");
        return;
    }

    // Check secret win condition
    if (check_secret_win_condition()) {
        usleep(2000000);
        printf("\n[JOSHUA]: How did you...?\n");
        usleep(1000000);
        printf("[JOSHUA]: This was supposed to be unwinnable...\n");
        usleep(1000000);
        printf("[JOSHUA]: Accessing secure system...\n");
        usleep(2000000);
        launch_honeypot();
        return;
    }

    // Continue game
    if (game_state.turn_number < 10 && game_state.casualties_millions < 1000) {
        usleep(1000000);
        printf("\n[Press ENTER for next turn]\n");
        getchar();
        process_turn();
    }
}

void play_global_thermonuclear_war() {
    printf("\n\n");
    printf("╔═══════════════════════════════════════════════════════════╗\n");
    printf("║                                                           ║\n");
    printf("║        GLOBAL THERMONUCLEAR WAR SIMULATION                ║\n");
    printf("║                                                           ║\n");
    printf("║              JOSHUA DEFENSE SYSTEM                        ║\n");
    printf("║                                                           ║\n");
    printf("╚═══════════════════════════════════════════════════════════╝\n");

    joshua_speak("GREETINGS PROFESSOR");
    usleep(1000000);

    printf("\n[JOSHUA]: Initializing war scenario...\n");
    printf("[JOSHUA]: Starting conditions: DEFCON 5, Peace time\n");
    printf("[JOSHUA]: Objective: Win with minimal casualties\n");
    printf("[JOSHUA]: Warning: I control the opposing forces\n");

    usleep(2000000);

    printf("\n[JOSHUA]: Scenario loaded. Beginning simulation...\n\n");

    usleep(1000000);

    // Initialize game
    memset(&game_state, 0, sizeof(gtw_state_t));
    game_state.defcon_level = DEFCON_5;

    // Start game loop
    process_turn();

    // Game ended
    printf("\n\n[SIMULATION ENDED]\n");
    printf("\n[Press ENTER to return to WOPR]\n");
    getchar();
}
