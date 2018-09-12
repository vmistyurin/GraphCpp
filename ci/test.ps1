Set-Variable BUILD_DIRECTORY -option Constant -value "build"

Set-Location $BUILD_DIRECTORY  
Set-Location "build"

if ($isWindows) {
    Set-Location $env:CONFIGURATION
} else { if ($isLinux) {
} else {
    "Unknown system!"
    return 1
}}

./unit_tests