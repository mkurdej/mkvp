macro(mk_add_test TARGET)
    mk_add_executable(${TARGET} ${ARGN})
    add_test(
        NAME ${TARGET}
        COMMAND ${TARGET}
    )
endmacro()

add_subdirectory(iterator)
add_subdirectory(utility)
