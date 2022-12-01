#!/bin/bash

pushd "vendor"
pushd "nginx-1.20.1"
CFLAGS="-g -O0" ./configure           \
    --with-debug                      \
    --prefix=$(pwd)/../../build/nginx \
    --conf-path=conf/nginx.conf       \
    --error-log-path=logs/error.log   \
    --http-log-path=logs/access.log
make
make install
popd
popd