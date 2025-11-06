#!/bin/bash
# GLOBALWAR Initramfs Integration Script
# Creates a bootable initramfs with WOPR authentication (games included!)

set -e

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
BUILD_DIR="${SCRIPT_DIR}/../build"
INITRAMFS_DIR="${SCRIPT_DIR}/../initramfs"
OUTPUT_DIR="${SCRIPT_DIR}/../output"

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

echo -e "${BLUE}"
echo "╔═══════════════════════════════════════════════════════════╗"
echo "║                                                           ║"
echo "║   GLOBALWAR Initramfs Builder                             ║"
echo "║   \"The only winning move is not to play\"                  ║"
echo "║                                                           ║"
echo "╚═══════════════════════════════════════════════════════════╝"
echo -e "${NC}"

# Check if running as root
if [ "$EUID" -ne 0 ]; then
    echo -e "${YELLOW}Warning: Not running as root. Some operations may fail.${NC}"
    echo "Consider running: sudo $0"
    read -p "Continue anyway? [y/N] " -n 1 -r
    echo
    if [[ ! $REPLY =~ ^[Yy]$ ]]; then
        exit 1
    fi
fi

# Step 1: Build WOPR if needed
echo -e "${GREEN}[1/8] Building WOPR system...${NC}"
cd "${SCRIPT_DIR}/.."
if [ ! -f "${BUILD_DIR}/wopr" ]; then
    make clean && make
else
    echo "WOPR already built (use 'make clean && make' to rebuild)"
fi

# Step 2: Create initramfs directory structure
echo -e "${GREEN}[2/8] Creating initramfs structure...${NC}"
rm -rf "${INITRAMFS_DIR}"
mkdir -p "${INITRAMFS_DIR}"/{bin,sbin,etc,proc,sys,dev,newroot,tmp,run,sounds}

# Step 3: Copy WOPR binaries
echo -e "${GREEN}[3/8] Installing WOPR components...${NC}"
cp "${BUILD_DIR}/wopr" "${INITRAMFS_DIR}/bin/"
chmod +x "${INITRAMFS_DIR}/bin/wopr"
echo "  ✓ WOPR main system installed"

# Step 4: Copy essential binaries
echo -e "${GREEN}[4/8] Installing system utilities...${NC}"

# Busybox for basic utilities
if command -v busybox &> /dev/null; then
    cp "$(which busybox)" "${INITRAMFS_DIR}/bin/"
    echo "  ✓ Busybox installed"
else
    echo -e "${YELLOW}  ⚠ Busybox not found - you'll need to provide sh, mount, etc.${NC}"
fi

# ZFS utilities (if available)
for util in zpool zfs; do
    if command -v $util &> /dev/null; then
        cp "$(which $util)" "${INITRAMFS_DIR}/sbin/"
        echo "  ✓ $util installed"
    else
        echo -e "${YELLOW}  ⚠ $util not found${NC}"
    fi
done

# Optional: espeak for TTS
if command -v espeak &> /dev/null; then
    cp "$(which espeak)" "${INITRAMFS_DIR}/bin/"
    echo "  ✓ espeak installed (for Joshua's voice)"
else
    echo "  ℹ espeak not found (audio will use beeps only)"
fi

# Step 5: Copy required libraries
echo -e "${GREEN}[5/8] Installing libraries...${NC}"
mkdir -p "${INITRAMFS_DIR}/lib" "${INITRAMFS_DIR}/lib64"

# Function to copy library and its dependencies
copy_libs() {
    local binary=$1
    echo "  Analyzing dependencies for $(basename $binary)..."

    ldd "$binary" 2>/dev/null | grep "=>" | awk '{print $3}' | while read lib; do
        if [ -f "$lib" ] && [ ! -f "${INITRAMFS_DIR}${lib}" ]; then
            mkdir -p "${INITRAMFS_DIR}$(dirname $lib)"
            cp "$lib" "${INITRAMFS_DIR}${lib}"
        fi
    done

    # Also copy ld-linux
    local ld_linux=$(ldd "$binary" 2>/dev/null | grep ld-linux | awk '{print $1}')
    if [ -n "$ld_linux" ] && [ -f "$ld_linux" ]; then
        cp "$ld_linux" "${INITRAMFS_DIR}${ld_linux}" 2>/dev/null || true
    fi
}

# Copy libs for WOPR
copy_libs "${BUILD_DIR}/wopr"

# Copy libs for system utilities
for binary in "${INITRAMFS_DIR}/bin"/* "${INITRAMFS_DIR}/sbin"/*; do
    if [ -f "$binary" ] && [ -x "$binary" ]; then
        copy_libs "$binary"
    fi
done

echo "  ✓ Libraries installed"

# Step 6: Create init script
echo -e "${GREEN}[6/8] Creating init script...${NC}"
cat > "${INITRAMFS_DIR}/init" << 'INIT_SCRIPT_EOF'
#!/bin/sh
# GLOBALWAR Initramfs Init Script
# "Shall we play a game?"

# Mount essential filesystems
mount -t proc proc /proc
mount -t sysfs sys /sys
mount -t devtmpfs dev /dev 2>/dev/null || mount -t tmpfs dev /dev

# Create device nodes if needed
[ -c /dev/null ] || mknod /dev/null c 1 3
[ -c /dev/console ] || mknod /dev/console c 5 1

# Clear screen and show boot banner
clear
echo ""
echo "╔═══════════════════════════════════════════════════════════╗"
echo "║                                                           ║"
echo "║        GLOBALWAR Defense System Initializing              ║"
echo "║                                                           ║"
echo "╚═══════════════════════════════════════════════════════════╝"
echo ""
sleep 2

# Set PATH
export PATH=/bin:/sbin:/usr/bin:/usr/sbin

# Check for emergency bypass
if grep -q "globalwar.bypass" /proc/cmdline; then
    echo ""
    echo "[EMERGENCY BYPASS DETECTED]"
    echo "[Skipping WOPR authentication]"
    echo ""
    sleep 2
else
    # Run WOPR authentication
    /bin/wopr

    # Check exit code
    if [ $? -ne 0 ]; then
        echo ""
        echo "╔════════════════════════════════════════╗"
        echo "║   AUTHENTICATION FAILED                ║"
        echo "║                                        ║"
        echo "║   System will not boot.                ║"
        echo "║                                        ║"
        echo "║   \"The only winning move is not to     ║"
        echo "║    play.\" - WOPR                       ║"
        echo "╚════════════════════════════════════════╝"
        echo ""

        # Drop to emergency shell
        echo "Dropping to emergency shell..."
        exec /bin/sh
    fi
fi

# If we get here, authentication succeeded
echo ""
echo "╔═══════════════════════════════════════════════════════════╗"
echo "║                                                           ║"
echo "║        AUTHENTICATION SUCCESSFUL                          ║"
echo "║        Mounting encrypted filesystems...                  ║"
echo "║                                                           ║"
echo "╚═══════════════════════════════════════════════════════════╝"
echo ""

# Import ZFS pool (if ZFS is being used)
if command -v zpool >/dev/null 2>&1; then
    echo "[ZFS] Importing pool..."
    zpool import -N rpool 2>/dev/null || true

    echo "[ZFS] Loading encryption keys..."
    # The ZFS passphrase was already entered in WOPR
    # In production, you'd pass it through securely
    # For now, prompt again (or use a keyfile)
    zfs load-key -a 2>/dev/null || true

    echo "[ZFS] Mounting root filesystem..."
    mount -t zfs rpool/ROOT/LONENOMAD /newroot 2>/dev/null || true
fi

# Check if root filesystem is mounted
if [ -d /newroot/bin ] || [ -d /newroot/usr ]; then
    echo ""
    echo "[SUCCESS] Root filesystem mounted"
    echo "[BOOT] Switching to real root..."
    sleep 1

    # Unmount initramfs filesystems
    umount /proc
    umount /sys
    umount /dev

    # Switch to real root
    exec switch_root /newroot /sbin/init
else
    echo ""
    echo "[ERROR] Failed to mount root filesystem"
    echo ""
    echo "Possible causes:"
    echo "  - Wrong ZFS pool name (expected: rpool/ROOT/LONENOMAD)"
    echo "  - Incorrect passphrase"
    echo "  - Pool not found"
    echo ""
    echo "Dropping to emergency shell..."
    exec /bin/sh
fi
INIT_SCRIPT_EOF

chmod +x "${INITRAMFS_DIR}/init"
echo "  ✓ Init script created"

# Step 7: Create the initramfs image
echo -e "${GREEN}[7/8] Building initramfs image...${NC}"
mkdir -p "${OUTPUT_DIR}"

cd "${INITRAMFS_DIR}"
find . -print0 | cpio --null --create --format=newc | gzip -9 > "${OUTPUT_DIR}/globalwar-initramfs.img"
cd - > /dev/null

INITRAMFS_SIZE=$(du -h "${OUTPUT_DIR}/globalwar-initramfs.img" | cut -f1)
echo "  ✓ Initramfs created: ${OUTPUT_DIR}/globalwar-initramfs.img (${INITRAMFS_SIZE})"

# Step 8: Create installation instructions
echo -e "${GREEN}[8/8] Creating installation instructions...${NC}"
cat > "${OUTPUT_DIR}/INSTALL.txt" << 'INSTALL_EOF'
╔═══════════════════════════════════════════════════════════╗
║                                                           ║
║   GLOBALWAR Initramfs Installation Instructions          ║
║                                                           ║
╚═══════════════════════════════════════════════════════════╝

Your GLOBALWAR initramfs has been built successfully!

FILE CREATED:
  output/globalwar-initramfs.img

INSTALLATION OPTIONS:

Option 1: Direct Boot (Testing)
--------------------------------
Copy to /boot and configure bootloader:

  sudo cp output/globalwar-initramfs.img /boot/

Then edit your bootloader config:

GRUB:
  Edit /etc/default/grub:
    GRUB_CMDLINE_LINUX="... initrd=/boot/globalwar-initramfs.img"
  Run: sudo update-grub

systemd-boot:
  Edit /boot/loader/entries/your-entry.conf:
    initrd /globalwar-initramfs.img

Option 2: Unified Kernel Image (UKI)
-------------------------------------
Create a single bootable EFI file:

  sudo ukify build \
    --linux=/boot/vmlinuz-$(uname -r) \
    --initrd=output/globalwar-initramfs.img \
    --cmdline="root=ZFS=rpool/ROOT/LONENOMAD quiet" \
    --output=/boot/efi/EFI/Linux/globalwar.efi

Then boot from this EFI file.

Option 3: Emergency Bypass
---------------------------
If you get locked out, add kernel parameter:
  globalwar.bypass

This skips WOPR authentication (for emergencies only!)

AUTHENTICATION REMINDERS:

Correct Path (to boot successfully):
  1. Refuse to play game 4+ times (press 'N')
  2. Enter backdoor code: JOSHUA, FALKEN, or CPE1704TKS
  3. Enter password: PENCIL or TICTHREE
  4. Enter your ZFS passphrase

Alternative Paths:
  - Type 'XYZZY' during dialogue → Enter trap games
  - Win GTW with <50M casualties → Honeypot
  - Type backwards quote from trap → Emergency escape

Easter Eggs:
  - HELP, GAMES, DAVID, MCKITTRICK, NORAD

IMPORTANT NOTES:

⚠️  This is a DEMONSTRATION system with GAMES INTACT
⚠️  All authentication is logged to /tmp/globalwar*.log
⚠️  Hardware checks are in SIMULATION mode by default
⚠️  For production, review and modify security settings

🎮  The games are intentionally frustrating - that's the point!
🎮  Chess is impossible to win (5 levels of cheating)
🎮  Trap games are rigged (but escapable via secret)

TROUBLESHOOTING:

Stuck in Chess Hell?
  → You need a YubiKey OR type 'XYZZY' to escape

Can't remember backdoor codes?
  → Check this file or README.md

Want to skip WOPR for testing?
  → Add 'globalwar.bypass' to kernel command line

HAVE FUN AND REMEMBER:
"The only winning move is not to play."
INSTALL_EOF

echo "  ✓ Installation instructions created: ${OUTPUT_DIR}/INSTALL.txt"

# Summary
echo ""
echo -e "${GREEN}╔═══════════════════════════════════════════════════════════╗${NC}"
echo -e "${GREEN}║                                                           ║${NC}"
echo -e "${GREEN}║   BUILD COMPLETE!                                         ║${NC}"
echo -e "${GREEN}║                                                           ║${NC}"
echo -e "${GREEN}╚═══════════════════════════════════════════════════════════╝${NC}"
echo ""
echo "Created files:"
echo "  📦 ${OUTPUT_DIR}/globalwar-initramfs.img (${INITRAMFS_SIZE})"
echo "  📄 ${OUTPUT_DIR}/INSTALL.txt"
echo ""
echo "Next steps:"
echo "  1. Read: ${OUTPUT_DIR}/INSTALL.txt"
echo "  2. Test in VM before deploying to real hardware"
echo "  3. Remember: Refuse to play 4 times, then use backdoor"
echo ""
echo -e "${YELLOW}Authentication Cheat Sheet:${NC}"
echo "  Backdoor codes: JOSHUA, FALKEN, CPE1704TKS"
echo "  Passwords: PENCIL, TICTHREE"
echo "  Emergency bypass: Add 'globalwar.bypass' to kernel cmdline"
echo ""
echo -e "${BLUE}\"A strange game. The only winning move is not to play.\"${NC}"
echo ""
