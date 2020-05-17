/*
Copyright (c) 2020, Marc Sune Clos
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

* Redistributions of source code must retain the above copyright notice, this
  list of conditions and the following disclaimer.

* Redistributions in binary form must reproduce the above copyright notice,
  this list of conditions and the following disclaimer in the documentation
  and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#ifndef __CDATA_MAP_H__
#define __CDATA_MAP_H__

#include <stdbool.h>
#include <stdint.h>
#include <cdata/utils.h>

/**
* @file cdata_map.h
* @author Marc Sune<marcdevel (at) gmail.com>
*
* @brief Map {key, value} data structure. Wraps std::map data structure
*/

/**
* cdata map structure
*/
typedef void cdata_map_t;

//In case it's included from C++
BEGIN_DECLS

/**
* cdata map structure iterator
*
* @param map Map ptr
* @param key Key (immutable)
* @param val Value
* @param opaque A pointer to an opaque object tat will be passed to the callback
*/
typedef void (*cdata_map_it)(const cdata_map_t* map, const void* key,
						void* val,
						void* opaque);

/**
* @internal Function pointer struct for autogen types
*/
typedef struct{
	void (*create)(cdata_map_t* map);
	void (*destroy)(cdata_map_t* map);
	void (*clear)(cdata_map_t* map);
	bool (*empty)(cdata_map_t* map);
	uint32_t (*size)(cdata_map_t* map);
	int (*insert)(cdata_map_t* map, const void* key, void* val);
	int (*erase)(cdata_map_t* map, const void* key);
	int (*find)(cdata_map_t* map, const void* key, void** val);
	int (*traverse)(cdata_map_t* map, cdata_map_it f, void* opaque);
	int (*rtraverse)(cdata_map_t* map, cdata_map_it f, void* opaque);
}__cdata_map_ops_t;

/**
* @brief Create and initialize a map data structure
*
* Allocate and initialize a map structure (std::map). For key sizes below 8
* bytes, the optimal key sizes are {1,2,4 or 8 bytes}.
*/
cdata_map_t* cdata_map_create(const uint16_t key_size);

/**
* @internal Create and initialize map with ops
*/
cdata_map_t* __cdata_map_create(const uint16_t key_size,
						__cdata_map_ops_t* ops);

/**
* Destroy a map structure
*/
int cdata_map_destroy(cdata_map_t* map);

/**
* Clears the contents of the map
*/
int cdata_map_clear(cdata_map_t* map);

/**
* Traverse map
*
* @param map Map
* @param func Traverse function for this specific map
* @param opaque User data (opaque ptr)
*/
int cdata_map_traverse(const cdata_map_t* map, cdata_map_it func,
							void* opaque);

/**
* Reverse traverse map
*
* @param map Map
* @param func Traverse function for this specific map
* @param opaque User data (opaque ptr)
*/
int cdata_map_rtraverse(const cdata_map_t* map, cdata_map_it func,
							void* opaque);

//Map properties

/**
* Is the map empty
*/
bool cdata_map_empty(cdata_map_t* map);

/**
* Return the size (number of elements) in the map
*/
uint32_t cdata_map_size(cdata_map_t* map);

//Element manipulation

/**
* Inserts an element in the map
*
* @param map Map pointer
* @param key Key. The key type _must_ have all bytes initialized
* @param val Pointer to the value
*/
int cdata_map_insert(cdata_map_t* map, const void* key, void* val);

/**
* Erase an element in the map
*
* @param map Map pointer
* @param key Key. The key type _must_ have all bytes initialized
*/
int cdata_map_erase(cdata_map_t* map, const void* key);

/**
* Finds a key in the map
*
* @param map Map pointer
* @param key Key. The key type _must_ have all bytes initialized
* @param val Pointer to the value
*/
int cdata_map_find(cdata_map_t* map, const void* key, void** val);

END_DECLS

#endif //__CDATA_MAP_H__
