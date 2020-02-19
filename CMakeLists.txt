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

project(litefs)  

# Download dependencies
hunter_add_package(cryptopp)
hunter_add_package(nlohmann_json)
find_package(cryptopp CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_BUILD_TYPE Debug)

# project include
include_directories("${CMAKE_SOURCE_DIR}")

add_subdirectory(thirdparty/cpp-httplib)
add_subdirectory(merkle_tree)
add_subdirectory(server)
add_subdirectory(cli)
add_subdirectory(lfs)


