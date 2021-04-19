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

#ifndef __CDADA_LIST_CUSTOM_CC_H__
#define __CDADA_LIST_CUSTOM_CC_H__

//This header should _always_ be included from C++
#ifndef __cplusplus
	#error CDADA autogenreation headers shall be included only from C++ files
#endif //__cplusplus

#define __CDADA_INTERNAL_INCLUDE

#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include <cdada/list.h>
#include <cdada/utils.h>
#include <cdada/__list_internal.h>

/**
* @file cdada/list_custom_cc.h
* @author Marc Sune<marcdevel (at) gmail.com>
*
* @brief This file needs to be included in a C++ file to autogenerate the
*        code necessary to use a custom type as a val/value for cdada structs.
*/

#define __CDADA_STD_LIST_TYPE(T) std::list< T >

/**
* @internal Custom type create f
*/
#define __CDADA_LIST_CUSTOM_CREATE_F(TYPE) \
	void __cdada_list_autogen_create_##TYPE (void* m){ \
		__cdada_list_int_t* s = (__cdada_list_int_t*)m; \
		s->list.custom = (void*)new __CDADA_STD_LIST_TYPE(TYPE)(); \
	}

/**
* @internal Custom type destroy f
*/
#define __CDADA_LIST_CUSTOM_DESTROY_F(TYPE) \
	void __cdada_list_autogen_destroy_##TYPE (void* m){ \
		__cdada_list_int_t* s = (__cdada_list_int_t*)m; \
		__CDADA_STD_LIST_TYPE(TYPE)* p = \
				(__CDADA_STD_LIST_TYPE(TYPE)*)s->list.custom; \
		delete p; \
	}

/**
* @internal Custom type clear f
*/
#define __CDADA_LIST_CUSTOM_CLEAR_F(TYPE) \
	void __cdada_list_autogen_clear_##TYPE (void* m){ \
		__cdada_list_int_t* s = (__cdada_list_int_t*)m; \
		__CDADA_STD_LIST_TYPE(TYPE)* p = \
				(__CDADA_STD_LIST_TYPE(TYPE)*)s->list.custom; \
		p->clear(); \
	}

/**
* @internal Custom type empty f
*/
#define __CDADA_LIST_CUSTOM_EMPTY_F(TYPE) \
	bool __cdada_list_autogen_empty_##TYPE (const void* m){ \
		__cdada_list_int_t* s = (__cdada_list_int_t*)m; \
		__CDADA_STD_LIST_TYPE(TYPE)* p = \
				(__CDADA_STD_LIST_TYPE(TYPE)*)s->list.custom; \
		return p->empty(); \
	}
/**
* @internal Custom type size f
*/
#define __CDADA_LIST_CUSTOM_SIZE_F(TYPE) \
	uint32_t __cdada_list_autogen_size_##TYPE (const void* m){ \
		__cdada_list_int_t* s = (__cdada_list_int_t*)m; \
		__CDADA_STD_LIST_TYPE(TYPE)* p = \
				(__CDADA_STD_LIST_TYPE(TYPE)*)s->list.custom; \
		return p->size(); \
	}
/**
* @internal Custom type insert f
*/
#define __CDADA_LIST_CUSTOM_INSERT_F(TYPE) \
	int __cdada_list_autogen_insert_##TYPE (void* m, const void* val, \
							const uint32_t pos){ \
		__cdada_list_int_t* s = (__cdada_list_int_t*)m; \
		__CDADA_STD_LIST_TYPE(TYPE)* p = \
				(__CDADA_STD_LIST_TYPE(TYPE)*)s->list.custom; \
		return cdada_list_insert_u< TYPE > (s, p, val, pos);\
	}

/**
* @internal Custom type get f
*/
#define __CDADA_LIST_CUSTOM_GET_F(TYPE) \
	int __cdada_list_autogen_get_##TYPE (const void* m, const uint32_t pos,\
							void* val){ \
		__cdada_list_int_t* s = (__cdada_list_int_t*)m; \
		__CDADA_STD_LIST_TYPE(TYPE)* p = \
				(__CDADA_STD_LIST_TYPE(TYPE)*)s->list.custom; \
		return cdada_list_get_u< TYPE > (s, p, pos, val);\
	}

/**
* @internal Custom type first_last f
*/
#define __CDADA_LIST_CUSTOM_FIRST_LAST_F(TYPE) \
	int __cdada_list_autogen_first_last_##TYPE (const void* m, bool first, \
							void* key){ \
		__cdada_list_int_t* s = (__cdada_list_int_t*)m; \
		__CDADA_STD_LIST_TYPE(TYPE)* p = \
				(__CDADA_STD_LIST_TYPE(TYPE)*)s->list.custom; \
		return cdada_list_first_last_u< TYPE > (s, p, first, key);\
	}

/**
* @internal Custom type erase f
*/
#define __CDADA_LIST_CUSTOM_ERASE_F(TYPE) \
	int __cdada_list_autogen_erase_##TYPE (void* m, const uint32_t pos){ \
		__cdada_list_int_t* s = (__cdada_list_int_t*)m; \
		__CDADA_STD_LIST_TYPE(TYPE)* p = \
				(__CDADA_STD_LIST_TYPE(TYPE)*)s->list.custom; \
		return cdada_list_erase_u< TYPE > (s, p, pos);\
	}

/**
* @internal Custom type remove f
*/
#define __CDADA_LIST_CUSTOM_REMOVE_F(TYPE) \
	int __cdada_list_autogen_remove_##TYPE (void* m, const void* val){ \
		__cdada_list_int_t* s = (__cdada_list_int_t*)m; \
		__CDADA_STD_LIST_TYPE(TYPE)* p = \
				(__CDADA_STD_LIST_TYPE(TYPE)*)s->list.custom; \
		return cdada_list_remove_u< TYPE > (s, p, val);\
	}

/**
* @internal Custom type push f
*/
#define __CDADA_LIST_CUSTOM_PUSH_F(TYPE) \
	int __cdada_list_autogen_push_##TYPE (void* m, const void* val,\
								bool front){ \
		__cdada_list_int_t* s = (__cdada_list_int_t*)m; \
		__CDADA_STD_LIST_TYPE(TYPE)* p = \
				(__CDADA_STD_LIST_TYPE(TYPE)*)s->list.custom; \
		return cdada_list_push_u< TYPE > (s, p, val, front);\
	}

/**
* @internal Custom type pop f
*/
#define __CDADA_LIST_CUSTOM_POP_F(TYPE) \
	int __cdada_list_autogen_pop_##TYPE (void* m, bool front){ \
		__cdada_list_int_t* s = (__cdada_list_int_t*)m; \
		__CDADA_STD_LIST_TYPE(TYPE)* p = \
				(__CDADA_STD_LIST_TYPE(TYPE)*)s->list.custom; \
		return cdada_list_pop_u< TYPE > (s, p, front);\
	}

/**
* @internal Custom type sort f
*/
#define __CDADA_LIST_CUSTOM_SORT_F(TYPE) \
	void __cdada_list_autogen_sort_##TYPE (void* m){ \
		__cdada_list_int_t* s = (__cdada_list_int_t*)m; \
		__CDADA_STD_LIST_TYPE(TYPE)* p = \
				(__CDADA_STD_LIST_TYPE(TYPE)*)s->list.custom; \
		p->sort(); \
	}

/**
* @internal Custom type reverse f
*/
#define __CDADA_LIST_CUSTOM_REVERSE_F(TYPE) \
	void __cdada_list_autogen_reverse_##TYPE (void* m){ \
		__cdada_list_int_t* s = (__cdada_list_int_t*)m; \
		__CDADA_STD_LIST_TYPE(TYPE)* p = \
				(__CDADA_STD_LIST_TYPE(TYPE)*)s->list.custom; \
		p->reverse(); \
	}

/**
* @internal Custom type unique f
*/
#define __CDADA_LIST_CUSTOM_UNIQUE_F(TYPE) \
	void __cdada_list_autogen_unique_##TYPE (void* m){ \
		__cdada_list_int_t* s = (__cdada_list_int_t*)m; \
		__CDADA_STD_LIST_TYPE(TYPE)* p = \
				(__CDADA_STD_LIST_TYPE(TYPE)*)s->list.custom; \
		p->unique(); \
	}

/**
* @internal Custom type traverse f
*/
#define __CDADA_LIST_CUSTOM_TRAVERSE_F(TYPE) \
	void __cdada_list_autogen_traverse_##TYPE (const void* m, \
							cdada_list_it f, \
							void* opaque){ \
		__cdada_list_int_t* s = (__cdada_list_int_t*)m; \
		__CDADA_STD_LIST_TYPE(TYPE)* p = \
				(__CDADA_STD_LIST_TYPE(TYPE)*)s->list.custom; \
		return cdada_list_traverse_u< TYPE > (s, p, f, opaque);\
	}

/**
* @internal Custom type rtraverse f
*/
#define __CDADA_LIST_CUSTOM_RTRAVERSE_F(TYPE) \
	void __cdada_list_autogen_rtraverse_##TYPE (const void* m, \
							cdada_list_it f, \
							void* opaque){ \
		__cdada_list_int_t* s = (__cdada_list_int_t*)m; \
		__CDADA_STD_LIST_TYPE(TYPE)* p = \
				(__CDADA_STD_LIST_TYPE(TYPE)*)s->list.custom; \
		return cdada_list_rtraverse_u< TYPE > (s, p, f, opaque);\
	}

/**
* @internal Custom type dump f
*/
#define __CDADA_LIST_CUSTOM_DUMP_F(TYPE) \
	void __cdada_list_autogen_dump_##TYPE (const void* m, \
							std::stringstream& ss){\
		__cdada_list_int_t* s = (__cdada_list_int_t*)m; \
		__CDADA_STD_LIST_TYPE(TYPE)* p = \
				(__CDADA_STD_LIST_TYPE(TYPE)*)s->list.custom; \
		return cdada_list_dump_u< TYPE > (s, p, ss);\
	}

/**
* @internal Create ops func ptrs struct
*/
#define __CDADA_LIST_CUSTOM_OPS(TYPE) \
	__cdada_list_ops_t __cdada_list_autogen_##TYPE = { \
		__cdada_list_autogen_create_##TYPE, \
		__cdada_list_autogen_destroy_##TYPE, \
		__cdada_list_autogen_clear_##TYPE, \
		__cdada_list_autogen_empty_##TYPE, \
		__cdada_list_autogen_size_##TYPE, \
		__cdada_list_autogen_insert_##TYPE, \
		__cdada_list_autogen_get_##TYPE, \
		__cdada_list_autogen_first_last_##TYPE, \
		__cdada_list_autogen_erase_##TYPE, \
		__cdada_list_autogen_remove_##TYPE, \
		__cdada_list_autogen_push_##TYPE, \
		__cdada_list_autogen_pop_##TYPE, \
		__cdada_list_autogen_sort_##TYPE, \
		__cdada_list_autogen_reverse_##TYPE, \
		__cdada_list_autogen_unique_##TYPE, \
		__cdada_list_autogen_traverse_##TYPE, \
		__cdada_list_autogen_rtraverse_##TYPE, \
		__cdada_list_autogen_dump_##TYPE, \
		}

/**
* Auto-generate (instantiate) new custom type list, with TYPE
*/
#define CDADA_LIST_CUSTOM_GEN(TYPE) 	\
	__CDADA_LIST_CUSTOM_CREATE_F(TYPE); \
	__CDADA_LIST_CUSTOM_DESTROY_F(TYPE); \
	__CDADA_LIST_CUSTOM_CLEAR_F(TYPE); \
	__CDADA_LIST_CUSTOM_EMPTY_F(TYPE); \
	__CDADA_LIST_CUSTOM_SIZE_F(TYPE); \
	__CDADA_LIST_CUSTOM_INSERT_F(TYPE); \
	__CDADA_LIST_CUSTOM_GET_F(TYPE); \
	__CDADA_LIST_CUSTOM_FIRST_LAST_F(TYPE); \
	__CDADA_LIST_CUSTOM_ERASE_F(TYPE); \
	__CDADA_LIST_CUSTOM_REMOVE_F(TYPE); \
	__CDADA_LIST_CUSTOM_PUSH_F(TYPE); \
	__CDADA_LIST_CUSTOM_POP_F(TYPE); \
	__CDADA_LIST_CUSTOM_SORT_F(TYPE); \
	__CDADA_LIST_CUSTOM_REVERSE_F(TYPE); \
	__CDADA_LIST_CUSTOM_UNIQUE_F(TYPE); \
	__CDADA_LIST_CUSTOM_TRAVERSE_F(TYPE); \
	__CDADA_LIST_CUSTOM_RTRAVERSE_F(TYPE); \
	__CDADA_LIST_CUSTOM_DUMP_F(TYPE); \
	__CDADA_LIST_CUSTOM_OPS(TYPE)

#undef __CDADA_INTERNAL_INCLUDE

#endif //__CDADA_LIST_CUSTOM_CC_H__
