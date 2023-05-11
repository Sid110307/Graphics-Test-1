cmake_minimum_required(VERSION 3.2)
project(graphicsTest1)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "-Wall -Wextra")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

set(SOURCE_FILES
        ${CMAKE_PREFIX_PATH}/lib/glad.c # TODO: Get glad.c from env with $ENV{GLAD_PATH}
        src/main.cpp
        src/arrayBuffer.cpp
        src/arrayObject.cpp
        src/shader.cpp
        src/vertexBuffer.cpp
        src/texture.cpp
        src/camera.cpp
        src/stb.cpp)

add_executable(graphicsTest1 ${SOURCE_FILES})
target_include_directories(graphicsTest1 PUBLIC ${CMAKE_PREFIX_PATH}/include)
target_compile_definitions(graphicsTest1 PUBLIC SCREEN_WIDTH=1920 SCREEN_HEIGHT=1080)

find_package(glfw3 REQUIRED)
target_link_libraries(graphicsTest1 glfw)

if (UNIX AND NOT APPLE)
	target_link_libraries(graphicsTest1 GL)
endif ()
