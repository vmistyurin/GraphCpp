macro(set_named_compiler_options PROJECT)
    if(MSVC)
      target_compile_options(${PROJECT_NAME} PRIVATE "/MT$<$<CONFIG:Debug>:d>")
      set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} \
        /std:c++latest \
        /W3 \
        /EHsc \ 
        /permissive- \ 
      ")
    else()
      
      set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} \
        -std=c++17 \
        -Wall \
        -pthread \
        -pedantic \
      ")
    endif()
endmacro()

macro(set_compiler_options)
  set_named_compiler_options(${PROJECT_NAME})
endmacro()