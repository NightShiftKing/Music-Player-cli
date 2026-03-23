#!/bin/bash
# ============================================================
# install.sh — One-line installer for music-player
# Usage: curl -fsSL https://raw.githubusercontent.com/NightShiftKing/Music-Player-cli/main/install.sh | bash
# ============================================================
set -e

REPO="NightShiftKing/Music-Player-cli"
INSTALL_DIR="${HOME}/.local/bin"

# Detect OS
OS="$(uname -s)"
case "$OS" in
    Linux*)  PLATFORM="linux-amd64";;
    Darwin*) PLATFORM="macos-amd64";;
    *)       echo "Error: Unsupported OS '$OS'. Use Windows? Download from GitHub Releases."; exit 1;;
esac

# Get latest release tag
echo "Fetching latest release..."
LATEST=$(curl -fsSL "https://api.github.com/repos/${REPO}/releases/latest" | grep '"tag_name"' | sed -E 's/.*"([^"]+)".*/\1/')

if [ -z "$LATEST" ]; then
    echo "Error: Could not find a release. Make sure the repo has at least one tagged release."
    exit 1
fi

echo "Latest release: ${LATEST}"

# Download
URL="https://github.com/${REPO}/releases/download/${LATEST}/music-player-${PLATFORM}.tar.gz"
echo "Downloading music-player for ${PLATFORM}..."
curl -fsSL "$URL" -o /tmp/music-player.tar.gz

# Extract and install
mkdir -p "$INSTALL_DIR"
tar -xzf /tmp/music-player.tar.gz -C "$INSTALL_DIR"
chmod +x "${INSTALL_DIR}/music-player"
rm /tmp/music-player.tar.gz

echo ""
echo "✅ music-player installed to ${INSTALL_DIR}/music-player"

# Check if INSTALL_DIR is in PATH
if [[ ":$PATH:" != *":${INSTALL_DIR}:"* ]]; then
    echo ""
    echo "⚠  ${INSTALL_DIR} is not in your PATH."
    echo "   Add it by running:"
    echo ""
    echo "   echo 'export PATH=\"\$HOME/.local/bin:\$PATH\"' >> ~/.bashrc && source ~/.bashrc"
    echo ""
fi

echo "Run it with: music-player ~/Music"
