#!/bin/bash

set -e

if [ "${1}" == "gcc" ]; then
	COMPILER="gcc-${2} g++-${2}"
elif [ "${1}" == "clang" ]; then
	COMPILER="clang-${2}"
else
	echo "ERROR: invalid compiler version"
	exit 1
fi

sudo apt-get update
sudo apt-get install -y python3 valgrind autoconf automake valgrind libtool make git $COMPILER
