cd containmentaction-favorites-0.2
mkdir build
cd build
cmake -DCMAKE_INSTALL_PREFIX=`kde4-config --prefix` .. && make -j8 && make install

