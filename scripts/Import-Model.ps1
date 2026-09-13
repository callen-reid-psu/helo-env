<#
.SYNOPSIS
    Imports MATLAB Coder generated C code into the HeloEnv native/ layout.

.DESCRIPTION
    - Copies *.c / *.cpp files (top-level only, no subfolders) -> src/helo_env/native/src/
    - Copies *.h / *.hpp files (top-level only, no subfolders) -> src/helo_env/native/include/
    - Attempts to locate tmwtypes.h from the local MATLAB install and
      copies it into native/include/ as well.

.PARAMETER CoderDir
    Path to the MATLAB Coder output directory. If omitted, a folder picker
    dialog is shown.

.PARAMETER MatlabRoot
    Optional explicit path to a MATLAB install (e.g. "C:\Program Files\MATLAB\R2024a").
    Overrides auto-detection.

.EXAMPLE
    .\scripts\Import-CoderOutput.ps1

.EXAMPLE
    .\scripts\Import-CoderOutput.ps1 -CoderDir "C:\Users\Me\matlab\MyModel_ert_rtw"

.EXAMPLE
    .\scripts\Import-CoderOutput.ps1 -CoderDir "C:\Users\Me\matlab\MyModel_ert_rtw" -MatlabRoot "C:\Program Files\MATLAB\R2024a"
#>

[CmdletBinding()]
param(
    [string]$CoderDir,
    [string]$MatlabRoot
)

$ErrorActionPreference = "Stop"

# ---------------------------------------------------------------------------
# Folder picker dialog (WinForms)
# ---------------------------------------------------------------------------
function Select-FolderDialog {
    param([string]$Title = "Select MATLAB Coder output folder")

    Add-Type -AssemblyName System.Windows.Forms
    $dialog = New-Object System.Windows.Forms.FolderBrowserDialog
    $dialog.Description = $Title
    $dialog.ShowNewFolderButton = $false

    if ($dialog.ShowDialog() -eq [System.Windows.Forms.DialogResult]::OK) {
        return $dialog.SelectedPath
    }
    return $null
}

# ---------------------------------------------------------------------------
# Args / sanity checks
# ---------------------------------------------------------------------------
if (-not $CoderDir) {
    Write-Host "No directory argument supplied, opening folder picker..."
    $CoderDir = Select-FolderDialog

    if (-not $CoderDir) {
        $CoderDir = Read-Host "Enter path to MATLAB Coder output directory"
    }
}

if (-not $CoderDir -or -not (Test-Path -LiteralPath $CoderDir -PathType Container)) {
    Write-Error "Coder output directory not found: $CoderDir"
    exit 1
}
$CoderDir = (Resolve-Path -LiteralPath $CoderDir).Path

# ---------------------------------------------------------------------------
# Resolve project paths (this script is expected to live in <repo>/scripts/)
# ---------------------------------------------------------------------------
$ScriptDir    = Split-Path -Parent $MyInvocation.MyCommand.Path
$ProjectRoot  = Split-Path -Parent $ScriptDir

$NativeDir    = Join-Path $ProjectRoot "src\helo_env\native"
$SrcDest      = Join-Path $NativeDir "src"
$IncludeDest  = Join-Path $NativeDir "include"

New-Item -ItemType Directory -Force -Path $SrcDest, $IncludeDest | Out-Null

Write-Host "Project root : $ProjectRoot"
Write-Host "Coder output : $CoderDir"
Write-Host "Dest src     : $SrcDest"
Write-Host "Dest include : $IncludeDest"
Write-Host ""

# ---------------------------------------------------------------------------
# Copy source files (top-level of CoderDir only, no recursion)
# ---------------------------------------------------------------------------
function Copy-Matches {
    param(
        [string]$Pattern,
        [string]$Dest
    )

    $files = Get-ChildItem -LiteralPath $CoderDir -File -Filter $Pattern -ErrorAction SilentlyContinue
    foreach ($f in $files) {
        Copy-Item -LiteralPath $f.FullName -Destination $Dest -Force -Verbose
    }
    Write-Host "Copied $($files.Count) file(s) matching '$Pattern' to $Dest"
}

Write-Host "== Copying .c/.cpp files (top-level only) =="
Copy-Matches -Pattern "*.c"   -Dest $SrcDest
Copy-Matches -Pattern "*.cpp" -Dest $SrcDest
Write-Host ""

Write-Host "== Copying .h/.hpp files (top-level only) =="
Copy-Matches -Pattern "*.h"   -Dest $IncludeDest
Copy-Matches -Pattern "*.hpp" -Dest $IncludeDest
Write-Host ""

# ---------------------------------------------------------------------------
# Locate MATLAB root
# ---------------------------------------------------------------------------
function Find-MatlabRoot {
    # 1. Explicit override wins
    if ($MatlabRoot) {
        return $MatlabRoot
    }

    # 2. Environment variable, if already set
    if ($env:MATLAB_ROOT) {
        return $env:MATLAB_ROOT
    }

    # 3. Ask MATLAB itself, if it's on PATH
    $matlabCmd = Get-Command matlab -ErrorAction SilentlyContinue
    if ($matlabCmd) {
        try {
            $root = & matlab -batch "disp(matlabroot)" 2>$null | Select-Object -Last 1
            $root = $root.Trim()
            if ($root -and (Test-Path -LiteralPath $root)) {
                return $root
            }
        } catch { }
    }

    # 4. Search common install locations
    $candidates = Get-ChildItem "C:\Program Files\MATLAB" -Directory -Filter "R*" -ErrorAction SilentlyContinue |
                  Sort-Object Name
    if ($candidates) {
        return $candidates[-1].FullName
    }

    return $null
}

Write-Host "== Locating tmwtypes.h =="
$MatlabRootFound = Find-MatlabRoot
$TmwtypesDest = Join-Path $IncludeDest "tmwtypes.h"

if ($MatlabRootFound) {
    Write-Host "MATLAB root candidate: $MatlabRootFound"
    $TmwtypesPath = Join-Path $MatlabRootFound "extern\include\tmwtypes.h"
    if (Test-Path -LiteralPath $TmwtypesPath) {
        Copy-Item -LiteralPath $TmwtypesPath -Destination $IncludeDest -Force -Verbose
        Write-Host "tmwtypes.h copied from MATLAB install."
    } else {
        Write-Warning "MATLAB root found but tmwtypes.h not at expected path: $TmwtypesPath"
    }
} else {
    Write-Host "MATLAB installation not found automatically."
}

# Fallback: sometimes tmwtypes.h ships alongside the coder output itself
if (-not (Test-Path -LiteralPath $TmwtypesDest)) {
    $localTmw = Get-ChildItem -LiteralPath $CoderDir -File -Filter "tmwtypes.h" -ErrorAction SilentlyContinue |
                Select-Object -First 1
    if ($localTmw) {
        Copy-Item -LiteralPath $localTmw.FullName -Destination $IncludeDest -Force -Verbose
        Write-Host "tmwtypes.h copied from coder output directory."
    }
}

if (-not (Test-Path -LiteralPath $TmwtypesDest)) {
    Write-Warning @"

tmwtypes.h could not be located automatically.
You can supply the MATLAB root manually, e.g.:

    .\scripts\Import-CoderOutput.ps1 -CoderDir <dir> -MatlabRoot "C:\Program Files\MATLAB\R2024a"

or copy it in yourself from <matlabroot>\extern\include\tmwtypes.h
"@
}

Write-Host ""
Write-Host "Done. Review $SrcDest and $IncludeDest, then update native/CMakeLists.txt if needed."
