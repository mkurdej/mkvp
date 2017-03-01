set(TEST_MAIN "${CMAKE_CURRENT_SOURCE_DIR}/main.cpp")

if(MSVC)
    add_definitions(
        -D_SCL_SECURE_NO_WARNINGS
    )
endif()

macro(mk_add_test TARGET)
    mk_add_executable(${TARGET} ${TEST_MAIN} ${ARGN})
    add_test(
        NAME ${TARGET}
        COMMAND ${TARGET}
    )
endmacro()

add_subdirectory(iterator)
add_subdirectory(utility)
