# Define an executable
add_executable(cli
    src/main.cc)

# Define the libraries this project depends upon
target_link_libraries(cli
  cryptopp-static
  libmerkle
  stdc++fs
  )

