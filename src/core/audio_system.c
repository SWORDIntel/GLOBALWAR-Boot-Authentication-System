/*
 * GLOBALWAR Audio System
 * Provides PC speaker, ALSA, and TTS capabilities
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/io.h>
#include <time.h>

// PC Speaker ports
#define SPEAKER_PORT 0x61
#define TIMER_PORT 0x43
#define COUNTER_PORT 0x42

// Note frequencies (Hz)
#define NOTE_C4  262
#define NOTE_D4  294
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_G4  392
#define NOTE_A4  440
#define NOTE_B4  494
#define NOTE_C5  523

// Audio modes
typedef enum {
    AUDIO_PCSPK,    // PC Speaker only
    AUDIO_ALSA,     // ALSA if available
    AUDIO_TTS       // Text-to-speech
} audio_mode_t;

static audio_mode_t audio_mode = AUDIO_PCSPK;

/*
 * PC Speaker Functions
 */
void enable_speaker() {
    if (ioperm(SPEAKER_PORT, 1, 1) == -1) return;
    if (ioperm(TIMER_PORT, 1, 1) == -1) return;
    if (ioperm(COUNTER_PORT, 1, 1) == -1) return;
}

void beep(int freq, int duration_ms) {
    if (freq == 0) {
        usleep(duration_ms * 1000);
        return;
    }
    
    int divisor = 1193180 / freq;
    
    outb(0xB6, TIMER_PORT);
    outb(divisor & 0xFF, COUNTER_PORT);
    outb(divisor >> 8, COUNTER_PORT);
    
    outb(inb(SPEAKER_PORT) | 0x03, SPEAKER_PORT);
    usleep(duration_ms * 1000);
    outb(inb(SPEAKER_PORT) & 0xFC, SPEAKER_PORT);
}

/*
 * Mission Impossible Theme
 */
void play_mission_impossible() {
    // Iconic MI theme: "dun dun da-da, dun dun da-da..."
    int notes[] = {
        NOTE_G4, NOTE_G4, 0, NOTE_A4, NOTE_F4,
        NOTE_G4, NOTE_G4, 0, NOTE_A4, NOTE_F4,
        NOTE_G4, NOTE_G4, 0, NOTE_A4, NOTE_F4,
        NOTE_G4, NOTE_G4, 0, NOTE_A4, NOTE_F4
    };
    int durations[] = {
        200, 200, 100, 200, 400,
        200, 200, 100, 200, 400,
        200, 200, 100, 200, 400,
        200, 200, 100, 200, 400
    };
    
    for (int i = 0; i < 20; i++) {
        beep(notes[i], durations[i]);
        usleep(50000); // Small gap between notes
    }
}

/*
 * System Status Sounds
 */
void sound_yubikey_detected() {
    // Ascending confirmation tone
    beep(NOTE_C4, 100);
    beep(NOTE_E4, 100);
    beep(NOTE_G4, 100);
    beep(NOTE_C5, 200);
    
    if (audio_mode == AUDIO_TTS) {
        system("espeak -s 120 'KEY PRESENT' 2>/dev/null &");
    }
}

void sound_yubikey_removed() {
    // Descending warning tone
    beep(NOTE_C5, 100);
    beep(NOTE_G4, 100);
    beep(NOTE_E4, 100);
    beep(NOTE_C4, 200);
    
    if (audio_mode == AUDIO_TTS) {
        system("espeak -s 120 'KEY REMOVED' 2>/dev/null &");
    }
}

void sound_tpm_verified() {
    // Quick positive chirp
    beep(NOTE_A4, 50);
    beep(NOTE_C5, 50);
    
    if (audio_mode == AUDIO_TTS) {
        system("espeak -s 150 'HARDWARE VERIFIED' 2>/dev/null &");
    }
}

void sound_authentication_failed() {
    // Harsh buzzer
    for (int i = 0; i < 3; i++) {
        beep(100, 200);  // Low frequency buzz
        usleep(100000);
    }
    
    if (audio_mode == AUDIO_TTS) {
        system("espeak -s 100 'ACCESS DENIED' 2>/dev/null &");
    }
}

/*
 * Joshua Voice Lines (via espeak or pre-recorded)
 */
void joshua_speak(const char* text) {
    char cmd[512];
    
    if (audio_mode == AUDIO_TTS) {
        // Use espeak with "robotic" voice settings
        snprintf(cmd, sizeof(cmd), 
                 "espeak -s 120 -p 30 -a 150 '%s' 2>/dev/null &", 
                 text);
        system(cmd);
    } else if (audio_mode == AUDIO_ALSA) {
        // Try to play pre-recorded file
        snprintf(cmd, sizeof(cmd), 
                 "aplay /sounds/joshua/%s.wav 2>/dev/null &", 
                 text);
        system(cmd);
    }
}

/*
 * WOPR Boot Sequence Sounds
 */
void sound_boot_sequence() {
    // Classic computer boot sounds
    
    // Power on
    beep(50, 500);  // Low hum
    
    // Memory test (rapid beeps)
    for (int i = 0; i < 10; i++) {
        beep(1000 + (i * 100), 20);
        usleep(30000);
    }
    
    // System ready
    beep(NOTE_C4, 100);
    beep(NOTE_G4, 100);
    beep(NOTE_C5, 200);
}

/*
 * Modem Connection Sounds
 */
void sound_modem_dial() {
    // DTMF dialing
    int dtmf_freqs[] = {697, 770, 852, 941};
    
    for (int i = 0; i < 7; i++) {
        beep(dtmf_freqs[rand() % 4], 100);
        usleep(50000);
    }
    
    // Handshake noise
    for (int i = 0; i < 20; i++) {
        beep(rand() % 2000 + 500, 50);
    }
    
    // Connected
    beep(NOTE_A4, 500);
}

/*
 * DEFCON Alert Sounds
 */
void sound_defcon_change(int level) {
    switch(level) {
        case 5:  // Peace
            beep(NOTE_C4, 500);
            break;
        case 4:  // Increased readiness
            beep(NOTE_C4, 200);
            beep(NOTE_C4, 200);
            break;
        case 3:  // Air Force ready
            for (int i = 0; i < 3; i++) {
                beep(NOTE_E4, 150);
                usleep(100000);
            }
            break;
        case 2:  // Armed forces ready
            for (int i = 0; i < 4; i++) {
                beep(NOTE_G4, 100);
                beep(NOTE_E4, 100);
            }
            break;
        case 1:  // Nuclear war
            // Air raid siren effect
            for (int i = 0; i < 5; i++) {
                for (int freq = 400; freq < 800; freq += 10) {
                    beep(freq, 5);
                }
                for (int freq = 800; freq > 400; freq -= 10) {
                    beep(freq, 5);
                }
            }
            break;
    }
    
    if (audio_mode == AUDIO_TTS) {
        char msg[32];
        snprintf(msg, sizeof(msg), "DEFCON %d", level);
        joshua_speak(msg);
    }
}

/*
 * Initialize Audio System
 */
void init_audio() {
    enable_speaker();
    
    // Check for ALSA
    if (access("/usr/bin/aplay", X_OK) == 0) {
        audio_mode = AUDIO_ALSA;
    }
    
    // Check for espeak
    if (access("/usr/bin/espeak", X_OK) == 0) {
        audio_mode = AUDIO_TTS;
    }
    
    // Play startup sound
    sound_boot_sequence();
}
EOFAUDIO < /dev/null
