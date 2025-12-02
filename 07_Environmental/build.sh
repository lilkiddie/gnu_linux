#!/bin/bash

set -e

if [ -f Makefile ]; then
    make distclean 2>/dev/null || true
fi

autoreconf --install --force
./configure --disable-dependency-tracking "$@"
make
make check
