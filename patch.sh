#!/bin/bash

ln -s libc-2.26.so libc.so.6
ln -s ld-2.26.so ld.so.2

patchelf --set-rpath $(pwd) --set-interpreter $(pwd)/ld.so.2 sandbox
