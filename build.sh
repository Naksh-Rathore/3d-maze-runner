#!/usr/bin/env bash
set -e

# Step 1: Find vcpkg
DEFAULT_PATHS=(
    "$HOME/programming/vcpkg"
    "$HOME/vcpkg"
    "/mnt/c/vcpkg"
    "/mnt/c/Users/$USER/vcpkg"
)

VCPKG_EXE=""
for path in "${DEFAULT_PATHS[@]}"; do
    if [[ -f "$path/vcpkg" ]]; then
        VCPKG_EXE="$path/vcpkg"
        break
    elif [[ -f "$path/vcpkg.exe" ]]; then
        VCPKG_EXE="$path/vcpkg.exe"
        break
    fi
done

if [[ -z "$VCPKG_EXE" ]]; then
    echo "vcpkg not found in default locations. Searching / (this may take a while)..."
    VCPKG_EXE=$(find / -type f \( -name "vcpkg" -o -name "vcpkg.exe" \) 2>/dev/null | head -n 1)
fi

if [[ -z "$VCPKG_EXE" ]]; then
    echo "Error: Could not find vcpkg on this system."
    exit 1
fi

echo "Found vcpkg at: $VCPKG_EXE"
VCPKG_PATH="$(dirname "$VCPKG_EXE")"

# Step 3: Clean previous build
BUILD_DIR="$PWD/build"
if [[ -d "$BUILD_DIR" ]]; then
    echo "Cleaning previous build directory..."
    rm -rf "$BUILD_DIR"
fi

# Step 4: Configure CMake
echo "Configuring CMake..."
cmake -S "$PWD" -B "$BUILD_DIR" -DCMAKE_TOOLCHAIN_FILE="$VCPKG_PATH/scripts/buildsystems/vcpkg.cmake"

# Step 5: Build project
echo "Building project..."
cmake --build "$BUILD_DIR" --config Release

echo "Build completed successfully! Executable is in $BUILD_DIR/bin"
