Set-Variable build_directory -option Constant -value "build"

if (Test-Path $build_directory) {
    Remove-Item $build_directory -Force -Recurse
}

New-Item -ItemType directory $build_directory
Set-Location $build_directory   

$CMAKE_CXX_FLAGS = " "
$CMAKE_BOOST_ROOT = ""

if ($isWindows) {
    $generator = "Visual Studio 15 2017"
    $CMAKE_BOOST_ROOT = "-DBOOST_ROOT=`"C:\Libraries\boost_1_64_0`""

    if ($env:PLATFORM -eq "x64") {
        $generator = $generator + " Win64"
    }
} else { if ($isLinux) {
    $generator = "Unix Makefiles"

    sudo apt-get install -y libboost-all-dev 
        
    if ($env:PLATFORM -eq "x64") {
        $CMAKE_CXX_FLAGS = $CMAKE_CXX_FLAGS + " -m64"
    }
} else {
    "Unknown system!"
    return 1
}}

cmake .. -G "$generator" `
    -DUSE_ALL_TESTS:BOOL=ON `
    -DCMAKE_CXX_FLAGS="$CMAKE_CXX_FLAGS" `
    $CMAKE_BOOST_ROOT
    
cmake --build . --config $env:CONFIGURATION

Set-Location ..