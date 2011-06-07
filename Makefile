bake:
	mkdir -p build
	cd build; cmake -DCMAKE_BUILD_TYPE="Release" ..; make -j3

clean:
	rm -r build


