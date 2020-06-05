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

#ifndef __CDADA_MAP_H__
#define __CDADA_MAP_H__

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <cdada/utils.h>

/**
* @file cdada/map.h
* @author Marc Sune<marcdevel (at) gmail.com>
*
* @brief Map {key, value} data structure. Wraps std::map data structure
*/

/**
* cdada map structure
*/
typedef void cdada_map_t;

//In case it's included from C++
CDADA_BEGIN_DECLS

//Fwd decl
struct __cdada_map_ops;
cdada_map_t* __cdada_map_create(const uint16_t key_size,
						struct __cdada_map_ops* ops);

/**
* cdada map structure iterator
*
* @param map Map ptr
* @param key Key (immutable)
* @param val Value
* @param opaque A pointer to an opaque object tat will be passed to the callback
*/
typedef void (*cdada_map_it)(const cdada_map_t* map, const void* key,
						void* val,
						void* opaque);

/**
* @brief Create and initialize a map data structure
*
* Allocate and initialize a map structure (std::map). Containers will perform
* better when TYPE has a size of {1,2,4,8,16,32,64,128,256} bytes
*
* For types > 256, use custom containers
*/
#define cdada_map_create(TYPE) \
	__cdada_map_create(sizeof( TYPE ), NULL)

/**
* Destroy a map structure
*/
int cdada_map_destroy(cdada_map_t* map);

/**
* Clears the contents of the map
*/
int cdada_map_clear(cdada_map_t* map);

/**
* Traverse map
*
* @param map Map
* @param func Traverse function for this specific map
* @param opaque User data (opaque ptr)
*/
int cdada_map_traverse(const cdada_map_t* map, cdada_map_it func,
							void* opaque);

/**
* Reverse traverse map
*
* @param map Map
* @param func Traverse function for this specific map
* @param opaque User data (opaque ptr)
*/
int cdada_map_rtraverse(const cdada_map_t* map, cdada_map_it func,
							void* opaque);

//Map properties

/**
* Is the map empty
*/
bool cdada_map_empty(const cdada_map_t* map);

/**
* Return the size (number of elements) in the map
*/
uint32_t cdada_map_size(const cdada_map_t* map);

//Element manipulation

/**
* Inserts an element in the map
*
* @param map Map pointer
* @param key Key. The key type _must_ have all bytes initialized
* @param val Pointer to the value
*/
int cdada_map_insert(cdada_map_t* map, const void* key, void* val);

/**
* Erase an element in the map
*
* @param map Map pointer
* @param key Key. The key type _must_ have all bytes initialized
*/
int cdada_map_erase(cdada_map_t* map, const void* key);

/**
* Finds a key in the map
*
* @param map Map pointer
* @param key Key
* @param val Pointer to the value
*/
int cdada_map_find(const cdada_map_t* map, const void* key, void** val);

/**
* Get the first element in the map
* @param map Map pointer
* @param key Key
* @param val Pointer to the value
*/
int cdada_map_first(const cdada_map_t* map, void* key, void** val);

/**
* Get the last element in the map
* @param map Map pointer
* @param key Key. The key type _must_ have all bytes initialized
* @param val Pointer to the value
*/
int cdada_map_last(const cdada_map_t* map, void* key, void** val);

/**
* Dump to a string the contents of the map
*
* @param map Map object
* @param size Size of the buffer
* @param buffer Buffer. If NULL, necessary bytes, including '\0' will be map in
*               'size_used'
* @param size_used If buffer != NULL, the number of bytes written else number of
*                  bytes necessary to write, including '\0'
*/
int cdada_map_dump(cdada_map_t* map, uint32_t size, char* buffer,
							uint32_t* bytes_used);

/**
* @brief Print the contents of the map
*
* @param map Map object
* @param stream stdout or stderr
*/
int cdada_map_print(cdada_map_t* map, FILE *stream);

//Custom types

/**
* Forward declare custom time ops
*/
#define CDADA_MAP_CUSTOM_TYPE_DECL(TYPE) \
	extern struct __cdada_map_ops __cdada_map_autogen_##TYPE

/**
* @brief Create a map with a custom type, with a dedicated std::map
*
* Requires instantiating CDADA_MAP_CUSTOM_GEN() or
* CDADA_MAP_CUSTOM_GEN_NO_MEMCP() once in a C++ compilation unit
*/
#define cdada_map_create_custom(TYPE) \
	__cdada_map_create(sizeof( TYPE ), & __cdada_map_autogen_##TYPE )

CDADA_END_DECLS

#endif //__CDADA_MAP_H__
