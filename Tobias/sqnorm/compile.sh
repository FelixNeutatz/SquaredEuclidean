mkdir build
cd build
cmake .. -D CMAKE_BUILD_TYPE=Release  -D CMAKE_CXX_COMPILER=g++-12
make 
./sqnorm
