build:
	cmake -H. -Bbuild -DHUNTER_STATUS_DEBUG=ON -DCMAKE_INSTALL_PREFIX=./install && cd build && make
install:
	cd build && make && make install && sudo cp ../install/bin/lfs /usr/local/bin/lfs
uninstall:
	sudo rm /usr/local/bin/lfs
clean:
	rm -rf build
