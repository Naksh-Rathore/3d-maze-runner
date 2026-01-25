# build.ps1
# Automatically finds vcpkg, installs dependencies, configures CMake, and builds the project

# =============================
# Step 1: Find vcpkg
# =============================
$defaultPaths = @(
    "$Env:USERPROFILE\programming\vcpkg",
    "$Env:USERPROFILE\vcpkg",
    "C:\vcpkg",
    "C:\Users\$Env:USERNAME\vcpkg"
)

$VcpkgFound = $false

foreach ($path in $defaultPaths) {
    if (Test-Path "$path\vcpkg.exe") {
        $VcpkgPath = $path
        $VcpkgFound = $true
        break
    }
}

if (-not $VcpkgFound) {
    Write-Host "vcpkg not found in default locations, searching C:\ (this may take a while)..."
    $search = Get-ChildItem -Path C:\ -Recurse -Filter vcpkg.exe -ErrorAction SilentlyContinue
    if ($search) {
        $VcpkgPath = Split-Path $search[0].FullName
        $VcpkgFound = $true
    }
}

if (-not $VcpkgFound) {
    Write-Error "Could not find vcpkg.exe on this system."
    exit 1
}

Write-Host "Found vcpkg at: $VcpkgPath"

# =============================
# Step 3: Clean previous build
# =============================
$BuildDir = Join-Path -Path $PSScriptRoot -ChildPath "build"
if (Test-Path $BuildDir) {
    Write-Host "Cleaning previous build directory..."
    Remove-Item $BuildDir -Recurse -Force
}

# =============================
# Step 4: Configure CMake
# =============================
Write-Host "Configuring CMake..."
& cmake -S $PSScriptRoot -B $BuildDir -DCMAKE_TOOLCHAIN_FILE="$VcpkgPath\scripts\buildsystems\vcpkg.cmake"

if ($LASTEXITCODE -ne 0) {
    Write-Error "CMake configuration failed."
    exit 1
}

# =============================
# Step 5: Build project
# =============================
Write-Host "Building project..."
& cmake --build $BuildDir --config Release

if ($LASTEXITCODE -ne 0) {
    Write-Error "Build failed."
    exit 1
}

Write-Host "Build completed successfully! Executable is in $BuildDir\bin"
