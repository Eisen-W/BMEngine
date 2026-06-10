cmake_minimum_required(VERSION 3.12)
project(MadokaScript-EWE)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB SOURCES CMAKE_CONFIGURE_DEPENDS
    "*.cpp"
    "base/src/*.cpp"
    "engine-mad/src/*.cpp"
    )

set(name mad)
add_executable(${name} ${SOURCES})

target_include_directories(${name} PRIVATE base/include/ engine-mad/include/)

#Linux
# if(UNIX) 
#     target_link_libraries(${name} PRIVATE m pthread dl GL raylib X11)
# endif()

#Windows
# if(WIN32)
#     target_link_libraries(${name} PRIVATE opengl32 gdi32 winmm raylib)
# endif()
