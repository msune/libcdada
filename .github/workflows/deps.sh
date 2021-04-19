#!/bin/sh

set -e

sudo -E apt-add-repository -y "ppa:ubuntu-toolchain-r/test"
sudo apt-get update
sudo apt-get install -y python3 valgrind gcc-4.8 g++-4.8 gcc-5 g++-5 gcc-6 g++-6 gcc-8 g++-8 gcc-9 g++-9 gcc-10 g++-10 clang
