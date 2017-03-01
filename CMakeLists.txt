cmake_minimum_required(VERSION 3.0)
project(mkvp)
enable_testing()

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set(CMAKE_DEBUG_POSTFIX "d")

macro(mk_add_executable TARGET)
    add_executable(${TARGET} ${ARGN})
    set_target_properties(${TARGET} PROPERTIES
        DEBUG_POSTFIX ${CMAKE_DEBUG_POSTFIX}
    )
    install(TARGETS ${TARGET}
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
    )
endmacro()

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/catch
)

add_subdirectory(tests)
