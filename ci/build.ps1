$ErrorActionPreference = "Stop"

Set-Variable BUILD_DIRECTORY -option Constant -value "build"

if (Test-Path $BUILD_DIRECTORY) {
    Remove-Item $BUILD_DIRECTORY -Force -Recurse
}

New-Item -ItemType directory $BUILD_DIRECTORY
Set-Location $BUILD_DIRECTORY   

$CMAKE_CXX_COMPILER = ""
$CMAKE_CXX_FLAGS = ""
$CMAKE_BOOST_ROOT = ""
$CMAKE_BUILD_CONFIGURATION = ""

if ($isWindows) {
    $GENERATOR = "Visual Studio 15 2017"
    $CMAKE_BOOST_ROOT = "-DBOOST_ROOT=`"C:\Libraries\boost_1_67_0`""

    if ($env:PLATFORM -eq "x64") {
        $GENERATOR = $GENERATOR + " Win64"
    }
} else { if ($isLinux) {
    $GENERATOR = "Unix Makefiles"
    $CMAKE_CXX_COMPILER = "-DCMAKE_CXX_COMPILER=`"/usr/bin/g++-8`""
    $CMAKE_BUILD_CONFIGURATION = "-DCMAKE_BUILD_TYPE=$env:CONFIGURATION"       
    $CMAKE_CXX_FLAGS = $CMAKE_CXX_FLAGS + " -m64"

    sudo apt-get update
    sudo apt-get install -y libboost-all-dev 
} else {
    "Unknown system!"
    return 1
}}

cmake .. -G "$GENERATOR" `
    -DUSE_ALL_TESTS:BOOL=ON `
    -DCMAKE_CXX_FLAGS="$CMAKE_CXX_FLAGS" `
    $CMAKE_CXX_COMPILER `
    $CMAKE_BUILD_CONFIGURATION `
    $CMAKE_BOOST_ROOT
    
cmake --build . --config $env:CONFIGURATION

Set-Location ..