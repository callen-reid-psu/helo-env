<#
.SYNOPSIS
    Configures and builds the C helicopter model into a shared library
    consumed by src/helo_env/native/bindings.py.

.EXAMPLE
    .\scripts\Build-Native.ps1

.EXAMPLE
    .\scripts\Build-Native.ps1 -Generator "Visual Studio 17 2022"
#>

[CmdletBinding()]
param(
    # Optional CMake generator override, e.g. "Visual Studio 17 2022" or "MinGW Makefiles".
    # If omitted, CMake picks its default based on what's on PATH.
    [string]$Generator
)

$ErrorActionPreference = "Stop"

# ---------------------------------------------------------------------------
# Sanity checks
# ---------------------------------------------------------------------------
if (-not (Get-Command cmake -ErrorAction SilentlyContinue)) {
    Write-Error @"
CMake was not found on PATH.

Install it from https://cmake.org/download/ and make sure
"Add CMake to system PATH" is selected during setup, then reopen
your terminal.
"@
    exit 1
}

$hasGcc = [bool](Get-Command gcc -ErrorAction SilentlyContinue)
$hasCl  = [bool](Get-Command cl  -ErrorAction SilentlyContinue)

if (-not $hasGcc -and -not $hasCl) {
    Write-Warning @"
No C/C++ compiler (gcc or cl) was found on PATH.
CMake configuration may fail without one. Options:

  - Install MinGW-w64 via MSYS2 (https://www.msys2.org/) and add
    its bin folder (e.g. C:\msys64\ucrt64\bin) to PATH, or
  - Install Visual Studio with the "Desktop development with C++"
    workload and run this script from a "Developer PowerShell for VS".
"@
}

# ---------------------------------------------------------------------------
# Resolve project paths (this script is expected to live in <repo>/scripts/)
# ---------------------------------------------------------------------------
$ScriptDir   = Split-Path -Parent $MyInvocation.MyCommand.Path
$ProjectRoot = Split-Path -Parent $ScriptDir
$NativeDir   = Join-Path $ProjectRoot "src\helo_env\native"
$BuildDir    = Join-Path $NativeDir "cmake-build"

New-Item -ItemType Directory -Force -Path $BuildDir | Out-Null

Write-Host "Native dir : $NativeDir"
Write-Host "Build dir  : $BuildDir"
Write-Host ""

# ---------------------------------------------------------------------------
# Configure + build
# ---------------------------------------------------------------------------
$configureArgs = @(
    "-S", $NativeDir,
    "-B", $BuildDir,
    "-DCMAKE_BUILD_TYPE=Release"
)
if ($Generator) {
    $configureArgs += @("-G", $Generator)
}

Write-Host "== Configuring =="
& cmake @configureArgs
if ($LASTEXITCODE -ne 0) { exit $LASTEXITCODE }

Write-Host ""
Write-Host "== Building =="
& cmake --build $BuildDir --config Release
if ($LASTEXITCODE -ne 0) { exit $LASTEXITCODE }

Write-Host ""
Write-Host "Native library built into: $NativeDir\build"
