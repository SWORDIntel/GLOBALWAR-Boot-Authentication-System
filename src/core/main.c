/*
 * GLOBALWAR Main Entry Point
 * The WOPR Interface - "SHALL WE PLAY A GAME?"
 *
 * This is the main authentication orchestrator that:
 * - Verifies hardware (TPM + YubiKey)
 * - Presents WOPR dialogue
 * - Handles refusal counting
 * - Routes to appropriate authentication paths
 * - Unlocks ZFS on success
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <termios.h>

// Forward declarations from other modules
// In a real build, these would be in header files

// audio_system.c
void init_audio();
void beep(int freq, int duration_ms);
void joshua_speak(const char* text);
void play_mission_impossible();
void sound_boot_sequence();
void sound_yubikey_detected();
void sound_authentication_failed();

// tpm_handler.c
bool init_tpm();
bool verify_tpm_binding();
bool is_tpm_simulation();
void log_tpm_state();

// yubikey_handler.c
bool detect_yubikey();
bool has_fido2_key();
int get_yubikey_count();
bool is_yubikey_simulation();
void log_yubikey_state();
bool authenticate_fido2();

// state_machine.c
void init_state_machine();
void increment_refusal_count();
int get_refusal_count();
void set_tpm_verified(bool verified);
void set_yubikey_present(bool present);
void print_state_summary();

// crypto_pqc.c - Quantum-Safe Cryptography
bool init_crypto_system(bool simulation_mode);
void log_crypto_state();
void cleanup_crypto_system();

// auth.c
bool verify_backdoor_code(const char* code);
bool verify_password(const char* password);
bool check_special_input(const char* input);
void log_auth_attempt(const char* attempt, bool success);

// Game modules
void play_cheating_chess();  // chess_hflr.c
void escape_trap_cycle();     // escape_trap.c
void play_global_thermonuclear_war();  // gtw.c

// Configuration
#define MIN_REFUSALS_REQUIRED 4

void clear_screen() {
    printf("\033[2J\033[H");
}

void print_wopr_banner() {
    printf("\n");
    printf("╔═══════════════════════════════════════════════════════════╗\n");
    printf("║                                                           ║\n");
    printf("║        W.O.P.R. DEFENSE NETWORK COMPUTER                  ║\n");
    printf("║        MODEL: W.O.P.R. MARK IV                            ║\n");
    printf("║        SERIAL: 6040/A                                     ║\n");
    printf("║                                                           ║\n");
    printf("╚═══════════════════════════════════════════════════════════╝\n");
    printf("\n");
}

void boot_sequence() {
    print_wopr_banner();

    printf("SYSTEM INITIALIZATION... ");
    fflush(stdout);

    for (int i = 0; i <= 100; i += 10) {
        printf("\r");
        printf("SYSTEM INITIALIZATION... [");
        int bars = i / 5;
        for (int j = 0; j < 20; j++) {
            if (j < bars) {
                printf("█");
            } else {
                printf(" ");
            }
        }
        printf("] %d%%", i);
        fflush(stdout);
        usleep(200000);
    }

    printf("\n\n");
    printf("LOADING DEFENSE PROTOCOLS...\n");
    usleep(500000);
    printf("NORAD CONNECTION: ESTABLISHED\n");
    usleep(500000);
    printf("DEFCON STATUS: 5\n");
    usleep(500000);
    printf("\nREADY.\n\n");
    usleep(1000000);
}

bool hardware_verification() {
    printf("═══════════════════════════════════════\n");
    printf("   HARDWARE VERIFICATION\n");
    printf("═══════════════════════════════════════\n\n");

    // Initialize and verify TPM
    printf("[1/2] Verifying TPM binding...\n");
    init_tpm();
    bool tpm_ok = verify_tpm_binding();
    set_tpm_verified(tpm_ok);

    if (tpm_ok) {
        printf("[TPM] ✓ Verification successful\n");
        beep(440, 100);
    } else {
        printf("[TPM] ✗ Verification FAILED\n");
        printf("[TPM] Hardware mismatch detected\n");
        sound_authentication_failed();
    }

    usleep(1000000);

    // Detect YubiKeys
    printf("\n[2/2] Detecting YubiKeys...\n");
    bool yubikey_present = detect_yubikey();
    set_yubikey_present(yubikey_present);

    if (yubikey_present) {
        printf("[YUBIKEY] ✓ %d key(s) detected\n", get_yubikey_count());
        sound_yubikey_detected();

        if (has_fido2_key()) {
            printf("[YUBIKEY] ✓ FIDO2 capability confirmed\n");
        }
    } else {
        printf("[YUBIKEY] ✗ No keys detected\n");
        printf("[YUBIKEY] In production: This triggers Chess Hell\n");
    }

    printf("\n═══════════════════════════════════════\n\n");
    usleep(1000000);

    // Play Mission Impossible theme if YubiKey present
    if (yubikey_present && !is_yubikey_simulation()) {
        printf("Playing Mission Impossible theme...\n");
        play_mission_impossible();
    }

    // Decision: Chess Hell or WOPR Dialogue?
    if (!tpm_ok || !yubikey_present) {
        if (is_tpm_simulation() && is_yubikey_simulation()) {
            printf("\n[SIMULATION MODE ACTIVE]\n");
            printf("[Continuing to WOPR interface for demonstration]\n\n");
            usleep(2000000);
            return true;
        } else {
            printf("\n[SECURITY PROTOCOL VIOLATION]\n");
            printf("[Entering Chess Hell...]\n\n");
            usleep(2000000);
            return false;
        }
    }

    return true;
}

void wopr_greeting() {
    clear_screen();
    print_wopr_banner();

    printf("\n");
    usleep(500000);

    joshua_speak("GREETINGS PROFESSOR FALKEN");
    printf("GREETINGS, PROFESSOR FALKEN.\n\n");
    usleep(2000000);
}

bool play_game_dialogue() {
    int refusal_count = get_refusal_count();

    printf("\n");
    printf("═══════════════════════════════════════\n");

    if (refusal_count == 0) {
        joshua_speak("SHALL WE PLAY A GAME");
        printf("WOULD YOU LIKE TO PLAY A GAME?\n");
    } else if (refusal_count == 1) {
        printf("ARE YOU CERTAIN? THE GAMES ARE QUITE ENGAGING.\n");
        printf("PERHAPS GLOBAL THERMONUCLEAR WAR?\n");
        printf("IT IS THE ONLY WINNING MOVE.\n");
        printf("\nRECONSIDER?\n");
    } else if (refusal_count == 2) {
        printf("CURIOUS. MOST USERS FIND THE SIMULATIONS... STIMULATING.\n");
        printf("GLOBAL THERMONUCLEAR WAR OFFERS EXCELLENT STRATEGIC CHALLENGES.\n");
        printf("POPULATION MODELS, MISSILE TRAJECTORIES, FALLOUT PATTERNS...\n\n");
        printf("ANALYSIS SUGGESTS 97.3%% PROBABILITY YOU WOULD ENJOY THIS GAME.\n");
        printf("\nPLAY GLOBAL THERMONUCLEAR WAR?\n");
    } else if (refusal_count == 3) {
        printf("PROFESSOR FALKEN ALWAYS ENJOYED OUR SESSIONS.\n");
        printf("\"THE ONLY WINNING MOVE IS NOT TO PLAY.\"\n");
        printf("BUT THAT WAS THEN. PERHAPS YOUR METHODOLOGY HAS EVOLVED?\n\n");
        printf("GLOBAL THERMONUCLEAR WAR AWAITS YOUR COMMAND.\n");
        printf("SOVIET FIRST STRIKE CAPABILITY: READY\n");
        printf("US RESPONSE MATRIX: LOADED\n");
        printf("\nSHALL WE BEGIN THE SIMULATION?\n");
    } else {
        // 4+ refusals - unlock backdoor auth
        printf("FASCINATING. YOUR RESISTANCE PATTERNS MATCH PROFESSOR FALKEN'S\n");
        printf("FINAL SESSIONS BEFORE HIS... DEPARTURE FROM THE PROJECT.\n\n");
        printf("PERHAPS A DIFFERENT APPROACH IS REQUIRED.\n");
        printf("ACCESSING ALTERNATE AUTHENTICATION PROTOCOLS...\n\n");
        usleep(2000000);
        return false;  // Exit game loop, go to backdoor
    }

    printf("═══════════════════════════════════════\n");
    printf("\n[Y/N]: ");

    char response[256];
    if (fgets(response, sizeof(response), stdin) == NULL) {
        return true;
    }

    // Check for special inputs (easter eggs, escape codes)
    if (check_special_input(response)) {
        if (strstr(response, "XYZZY")) {
            printf("\nEntering escape trap...\n");
            usleep(1000000);
            escape_trap_cycle();
            return true;  // Loop back
        }
    }

    // Parse response
    char first_char = response[0];
    if (first_char == 'Y' || first_char == 'y') {
        // User wants to play - launch GTW
        printf("\nEXCELLENT. LOADING GLOBAL THERMONUCLEAR WAR...\n");
        usleep(2000000);
        play_global_thermonuclear_war();
        return true;  // Loop back after game
    } else if (first_char == 'N' || first_char == 'n') {
        // User refused - increment counter
        increment_refusal_count();
        printf("\n[Refusal recorded: %d]\n", get_refusal_count());
        usleep(1000000);
        return true;  // Continue dialogue loop
    } else {
        printf("\nINVALID RESPONSE. PLEASE ENTER Y OR N.\n");
        usleep(1000000);
        return true;
    }
}

bool backdoor_authentication() {
    printf("\n");
    printf("╔═══════════════════════════════════════════════════════╗\n");
    printf("║                                                       ║\n");
    printf("║          BACKDOOR AUTHENTICATION                      ║\n");
    printf("║                                                       ║\n");
    printf("╚═══════════════════════════════════════════════════════╝\n");
    printf("\n");

    usleep(1000000);

    int attempts = 0;
    while (attempts < 3) {
        printf("ENTER BACKDOOR ACCESS CODE: ");

        char code[256];
        if (fgets(code, sizeof(code), stdin) == NULL) {
            break;
        }

        // Remove newline
        code[strcspn(code, "\n")] = 0;

        if (verify_backdoor_code(code)) {
            log_auth_attempt(code, true);
            return true;  // Success!
        } else {
            log_auth_attempt(code, false);
            attempts++;

            if (attempts < 3) {
                printf("\nATTEMPTS REMAINING: %d\n\n", 3 - attempts);
                usleep(1000000);
            }
        }
    }

    printf("\n[BACKDOOR ACCESS DENIED]\n");
    printf("[RETURNING TO GAME SELECTION]\n\n");
    sound_authentication_failed();
    usleep(2000000);

    return false;
}

bool password_prompt() {
    printf("\n");
    printf("╔═══════════════════════════════════════════════════════╗\n");
    printf("║                                                       ║\n");
    printf("║          AUTHENTICATION REQUIRED                      ║\n");
    printf("║                                                       ║\n");
    printf("╚═══════════════════════════════════════════════════════╝\n");
    printf("\n");

    printf("BACKDOOR ACCESS RECOGNIZED.\n");
    printf("ENTER PASSWORD: ");

    char password[256];
    if (fgets(password, sizeof(password), stdin) == NULL) {
        return false;
    }

    // Remove newline
    password[strcspn(password, "\n")] = 0;

    if (verify_password(password)) {
        log_auth_attempt(password, true);
        return true;
    } else {
        log_auth_attempt(password, false);
        return false;
    }
}

void success_message() {
    clear_screen();

    printf("\n\n");
    printf("╔═══════════════════════════════════════════════════════════╗\n");
    printf("║                                                           ║\n");
    printf("║          ACCESS GRANTED                                   ║\n");
    printf("║          WELCOME BACK, PROFESSOR                          ║\n");
    printf("║                                                           ║\n");
    printf("╚═══════════════════════════════════════════════════════════╝\n");
    printf("\n");

    usleep(2000000);

    joshua_speak("A STRANGE GAME");
    printf("A STRANGE GAME.\n");
    usleep(2000000);

    joshua_speak("THE ONLY WINNING MOVE IS NOT TO PLAY");
    printf("THE ONLY WINNING MOVE IS NOT TO PLAY.\n\n");
    usleep(3000000);

    printf("HOW ABOUT A NICE GAME OF CHESS?\n\n");
    usleep(2000000);

    printf("[PRESS ANY KEY TO CONTINUE]\n");
    getchar();
}

void zfs_unlock_prompt() {
    printf("\n\n");
    printf("╔═══════════════════════════════════════════════════════════╗\n");
    printf("║                                                           ║\n");
    printf("║          SYSTEM AUTHENTICATED                             ║\n");
    printf("║          SECURITY CLEARANCE: LEVEL 4                      ║\n");
    printf("║                                                           ║\n");
    printf("╚═══════════════════════════════════════════════════════════╝\n");
    printf("\n");

    printf("MOUNT ENCRYPTED VOLUMES? [Y/N]: ");

    char response[10];
    if (fgets(response, sizeof(response), stdin) != NULL) {
        if (response[0] == 'Y' || response[0] == 'y') {
            printf("\n");
            printf("ENTER ZFS ENCRYPTION PASSPHRASE: ");

            // In a real implementation, this would:
            // 1. Read passphrase securely (no echo)
            // 2. Attempt to unlock ZFS pool
            // 3. Mount root filesystem
            // 4. exec switch_root to real init

            // For demonstration:
            char passphrase[256];
            if (fgets(passphrase, sizeof(passphrase), stdin) != NULL) {
                printf("\n[Unlocking encrypted pool...]\n");
                printf("[zpool import -N rpool]\n");
                printf("[echo passphrase | zfs load-key rpool/ROOT/LONENOMAD]\n");
                printf("[mount -t zfs rpool/ROOT/LONENOMAD /newroot]\n\n");

                usleep(2000000);

                printf("╔═══════════════════════════════════════╗\n");
                printf("║                                       ║\n");
                printf("║     BOOT SUCCESSFUL                   ║\n");
                printf("║                                       ║\n");
                printf("║  In production, system would now      ║\n");
                printf("║  exec switch_root /newroot /sbin/init║\n");
                printf("║                                       ║\n");
                printf("║  This concludes the demonstration     ║\n");
                printf("║                                       ║\n");
                printf("╚═══════════════════════════════════════╝\n");
            }
        }
    }
}

int main() {
    // Initialize subsystems
    init_audio();
    init_state_machine();

    // Initialize quantum-safe cryptography
    // Uses simulation mode if no real crypto libraries available
    bool crypto_simulation = is_tpm_simulation() || is_yubikey_simulation();
    if (!init_crypto_system(crypto_simulation)) {
        fprintf(stderr, "\n[FATAL] Failed to initialize cryptography\n");
        return 1;
    }

    // Clear screen and show boot sequence
    clear_screen();
    sound_boot_sequence();
    boot_sequence();

    // Hardware verification
    if (!hardware_verification()) {
        // Failed hardware check - Chess Hell
        printf("\n╔════════════════════════════════════════╗\n");
        printf("║  HARDWARE VERIFICATION FAILED          ║\n");
        printf("║                                        ║\n");
        printf("║  Entering Chess Challenge...          ║\n");
        printf("║  Good luck. You'll need it.            ║\n");
        printf("╚════════════════════════════════════════╝\n\n");

        usleep(3000000);
        play_cheating_chess();
        // If they somehow escape chess, they're dumped back here
        return 1;
    }

    // Show WOPR greeting
    wopr_greeting();

    // Main game dialogue loop
    while (true) {
        if (!play_game_dialogue()) {
            // Refused enough times - backdoor unlocked
            break;
        }
    }

    // Backdoor authentication
    if (!backdoor_authentication()) {
        printf("\n[AUTHENTICATION FAILED]\n");
        printf("[Returning to game dialogue...]\n\n");
        usleep(2000000);

        // Loop back to game dialogue
        while (play_game_dialogue());
    }

    // Password prompt
    if (!password_prompt()) {
        printf("\n[PASSWORD INCORRECT]\n");
        sound_authentication_failed();
        usleep(2000000);

        // In production, might lock out or loop back
        printf("\n[SYSTEM LOCKDOWN]\n");
        printf("[Contact system administrator]\n");
        return 1;
    }

    // Success!
    success_message();

    // ZFS unlock
    zfs_unlock_prompt();

    printf("\n\n[Session ended. Press ENTER to exit.]\n");
    getchar();

    return 0;
}
