cmake_minimum_required(VERSION 3.3)
project(cosc2131_project_s3445846_s3372771)

set(CMAKE_CXX_COMPILER clang++)
# Use this on Mac
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -framework sfml-window -framework sfml-graphics -framework sfml-system")
# Use this on Linux
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -lsfml-graphics -lsfml-window -lsfml-system")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")

set(SOURCE_FILES main.cpp)
add_executable(cosc2131_project_s3445846_s3372771 ${SOURCE_FILES})