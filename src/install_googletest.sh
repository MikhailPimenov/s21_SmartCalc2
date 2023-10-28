git clone https://github.com/google/googletest
cd googletest
mkdir googletest_build
cd googletest_build
cmake -DCMAKE_INSTALL_PREFIX:PATH=`pwd` ../googletest
make
make install