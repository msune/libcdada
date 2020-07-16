[![Build Status](https://travis-ci.org/msune/libcdada.svg?branch=master)](https://travis-ci.org/msune/libcdada)

**libcdada** - basic data structures in C (`libstdc++` wrapper)
---------------------------------------------------------------

Small library that offers basic data structures (`list`, `set`, `map`...) in a pure C API for user-space applications. Key features:

* Easy to use, portable
* No "magic" MACROs, and no need to modify your data structures (except, perhaps, for `__attribute__((packed))`)
* Stable and well-tested backend engine (`libstdc++`) for most of the data structures
* Reasonable performance - comparable to `libstdc++`

Example
-------
```c
#include <cdada/list.h>

int x, val=0;
cdada_list_t* my_list = cdada_list_create(int);

//Add to list {10, 11, 5, 5}
x=10;
cdada_list_push_back(my_list, &x);
x=11;
cdada_list_push_back(my_list, &x);
x=5;
cdada_list_push_back(my_list, &x);
cdada_list_push_back(my_list, &x);

//Get element in position 1
cdada_list_get(my_list, 1, &val);
assert(val == 11);

//First/last
cdada_list_first(my_list, &val);
assert(val == 10);

//Add {10, 11, 5, 11}
x=11;
cdada_list_push_back(my_list, &val);

//Traverse list
cdada_list_traverse(my_list, my_iterator_func, opaque);
```

```c
#include <cdada/str.h>

cdada_str_t* s = cdada_str_create("One string");
fprintf(stdout, "%s\n", cdada_str(s));

//Reset
cdada_str_set(s, "This is a test");
fprintf(stdout, "%s\n", cdada_str(s));

cdada_str_append(s, " simple string");

cdada_str_lower(s);
cdada_str_replace_all(s, "test ", "");

//Will print: "this is a simple string"
fprintf(stdout, "%s\n", cdada_str(s));
```

More examples for `map` and `set` and custom containers in the [examples](examples/) folder.

Documentation
-------------

Public API:

* [bbitmap.h](include/cdada/bbitmap.h): big bitmap (> 64bit)
* [list.h](include/cdada/list.h): an ordered list of objects (equivalent to `std::list`)
* [map.h](include/cdada/map.h): a hashmap {key -> value}, with unique keys (equivalent to `std::map`)
* [queue.h](include/cdada/queue.h): queue (FIFO queue) implementation (equivalent to `std::queue`)
* [set.h](include/cdada/set.h): a set of objects (equivalent to `std::set`)
* [stack.h](include/cdada/stack.h): stack (LIFO queue) implementation (equivalent to `std::stack`)
* [str.h](include/cdada/str.h): a string (equivalent to `std::string`)
* [util.h](include/cdada/util.h): error codes and utility functions

`libcdada` is not thread-safe.

Default containers support 1-256 bytes keys (values for lists), but they will
perform better when aligned to {1,2,4,8,32,64,128,256} bytes - keys are padded to
a power of 2 bytes.

#### Custom containers

For larger keys (any length), optimal memory usage and performance take a look at `libcdada`'s
**[custom containers](doc/Custom.md)**.

#### Benchmarking

Take a look at **[benchmarking](doc/Benchmarks.md)** for an rough idea
of the overhead of `libcdada` compared to `libstdc++`.

Installation
------------

Requirements:

* POSIX system
* C and C++ gcc compatible compilers (gcc, icc, clang...)
* Automake
* Autoconf
* Libtool
* libstdc++ (C++98)

```
sh autogen.sh
cd build
../configure
sudo make install
```

#### Windows support

The library solely depends on `libstdc++`, so it should be very easy to port it
to Windows. If you are interested, consider submitting a PR.

Author
------

Marc Sune < marcdevel (at) gmail (dot) com>
