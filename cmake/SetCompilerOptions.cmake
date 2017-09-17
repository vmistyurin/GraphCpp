macro(set_named_compiler_options PROJECT)
    if(MSVC)
      target_compile_options(${PROJECT} 
        PRIVATE "/MT$<$<CONFIG:Debug>:d>" 
        PRIVATE "-W3"
        PRIVATE "/std:c++latest"
        PRIVATE "/openmp"
      )
    else()
      target_compile_options(${PROJECT} 
        PRIVATE "-std=c++17" 
        PRIVATE "-Wall"
        PRIVATE "-fopenmp"
      )
    endif()
endmacro()

macro(set_compiler_options)
  set_named_compiler_options(${PROJECT_NAME})
endmacro()