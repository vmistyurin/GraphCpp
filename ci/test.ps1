Set-Variable build_directory -option Constant -value "build"

Set-Location $build_directory  
Set-Location "build"

$configuration

if ($isWindows) {
    Set-Location $configuration
} else { if ($isLinux) {
} else {
    "Unknown system!"
}}

./unit_tests