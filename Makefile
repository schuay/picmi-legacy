bake:
	mkdir -p build
	cd build; cmake -DCMAKE_BUILD_TYPE="Release" -DCMAKE_INSTALL_PREFIX="/usr" ..; make -j3

clean:
	rm -r build


