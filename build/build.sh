#!/bin/sh
cmake -DCMAKE_BUILD_TYPE=RELEASE -S ../src/base/third_party/libevent -B ../src/base/third_party/libevent/build && make -C ../src/base/third_party/libevent/build
rm -rf ../src/base/third_party/libevent/build
cmake -DCMAKE_BUILD_TYPE=RELEASE -S ../src/ -B . && make
