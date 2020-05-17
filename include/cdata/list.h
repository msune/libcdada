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

#ifndef __CDATA_LIST_H__
#define __CDATA_LIST_H__

#include <stdbool.h>
#include <stdint.h>
#include <cdata/utils.h>

/**
* @file cdata/list.h
* @author Marc Sune<marcdevel (at) gmail.com>
*
* @brief List data structure. Wraps std::list data structure
*/

/**
* cdata list structure
*/
typedef void cdata_list_t;

//In case it's included from C++
BEGIN_DECLS

/**
* cdata list structure iterator
*
* @param list List ptr
* @param val Val (immutable)
* @param opaque A pointer to an opaque object tat will be passed to the callback
*/
typedef void (*cdata_list_it)(const cdata_list_t* list, const void* val,
						void* opaque);

/**
* @internal Function pointer struct for autogen types
*/
typedef struct{
	void (*create)(cdata_list_t* l);
	void (*destroy)(cdata_list_t* l);
	void (*clear)(cdata_list_t* l);
	bool (*empty)(cdata_list_t* l);
	uint32_t (*size)(cdata_list_t* l);
	int (*insert)(cdata_list_t* l, const void* val, const uint32_t pos);
	int (*get)(cdata_list_t* l, const uint32_t pos, void* val);
	int (*erase)(cdata_list_t* l, const uint32_t pos);
	int (*remove)(cdata_list_t* l, const void* val);
	int (*push)(cdata_list_t* l, const void* val, bool front);
	int (*pop)(cdata_list_t* l, bool front);
	int (*sort)(cdata_list_t* l);
	int (*reverse)(cdata_list_t* l);
	int (*unique)(cdata_list_t* l);
	int (*traverse)(cdata_list_t* l, cdata_list_it f, void* opaque);
	int (*rtraverse)(cdata_list_t* l, cdata_list_it f, void* opaque);
}__cdata_list_ops_t;

/**
* @brief Create and initialize a list data structure
*
* Allocate and initialize a list structure (std::list). For val sizes below 8
* bytes, the optimal val sizes are {1,2,4 or 8 bytes}.
*/
cdata_list_t* cdata_list_create(const uint16_t val_size);

/**
* @internal Create and initialize list with ops
*/
cdata_list_t* __cdata_list_create(const uint16_t val_size,
						__cdata_list_ops_t* ops);

/**
* Destroy a list structure
*/
int cdata_list_destroy(cdata_list_t* list);

/**
* Clears the contents of the list
*/
int cdata_list_clear(cdata_list_t* list);

/**
* Traverse list
*
* @param list List
* @param func Traverse function for this specific list
* @param opaque User data (opaque ptr)
*/
int cdata_list_traverse(const cdata_list_t* list, cdata_list_it func,
							void* opaque);

/**
* Reverse traverse list
*
* @param list List
* @param func Traverse function for this specific list
* @param opaque User data (opaque ptr)
*/
int cdata_list_rtraverse(const cdata_list_t* list, cdata_list_it func,
							void* opaque);

//List properties

/**
* Is the list empty
*/
bool cdata_list_empty(cdata_list_t* list);

/**
* Return the size (number of elements) in the list
*/
uint32_t cdata_list_size(cdata_list_t* list);

//Element manipulation

/**
* Inserts an element in the list
*
* @param list List pointer
* @param val Value
* @param pos Position in the list
*/
int cdata_list_insert(cdata_list_t* list, const void* val, const uint32_t pos);

/**
* Get an element at a position
*
* @param list List pointer
* @param pos Position in the list
* @param val Value if found
*/
int cdata_list_get(cdata_list_t* list, const uint32_t pos, void* val);

/**
* Erase an element from the list in a specific position
*
* @param list List pointer
* @param pos Position in the list
*/
int cdata_list_erase(cdata_list_t* list, uint32_t pos);

/**
* Remove elements with a specific value
*
* @param list List pointer
* @param val Val. The val type _must_ have all bytes initialized
*/
int cdata_list_remove(cdata_list_t* list, const void* val);

/**
* Push front
*
* @param list List pointer
* @param val Val. The val type _must_ have all bytes initialized
* @param pos Position in the list
*/
int cdata_list_push_front(cdata_list_t* list, const void* val);

/**
* Push back
*
* @param list List pointer
* @param val Val. The val type _must_ have all bytes initialized
*/
int cdata_list_push_back(cdata_list_t* list, const void* val);

/**
* Pop front
*
* @param list List pointer
* @param val Val. The val type _must_ have all bytes initialized
*/
int cdata_list_pop_front(cdata_list_t* list);

/**
* Pop back
*
* @param list List pointer
* @param val Val. The val type _must_ have all bytes initialized
*/
int cdata_list_pop_back(cdata_list_t* list);

/**
* Sort
*
* @param list List pointer
*/
int cdata_list_sort(cdata_list_t* list);

/**
* Reverse order of elements
*
* @param list List pointer
*/
int cdata_list_reverse(cdata_list_t* list);

/**
* Remove duplicate values
*
* @param list List pointer
*/
int cdata_list_unique(cdata_list_t* list);

END_DECLS

#endif //__CDATA_LIST_H__
