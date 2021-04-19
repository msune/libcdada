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

#ifndef __CDADA_LIST_H__
#define __CDADA_LIST_H__

#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>
#include <cdada/utils.h>

/**
* @file cdada/list.h
* @author Marc Sune<marcdevel (at) gmail.com>
*
* @brief List data structure
*
* `cdada_list` data structure is an ordered list of elements of type 'TYPE'.
* During insertions, a _copy_ of the element `val` will be stored in the list.
* During accesses (e.g. `cdada_list_first`), if found, a _copy_ of the value
* will be stored in the region of memory pointed by `val`.
*
* Uses std::list as a backend
*/

/**
* cdada list structure
*/
typedef void cdada_list_t;

//In case it's included from C++
CDADA_BEGIN_DECLS

//Fwd decl
//See cdada_list_create() for return codes
struct __cdada_list_ops;
cdada_list_t* __cdada_list_create(const uint16_t val_size,
						struct __cdada_list_ops* ops);

/**
* cdada list structure iterator
*
* @param list List ptr
* @param val Val (immutable)
* @param opaque A pointer to an opaque object tat will be passed to the callback
*/
typedef void (*cdada_list_it)(const cdada_list_t* list, const void* val,
						void* opaque);

/**
* @brief Create and initialize a list data structure
*
* Allocate and initialize a list structure. Containers will perform  better when
* TYPE has a size of {1,2,4,8,16,32,64,128,256} bytes
*
* For types > 256, use custom containers
*
* @param TYPE A typename (not a function parameter)
*
* @returns Returns a cdada_list object or NULL, if some error is found
*/
#define cdada_list_create(TYPE) \
	__cdada_list_create(sizeof( TYPE ), NULL)

/**
* Destroy a list structure
*
* @returns Return codes:
*          CDADA_SUCCESS: list is destroyed
*          CDADA_E_UNKNOWN: corrupted list or internal error (bug)
*          CDADA_E_INVALID: list is NULL or corrupted
*/
int cdada_list_destroy(cdada_list_t* list);

/**
* Clear the contents of the list
*
* @returns Return codes:
*          CDADA_SUCCESS: list is cleared
*          CDADA_E_MEM: out of memory
*          CDADA_E_UNKNOWN: corrupted list or internal error (bug)
*          CDADA_E_INVALID: list is NULL or corrupted
*/
int cdada_list_clear(cdada_list_t* list);

/**
* Traverse list
*
* @param list List
* @param func Traverse function for this specific list
* @param opaque User data (opaque ptr)
*
* @returns Return codes:
*          CDADA_SUCCESS: list was successfully traversed
*          CDADA_E_UNKNOWN: corrupted list or internal error (bug)
*          CDADA_E_INVALID: list is NULL or corrupted
*/
int cdada_list_traverse(const cdada_list_t* list, cdada_list_it func,
							void* opaque);

/**
* Reverse traverse list
*
* @param list List
* @param func Traverse function for this specific list
* @param opaque User data (opaque ptr)
*
* @returns Return codes:
*          CDADA_SUCCESS: list was successfully reverse traversed
*          CDADA_E_UNKNOWN: corrupted list or internal error (bug)
*          CDADA_E_INVALID: list is NULL or corrupted
*/
int cdada_list_rtraverse(const cdada_list_t* list, cdada_list_it func,
							void* opaque);

//List properties

/**
* Is the list empty
*
* @returns Returns true if list is empty else (including invalid) false
*/
bool cdada_list_empty(const cdada_list_t* list);

/**
* Return the size (number of elements) in the list
*
* @returns Returns number of elements. If list is NULL or corrupted, returns 0
*/
uint32_t cdada_list_size(const cdada_list_t* list);

//Element manipulation

/**
* Insert an element (a copy) in the list
*
* @param list List pointer
* @param val Value
* @param pos Position in the list
*
* @returns Return codes:
*          CDADA_SUCCESS: element is inserted
*          CDADA_E_MEM: out of memory
*          CDADA_E_UNKNOWN: corrupted list or internal error (bug)
*          CDADA_E_INVALID: list is NULL or corrupted
*/
int cdada_list_insert(cdada_list_t* list, const void* val, const uint32_t pos);

/**
* Get an element at a position
*
* @param list List pointer
* @param pos Position in the list
* @param val If an element in the position `pos` (starting from 0) exists,
*            a copy of the element will be stored in *val
*
* @returns Return codes:
*          CDADA_SUCCESS: element was retrieved
*          CDADA_E_NOT_FOUND: no element at position `pos`
*          CDADA_E_UNKNOWN: corrupted list or internal error (bug)
*          CDADA_E_INVALID: list is NULL or corrupted
*/
int cdada_list_get(const cdada_list_t* list, const uint32_t pos, void* val);

/**
* Get the first element (a copy) in the list
* @param list Map pointer
* @param val When the list has elements, a copy of the first element will
*            be stored in *val
*
* @returns Return codes:
*          CDADA_SUCCESS: first element was retrieved
*          CDADA_E_EMPTY: list has no elements
*          CDADA_E_UNKNOWN: corrupted list or internal error (bug)
*          CDADA_E_INVALID: list is NULL or corrupted
*/
int cdada_list_first(const cdada_list_t* list, void* val);

/**
* Get the last element (a copy) in the list
* @param list Map pointer
* @param val When the list has elements, a copy of the last element will
*            be stored in *val
*
* @returns Return codes:
*          CDADA_SUCCESS: last element was retrieved
*          CDADA_E_EMPTY: list has no elements
*          CDADA_E_UNKNOWN: corrupted list or internal error (bug)
*          CDADA_E_INVALID: list is NULL or corrupted
*/
int cdada_list_last(const cdada_list_t* list, void* val);

/**
* Erase an element from the list in a specific position
*
* @param list List pointer
* @param pos Position in the list
*
* @returns Return codes:
*          CDADA_SUCCESS: element at position `pos` was successfully erased
*          CDADA_E_NOT_FOUND: no element at position `pos`
*          CDADA_E_MEM: out of memory
*          CDADA_E_UNKNOWN: corrupted list or internal error (bug)
*          CDADA_E_INVALID: list is NULL or corrupted
*/
int cdada_list_erase(cdada_list_t* list, uint32_t pos);

/**
* Remove elements with a specific value
*
* @param list List pointer
* @param val Element
*
* @returns Return codes:
*          CDADA_SUCCESS: at least one element was successfully removed
*          CDADA_E_NOT_FOUND: no elements match `val`
*          CDADA_E_MEM: out of memory
*          CDADA_E_UNKNOWN: corrupted list or internal error (bug)
*          CDADA_E_INVALID: list is NULL or corrupted
*/
int cdada_list_remove(cdada_list_t* list, const void* val);

/**
* Push front (a copy)
*
* @param list List pointer
* @param val Element
*
* @returns Return codes:
*          CDADA_SUCCESS: element was successfully pushed to the front
*          CDADA_E_MEM: out of memory
*          CDADA_E_UNKNOWN: corrupted list or internal error (bug)
*          CDADA_E_INVALID: list is NULL or corrupted
*/
int cdada_list_push_front(cdada_list_t* list, const void* val);

/**
* Push back (a copy)
*
* @param list List pointer
* @param val Element
*
* @returns Return codes:
*          CDADA_SUCCESS: element was successfully pushed to the back
*          CDADA_E_MEM: out of memory
*          CDADA_E_UNKNOWN: corrupted list or internal error (bug)
*          CDADA_E_INVALID: list is NULL or corrupted
*/
int cdada_list_push_back(cdada_list_t* list, const void* val);

/**
* Pop (remove) from the front of the list
*
* @param list List pointer
*
* @returns Return codes:
*          CDADA_SUCCESS: element was successfully popped from the front
*          CDADA_E_EMPTY: list is empty
*          CDADA_E_MEM: out of memory
*          CDADA_E_UNKNOWN: corrupted list or internal error (bug)
*          CDADA_E_INVALID: list is NULL or corrupted
*/
int cdada_list_pop_front(cdada_list_t* list);

/**
* Pop (remove) from the back of the list
*
* @param list List pointer
*
* @returns Return codes:
*          CDADA_SUCCESS: element was successfully popped from the back
*          CDADA_E_EMPTY: list is empty
*          CDADA_E_MEM: out of memory
*          CDADA_E_UNKNOWN: corrupted list or internal error (bug)
*          CDADA_E_INVALID: list is NULL or corrupted
*/
int cdada_list_pop_back(cdada_list_t* list);

/**
* Sort
*
* @param list List pointer
*
* @returns Return codes:
*          CDADA_SUCCESS: list was sorted
*          CDADA_E_MEM: out of memory
*          CDADA_E_UNKNOWN: corrupted list or internal error (bug)
*          CDADA_E_INVALID: list is NULL or corrupted
*/
int cdada_list_sort(cdada_list_t* list);

/**
* Reverse order of elements
*
* @param list List pointer
*
* @returns Return codes:
*          CDADA_SUCCESS: list was reversed
*          CDADA_E_MEM: out of memory
*          CDADA_E_UNKNOWN: corrupted list or internal error (bug)
*          CDADA_E_INVALID: list is NULL or corrupted
*/
int cdada_list_reverse(cdada_list_t* list);

/**
* Remove duplicate values
*
* @param list List pointer
*
* @returns Return codes:
*          CDADA_SUCCESS: list had duplicate elements successfully removed
*          CDADA_E_MEM: out of memory
*          CDADA_E_UNKNOWN: corrupted list or internal error (bug)
*          CDADA_E_INVALID: list is NULL or corrupted
*/
int cdada_list_unique(cdada_list_t* list);

//Dumpers

/**
* Dump to a string the contents of the list
*
* @param list List object
* @param size Size of the buffer
* @param buffer Buffer. If NULL, necessary bytes, including '\0' will be list in
*               'size_used'
* @param size_used If buffer != NULL, the number of bytes written else number of
*                  bytes necessary to write, including '\0'
*
* @returns Return codes:
*          CDADA_SUCCESS: list was dumped to buffer
*          CDADA_E_INCOMPLETE: not enough room in buffer
*          CDADA_E_MEM: out of memory
*          CDADA_E_UNKNOWN: corrupted list or internal error (bug)
*          CDADA_E_INVALID: list is NULL or corrupted
*/
int cdada_list_dump(cdada_list_t* list, uint32_t size, char* buffer,
							uint32_t* bytes_used);

/**
* @brief Print the contents of the list
*
* @param list List object
* @param stream stdout or stderr
*
* @returns Return codes:
*          CDADA_SUCCESS: list was dumped to `stream`
*          CDADA_E_MEM: out of memory
*          CDADA_E_UNKNOWN: corrupted list or internal error (bug)
*          CDADA_E_INVALID: list is NULL or corrupted
*/
int cdada_list_print(cdada_list_t* list, FILE *stream);

//Custom types

/**
* Forward declare custom time ops
*/
#define CDADA_LIST_CUSTOM_TYPE_DECL(TYPE) \
	extern struct __cdada_list_ops __cdada_list_autogen_##TYPE

/**
* @brief Create a list with a custom type, with a dedicated std::list
*
* Requires instantiating CDADA_LIST_CUSTOM_GEN() or
* CDADA_LIST_CUSTOM_GEN_NO_MEMCP() once in a C++ compilation unit
*/
#define cdada_list_create_custom(TYPE) \
	__cdada_list_create(sizeof( TYPE ), & __cdada_list_autogen_##TYPE )

CDADA_END_DECLS

#endif //__CDADA_LIST_H__
