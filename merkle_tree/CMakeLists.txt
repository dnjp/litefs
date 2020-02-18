project(merkle)

add_library(libmerkle
  src/tree.cc
  src/node.cc
  src/content.cc
  src/hash.cc)

# Define headers for this library. PUBLIC headers are used for
# compiling the library, and will be added to consumers' build
# paths.
target_include_directories(libmerkle PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
    PRIVATE src)
  
# Depend on a library that we defined in the top-level file
target_link_libraries(libmerkle
    cryptopp-static)

# This makes the project importable from the build directory
export(TARGETS libmerkle FILE LibMerkleConfig.cmake)
