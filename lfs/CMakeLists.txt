project(lfs)

add_executable(lfs main.cc)

target_link_libraries(${PROJECT_NAME}
  libcli
  )

install(TARGETS lfs DESTINATION bin)
