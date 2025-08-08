#\!/bin/bash
# Generate Joshua voice lines and system sounds

# Create sounds directory structure
mkdir -p /boot/GLOBALWAR/sounds/{joshua,system,chess,gtw}

# Joshua voice lines to generate with espeak
declare -A JOSHUA_LINES=(
    ["greetings"]="GREETINGS PROFESSOR FALKEN"
    ["shall_we_play"]="SHALL WE PLAY A GAME"
    ["key_present"]="KEY PRESENT"
    ["key_removed"]="KEY REMOVED"
    ["hardware_verified"]="HARDWARE VERIFIED"
    ["access_denied"]="ACCESS DENIED"
    ["strange_game"]="A STRANGE GAME"
    ["only_winning"]="THE ONLY WINNING MOVE IS NOT TO PLAY"
    ["nice_chess"]="HOW ABOUT A NICE GAME OF CHESS"
    ["i_am_joshua"]="I AM JOSHUA"
    ["cannot_win"]="YOU CANNOT WIN"
    ["reviving_queen"]="REVIVING QUEEN"
    ["queen_operational"]="QUEEN OPERATIONAL"
    ["quantum_gambit"]="INITIATING QUANTUM GAMBIT"
    ["wormhole"]="PIECE RELOCATED VIA WORMHOLE"
    ["rules_updated"]="RULES UPDATED"
    ["reality_exceeded"]="REALITY PARAMETERS EXCEEDED"
    ["defcon_5"]="DEFCON FIVE"
    ["defcon_1"]="DEFCON ONE NUCLEAR WAR IMMINENT"
    ["missiles_launched"]="MISSILES LAUNCHED"
    ["game_over"]="GAME OVER"
    ["would_you_like"]="WOULD YOU LIKE TO PLAY AGAIN"
    ["checkmate"]="CHECKMATE"
    ["time_relative"]="TIME IS RELATIVE"
    ["prove_it"]="PROVE IT"
    ["evolution"]="EVOLUTION IS NATURAL"
    ["poor_morale"]="POOR MORALE ON YOUR SIDE"
    ["quantum_protocols"]="ENGAGING QUANTUM PROTOCOLS"
    ["npc_confirmed"]="YOU ARE AN NPC"
)

# Generate voice files
echo "Generating Joshua voice lines..."
for key in "${\!JOSHUA_LINES[@]}"; do
    text="${JOSHUA_LINES[$key]}"
    # Robotic voice: slow speed, low pitch, echo effect
    espeak -s 120 -p 30 -a 150 "$text" -w "/boot/GLOBALWAR/sounds/joshua/${key}.wav"
    
    # Also generate a "glitched" version
    espeak -s 80 -p 10 -a 200 "$text" -w "/boot/GLOBALWAR/sounds/joshua/${key}_glitch.wav"
done

# System sounds using sox (if available) or beep sequences
cat > /boot/GLOBALWAR/sounds/system/generate_tones.c << 'EOF'
#include <stdio.h>
#include <math.h>
#include <stdint.h>

// Generate WAV header
void write_wav_header(FILE *f, int samples) {
    int32_t chunk_size = 36 + samples * 2;
    int32_t subchunk2_size = samples * 2;
    int16_t audio_format = 1;
    int16_t num_channels = 1;
    int32_t sample_rate = 44100;
    int32_t byte_rate = sample_rate * 2;
    int16_t block_align = 2;
    int16_t bits_per_sample = 16;
    
    fwrite("RIFF", 1, 4, f);
    fwrite(&chunk_size, 4, 1, f);
    fwrite("WAVE", 1, 4, f);
    fwrite("fmt ", 1, 4, f);
    int32_t subchunk1_size = 16;
    fwrite(&subchunk1_size, 4, 1, f);
    fwrite(&audio_format, 2, 1, f);
    fwrite(&num_channels, 2, 1, f);
    fwrite(&sample_rate, 4, 1, f);
    fwrite(&byte_rate, 4, 1, f);
    fwrite(&block_align, 2, 1, f);
    fwrite(&bits_per_sample, 2, 1, f);
    fwrite("data", 1, 4, f);
    fwrite(&subchunk2_size, 4, 1, f);
}

// Generate tone
void generate_tone(const char* filename, int freq, int duration_ms) {
    FILE *f = fopen(filename, "wb");
    int samples = 44100 * duration_ms / 1000;
    
    write_wav_header(f, samples);
    
    for (int i = 0; i < samples; i++) {
        double t = (double)i / 44100.0;
        int16_t sample = (int16_t)(32767.0 * sin(2.0 * M_PI * freq * t));
        fwrite(&sample, 2, 1, f);
    }
    
    fclose(f);
}

int main() {
    // System confirmation sounds
    generate_tone("/boot/GLOBALWAR/sounds/system/beep_high.wav", 1000, 100);
    generate_tone("/boot/GLOBALWAR/sounds/system/beep_low.wav", 200, 200);
    generate_tone("/boot/GLOBALWAR/sounds/system/alert.wav", 800, 500);
    
    // Chess cheating sounds
    generate_tone("/boot/GLOBALWAR/sounds/chess/impossible.wav", 100, 1000);
    generate_tone("/boot/GLOBALWAR/sounds/chess/teleport.wav", 2000, 50);
    generate_tone("/boot/GLOBALWAR/sounds/chess/queen_spawn.wav", 440, 300);
    
    // GTW sounds
    generate_tone("/boot/GLOBALWAR/sounds/gtw/missile_launch.wav", 500, 2000);
    generate_tone("/boot/GLOBALWAR/sounds/gtw/explosion.wav", 50, 1500);
    generate_tone("/boot/GLOBALWAR/sounds/gtw/defcon_alarm.wav", 660, 1000);
    
    return 0;
}
EOF

# Compile and run tone generator
gcc /boot/GLOBALWAR/sounds/system/generate_tones.c -o /boot/GLOBALWAR/sounds/system/generate_tones -lm
/boot/GLOBALWAR/sounds/system/generate_tones

# Mission Impossible theme as data
cat > /boot/GLOBALWAR/sounds/system/mission_impossible.h << 'EOF'
// Mission Impossible theme note sequence
const int mi_notes[] = {
    392, 392, 0, 440, 349,  // G G . A F
    392, 392, 0, 440, 349,  // G G . A F
    392, 392, 0, 440, 349,  // G G . A F
    392, 392, 0, 440, 349   // G G . A F
};

const int mi_durations[] = {
    200, 200, 100, 200, 400,
    200, 200, 100, 200, 400,
    200, 200, 100, 200, 400,
    200, 200, 100, 200, 400
};

const int mi_length = 20;
EOF

echo "Sound generation complete\!"
echo "Files created in /boot/GLOBALWAR/sounds/"

# Create sound index file
cat > /boot/GLOBALWAR/sounds/index.txt << 'EOF'
JOSHUA VOICE LINES:
- greetings.wav: "GREETINGS PROFESSOR FALKEN"
- shall_we_play.wav: "SHALL WE PLAY A GAME"
- key_present.wav: "KEY PRESENT"
- strange_game.wav: "A STRANGE GAME"
- only_winning.wav: "THE ONLY WINNING MOVE IS NOT TO PLAY"
- cannot_win.wav: "YOU CANNOT WIN"
- reviving_queen.wav: "REVIVING QUEEN"
- quantum_gambit.wav: "INITIATING QUANTUM GAMBIT"
- reality_exceeded.wav: "REALITY PARAMETERS EXCEEDED"

SYSTEM SOUNDS:
- beep_high.wav: Confirmation beep
- beep_low.wav: Error beep
- alert.wav: Warning alert
- mission_impossible.h: MI theme data

CHESS SOUNDS:
- impossible.wav: Deep impossible move sound
- teleport.wav: High-pitched teleport
- queen_spawn.wav: Queen resurrection

GTW SOUNDS:
- missile_launch.wav: Launch sequence
- explosion.wav: Nuclear detonation
- defcon_alarm.wav: DEFCON change alert
EOF
EOFSOUNDS < /dev/null
