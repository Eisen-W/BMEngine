cmake_minimum_required(VERSION 3.12)
project(BlueManiacEngine)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(USE_RAYMEDIA "Enable raymedia video support" OFF)
option(USE_BOX2D   "Enable Box2D physics support" ON)

file(GLOB SOURCES CONFIGURE_DEPENDS
    "*.cpp"
    "engine/src/*.cpp"
    "engine/madokascript-engine/engine-mad/src/*.cpp"
    "engine/madokascript-engine/base/src/*.cpp"

    # add game directories here like shown below
    "game/src/main/*.cpp"
)

set(name BME)
add_executable(${name} ${SOURCES})

target_include_directories(${name} PRIVATE engine/include/ 
                                            engine/include/vendor/
                                            engine/madokascript-engine/engine-mad/include/ 
                                            engine/madokascript-engine/base/include/ 
                                            game/include/)
                                            
target_link_directories(${name} PRIVATE engine/lib/ )

if(USE_RAYMEDIA)
    target_include_directories(${name} PRIVATE engine/include/vendor/raymedia/ )
    target_sources(${name} PRIVATE engine/src/vendor/rmedia.c)
    target_link_libraries(${name} PRIVATE avcodec avformat avutil swresample swscale)
    target_compile_definitions(${name} PRIVATE USE_RAYMEDIA)
endif()

if(USE_BOX2D)
    target_include_directories(${name} PRIVATE engine/include/vendor/box2d/ )
    target_link_libraries(${name} PRIVATE box2d)
    target_compile_definitions(${name} PRIVATE USE_BOX2D)
endif()


#Linux
if(UNIX) 
    target_link_libraries(${name} PRIVATE m pthread dl GL raylib X11)
endif()

#Windows
if(WIN32)
    target_link_libraries(${name} PRIVATE opengl32 gdi32 winmm raylib)
endif()
