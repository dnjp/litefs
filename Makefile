build:
	cmake -H. -Bbuild -DHUNTER_STATUS_DEBUG=ON && cd build && make
clean:
	rm -rf build
