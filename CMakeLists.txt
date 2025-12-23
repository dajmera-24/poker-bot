cmake_minimum_required(VERSION 3.16)
project(MyProject)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Automatically find all .cpp files in src/
file(GLOB_RECURSE SOURCES "src/*.cpp")

# Create executable from all src/ files
add_executable(myprog ${SOURCES})

# Tell compiler where your include/ headers are
target_include_directories(myprog PRIVATE 
    include/
    eigen-5.0.0/
)