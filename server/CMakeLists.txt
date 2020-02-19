project(server)

add_library(libserver
  src/server.cc
  )

# Define headers for this library. PUBLIC headers are used for
# compiling the library, and will be added to consumers' build
# paths.
target_include_directories(libserver PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
    PRIVATE src)



# Depend on a library that we defined in the top-level file
target_link_libraries(libserver
  httplib)

# This makes the project importable from the build directory
export(TARGETS libserver FILE LibServerConfig.cmake)  

