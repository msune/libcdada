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

#ifndef __CDADA_SET_CUSTOM_CC_H__
#define __CDADA_SET_CUSTOM_CC_H__

//This header should _always_ be included from C++
#ifndef __cplusplus
	#error CDADA autogenreation headers shall be included only from C++ files
#endif //__cplusplus

#define __CDADA_INTERNAL_INCLUDE

#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include <cdada/set.h>
#include <cdada/utils.h>
#include <cdada/__set_internal.h>

/**
* @file cdada/set_custom_cc.h
* @author Marc Sune<marcdevel (at) gmail.com>
*
* @brief This file needs to be included in a C++ file to autogenerate the
*        code necessary to use a custom type as a key/value for cdada structs.
*/

#define __CDADA_STD_SET_TYPE(T) std::set< T >

/**
* @internal Custom type create f
*/
#define __CDADA_SET_CUSTOM_CREATE_F(TYPE) \
	void __cdada_set_autogen_create_##TYPE (void* m){ \
		__cdada_set_int_t* s = (__cdada_set_int_t*)m; \
		s->set.custom = (void*)new __CDADA_STD_SET_TYPE(TYPE)(); \
	}

/**
* @internal Custom type destroy f
*/
#define __CDADA_SET_CUSTOM_DESTROY_F(TYPE) \
	void __cdada_set_autogen_destroy_##TYPE (void* m){ \
		__cdada_set_int_t* s = (__cdada_set_int_t*)m; \
		__CDADA_STD_SET_TYPE(TYPE)* p = \
				(__CDADA_STD_SET_TYPE(TYPE)*)s->set.custom; \
		delete p; \
	}

/**
* @internal Custom type clear f
*/
#define __CDADA_SET_CUSTOM_CLEAR_F(TYPE) \
	void __cdada_set_autogen_clear_##TYPE (void* m){ \
		__cdada_set_int_t* s = (__cdada_set_int_t*)m; \
		__CDADA_STD_SET_TYPE(TYPE)* p = \
				(__CDADA_STD_SET_TYPE(TYPE)*)s->set.custom; \
		p->clear(); \
	}

/**
* @internal Custom type empty f
*/
#define __CDADA_SET_CUSTOM_EMPTY_F(TYPE) \
	bool __cdada_set_autogen_empty_##TYPE (const void* m){ \
		__cdada_set_int_t* s = (__cdada_set_int_t*)m; \
		__CDADA_STD_SET_TYPE(TYPE)* p = \
				(__CDADA_STD_SET_TYPE(TYPE)*)s->set.custom; \
		return p->empty(); \
	}
/**
* @internal Custom type size f
*/
#define __CDADA_SET_CUSTOM_SIZE_F(TYPE) \
	uint32_t __cdada_set_autogen_size_##TYPE (const void* m){ \
		__cdada_set_int_t* s = (__cdada_set_int_t*)m; \
		__CDADA_STD_SET_TYPE(TYPE)* p = \
				(__CDADA_STD_SET_TYPE(TYPE)*)s->set.custom; \
		return p->size(); \
	}
/**
* @internal Custom type insert f
*/
#define __CDADA_SET_CUSTOM_INSERT_F(TYPE) \
	int __cdada_set_autogen_insert_##TYPE (void* m, const void* key){ \
		__cdada_set_int_t* s = (__cdada_set_int_t*)m; \
		__CDADA_STD_SET_TYPE(TYPE)* p = \
				(__CDADA_STD_SET_TYPE(TYPE)*)s->set.custom; \
		return cdada_set_insert_u< TYPE > (s, p, key);\
	}
/**
* @internal Custom type erase f
*/
#define __CDADA_SET_CUSTOM_ERASE_F(TYPE) \
	int __cdada_set_autogen_erase_##TYPE (void* m, const void* key){ \
		__cdada_set_int_t* s = (__cdada_set_int_t*)m; \
		__CDADA_STD_SET_TYPE(TYPE)* p = \
				(__CDADA_STD_SET_TYPE(TYPE)*)s->set.custom; \
		return cdada_set_erase_u< TYPE > (s, p, key);\
	}

/**
* @internal Custom type find f
*/
#define __CDADA_SET_CUSTOM_FIND_F(TYPE) \
	bool __cdada_set_autogen_find_##TYPE (const void* m, const void* key){ \
		__cdada_set_int_t* s = (__cdada_set_int_t*)m; \
		__CDADA_STD_SET_TYPE(TYPE)* p = \
				(__CDADA_STD_SET_TYPE(TYPE)*)s->set.custom; \
		return cdada_set_find_u< TYPE > (s, p, key);\
	}

/**
* @internal Custom type first_last f
*/
#define __CDADA_SET_CUSTOM_FIRST_LAST_F(TYPE) \
	int __cdada_set_autogen_first_last_##TYPE (const void* m, bool first, \
							void* key){ \
		__cdada_set_int_t* s = (__cdada_set_int_t*)m; \
		__CDADA_STD_SET_TYPE(TYPE)* p = \
				(__CDADA_STD_SET_TYPE(TYPE)*)s->set.custom; \
		return cdada_set_first_last_u< TYPE > (s, p, first, key);\
	}

/**
* @internal Custom type traverse f
*/
#define __CDADA_SET_CUSTOM_TRAVERSE_F(TYPE) \
	void __cdada_set_autogen_traverse_##TYPE (const void* m, \
							cdada_set_it f, \
							void* opaque){ \
		__cdada_set_int_t* s = (__cdada_set_int_t*)m; \
		__CDADA_STD_SET_TYPE(TYPE)* p = \
				(__CDADA_STD_SET_TYPE(TYPE)*)s->set.custom; \
		return cdada_set_traverse_u< TYPE > (s, p, f, opaque);\
	}

/**
* @internal Custom type rtraverse f
*/
#define __CDADA_SET_CUSTOM_RTRAVERSE_F(TYPE) \
	void __cdada_set_autogen_rtraverse_##TYPE (const void* m, \
							cdada_set_it f, \
							void* opaque){ \
		__cdada_set_int_t* s = (__cdada_set_int_t*)m; \
		__CDADA_STD_SET_TYPE(TYPE)* p = \
				(__CDADA_STD_SET_TYPE(TYPE)*)s->set.custom; \
		return cdada_set_rtraverse_u< TYPE > (s, p, f, opaque);\
	}

/**
* @internal Custom type dump f
*/
#define __CDADA_SET_CUSTOM_DUMP_F(TYPE) \
	void __cdada_set_autogen_dump_##TYPE (const void* m, \
							std::stringstream& ss){\
		__cdada_set_int_t* s = (__cdada_set_int_t*)m; \
		__CDADA_STD_SET_TYPE(TYPE)* p = \
				(__CDADA_STD_SET_TYPE(TYPE)*)s->set.custom; \
		return cdada_set_dump_u< TYPE > (s, p, ss);\
	}

/**
* @internal Create ops func ptrs struct
*/
#define __CDADA_SET_CUSTOM_OPS(TYPE) \
	__cdada_set_ops_t __cdada_set_autogen_##TYPE = { \
		__cdada_set_autogen_create_##TYPE, \
		__cdada_set_autogen_destroy_##TYPE, \
		__cdada_set_autogen_clear_##TYPE, \
		__cdada_set_autogen_empty_##TYPE, \
		__cdada_set_autogen_size_##TYPE, \
		__cdada_set_autogen_insert_##TYPE, \
		__cdada_set_autogen_erase_##TYPE, \
		__cdada_set_autogen_find_##TYPE, \
		__cdada_set_autogen_first_last_##TYPE, \
		__cdada_set_autogen_traverse_##TYPE, \
		__cdada_set_autogen_rtraverse_##TYPE, \
		__cdada_set_autogen_dump_##TYPE, \
		}

/**
* Auto-generate (instantiate) new custom type set, with TYPE
*/
#define CDADA_SET_CUSTOM_GEN(TYPE) 	\
	__CDADA_SET_CUSTOM_CREATE_F(TYPE); \
	__CDADA_SET_CUSTOM_DESTROY_F(TYPE); \
	__CDADA_SET_CUSTOM_CLEAR_F(TYPE); \
	__CDADA_SET_CUSTOM_EMPTY_F(TYPE); \
	__CDADA_SET_CUSTOM_SIZE_F(TYPE); \
	__CDADA_SET_CUSTOM_INSERT_F(TYPE); \
	__CDADA_SET_CUSTOM_ERASE_F(TYPE); \
	__CDADA_SET_CUSTOM_FIND_F(TYPE); \
	__CDADA_SET_CUSTOM_FIRST_LAST_F(TYPE); \
	__CDADA_SET_CUSTOM_TRAVERSE_F(TYPE); \
	__CDADA_SET_CUSTOM_RTRAVERSE_F(TYPE); \
	__CDADA_SET_CUSTOM_DUMP_F(TYPE); \
	__CDADA_SET_CUSTOM_OPS(TYPE)

#undef __CDADA_INTERNAL_INCLUDE

#endif //__CDADA_SET_CUSTOM_CC_H__
