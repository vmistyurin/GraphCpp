Set-Variable BUILD_DIRECTORY -option Constant -value "build"

if (Test-Path $BUILD_DIRECTORY) {
    Remove-Item $BUILD_DIRECTORY -Force -Recurse
}

New-Item -ItemType directory $BUILD_DIRECTORY
Set-Location $BUILD_DIRECTORY   

$CMAKE_CXX_FLAGS = ""
$CMAKE_BOOST_ROOT = ""
$CMAKE_CXX_COMPILER = ""

$CMAKE_GENERATE_CONFIGURATION = ""
$CMAKE_BUILD_CONFIGURATION = ""

if ($isWindows) {
    $GENERATOR = "Visual Studio 15 2017"
    $CMAKE_BOOST_ROOT = "-DBOOST_ROOT=`"C:\Libraries\boost_1_67_0`""
    $CMAKE_BUILD_CONFIGURATION = "--config $env:CONFIGURATION"

    if ($env:PLATFORM -eq "x64") {
        $GENERATOR = $GENERATOR + " Win64"
    }
} else { if ($isLinux) {
    $GENERATOR = "Unix Makefiles"
    $CMAKE_CXX_COMPILER="-DCMAKE_CXX_COMPILER=`"/usr/bin/g++-8`""
    $CMAKE_GENERATE_CONFIGURATION = "-DCMAKE_BUILD_TYPE=$env:CONFIGURATION"

    sudo apt-get install -y libboost-all-dev 
        
    if ($env:PLATFORM -eq "x64") {
        $CMAKE_CXX_FLAGS = $CMAKE_CXX_FLAGS + " -m64"
    }
} else {
    "Unknown system!"
    return 1
}}

cmake .. -G "$GENERATOR" `
    -DUSE_ALL_TESTS:BOOL=ON `
    -DCMAKE_CXX_FLAGS="$CMAKE_CXX_FLAGS" `
    $CMAKE_GENERATE_CONFIGURATION `
    $CMAKE_BOOST_ROOT `
    $CMAKE_CXX_COMPILER
    
cmake --build . $CMAKE_BUILD_CONFIGURATION

Set-Location ..