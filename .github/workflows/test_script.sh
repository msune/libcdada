#!/bin/sh

set -e

echo "Compilers:"
echo $CC
echo $CXX

echo "Env:"
echo $CONFIG_FLAGS

echo "Building in-tree"
./autogen.sh
./configure $CONFIG_FLAGS || (cat config.log && /bin/false)
make
make maintainer-clean

echo "Building out-tree"
./autogen.sh
cd build
../configure $CONFIG_FLAGS || (cat config.log && /bin/false)
make check || ((for f in `find test/ -name "*.log"`; do cat $f; done;) && /bin/false)

echo "Running examples..."
valgrind --leak-check=full examples/bbitmap
valgrind --leak-check=full examples/list_u32
valgrind --leak-check=full examples/map_struct
valgrind --leak-check=full examples/queue_u32
valgrind --leak-check=full examples/stack_u32
valgrind --leak-check=full examples/str
valgrind --leak-check=full examples/custom_gen
valgrind --leak-check=full examples/custom_macro
valgrind --leak-check=full examples/custom_macro

echo "Installing in the system.."
sudo make install
sudo ldconfig

echo "Building examples with installed headers and libs.."
mkdir -p examples_sys && cd examples_sys
$CC ../../examples/bbitmap.c -lcdada -o bbitmap_sys
$CC ../../examples/list_u32.c -lcdada -o list_u32_sys
$CC ../../examples/map_struct.c -lcdada -o map_struct_sys
$CC ../../examples/queue_u32.c -lcdada -o queue_u32_sys
$CC ../../examples/stack_u32.c -lcdada -o stack_u32_sys
$CC ../../examples/str.c -lcdada -o str_sys
$CXX ../../examples/custom-gen/my_program_gen.c ../../examples/custom-gen/cdada.cc -lcdada -o custom_gen_sys
$CXX ../../examples/custom-macro/my_program.c ../../examples/custom-macro/cdada.cc -lcdada -o custom_macro_sys

echo "Running examples (sys)..."
valgrind --leak-check=full ./bbitmap_sys
valgrind --leak-check=full ./list_u32_sys
valgrind --leak-check=full ./map_struct_sys
valgrind --leak-check=full ./str_sys
valgrind --leak-check=full ./queue_u32_sys
valgrind --leak-check=full ./stack_u32_sys
valgrind --leak-check=full ./custom_gen_sys
valgrind --leak-check=full ./custom_macro_sys

echo "Test cdada-gen code generator (sys)..."
cdada-gen -o a.cc set:test_u552_t map:test_u552_t list:test_u552_t queue:test_u552_t stack:test_u552_t
echo "#include \"../../test/u552.h\"" >> b.cc
cat a.cc >> b.cc
$CXX -c b.cc -o b.o
$CC ../../test/combined_test.c b.o -lcdada -lstdc++ -o b
valgrind --leak-check=full ./b

echo "Test cdada.h (sys)..."
$CC ../../test/cdada_h_include.c -lcdada  -o c
valgrind --leak-check=full ./c

echo "Cleaning the house..."
cd .. && make maintainer-clean
rm -rf *
git clean -d -f
