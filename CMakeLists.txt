cmake_minimum_required(VERSION 3.12)
project(EWE2D)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB SOURCES CMAKE_CONFIGURE_DEPENDS
    "*.cpp"
    # add game directories here like shown below
    "game/src/main/*.cpp"
    "engine/src/*.cpp"
    "engine/madokascript-engine/engine-mad/src/*.cpp"
    "engine/madokascript-engine/base/src/*.cpp")

set(name EWE)
add_executable(${name} ${SOURCES})

target_include_directories(${name} PRIVATE engine/include/ engine/madokascript-engine/engine-mad/include/ 
                                            engine/madokascript-engine/base/include/ game/include/)
target_link_directories(${name} PRIVATE engine/lib/)

#Linux
if(UNIX) 
    target_link_libraries(${name} PRIVATE m pthread dl GL raylib X11)
endif()

#Windows
if(WIN32)
    target_link_libraries(${name} PRIVATE opengl32 gdi32 winmm raylib)
endif()
