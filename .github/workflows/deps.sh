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

(sudo --help > /dev/null 2>&1 ) || (apt update && apt install -y sudo software-properties-common automake autoconf libtool make) #containers
sudo -E apt-add-repository -y "ppa:ubuntu-toolchain-r/test"
sudo apt-get update
sudo apt-get install -y python3 valgrind $COMPILER
