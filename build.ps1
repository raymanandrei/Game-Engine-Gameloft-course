param (
    [string]$Config = "Debug",
    [string]$BuildDir = "build",
    [switch]$Clean,
    [switch]$Rebuild,
    [switch]$Run
)

if ($Clean -or $Rebuild) {
    if (Test-Path $BuildDir) {
        Write-Host "Deleting $BuildDir..." -ForegroundColor Red
        Remove-Item -Recurse -Force $BuildDir
    }
    if ($Clean) { 
      exit 
    }
}

Write-Host "Configuring CMake ($Config - Win32)..." -ForegroundColor Cyan
cmake -B $BuildDir -S . -A Win32 -DCMAKE_BUILD_TYPE=$Config

if ($LASTEXITCODE -ne 0) {
    Write-Error "Configuring CMake failed"
    exit $LASTEXITCODE
}

Write-Host "Compiling project" -ForegroundColor Green
cmake --build $BuildDir --config $Config

if ($LASTEXITCODE -ne 0) {
    Write-Error "Compile Error"
    exit $LASTEXITCODE
}

if ($Run) {
    $ExeDir = ".\$BuildDir\$Config"
    $ExePath = ".\$BuildDir\$Config\MiniGameEngine.exe"
    if (Test-Path $ExePath) {
        Write-Host "Launghing $ExePath..." -ForegroundColor Cyan
        Start-Process -FilePath $ExePath -WorkingDirectory $ExeDir
    } else {
        Write-Error "Executable was not found $ExePath"
    }
}