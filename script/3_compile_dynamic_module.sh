#!/bin/bash

pushd "vendor"
pushd "nginx-1.22.0"
rm -rf objs
CFLAGS="-g -O0" ./configure \
    --with-compat \
    --add-dynamic-module=../../src/ngx_http_waf_module
make modules
cp objs/ngx_http_waf_module.so ../../build/nginx/modules/
popd
popd    