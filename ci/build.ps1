Set-Variable build_directory -option Constant -value "build"

if (Test-Path $build_directory) {
    Remove-Item $build_directory -Force -Recurse
}

New-Item -ItemType directory $build_directory
Set-Location $build_directory   

$CMAKE_CXX_FLAGS = " "

$configuration
$Configuration

if ($isWindows) {
    $generator = "Visual Studio 15 2017"

    if ($platform -eq "x64") {
        $generator = $generator + " Win64"
    }
} else { if ($isLinux) {
    $generator = "Unix Makefiles"

    if ($platform -eq "x64") {
        $CMAKE_CXX_FLAGS = $CMAKE_CXX_FLAGS + " -m64"
    }
} else {
    "Unknown system!"
}}

cmake .. -G "$generator" `
    -DCMAKE_CXX_FLAGS="$CMAKE_CXX_FLAGS" `
    -DUSE_ALL_TESTS:BOOL=ON `
    -DBOOST_ROOT="C:\Libraries\boost_1_64_0"
    
cmake --build . --config $configuration

Set-Location ..