/*
 * GLOBALWAR Audio System Header
 */

#ifndef AUDIO_SYSTEM_H
#define AUDIO_SYSTEM_H

// Initialize audio system
void init_audio();

// Basic beep function
void beep(int freq, int duration_ms);

// Joshua speech
void joshua_speak(const char* text);

// Musical themes
void play_mission_impossible();

// System status sounds
void sound_yubikey_detected();
void sound_yubikey_removed();
void sound_tpm_verified();
void sound_authentication_failed();

// Boot sounds
void sound_boot_sequence();
void sound_modem_dial();

// DEFCON alerts
void sound_defcon_change(int level);

#endif // AUDIO_SYSTEM_H
