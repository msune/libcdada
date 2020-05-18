[![Build Status](https://travis-ci.org/msune/libcdata.svg?branch=master)](https://travis-ci.org/msune/libcdata)

**libcdata** - basic data structures in C (`libstdc++` wrapper)
---------------------------------------------------------------

Small library that offers basic data structures (`list`, `set`, `map`...) in a pure C API. Key features:

* Easy to use and portable
* Uses stable and well-tested `libstdc++` backend engine for most of the data structures
* No "magic" MACROs, and no need to modify your data structures (except, perhaps for `__attribute__((packed))`)
* Reasonable performance (should be comparable to `libstdc++`)

Example
-------
```c
#include <cdata/list.h>

int x, val=0;
cdata_list_t* my_list = cdata_list_create(sizeof(int));

//Add to list {10, 11, 5, 5}
x=10;
cdata_list_push_back(my_list, &x);
x=11;
cdata_list_push_back(my_list, &x);
x=5;
cdata_list_push_back(my_list, &x);
cdata_list_push_back(my_list, &x);

//Get element in position 1
cdata_list_get(my_list, 1, &val);
assert(val == 11);

//Remove duplicates {10,11,5}
cdata_list_unique(my_list);
assert(cdata_list_size(my_list) == 3);

//Add {10, 11, 5, 11}
x=11;
cdata_list_push_back(my_list, &val);

//Remove all 11s
cdata_list_remove(my_list, &val);
assert(cdata_list_size(my_list) == 2);

//Traverse list
cdata_list_traverse(my_list, my_iterator_func, opaque);
```

Don't forget to link `-lcdata`. More examples for `map` and `set` in [examples/README.md].

Documentation
-------------

`libcdata`, by default, will allow to create containers with keys (values for lists)
of 1-256 bytes, but will perform better if they are aligned to {1,2,4,8,32,64,128,256} bytes.

If you need larger keys, or cannot affort the extra padding added by default, you should
look into `libcdata`'s custom containers [TODO link].

Detailed documentation and examples:

* `list`: equivalent to `std::list` [TODO link]
* `map`: equivalent to `std::map` [TODO link]
* `set`: equivalent to `std::set` [TODO link]

Custom container example:

* TODO

`libcdata` (as `libstdc++`) is not thread-safe.

Note: `libcata` is designed to be easy to use. The performance goal is to be _as_ fast as
`libstdc++`, given that for most structures it is just a simple wrapper. If you have _hard_
performance or memory requirements, take a look at `libcdata`'s custom containers or
other libraries.

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

Author
------

Marc Sune < marcdevel (at) gmail (dot) com>
