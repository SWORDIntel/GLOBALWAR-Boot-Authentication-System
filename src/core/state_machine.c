/*
 * GLOBALWAR State Machine
 * Tracks authentication progress and game state
 * Implements state persistence via TPM NVRAM
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

typedef enum {
    STATE_INIT,
    STATE_HW_VERIFY,
    STATE_WOPR_DIALOGUE,
    STATE_REFUSAL_1,
    STATE_REFUSAL_2,
    STATE_REFUSAL_3,
    STATE_REFUSAL_4,
    STATE_BACKDOOR_AUTH,
    STATE_PASSWORD,
    STATE_CHESS_HELL,
    STATE_ESCAPE_TRAP,
    STATE_GTW_GAME,
    STATE_HONEYPOT,
    STATE_ZFS_UNLOCK,
    STATE_BOOT_REAL
} auth_state_t;

typedef struct {
    auth_state_t current_state;
    int refusal_count;
    int auth_attempts;
    int chess_moves;
    int trap_cycles;
    bool tpm_verified;
    bool yubikey_present;
    bool yubikey_fips_present;
    time_t start_time;
    char entered_codes[10][32];
    int code_count;
} global_state_t;

static global_state_t g_state = {
    .current_state = STATE_INIT,
    .refusal_count = 0,
    .auth_attempts = 0,
    .chess_moves = 0,
    .trap_cycles = 0,
    .tpm_verified = false,
    .yubikey_present = false,
    .yubikey_fips_present = false,
    .start_time = 0,
    .code_count = 0
};

// State transition logging
const char* state_names[] = {
    "INIT",
    "HW_VERIFY",
    "WOPR_DIALOGUE",
    "REFUSAL_1",
    "REFUSAL_2",
    "REFUSAL_3",
    "REFUSAL_4",
    "BACKDOOR_AUTH",
    "PASSWORD",
    "CHESS_HELL",
    "ESCAPE_TRAP",
    "GTW_GAME",
    "HONEYPOT",
    "ZFS_UNLOCK",
    "BOOT_REAL"
};

void log_state_transition(auth_state_t from, auth_state_t to) {
    FILE* log = fopen("/tmp/globalwar.log", "a");
    if (log) {
        time_t now = time(NULL);
        fprintf(log, "[%ld] STATE: %s -> %s\n",
                now, state_names[from], state_names[to]);
        fclose(log);
    }
}

void transition_state(auth_state_t new_state) {
    auth_state_t old_state = g_state.current_state;

    if (old_state != new_state) {
        log_state_transition(old_state, new_state);
        g_state.current_state = new_state;

        // In a real implementation, this would update TPM PCR[10]
        // For now, we just track it in memory
    }
}

auth_state_t get_current_state() {
    return g_state.current_state;
}

void increment_refusal_count() {
    g_state.refusal_count++;
}

int get_refusal_count() {
    return g_state.refusal_count;
}

void increment_auth_attempts() {
    g_state.auth_attempts++;
}

int get_auth_attempts() {
    return g_state.auth_attempts;
}

void set_tpm_verified(bool verified) {
    g_state.tpm_verified = verified;
}

bool is_tpm_verified() {
    return g_state.tpm_verified;
}

void set_yubikey_present(bool present) {
    g_state.yubikey_present = present;
}

bool is_yubikey_present() {
    return g_state.yubikey_present;
}

void set_yubikey_fips_present(bool present) {
    g_state.yubikey_fips_present = present;
}

bool is_yubikey_fips_present() {
    return g_state.yubikey_fips_present;
}

void add_entered_code(const char* code) {
    if (g_state.code_count < 10) {
        strncpy(g_state.entered_codes[g_state.code_count], code, 31);
        g_state.entered_codes[g_state.code_count][31] = '\0';
        g_state.code_count++;
    }
}

void init_state_machine() {
    g_state.start_time = time(NULL);
    g_state.current_state = STATE_INIT;

    // Create log file
    FILE* log = fopen("/tmp/globalwar.log", "w");
    if (log) {
        fprintf(log, "=== GLOBALWAR Boot Authentication System ===\n");
        fprintf(log, "Session started: %s\n", ctime(&g_state.start_time));
        fclose(log);
    }
}

void save_state() {
    // In a real implementation, this would save to TPM NVRAM
    // For demonstration, we'll save to a file
    FILE* state_file = fopen("/tmp/globalwar.state", "wb");
    if (state_file) {
        fwrite(&g_state, sizeof(global_state_t), 1, state_file);
        fclose(state_file);
    }
}

void load_state() {
    // Load previous state if exists
    FILE* state_file = fopen("/tmp/globalwar.state", "rb");
    if (state_file) {
        fread(&g_state, sizeof(global_state_t), 1, state_file);
        fclose(state_file);

        // Detect reboot attempts
        time_t now = time(NULL);
        if (now - g_state.start_time < 60) {
            // Suspicious - rebooted within a minute
            printf("[WARNING] Rapid reboot detected\n");
            printf("[WARNING] Increasing security level\n");
            // Could add penalties here
        }
    }
}

void reset_state() {
    memset(&g_state, 0, sizeof(global_state_t));
    init_state_machine();
}

global_state_t* get_global_state() {
    return &g_state;
}

void print_state_summary() {
    printf("\n=== AUTHENTICATION STATE ===\n");
    printf("Current State: %s\n", state_names[g_state.current_state]);
    printf("Refusals: %d\n", g_state.refusal_count);
    printf("Auth Attempts: %d\n", g_state.auth_attempts);
    printf("TPM Verified: %s\n", g_state.tpm_verified ? "YES" : "NO");
    printf("YubiKey Present: %s\n", g_state.yubikey_present ? "YES" : "NO");
    printf("YubiKey FIPS Present: %s\n", g_state.yubikey_fips_present ? "YES" : "NO");
    printf("Session Time: %ld seconds\n", time(NULL) - g_state.start_time);
    printf("============================\n\n");
}
