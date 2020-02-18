project(cli)

add_library(libcli
  src/cli.cc)

# Define headers for this library. PUBLIC headers are used for
# compiling the library, and will be added to consumers' build
# paths.
target_include_directories(libcli PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
    PRIVATE src)



# Depend on a library that we defined in the top-level file
target_link_libraries(libcli
  libmerkle
  nlohmann_json::nlohmann_json
  stdc++fs)

# This makes the project importable from the build directory
export(TARGETS libcli FILE LibCliConfig.cmake)  

