cmake_minimum_required(VERSION 3.9.3)

set(LT_CMAKE_DIR "${CMAKE_CURRENT_LIST_DIR}/cmake" CACHE PATH "The path to the cmake directory")
list(APPEND CMAKE_MODULE_PATH ${LT_CMAKE_DIR})

# HUNTER dependencency manager
include(HunterGate)
HunterGate(
    URL "https://github.com/ruslo/hunter/archive/v0.23.211.tar.gz"
    SHA1 "c022f0c2480e835a6bafdd734035ec2071b51897"
    LOCAL
)

project(lightfs)  

# Download dependencies
hunter_add_package(cryptopp)
find_package(cryptopp CONFIG REQUIRED)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_BUILD_TYPE Debug)

# project include
include_directories("${CMAKE_SOURCE_DIR}")
# include_directories(${PROJECT_SOURCE_DIR}/src)
add_subdirectory(merkle)
add_subdirectory(cli)

  

  
