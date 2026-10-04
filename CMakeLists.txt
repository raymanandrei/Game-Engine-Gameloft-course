cmake_minimum_required(VERSION 3.20)
project(MiniGameEngine LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(GPU_VENDOR "Nvidia" CACHE STRING "Nvidia or ATI")
set_property(CACHE GPU_VENDOR PROPERTY STRINGS Nvidia ATI)
set(GLES_DIR ${CMAKE_SOURCE_DIR}/gles/${GPU_VENDOR})

file(GLOB ENGINE_SRC CONFIGURE_DEPENDS src/*.cpp)
set(UTIL_SRC
    Utilities/EngineMath.cpp
    Utilities/esShader.cpp
    Utilities/esUtil.cpp
    Utilities/esUtil_win.cpp
    Utilities/stdafx.cpp
    Utilities/TGA.cpp
    Utilities/pugixml-1.16/pugixml.cpp
)

add_executable(MiniGameEngine ${ENGINE_SRC} ${UTIL_SRC})

target_include_directories(MiniGameEngine PRIVATE
    src/headers 
    Utilities 
    Utilities/rapidxml 
    Utilities/pugixml-1.16 
    ${GLES_DIR})

target_include_directories(MiniGameEngine PRIVATE
    ${CMAKE_SOURCE_DIR}/gles/Nvidia
    ${CMAKE_SOURCE_DIR}/Include
    ${CMAKE_SOURCE_DIR}/Utilities
    ${CMAKE_SOURCE_DIR}/src/headers
)

target_link_libraries(MiniGameEngine PRIVATE
    ${GLES_DIR}/lib/libEGL.lib
    ${GLES_DIR}/lib/libGLESv2.lib)

add_custom_command(TARGET MiniGameEngine POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${GLES_DIR}/bin $<TARGET_FILE_DIR:MiniGameEngine>
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/assets $<TARGET_FILE_DIR:MiniGameEngine>)