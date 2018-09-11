Set-Variable build_directory -option Constant -value "build"

Set-Location $build_directory  
Set-Location "build"

if ($isWindows) {
    Set-Location $env:CONFIGURATION
} else { if ($isLinux) {
} else {
    "Unknown system!"
}}

./unit_tests