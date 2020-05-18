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
#include <stdint.h>
#include <cdada/utils.h>

/**
* @file cdada/list.h
* @author Marc Sune<marcdevel (at) gmail.com>
*
* @brief List data structure. Wraps std::list data structure
*/

/**
* cdada list structure
*/
typedef void cdada_list_t;

//In case it's included from C++
BEGIN_DECLS

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
* @internal Function pointer struct for autogen types
*/
typedef struct{
	void (*create)(cdada_list_t* l);
	void (*destroy)(cdada_list_t* l);
	void (*clear)(cdada_list_t* l);
	bool (*empty)(cdada_list_t* l);
	uint32_t (*size)(cdada_list_t* l);
	int (*insert)(cdada_list_t* l, const void* val, const uint32_t pos);
	int (*get)(cdada_list_t* l, const uint32_t pos, void* val);
	int (*erase)(cdada_list_t* l, const uint32_t pos);
	int (*remove)(cdada_list_t* l, const void* val);
	int (*push)(cdada_list_t* l, const void* val, bool front);
	int (*pop)(cdada_list_t* l, bool front);
	void (*sort)(cdada_list_t* l);
	void (*reverse)(cdada_list_t* l);
	void (*unique)(cdada_list_t* l);
	void (*traverse)(cdada_list_t* l, cdada_list_it f, void* opaque);
	void (*rtraverse)(cdada_list_t* l, cdada_list_it f, void* opaque);
}__cdada_list_ops_t;

/**
* @brief Create and initialize a list data structure
*
* Allocate and initialize a list structure (std::list). For val sizes below 8
* bytes, the optimal val sizes are {1,2,4 or 8 bytes}.
*/
cdada_list_t* cdada_list_create(const uint16_t val_size);

/**
* @internal Create and initialize list with ops
*/
cdada_list_t* __cdada_list_create(const uint16_t val_size,
						__cdada_list_ops_t* ops);

/**
* Forward declare custom time ops
*/
#define CDADA_LIST_CUSTOM_TYPE_DECL(TYPE) \
	extern __cdada_list_ops_t __cdada_list_autogen_##TYPE

/**
* @brief Create a list with a custom type, with a dedicated std::list
*
* Requires instantiating CDADA_LIST_CUSTOM_GEN() or
* CDADA_LIST_CUSTOM_GEN_NO_MEMCP() once in a C++ compilation unit
*/
#define cdada_list_create_custom(TYPE) \
	__cdada_list_create(sizeof( TYPE ), & __cdada_list_autogen_##TYPE )

/**
* Destroy a list structure
*/
int cdada_list_destroy(cdada_list_t* list);

/**
* Clears the contents of the list
*/
int cdada_list_clear(cdada_list_t* list);

/**
* Traverse list
*
* @param list List
* @param func Traverse function for this specific list
* @param opaque User data (opaque ptr)
*/
int cdada_list_traverse(const cdada_list_t* list, cdada_list_it func,
							void* opaque);

/**
* Reverse traverse list
*
* @param list List
* @param func Traverse function for this specific list
* @param opaque User data (opaque ptr)
*/
int cdada_list_rtraverse(const cdada_list_t* list, cdada_list_it func,
							void* opaque);

//List properties

/**
* Is the list empty
*/
bool cdada_list_empty(cdada_list_t* list);

/**
* Return the size (number of elements) in the list
*/
uint32_t cdada_list_size(cdada_list_t* list);

//Element manipulation

/**
* Inserts an element in the list
*
* @param list List pointer
* @param val Value
* @param pos Position in the list
*/
int cdada_list_insert(cdada_list_t* list, const void* val, const uint32_t pos);

/**
* Get an element at a position
*
* @param list List pointer
* @param pos Position in the list
* @param val Value if found
*/
int cdada_list_get(cdada_list_t* list, const uint32_t pos, void* val);

/**
* Erase an element from the list in a specific position
*
* @param list List pointer
* @param pos Position in the list
*/
int cdada_list_erase(cdada_list_t* list, uint32_t pos);

/**
* Remove elements with a specific value
*
* @param list List pointer
* @param val Val. The val type _must_ have all bytes initialized
*/
int cdada_list_remove(cdada_list_t* list, const void* val);

/**
* Push front
*
* @param list List pointer
* @param val Val. The val type _must_ have all bytes initialized
* @param pos Position in the list
*/
int cdada_list_push_front(cdada_list_t* list, const void* val);

/**
* Push back
*
* @param list List pointer
* @param val Val. The val type _must_ have all bytes initialized
*/
int cdada_list_push_back(cdada_list_t* list, const void* val);

/**
* Pop front
*
* @param list List pointer
* @param val Val. The val type _must_ have all bytes initialized
*/
int cdada_list_pop_front(cdada_list_t* list);

/**
* Pop back
*
* @param list List pointer
* @param val Val. The val type _must_ have all bytes initialized
*/
int cdada_list_pop_back(cdada_list_t* list);

/**
* Sort
*
* @param list List pointer
*/
int cdada_list_sort(cdada_list_t* list);

/**
* Reverse order of elements
*
* @param list List pointer
*/
int cdada_list_reverse(cdada_list_t* list);

/**
* Remove duplicate values
*
* @param list List pointer
*/
int cdada_list_unique(cdada_list_t* list);

END_DECLS

#endif //__CDADA_LIST_H__
