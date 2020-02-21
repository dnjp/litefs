build:
	cmake -H. -Bbuild -DHUNTER_STATUS_DEBUG=ON CMAKE_C_COMPILER=gcc-8 -D CMAKE_CXX_COMPILER=g++-8 -DCMAKE_INSTALL_PREFIX=./install && cd build && make
install:
	cd build && make && make install && sudo cp ../install/bin/lfs /usr/local/bin/lfs
uninstall:
	sudo rm /usr/local/bin/lfs
clean:
	rm -rf build install
