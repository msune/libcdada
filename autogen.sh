#!/bin/sh

export AUTOMAKE="automake --foreign -a"
autoreconf -f -i

echo "Cloning dependencies..."
git submodule update --init --recursive
echo "Done"
