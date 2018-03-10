mkdir build
cd build

set vs_generator=Visual Studio 15 2017

if not [x%PLATFORM:x64=%]==[x%PLATFORM%] set vs_generator=%vs_generator% Win64

cmake .. -G "%vs_generator%" -DCMAKE_BUILD_TYPE=%CONFIGURATION% -DUSE_ALL_TESTS:BOOL=ON 