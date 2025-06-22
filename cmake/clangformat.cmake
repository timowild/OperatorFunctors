file(GLOB_RECURSE ALL_SOURCE_FILES 
    ${CMAKE_CURRENT_SOURCE_DIR}/include/*.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/tests/*.cpp
)

add_custom_target(clang-format
    COMMAND clang-format -i -style=file ${ALL_SOURCE_FILES}
    COMMENT "Running clang-format"
    VERBATIM
)