cmake_minimum_required(VERSION 3.2)
project(graphicsTest1)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "-pedantic -g -Wall -Wextra")

set(PROJECT_SOURCE_DIR src)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

set(SOURCE_FILES
        ${CMAKE_INSTALL_PREFIX}/lib/glad.c # TODO: Get glad.c from env var with $ENV{GLAD_PATH}
        ${PROJECT_SOURCE_DIR}/main.cpp
        ${PROJECT_SOURCE_DIR}/arrayBuffer.cpp
        ${PROJECT_SOURCE_DIR}/arrayObject.cpp
        ${PROJECT_SOURCE_DIR}/shader.cpp
        ${PROJECT_SOURCE_DIR}/vertexBuffer.cpp
        ${PROJECT_SOURCE_DIR}/texture.cpp
        ${PROJECT_SOURCE_DIR}/camera.cpp
        ${PROJECT_SOURCE_DIR}/stb.cpp)

add_executable(graphicsTest1 ${SOURCE_FILES})
target_compile_definitions(graphicsTest1 PUBLIC SCREEN_WIDTH=800 SCREEN_HEIGHT=800)

target_include_directories(graphicsTest1 PUBLIC ${CMAKE_INSTALL_PREFIX}/include/glad)
target_link_libraries(graphicsTest1 GL glfw)
