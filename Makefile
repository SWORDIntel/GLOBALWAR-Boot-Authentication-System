# GLOBALWAR Boot Authentication System - Makefile
# Builds all components of the humorous WarGames-inspired boot system

CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -D_POSIX_C_SOURCE=200809L
LDFLAGS = -lm
INCLUDES = -I./src/core -I./src/game

# Build directories
BUILD_DIR = build
SRC_CORE = src/core
SRC_GAME = src/game

# Output binaries
WOPR = $(BUILD_DIR)/wopr
CHESS = $(BUILD_DIR)/chess_hflr
ESCAPE = $(BUILD_DIR)/escape_trap
GTW = $(BUILD_DIR)/gtw

# Core object files
CORE_OBJS = $(BUILD_DIR)/state_machine.o \
            $(BUILD_DIR)/tpm_handler.o \
            $(BUILD_DIR)/yubikey_handler.o \
            $(BUILD_DIR)/auth.o \
            $(BUILD_DIR)/audio_system.o

# All targets (build main WOPR only by default)
all: $(BUILD_DIR) $(WOPR)

# Create build directory
$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)
	@echo "Created build directory"

# Main WOPR executable (combines all modules)
$(WOPR): $(SRC_CORE)/main.c $(CORE_OBJS) $(BUILD_DIR)/chess_hflr.o $(BUILD_DIR)/escape_trap.o $(BUILD_DIR)/gtw.o
	@echo "Building WOPR main system..."
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $^ $(LDFLAGS)
	@echo "✓ WOPR system built successfully"

# Individual game executables (for testing)
$(CHESS): $(SRC_GAME)/chess_hflr.c $(BUILD_DIR)/audio_system.o
	@echo "Building Chess Hell..."
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $^ $(LDFLAGS)
	@echo "✓ Chess Hell built"

$(ESCAPE): $(SRC_GAME)/escape_trap.c $(BUILD_DIR)/audio_system.o
	@echo "Building Escape Trap..."
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $^ $(LDFLAGS)
	@echo "✓ Escape Trap built"

$(GTW): $(SRC_GAME)/gtw.c $(BUILD_DIR)/audio_system.o
	@echo "Building Global Thermonuclear War..."
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $^ $(LDFLAGS)
	@echo "✓ GTW built"

# Core module object files
$(BUILD_DIR)/state_machine.o: $(SRC_CORE)/state_machine.c
	@echo "Compiling state machine..."
	$(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $<

$(BUILD_DIR)/tpm_handler.o: $(SRC_CORE)/tpm_handler.c
	@echo "Compiling TPM handler..."
	$(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $<

$(BUILD_DIR)/yubikey_handler.o: $(SRC_CORE)/yubikey_handler.c
	@echo "Compiling YubiKey handler..."
	$(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $<

$(BUILD_DIR)/auth.o: $(SRC_CORE)/auth.c
	@echo "Compiling authentication module..."
	$(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $<

$(BUILD_DIR)/audio_system.o: $(SRC_CORE)/audio_system.c
	@echo "Compiling audio system..."
	$(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $<

# Game module object files
$(BUILD_DIR)/chess_hflr.o: $(SRC_GAME)/chess_hflr.c
	@echo "Compiling chess game module..."
	$(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $<

$(BUILD_DIR)/escape_trap.o: $(SRC_GAME)/escape_trap.c
	@echo "Compiling escape trap module..."
	$(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $<

$(BUILD_DIR)/gtw.o: $(SRC_GAME)/gtw.c
	@echo "Compiling GTW module..."
	$(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $<

# Clean build artifacts
clean:
	@echo "Cleaning build directory..."
	@rm -rf $(BUILD_DIR)
	@echo "✓ Clean complete"

# Run the WOPR system (requires permissions for audio)
run: $(WOPR)
	@echo ""
	@echo "╔════════════════════════════════════════════════════════════╗"
	@echo "║                                                            ║"
	@echo "║          STARTING GLOBALWAR BOOT SYSTEM                    ║"
	@echo "║                                                            ║"
	@echo "║  Note: Audio features require root for PC speaker access  ║"
	@echo "║  Run with: sudo make run                                   ║"
	@echo "║                                                            ║"
	@echo "╚════════════════════════════════════════════════════════════╝"
	@echo ""
	@sleep 2
	$(WOPR)

# Test individual games
test-chess: $(CHESS)
	@echo "Testing Chess Hell (Warning: Frustrating!)"
	$(CHESS)

test-escape: $(ESCAPE)
	@echo "Testing Escape Trap"
	$(ESCAPE)

test-gtw: $(GTW)
	@echo "Testing Global Thermonuclear War"
	$(GTW)

# Install (copies to /boot/GLOBALWAR - requires root)
install: all
	@echo "Installing to /boot/GLOBALWAR..."
	@sudo mkdir -p /boot/GLOBALWAR/bin
	@sudo cp $(WOPR) /boot/GLOBALWAR/bin/
	@sudo cp $(CHESS) /boot/GLOBALWAR/bin/
	@sudo cp $(ESCAPE) /boot/GLOBALWAR/bin/
	@sudo cp $(GTW) /boot/GLOBALWAR/bin/
	@echo "✓ Installation complete"
	@echo ""
	@echo "Note: This is a demonstration system."
	@echo "For actual boot integration, see docs/IMPLEMENTATION_GUIDE.md"

# Help target
help:
	@echo ""
	@echo "GLOBALWAR Boot Authentication System - Build System"
	@echo ""
	@echo "Available targets:"
	@echo "  make all        - Build all components (default)"
	@echo "  make wopr       - Build main WOPR system only"
	@echo "  make chess      - Build Chess Hell standalone"
	@echo "  make escape     - Build Escape Trap standalone"
	@echo "  make gtw        - Build GTW standalone"
	@echo "  make run        - Build and run WOPR system"
	@echo "  make test-*     - Run individual game tests"
	@echo "  make clean      - Remove build artifacts"
	@echo "  make install    - Install to /boot/GLOBALWAR (requires sudo)"
	@echo "  make help       - Show this help message"
	@echo ""
	@echo "Authentication Path (to successfully boot):"
	@echo "  1. Refuse to play game 4+ times (say 'N')"
	@echo "  2. Enter backdoor code: JOSHUA, FALKEN, or CPE1704TKS"
	@echo "  3. Enter password: PENCIL or TICTHREE"
	@echo "  4. Enter ZFS passphrase"
	@echo ""
	@echo "Secret Paths:"
	@echo "  - Type 'XYZZY' during dialogue to enter Escape Trap"
	@echo "  - Type backwards quote to escape: YALP OT TON SI EVOM GNINNOW YLNO EHT"
	@echo "  - Win GTW game with <50M casualties for honeypot"
	@echo ""

.PHONY: all clean run test-chess test-escape test-gtw install help
