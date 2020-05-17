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

#ifndef __CDATA_SET_CUSTOM_CC_H__
#define __CDATA_SET_CUSTOM_CC_H__

//This header should _always_ be included from C++
#ifndef __cplusplus
	#error CDATA autogenreation headers shall be included only from C++ files
#endif //__cplusplus

#define __CDATA_INTERNAL_INCLUDE

#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include <cdata/set.h>
#include <cdata/utils.h>
#include <cdata/__set_internal.h>

/**
* @file cdata/set_custom_cc.h
* @author Marc Sune<marcdevel (at) gmail.com>
*
* @brief This file needs to be included in a C++ file to autogenerate the
*        code necessary to use a custom type as a key/value for cdata structs.
*/

#define __CDATA_STD_SET_TYPE(T) std::set< T >

/**
* @internal Custom type create f
*/
#define __CDATA_SET_CUSTOM_CREATE_F(TYPE) \
	void __cdata_set_autogen_create_##TYPE (void* m){ \
		__cdata_set_int_t* s = (__cdata_set_int_t*)m; \
		s->set.custom = (void*)new __CDATA_STD_SET_TYPE(TYPE)(); \
	}

/**
* @internal Custom type destroy f
*/
#define __CDATA_SET_CUSTOM_DESTROY_F(TYPE) \
	void __cdata_set_autogen_destroy_##TYPE (void* m){ \
		__cdata_set_int_t* s = (__cdata_set_int_t*)m; \
		__CDATA_STD_SET_TYPE(TYPE)* p = \
				(__CDATA_STD_SET_TYPE(TYPE)*)s->set.custom; \
		delete p; \
	}

/**
* @internal Custom type clear f
*/
#define __CDATA_SET_CUSTOM_CLEAR_F(TYPE) \
	void __cdata_set_autogen_clear_##TYPE (void* m){ \
		__cdata_set_int_t* s = (__cdata_set_int_t*)m; \
		__CDATA_STD_SET_TYPE(TYPE)* p = \
				(__CDATA_STD_SET_TYPE(TYPE)*)s->set.custom; \
		p->clear(); \
	}

/**
* @internal Custom type empty f
*/
#define __CDATA_SET_CUSTOM_EMPTY_F(TYPE) \
	bool __cdata_set_autogen_empty_##TYPE (void* m){ \
		__cdata_set_int_t* s = (__cdata_set_int_t*)m; \
		__CDATA_STD_SET_TYPE(TYPE)* p = \
				(__CDATA_STD_SET_TYPE(TYPE)*)s->set.custom; \
		return p->empty(); \
	}
/**
* @internal Custom type size f
*/
#define __CDATA_SET_CUSTOM_SIZE_F(TYPE) \
	uint32_t __cdata_set_autogen_size_##TYPE (void* m){ \
		__cdata_set_int_t* s = (__cdata_set_int_t*)m; \
		__CDATA_STD_SET_TYPE(TYPE)* p = \
				(__CDATA_STD_SET_TYPE(TYPE)*)s->set.custom; \
		return p->size(); \
	}
/**
* @internal Custom type insert f
*/
#define __CDATA_SET_CUSTOM_INSERT_F(TYPE) \
	int __cdata_set_autogen_insert_##TYPE (void* m, const void* key){ \
		__cdata_set_int_t* s = (__cdata_set_int_t*)m; \
		__CDATA_STD_SET_TYPE(TYPE)* p = \
				(__CDATA_STD_SET_TYPE(TYPE)*)s->set.custom; \
		return cdata_set_insert_u< TYPE > (s, p, key);\
	}
/**
* @internal Custom type erase f
*/
#define __CDATA_SET_CUSTOM_ERASE_F(TYPE) \
	int __cdata_set_autogen_erase_##TYPE (void* m, const void* key){ \
		__cdata_set_int_t* s = (__cdata_set_int_t*)m; \
		__CDATA_STD_SET_TYPE(TYPE)* p = \
				(__CDATA_STD_SET_TYPE(TYPE)*)s->set.custom; \
		return cdata_set_erase_u< TYPE > (s, p, key);\
	}

/**
* @internal Custom type find f
*/
#define __CDATA_SET_CUSTOM_FIND_F(TYPE) \
	bool __cdata_set_autogen_find_##TYPE (void* m, const void* key){ \
		__cdata_set_int_t* s = (__cdata_set_int_t*)m; \
		__CDATA_STD_SET_TYPE(TYPE)* p = \
				(__CDATA_STD_SET_TYPE(TYPE)*)s->set.custom; \
		return cdata_set_find_u< TYPE > (s, p, key);\
	}

/**
* @internal Custom type traverse f
*/
#define __CDATA_SET_CUSTOM_TRAVERSE_F(TYPE) \
	void __cdata_set_autogen_traverse_##TYPE (void* m, cdata_set_it f, \
								void* opaque){ \
		__cdata_set_int_t* s = (__cdata_set_int_t*)m; \
		__CDATA_STD_SET_TYPE(TYPE)* p = \
				(__CDATA_STD_SET_TYPE(TYPE)*)s->set.custom; \
		return cdata_set_traverse_u< TYPE > (s, p, f, opaque);\
	}

/**
* @internal Custom type rtraverse f
*/
#define __CDATA_SET_CUSTOM_RTRAVERSE_F(TYPE) \
	void __cdata_set_autogen_rtraverse_##TYPE (void* m, cdata_set_it f, \
								void* opaque){ \
		__cdata_set_int_t* s = (__cdata_set_int_t*)m; \
		__CDATA_STD_SET_TYPE(TYPE)* p = \
				(__CDATA_STD_SET_TYPE(TYPE)*)s->set.custom; \
		return cdata_set_rtraverse_u< TYPE > (s, p, f, opaque);\
	}


/**
* @internal Create ops func ptrs struct
*/
#define __CDATA_SET_CUSTOM_OPS(TYPE) \
	__cdata_set_ops_t __cdata_set_autogen_##TYPE = { \
		.create  = __cdata_set_autogen_create_##TYPE, \
		.destroy = __cdata_set_autogen_destroy_##TYPE, \
		.clear = __cdata_set_autogen_clear_##TYPE, \
		.empty = __cdata_set_autogen_empty_##TYPE, \
		.size = __cdata_set_autogen_size_##TYPE, \
		.insert = __cdata_set_autogen_insert_##TYPE, \
		.erase = __cdata_set_autogen_erase_##TYPE, \
		.find = __cdata_set_autogen_find_##TYPE, \
		.traverse = __cdata_set_autogen_traverse_##TYPE, \
		.rtraverse = __cdata_set_autogen_rtraverse_##TYPE, \
		}

/**
* @internal Default memcp comparison operator
*/
#define __CDATA_SET_CUSTOM_GEN_MEMCP_OP(TYPE) \
	inline bool operator<(const TYPE & a1, const TYPE & a2){ \
		return memcmp((const void*)&a1, (const void*)&a2, \
						sizeof( TYPE )) < 0; \
	}

/**
* @brief Auto-generate (instantiate) new custom type set, with TYPE
*
* This MACRO shall only be used when a custom operator< wants to be used, and
* it has to be defined beforehand.
*/
#define CDATA_SET_CUSTOM_GEN_NO_MEMCP(TYPE) 	\
	__CDATA_SET_CUSTOM_CREATE_F(TYPE); \
	__CDATA_SET_CUSTOM_DESTROY_F(TYPE); \
	__CDATA_SET_CUSTOM_CLEAR_F(TYPE); \
	__CDATA_SET_CUSTOM_EMPTY_F(TYPE); \
	__CDATA_SET_CUSTOM_SIZE_F(TYPE); \
	__CDATA_SET_CUSTOM_INSERT_F(TYPE); \
	__CDATA_SET_CUSTOM_ERASE_F(TYPE); \
	__CDATA_SET_CUSTOM_FIND_F(TYPE); \
	__CDATA_SET_CUSTOM_TRAVERSE_F(TYPE); \
	__CDATA_SET_CUSTOM_RTRAVERSE_F(TYPE); \
	__CDATA_SET_CUSTOM_OPS(TYPE)

/**
* Auto-generate (instantiate) new custom type set, with TYPE
*/
#define CDATA_SET_CUSTOM_GEN(TYPE) 	\
	__CDATA_SET_CUSTOM_GEN_MEMCP_OP(TYPE); \
	CDATA_SET_CUSTOM_GEN_NO_MEMCP(TYPE)

#undef __CDATA_INTERNAL_INCLUDE

#endif //__CDATA_SET_CUSTOM_CC_H__
