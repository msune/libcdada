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

#ifndef __CDATA_SET_H__
#define __CDATA_SET_H__

#include <stdbool.h>
#include <stdint.h>
#include <cdata/utils.h>

/**
* @file cdata_set.h
* @author Marc Sune<marcdevel (at) gmail.com>
*
* @brief Set data structure. Wraps std::set data structure
*/

/**
* cdata set structure
*/
typedef void cdata_set_t;

//In case it's included from C++
BEGIN_DECLS

/**
* cdata set structure iterator
*
* @param set Set ptr
* @param key Key (immutable)
* @param opaque A pointer to an opaque object tat will be passed to the callback
*/
typedef void (*cdata_set_it)(const cdata_set_t* set, const void* key,
						void* opaque);

/**
* @internal Function pointer struct for autogen types
*/
typedef struct{
	void (*create)(void* m);
	void (*destroy)(void* m);
	void (*clear)(void* m);
	bool (*empty)(void* m);
	uint32_t (*size)(void* m);
	int (*insert)(void* m, const void* key);
	int (*erase)(void* m, const void* key);
	bool (*find)(void* m, const void* key);
	void (*traverse)(void* m, cdata_set_it f, void* opaque);
	void (*rtraverse)(void* m, cdata_set_it f, void* opaque);
}__cdata_set_ops_t;

/**
* @brief Create and initialize a set data structure
*
* Allocate and initialize a set structure (std::set). For key sizes below 8
* bytes, the optimal key sizes are {1,2,4 or 8 bytes}.
*/
cdata_set_t* cdata_set_create(const uint16_t key_size);

/**
* @internal Create and initialize set with ops
*/
cdata_set_t* __cdata_set_create(const uint16_t key_size,
						__cdata_set_ops_t* ops);

/**
* Forward declare custom time ops
*/
#define CDATA_SET_CUSTOM_TYPE_DECL(TYPE) \
	extern __cdata_set_ops_t __cdata_set_autogen_##TYPE

/**
* @brief Create a set with a custom type, with a dedicated std::set
*
* Requires instantiating CDATA_SET_CUSTOM_GEN() or
* CDATA_SET_CUSTOM_GEN_NO_MEMCP() once in a C++ compilation unit
*/
#define cdata_set_create_custom(TYPE) \
	__cdata_set_create(sizeof( TYPE ), & __cdata_set_autogen_##TYPE )

/**
* Destroy a set structure
*/
int cdata_set_destroy(cdata_set_t* set);

/**
* Clears the contents of the set
*/
int cdata_set_clear(cdata_set_t* set);

/**
* Traverse set
*
* @param set Set
* @param func Traverse function for this specific set
* @param opaque User data (opaque ptr)
*/
int cdata_set_traverse(const cdata_set_t* set, cdata_set_it func,
							void* opaque);

/**
* Reverse traverse set
*
* @param set Set
* @param func Traverse function for this specific set
* @param opaque User data (opaque ptr)
*/
int cdata_set_rtraverse(const cdata_set_t* set, cdata_set_it func,
							void* opaque);

//Set properties

/**
* Is the set empty
*/
bool cdata_set_empty(cdata_set_t* set);

/**
* Return the size (number of elements) in the set
*/
uint32_t cdata_set_size(cdata_set_t* set);

//Element manipulation

/**
* Inserts an element in the set
*
* @param set Set pointer
* @param key Key. The key type _must_ have all bytes initialized
*/
int cdata_set_insert(cdata_set_t* set, const void* key);

/**
* Erase an element in the set
*
* @param set Set pointer
* @param key Key. The key type _must_ have all bytes initialized
*/
int cdata_set_erase(cdata_set_t* set, const void* key);

/**
* Finds a key in the set
*
* @param set Set pointer
* @param key Key. The key type _must_ have all bytes initialized
*/
bool cdata_set_find(cdata_set_t* set, const void* key);

END_DECLS

#endif //__CDATA_SET_H__
