cmake_minimum_required(VERSION 3.12)
project(RPS)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB SOURCES CMAKE_CONFIGURE_DEPENDS
    "*.cpp"
    # add game directories here
    "engine/src/*.cpp")

set(name RPS)
add_executable(${name} ${SOURCES})

target_include_directories(${name} PRIVATE 
                                    "engine/include/"
                                    #"game/include/"
                                    )
target_link_directories(${name} PRIVATE engine/lib/)

#Linux
if(UNIX) 
    target_link_libraries(${name} PRIVATE m pthread dl GL X11 raylib)
endif()

#Windows
if(WIN32)
    target_link_libraries(${name} PRIVATE opengl32 gdi32 winmm raylib)
endif()