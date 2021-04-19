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

#ifndef __CDADA_SET_H__
#define __CDADA_SET_H__

#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>
#include <cdada/utils.h>

/**
* @file cdada/set.h
* @author Marc Sune<marcdevel (at) gmail.com>
*
* @brief Set data structure.
*
* `cdada_set` data structure is a collection of unique elements of type 'TYPE'.
* During insertions, a _copy_ of the element `key` will be stored in the set.
* During accesses (e.g. `cdada_set_first`), if found, a _copy_ of the value
* will be stored in the region of memory pointed by `key`.
*
* Uses std::set as a backend
*/

/**
* cdada set structure
*/
typedef void cdada_set_t;

//In case it's included from C++
CDADA_BEGIN_DECLS

//Fwd decl
//See cdada_set_create() for return codes
struct __cdada_set_ops;
cdada_set_t* __cdada_set_create(const uint16_t key_size,
						struct __cdada_set_ops* ops);

/**
* cdada set structure iterator
*
* @param set Set ptr
* @param key Key (immutable)
* @param opaque A pointer to an opaque object tat will be passed to the callback
*/
typedef void (*cdada_set_it)(const cdada_set_t* set, const void* key,
						void* opaque);

/**
* @brief Create and initialize a set data structure
*
* Allocate and initialize a set structure. Containers will perform
* better when TYPE has a size of {1,2,4,8,16,32,64,128,256} bytes
*
* For types > 256, use custom containers
*
* @returns Returns a cdada_set object or NULL, if some error is found
*/
#define cdada_set_create(TYPE) \
	__cdada_set_create(sizeof( TYPE ), NULL)

/**
* Destroy a set structure
*
* @returns Return codes:
*          CDADA_SUCCESS: set is destroyed
*          CDADA_E_UNKNOWN: corrupted set or internal error (bug)
*          CDADA_E_INVALID: set is NULL or corrupted
*/
int cdada_set_destroy(cdada_set_t* set);

/**
* Clear the contents of the set
*
* @returns Return codes:
*          CDADA_SUCCESS: set is cleared
*          CDADA_E_MEM: out of memory
*          CDADA_E_UNKNOWN: corrupted set or internal error (bug)
*          CDADA_E_INVALID: set is NULL or corrupted
*/
int cdada_set_clear(cdada_set_t* set);

/**
* Traverse set
*
* @param set Set
* @param func Traverse function for this specific set
* @param opaque User data (opaque ptr)
*
* @returns Return codes:
*          CDADA_SUCCESS: set was successfully traversed
*          CDADA_E_UNKNOWN: corrupted set or internal error (bug)
*          CDADA_E_INVALID: set is NULL or corrupted
*/
int cdada_set_traverse(const cdada_set_t* set, cdada_set_it func,
							void* opaque);

/**
* Reverse traverse set
*
* @param set Set
* @param func Traverse function for this specific set
* @param opaque User data (opaque ptr)
*
* @returns Return codes:
*          CDADA_SUCCESS: set was successfully reverse traversed
*          CDADA_E_UNKNOWN: corrupted set or internal error (bug)
*          CDADA_E_INVALID: set is NULL or corrupted
*/
int cdada_set_rtraverse(const cdada_set_t* set, cdada_set_it func,
							void* opaque);

//Set properties

/**
* Is the set empty
*
* @returns Returns true if set is empty else (including invalid) false
*/
bool cdada_set_empty(const cdada_set_t* set);

/**
* Return the size (number of elements) in the set
*
* @returns Returns number of elements. If set is NULL or corrupted, returns 0
*/
uint32_t cdada_set_size(const cdada_set_t* set);

//Element manipulation

/**
* Insert an element (a copy) in the set
*
* @param set Set pointer
* @param key Key. The key type _must_ have all bytes initialized
*
* @returns Return codes:
*          CDADA_SUCCESS: element is inserted
*          CDADA_E_EXISTS: element exists
*          CDADA_E_MEM: out of memory
*          CDADA_E_UNKNOWN: corrupted set or internal error (bug)
*          CDADA_E_INVALID: set is NULL or corrupted
*/
int cdada_set_insert(cdada_set_t* set, const void* key);

/**
* Erase an element in the set
*
* @param set Set pointer
* @param key Key. The key type _must_ have all bytes initialized
*
* @returns Return codes:
*          CDADA_SUCCESS: element was successfully erased
*          CDADA_E_NOT_FOUND: no element `key` was found
*          CDADA_E_MEM: out of memory
*          CDADA_E_UNKNOWN: corrupted set or internal error (bug)
*          CDADA_E_INVALID: set is NULL or corrupted
*/
int cdada_set_erase(cdada_set_t* set, const void* key);

/**
* Find a key in the set
*
* @param set Set pointer
* @param key Key to search
*
* @returns Returns true if set has element else (including invalid) false
*/
bool cdada_set_find(const cdada_set_t* set, const void* key);

/**
* Get the first element in the set
* @param set Set pointer
* @param key If set has elements, a copy of the first element will be stored
*            in *key
*
* @returns Return codes:
*          CDADA_SUCCESS: first element was retrieved
*          CDADA_E_EMPTY: set has no elements
*          CDADA_E_UNKNOWN: corrupted set or internal error (bug)
*          CDADA_E_INVALID: set is NULL or corrupted
*/
int cdada_set_first(const cdada_set_t* set, void* key);

/**
* Get the last element in the set
* @param set Set pointer
* @param key If set has elements, a copy of the last element will be stored
*            in *key
*
* @returns Return codes:
*          CDADA_SUCCESS: last element was retrieved
*          CDADA_E_EMPTY: set has no elements
*          CDADA_E_UNKNOWN: corrupted set or internal error (bug)
*          CDADA_E_INVALID: set is NULL or corrupted
*/
int cdada_set_last(const cdada_set_t* set, void* key);

//Dumpers

/**
* Dump to a string the contents of the set
*
* @param set Set object
* @param size Size of the buffer
* @param buffer Buffer. If NULL, necessary bytes, including '\0' will be set in
*               'size_used'
* @param size_used If buffer != NULL, the number of bytes written else number of
*                  bytes necessary to write, including '\0'
*
* @returns Return codes:
*          CDADA_SUCCESS: set was dumped to buffer
*          CDADA_E_INCOMPLETE: not enough room in buffer
*          CDADA_E_MEM: out of memory
*          CDADA_E_UNKNOWN: corrupted set or internal error (bug)
*          CDADA_E_INVALID: set is NULL or corrupted
*/
int cdada_set_dump(cdada_set_t* set, uint32_t size, char* buffer,
							uint32_t* bytes_used);

/**
* @brief Print the contents of the set
*
* @param set Set object
* @param stream stdout or stderr
*
* @returns Return codes:
*          CDADA_SUCCESS: set was dumped to `stream`
*          CDADA_E_MEM: out of memory
*          CDADA_E_UNKNOWN: corrupted set or internal error (bug)
*          CDADA_E_INVALID: set is NULL or corrupted
*/
int cdada_set_print(cdada_set_t* set, FILE *stream);

//Custom types

/**
* Forward declare custom time ops
*/
#define CDADA_SET_CUSTOM_TYPE_DECL(TYPE) \
	extern struct __cdada_set_ops __cdada_set_autogen_##TYPE

/**
* @brief Create a set with a custom type, with a dedicated std::set
*
* Requires instantiating CDADA_SET_CUSTOM_GEN() or
* CDADA_SET_CUSTOM_GEN_NO_MEMCP() once in a C++ compilation unit
*/
#define cdada_set_create_custom(TYPE) \
	__cdada_set_create(sizeof( TYPE ), & __cdada_set_autogen_##TYPE )

CDADA_END_DECLS

#endif //__CDADA_SET_H__
