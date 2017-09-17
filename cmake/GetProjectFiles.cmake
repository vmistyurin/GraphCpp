function(get_project_files FILES)
    list(APPEND FILES_LIST "")

    file(GLOB_RECURSE PROJECT_FILES
      ${CMAKE_CURRENT_SOURCE_DIR}/*.hpp    
      ${CMAKE_CURRENT_SOURCE_DIR}/*.h
      ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
      ${CMAKE_CURRENT_SOURCE_DIR}/*.c
    )

    foreach(PROJECT_FILE ${PROJECT_FILES})
      file(RELATIVE_PATH FILTER_PATH ${CMAKE_CURRENT_SOURCE_DIR} ${PROJECT_FILE})

      list(APPEND FILES_LIST ${PROJECT_FILE})

      string(REGEX REPLACE "(.*)(/[^/]*)$" "\\1" FILTER_PATH ${FILTER_PATH})
      string(REPLACE / \\ FILTER_PATH ${FILTER_PATH})
      source_group("${FILTER_PATH}" FILES ${PROJECT_FILE})
    endforeach()

    set(${FILES} ${FILES_LIST} PARENT_SCOPE)
endfunction()