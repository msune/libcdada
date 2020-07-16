`libcdada` examples
-------------------

Two simple examples and one advanced are provided:

* [bbitmap](bbitmap.c): big bitmap example (bitmap > 64 bits)
* [list_u32](list_u32.c): unsigned integer `list` manipulation (equivalent `std::list<uint32_t>`)
* [map_struct](map_struct.c): `map` with a complex struct (strings) (equivalent to `std::map<my_struct_t, void*>`
* [queue](queue.c): `queue` (FIFO queue) (equivalent to `std::queue<uint32_t>`)
* [stack](stack.c): `stack` (LIFO queue) (equivalent to `std::stack<uint32_t>`)
* [str](str.c): string manipulation example
* Custom type examples using a combination of custom data structures (`set`, `data`). These are more efficient and don't have size limits:
   * [custom-gen/my_program_gen](custom-gen/): using C++ code generator `cdada-gen`
   * [custom-macro/my_program](custom-macro/): using cdada MACROs for code generation
