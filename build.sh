mkdir -p build
cd build
cmake -DCMAKE_BUILD_TYPE=Debug -G Ninja ..
cmake --build .
