`libcdada` examples
-------------------

Two simple examples and one advanced are provided:

* [bbitmap](https://github.com/msune/libcdada/tree/master/examples/bbitmap.c): big bitmap example (bitmap > 64 bits)
* [list_u32](https://github.com/msune/libcdada/tree/master/examples/list_u32.c): unsigned integer `list` manipulation (equivalent `std::list<uint32_t>`)
* [map_struct](https://github.com/msune/libcdada/tree/master/examples/map_struct.c): `map` with a complex struct (strings) (equivalent to `std::map<my_struct_t, void*>`
* [queue](https://github.com/msune/libcdada/tree/master/examples/queue_u32.c): `queue` (FIFO queue) (equivalent to `std::queue<uint32_t>`)
* [stack](https://github.com/msune/libcdada/tree/master/examples/stack_u32.c): `stack` (LIFO queue) (equivalent to `std::stack<uint32_t>`)
* [str](https://github.com/msune/libcdada/tree/master/examples/str.c): string manipulation example
* Custom type examples using a combination of custom data structures (`set`, `data`). These are more efficient and don't have size limits:
   * [custom-gen/my_program_gen](https://github.com/msune/libcdada/tree/master/examples/custom-gen/): using C++ code generator `cdada-gen`
   * [custom-macro/my_program](https://github.com/msune/libcdada/tree/master/examples/custom-macro/): using cdada MACROs for code generation
