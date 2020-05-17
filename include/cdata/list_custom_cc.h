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

#ifndef __CDATA_LIST_CUSTOM_CC_H__
#define __CDATA_LIST_CUSTOM_CC_H__

//This header should _always_ be included from C++
#ifndef __cplusplus
	#error CDATA autogenreation headers shall be included only from C++ files
#endif //__cplusplus

#define __CDATA_INTERNAL_INCLUDE

#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include <cdata/list.h>
#include <cdata/utils.h>
#include <cdata/__list_internal.h>

/**
* @file cdata/list_custom_cc.h
* @author Marc Sune<marcdevel (at) gmail.com>
*
* @brief This file needs to be included in a C++ file to autogenerate the
*        code necessary to use a custom type as a val/value for cdata structs.
*/

#define __CDATA_STD_LIST_TYPE(T) std::list< T >

/**
* @internal Custom type create f
*/
#define __CDATA_LIST_CUSTOM_CREATE_F(TYPE) \
	void __cdata_list_autogen_create_##TYPE (void* m){ \
		__cdata_list_int_t* s = (__cdata_list_int_t*)m; \
		s->list.custom = (void*)new __CDATA_STD_LIST_TYPE(TYPE)(); \
	}

/**
* @internal Custom type destroy f
*/
#define __CDATA_LIST_CUSTOM_DESTROY_F(TYPE) \
	void __cdata_list_autogen_destroy_##TYPE (void* m){ \
		__cdata_list_int_t* s = (__cdata_list_int_t*)m; \
		__CDATA_STD_LIST_TYPE(TYPE)* p = \
				(__CDATA_STD_LIST_TYPE(TYPE)*)s->list.custom; \
		delete p; \
	}

/**
* @internal Custom type clear f
*/
#define __CDATA_LIST_CUSTOM_CLEAR_F(TYPE) \
	void __cdata_list_autogen_clear_##TYPE (void* m){ \
		__cdata_list_int_t* s = (__cdata_list_int_t*)m; \
		__CDATA_STD_LIST_TYPE(TYPE)* p = \
				(__CDATA_STD_LIST_TYPE(TYPE)*)s->list.custom; \
		p->clear(); \
	}

/**
* @internal Custom type empty f
*/
#define __CDATA_LIST_CUSTOM_EMPTY_F(TYPE) \
	bool __cdata_list_autogen_empty_##TYPE (void* m){ \
		__cdata_list_int_t* s = (__cdata_list_int_t*)m; \
		__CDATA_STD_LIST_TYPE(TYPE)* p = \
				(__CDATA_STD_LIST_TYPE(TYPE)*)s->list.custom; \
		return p->empty(); \
	}
/**
* @internal Custom type size f
*/
#define __CDATA_LIST_CUSTOM_SIZE_F(TYPE) \
	uint32_t __cdata_list_autogen_size_##TYPE (void* m){ \
		__cdata_list_int_t* s = (__cdata_list_int_t*)m; \
		__CDATA_STD_LIST_TYPE(TYPE)* p = \
				(__CDATA_STD_LIST_TYPE(TYPE)*)s->list.custom; \
		return p->size(); \
	}
/**
* @internal Custom type insert f
*/
#define __CDATA_LIST_CUSTOM_INSERT_F(TYPE) \
	int __cdata_list_autogen_insert_##TYPE (void* m, const void* val, \
							const uint32_t pos){ \
		__cdata_list_int_t* s = (__cdata_list_int_t*)m; \
		__CDATA_STD_LIST_TYPE(TYPE)* p = \
				(__CDATA_STD_LIST_TYPE(TYPE)*)s->list.custom; \
		return cdata_list_insert_u< TYPE > (s, p, val, pos);\
	}

/**
* @internal Custom type get f
*/
#define __CDATA_LIST_CUSTOM_GET_F(TYPE) \
	int __cdata_list_autogen_get_##TYPE (void* m, const uint32_t pos, \
							void* val){ \
		__cdata_list_int_t* s = (__cdata_list_int_t*)m; \
		__CDATA_STD_LIST_TYPE(TYPE)* p = \
				(__CDATA_STD_LIST_TYPE(TYPE)*)s->list.custom; \
		return cdata_list_get_u< TYPE > (s, p, pos, val);\
	}
/**
* @internal Custom type erase f
*/
#define __CDATA_LIST_CUSTOM_ERASE_F(TYPE) \
	int __cdata_list_autogen_erase_##TYPE (void* m, const uint32_t pos){ \
		__cdata_list_int_t* s = (__cdata_list_int_t*)m; \
		__CDATA_STD_LIST_TYPE(TYPE)* p = \
				(__CDATA_STD_LIST_TYPE(TYPE)*)s->list.custom; \
		return cdata_list_erase_u< TYPE > (s, p, pos);\
	}

/**
* @internal Custom type remove f
*/
#define __CDATA_LIST_CUSTOM_REMOVE_F(TYPE) \
	int __cdata_list_autogen_remove_##TYPE (void* m, const void* val){ \
		__cdata_list_int_t* s = (__cdata_list_int_t*)m; \
		__CDATA_STD_LIST_TYPE(TYPE)* p = \
				(__CDATA_STD_LIST_TYPE(TYPE)*)s->list.custom; \
		return cdata_list_remove_u< TYPE > (s, p, val);\
	}

/**
* @internal Custom type push f
*/
#define __CDATA_LIST_CUSTOM_PUSH_F(TYPE) \
	int __cdata_list_autogen_push_##TYPE (void* m, const void* val,\
								bool front){ \
		__cdata_list_int_t* s = (__cdata_list_int_t*)m; \
		__CDATA_STD_LIST_TYPE(TYPE)* p = \
				(__CDATA_STD_LIST_TYPE(TYPE)*)s->list.custom; \
		return cdata_list_push_u< TYPE > (s, p, val, front);\
	}

/**
* @internal Custom type pop f
*/
#define __CDATA_LIST_CUSTOM_POP_F(TYPE) \
	int __cdata_list_autogen_pop_##TYPE (void* m, bool front){ \
		__cdata_list_int_t* s = (__cdata_list_int_t*)m; \
		__CDATA_STD_LIST_TYPE(TYPE)* p = \
				(__CDATA_STD_LIST_TYPE(TYPE)*)s->list.custom; \
		return cdata_list_pop_u< TYPE > (s, p, front);\
	}

/**
* @internal Custom type sort f
*/
#define __CDATA_LIST_CUSTOM_SORT_F(TYPE) \
	void __cdata_list_autogen_sort_##TYPE (void* m){ \
		__cdata_list_int_t* s = (__cdata_list_int_t*)m; \
		__CDATA_STD_LIST_TYPE(TYPE)* p = \
				(__CDATA_STD_LIST_TYPE(TYPE)*)s->list.custom; \
		p->sort(); \
	}

/**
* @internal Custom type reverse f
*/
#define __CDATA_LIST_CUSTOM_REVERSE_F(TYPE) \
	void __cdata_list_autogen_reverse_##TYPE (void* m){ \
		__cdata_list_int_t* s = (__cdata_list_int_t*)m; \
		__CDATA_STD_LIST_TYPE(TYPE)* p = \
				(__CDATA_STD_LIST_TYPE(TYPE)*)s->list.custom; \
		p->reverse(); \
	}

/**
* @internal Custom type unique f
*/
#define __CDATA_LIST_CUSTOM_UNIQUE_F(TYPE) \
	void __cdata_list_autogen_unique_##TYPE (void* m){ \
		__cdata_list_int_t* s = (__cdata_list_int_t*)m; \
		__CDATA_STD_LIST_TYPE(TYPE)* p = \
				(__CDATA_STD_LIST_TYPE(TYPE)*)s->list.custom; \
		p->unique(); \
	}

/**
* @internal Custom type traverse f
*/
#define __CDATA_LIST_CUSTOM_TRAVERSE_F(TYPE) \
	void __cdata_list_autogen_traverse_##TYPE (void* m, cdata_list_it f, \
								void* opaque){ \
		__cdata_list_int_t* s = (__cdata_list_int_t*)m; \
		__CDATA_STD_LIST_TYPE(TYPE)* p = \
				(__CDATA_STD_LIST_TYPE(TYPE)*)s->list.custom; \
		return cdata_list_traverse_u< TYPE > (s, p, f, opaque);\
	}

/**
* @internal Custom type rtraverse f
*/
#define __CDATA_LIST_CUSTOM_RTRAVERSE_F(TYPE) \
	void __cdata_list_autogen_rtraverse_##TYPE (void* m, cdata_list_it f, \
								void* opaque){ \
		__cdata_list_int_t* s = (__cdata_list_int_t*)m; \
		__CDATA_STD_LIST_TYPE(TYPE)* p = \
				(__CDATA_STD_LIST_TYPE(TYPE)*)s->list.custom; \
		return cdata_list_rtraverse_u< TYPE > (s, p, f, opaque);\
	}


/**
* @internal Create ops func ptrs struct
*/
#define __CDATA_LIST_CUSTOM_OPS(TYPE) \
	__cdata_list_ops_t __cdata_list_autogen_##TYPE = { \
		.create  = __cdata_list_autogen_create_##TYPE, \
		.destroy = __cdata_list_autogen_destroy_##TYPE, \
		.clear = __cdata_list_autogen_clear_##TYPE, \
		.empty = __cdata_list_autogen_empty_##TYPE, \
		.size = __cdata_list_autogen_size_##TYPE, \
		.insert = __cdata_list_autogen_insert_##TYPE, \
		.get = __cdata_list_autogen_get_##TYPE, \
		.erase = __cdata_list_autogen_erase_##TYPE, \
		.remove = __cdata_list_autogen_remove_##TYPE, \
		.push = __cdata_list_autogen_push_##TYPE, \
		.pop = __cdata_list_autogen_pop_##TYPE, \
		.sort = __cdata_list_autogen_sort_##TYPE, \
		.reverse = __cdata_list_autogen_reverse_##TYPE, \
		.unique = __cdata_list_autogen_unique_##TYPE, \
		.traverse = __cdata_list_autogen_traverse_##TYPE, \
		.rtraverse = __cdata_list_autogen_rtraverse_##TYPE, \
		}

/**
* Auto-generate (instantiate) new custom type list, with TYPE
*/
#define CDATA_LIST_CUSTOM_GEN(TYPE) 	\
	__CDATA_LIST_CUSTOM_CREATE_F(TYPE); \
	__CDATA_LIST_CUSTOM_DESTROY_F(TYPE); \
	__CDATA_LIST_CUSTOM_CLEAR_F(TYPE); \
	__CDATA_LIST_CUSTOM_EMPTY_F(TYPE); \
	__CDATA_LIST_CUSTOM_SIZE_F(TYPE); \
	__CDATA_LIST_CUSTOM_INSERT_F(TYPE); \
	__CDATA_LIST_CUSTOM_GET_F(TYPE); \
	__CDATA_LIST_CUSTOM_ERASE_F(TYPE); \
	__CDATA_LIST_CUSTOM_REMOVE_F(TYPE); \
	__CDATA_LIST_CUSTOM_PUSH_F(TYPE); \
	__CDATA_LIST_CUSTOM_POP_F(TYPE); \
	__CDATA_LIST_CUSTOM_SORT_F(TYPE); \
	__CDATA_LIST_CUSTOM_REVERSE_F(TYPE); \
	__CDATA_LIST_CUSTOM_UNIQUE_F(TYPE); \
	__CDATA_LIST_CUSTOM_TRAVERSE_F(TYPE); \
	__CDATA_LIST_CUSTOM_RTRAVERSE_F(TYPE); \
	__CDATA_LIST_CUSTOM_OPS(TYPE)

#undef __CDATA_INTERNAL_INCLUDE

#endif //__CDATA_LIST_CUSTOM_CC_H__
