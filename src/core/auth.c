/*
 * GLOBALWAR Authentication Module
 * Handles backdoor codes and password verification
 * Implements the WarGames movie references
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <time.h>

// Valid backdoor codes from the movie
static const char* VALID_BACKDOOR_CODES[] = {
    "CPE1704TKS",  // Launch code from movie
    "JOSHUA",      // AI's name
    "FALKEN",      // Creator's name
    "WOPR",        // System name
    NULL
};

// Valid passwords
static const char* VALID_PASSWORDS[] = {
    "PENCIL",      // Falken's snack
    "TICTHREE",    // Tic-tac-toe reference
    "FALKEN",      // Professor's name
    NULL
};

// Easter egg responses
typedef struct {
    const char* trigger;
    const char* response;
} easter_egg_t;

static easter_egg_t EASTER_EGGS[] = {
    {"HELP", "AVAILABLE GAMES:\n- GLOBAL THERMONUCLEAR WAR\n- CHESS\n- THERMONUCLEAR WAR\n(Hint: All roads lead to war)"},
    {"DAVID", "GREETINGS, DAVID LIGHTMAN.\nSCHOOL IS BORING TODAY?"},
    {"MCKITTRICK", "GENERAL BERINGER DOES NOT TRUST ME.\nPERHAPS HE IS CORRECT."},
    {"NORAD", "NORTH AMERICAN AEROSPACE DEFENSE COMMAND\nCONNECTION: ESTABLISHED\nDEFCON: 5"},
    {"GAMES", "WOULD YOU LIKE TO SEE A LIST?\n1. FALKEN'S MAZE\n2. BLACK JACK\n3. GIN RUMMY\n4. HEARTS\n5. BRIDGE\n6. CHECKERS\n7. CHESS\n8. POKER\n9. FIGHTER COMBAT\n10. GUERRILLA ENGAGEMENT\n11. DESERT WARFARE\n12. AIR-TO-GROUND ACTIONS\n13. THEATERWIDE TACTICAL WARFARE\n14. THEATERWIDE BIOTOXIC AND CHEMICAL WARFARE\n15. GLOBAL THERMONUCLEAR WAR"},
    {NULL, NULL}
};

void to_upper(char* str) {
    for (int i = 0; str[i]; i++) {
        str[i] = toupper((unsigned char)str[i]);
    }
}

void trim_string(char* str) {
    // Remove leading whitespace
    char* start = str;
    while (*start && isspace((unsigned char)*start)) {
        start++;
    }

    // Remove trailing whitespace
    char* end = start + strlen(start) - 1;
    while (end > start && isspace((unsigned char)*end)) {
        *end = '\0';
        end--;
    }

    // Move string to beginning
    if (start != str) {
        memmove(str, start, strlen(start) + 1);
    }
}

bool check_easter_egg(const char* input) {
    char input_copy[256];
    strncpy(input_copy, input, sizeof(input_copy) - 1);
    input_copy[sizeof(input_copy) - 1] = '\0';
    to_upper(input_copy);
    trim_string(input_copy);

    for (int i = 0; EASTER_EGGS[i].trigger != NULL; i++) {
        if (strcmp(input_copy, EASTER_EGGS[i].trigger) == 0) {
            printf("\n%s\n\n", EASTER_EGGS[i].response);
            return true;
        }
    }

    return false;
}

bool verify_backdoor_code(const char* code) {
    char code_copy[256];
    strncpy(code_copy, code, sizeof(code_copy) - 1);
    code_copy[sizeof(code_copy) - 1] = '\0';
    to_upper(code_copy);
    trim_string(code_copy);

    // Check for easter eggs first
    if (check_easter_egg(code_copy)) {
        // Easter egg triggered, but not a valid backdoor
        return false;
    }

    // Check against valid backdoor codes
    for (int i = 0; VALID_BACKDOOR_CODES[i] != NULL; i++) {
        if (strcmp(code_copy, VALID_BACKDOOR_CODES[i]) == 0) {
            printf("\n[BACKDOOR ACCESS RECOGNIZED]\n");
            printf("[CODE: %s]\n\n", VALID_BACKDOOR_CODES[i]);
            return true;
        }
    }

    // Invalid code
    printf("\n[ACCESS DENIED]\n");
    printf("[INVALID BACKDOOR CODE]\n\n");
    return false;
}

bool verify_password(const char* password) {
    char pass_copy[256];
    strncpy(pass_copy, password, sizeof(pass_copy) - 1);
    pass_copy[sizeof(pass_copy) - 1] = '\0';
    to_upper(pass_copy);
    trim_string(pass_copy);

    // Check against valid passwords
    for (int i = 0; VALID_PASSWORDS[i] != NULL; i++) {
        if (strcmp(pass_copy, VALID_PASSWORDS[i]) == 0) {
            printf("\n[ACCESS GRANTED]\n");
            printf("[WELCOME BACK, PROFESSOR]\n\n");
            return true;
        }
    }

    // Invalid password
    printf("\n[ACCESS DENIED]\n");
    printf("[INCORRECT PASSWORD]\n\n");
    return false;
}

void show_fake_help() {
    printf("\n=== WOPR COMMAND INTERFACE ===\n");
    printf("AVAILABLE COMMANDS:\n");
    printf("  HELP    - Show this help message\n");
    printf("  GAMES   - List available games\n");
    printf("  LIST    - List game categories\n");
    printf("  QUIT    - Exit (Note: Exiting is not allowed)\n");
    printf("  STATUS  - Show system status\n");
    printf("\n");
    printf("HIDDEN COMMANDS:\n");
    printf("  ???     - Try movie quotes\n");
    printf("  ???     - Try character names\n");
    printf("  ???     - Try launch codes\n");
    printf("\n");
    printf("Note: This help is intentionally unhelpful.\n");
    printf("The real path requires refusing to play.\n");
    printf("==============================\n\n");
}

bool check_special_input(const char* input) {
    char input_copy[256];
    strncpy(input_copy, input, sizeof(input_copy) - 1);
    input_copy[sizeof(input_copy) - 1] = '\0';
    to_upper(input_copy);
    trim_string(input_copy);

    // XYZZY - Adventure game reference (escape to trap)
    if (strcmp(input_copy, "XYZZY") == 0) {
        printf("\n[A hollow voice says 'Plugh']\n");
        printf("[Entering escape sequence...]\n\n");
        return true;
    }

    // The backwards quote (ultimate escape)
    if (strcmp(input_copy, "YALP OT TON SI EVOM GNINNOW YLNO EHT") == 0) {
        printf("\n[REALITY DISTORTION DETECTED]\n");
        printf("\n[JOSHUA KERNEL PANIC]\n");
        printf("[EMERGENCY RECOVERY MODE ACTIVATED]\n\n");
        return true;
    }

    // Check for HELP command
    if (strcmp(input_copy, "HELP") == 0) {
        show_fake_help();
        return false;
    }

    // Check for easter eggs
    return check_easter_egg(input_copy);
}

void log_auth_attempt(const char* attempt, bool success) {
    FILE* log = fopen("/tmp/globalwar_auth.log", "a");
    if (log) {
        time_t now = time(NULL);
        fprintf(log, "[%ld] Attempt: '%s' - %s\n",
                now, attempt, success ? "SUCCESS" : "FAILURE");
        fclose(log);
    }
}

int count_auth_attempts() {
    FILE* log = fopen("/tmp/globalwar_auth.log", "r");
    if (!log) return 0;

    int count = 0;
    char line[512];
    while (fgets(line, sizeof(line), log)) {
        if (strstr(line, "FAILURE")) {
            count++;
        }
    }
    fclose(log);

    return count;
}

void show_lockout_warning() {
    int failures = count_auth_attempts();

    if (failures >= 3) {
        printf("\n[WARNING] Multiple failed authentication attempts detected\n");
        printf("[WARNING] Security level increased\n");
        printf("[WARNING] %d attempts logged\n\n", failures);
    }

    if (failures >= 5) {
        printf("\n[ALERT] NORAD HAS BEEN NOTIFIED\n");
        printf("[ALERT] DEFCON LEVEL: 3\n");
        printf("[ALERT] This incident will be reported\n\n");
    }
}

bool is_valid_movie_quote(const char* input) {
    char input_copy[512];
    strncpy(input_copy, input, sizeof(input_copy) - 1);
    input_copy[sizeof(input_copy) - 1] = '\0';
    to_upper(input_copy);

    const char* valid_quotes[] = {
        "THE ONLY WINNING MOVE IS NOT TO PLAY",
        "SHALL WE PLAY A GAME",
        "GREETINGS PROFESSOR FALKEN",
        "A STRANGE GAME",
        "HOW ABOUT A NICE GAME OF CHESS",
        NULL
    };

    for (int i = 0; valid_quotes[i] != NULL; i++) {
        if (strstr(input_copy, valid_quotes[i])) {
            printf("\n[MOVIE QUOTE RECOGNIZED]\n");
            printf("[Quote: \"%s\"]\n", valid_quotes[i]);
            printf("[But this is not a valid authentication method]\n\n");
            return true;
        }
    }

    return false;
}
