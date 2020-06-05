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

#ifndef __CDADA_MAP_CUSTOM_CC_H__
#define __CDADA_MAP_CUSTOM_CC_H__

//This header should _always_ be included from C++
#ifndef __cplusplus
	#error CDADA autogenreation headers shall be included only from C++ files
#endif //__cplusplus

#define __CDADA_INTERNAL_INCLUDE

#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include <cdada/map.h>
#include <cdada/utils.h>
#include <cdada/__map_internal.h>

/**
* @file cdada/map_custom_cc.h
* @author Marc Sune<marcdevel (at) gmail.com>
*
* @brief This file needs to be included in a C++ file to autogenerate the
*        code necessary to use a custom type as a key/value for cdada structs.
*/

#define __CDADA_STD_MAP_TYPE(T) std::map< T , void* >

/**
* @internal Custom type create f
*/
#define __CDADA_MAP_CUSTOM_CREATE_F(TYPE) \
	void __cdada_map_autogen_create_##TYPE (void* m){ \
		__cdada_map_int_t* s = (__cdada_map_int_t*)m; \
		s->map.custom = (void*)new __CDADA_STD_MAP_TYPE(TYPE)(); \
	}

/**
* @internal Custom type destroy f
*/
#define __CDADA_MAP_CUSTOM_DESTROY_F(TYPE) \
	void __cdada_map_autogen_destroy_##TYPE (void* m){ \
		__cdada_map_int_t* s = (__cdada_map_int_t*)m; \
		__CDADA_STD_MAP_TYPE(TYPE)* p = \
				(__CDADA_STD_MAP_TYPE(TYPE)*)s->map.custom; \
		delete p; \
	}

/**
* @internal Custom type clear f
*/
#define __CDADA_MAP_CUSTOM_CLEAR_F(TYPE) \
	void __cdada_map_autogen_clear_##TYPE (void* m){ \
		__cdada_map_int_t* s = (__cdada_map_int_t*)m; \
		__CDADA_STD_MAP_TYPE(TYPE)* p = \
				(__CDADA_STD_MAP_TYPE(TYPE)*)s->map.custom; \
		p->clear(); \
	}

/**
* @internal Custom type empty f
*/
#define __CDADA_MAP_CUSTOM_EMPTY_F(TYPE) \
	bool __cdada_map_autogen_empty_##TYPE (const void* m){ \
		__cdada_map_int_t* s = (__cdada_map_int_t*)m; \
		__CDADA_STD_MAP_TYPE(TYPE)* p = \
				(__CDADA_STD_MAP_TYPE(TYPE)*)s->map.custom; \
		return p->empty(); \
	}
/**
* @internal Custom type size f
*/
#define __CDADA_MAP_CUSTOM_SIZE_F(TYPE) \
	uint32_t __cdada_map_autogen_size_##TYPE (const void* m){ \
		__cdada_map_int_t* s = (__cdada_map_int_t*)m; \
		__CDADA_STD_MAP_TYPE(TYPE)* p = \
				(__CDADA_STD_MAP_TYPE(TYPE)*)s->map.custom; \
		return p->size(); \
	}
/**
* @internal Custom type insert f
*/
#define __CDADA_MAP_CUSTOM_INSERT_F(TYPE) \
	int __cdada_map_autogen_insert_##TYPE (void* m, const void* key, \
							void* val){ \
		__cdada_map_int_t* s = (__cdada_map_int_t*)m; \
		__CDADA_STD_MAP_TYPE(TYPE)* p = \
				(__CDADA_STD_MAP_TYPE(TYPE)*)s->map.custom; \
		return cdada_map_insert_u< TYPE > (s, p, key, val);\
	}
/**
* @internal Custom type erase f
*/
#define __CDADA_MAP_CUSTOM_ERASE_F(TYPE) \
	int __cdada_map_autogen_erase_##TYPE (void* m, const void* key){ \
		__cdada_map_int_t* s = (__cdada_map_int_t*)m; \
		__CDADA_STD_MAP_TYPE(TYPE)* p = \
				(__CDADA_STD_MAP_TYPE(TYPE)*)s->map.custom; \
		return cdada_map_erase_u< TYPE > (s, p, key);\
	}

/**
* @internal Custom type find f
*/
#define __CDADA_MAP_CUSTOM_FIND_F(TYPE) \
	int __cdada_map_autogen_find_##TYPE (const void* m, const void* key, \
							void** val){ \
		__cdada_map_int_t* s = (__cdada_map_int_t*)m; \
		__CDADA_STD_MAP_TYPE(TYPE)* p = \
				(__CDADA_STD_MAP_TYPE(TYPE)*)s->map.custom; \
		return cdada_map_find_u< TYPE > (s, p, key, val);\
	}

/**
* @internal Custom type first_last f
*/
#define __CDADA_MAP_CUSTOM_FIRST_LAST_F(TYPE) \
	int __cdada_map_autogen_first_last_##TYPE (const void* m, bool first, \
							void* key, \
							void** val){ \
		__cdada_map_int_t* s = (__cdada_map_int_t*)m; \
		__CDADA_STD_MAP_TYPE(TYPE)* p = \
				(__CDADA_STD_MAP_TYPE(TYPE)*)s->map.custom; \
		return cdada_map_first_last_u< TYPE > (s, p, first, key, val);\
	}

/**
* @internal Custom type traverse f
*/
#define __CDADA_MAP_CUSTOM_TRAVERSE_F(TYPE) \
	void __cdada_map_autogen_traverse_##TYPE (const void* m, \
							cdada_map_it f, \
							void* opaque){ \
		__cdada_map_int_t* s = (__cdada_map_int_t*)m; \
		__CDADA_STD_MAP_TYPE(TYPE)* p = \
				(__CDADA_STD_MAP_TYPE(TYPE)*)s->map.custom; \
		return cdada_map_traverse_u< TYPE > (s, p, f, opaque);\
	}

/**
* @internal Custom type rtraverse f
*/
#define __CDADA_MAP_CUSTOM_RTRAVERSE_F(TYPE) \
	void __cdada_map_autogen_rtraverse_##TYPE (const void* m, \
							cdada_map_it f, \
							void* opaque){ \
		__cdada_map_int_t* s = (__cdada_map_int_t*)m; \
		__CDADA_STD_MAP_TYPE(TYPE)* p = \
				(__CDADA_STD_MAP_TYPE(TYPE)*)s->map.custom; \
		return cdada_map_rtraverse_u< TYPE > (s, p, f, opaque);\
	}

/**
* @internal Custom type dump f
*/
#define __CDADA_MAP_CUSTOM_DUMP_F(TYPE) \
	void __cdada_map_autogen_dump_##TYPE (const void* m, \
							std::stringstream& ss){\
		__cdada_map_int_t* s = (__cdada_map_int_t*)m; \
		__CDADA_STD_MAP_TYPE(TYPE)* p = \
				(__CDADA_STD_MAP_TYPE(TYPE)*)s->map.custom; \
		return cdada_map_dump_u< TYPE > (s, p, ss);\
	}

/**
* @internal Create ops func ptrs struct
*/
#define __CDADA_MAP_CUSTOM_OPS(TYPE) \
	__cdada_map_ops_t __cdada_map_autogen_##TYPE = { \
		.create  = __cdada_map_autogen_create_##TYPE, \
		.destroy = __cdada_map_autogen_destroy_##TYPE, \
		.clear = __cdada_map_autogen_clear_##TYPE, \
		.empty = __cdada_map_autogen_empty_##TYPE, \
		.size = __cdada_map_autogen_size_##TYPE, \
		.insert = __cdada_map_autogen_insert_##TYPE, \
		.erase = __cdada_map_autogen_erase_##TYPE, \
		.find = __cdada_map_autogen_find_##TYPE, \
		.first_last = __cdada_map_autogen_first_last_##TYPE, \
		.traverse = __cdada_map_autogen_traverse_##TYPE, \
		.rtraverse = __cdada_map_autogen_rtraverse_##TYPE, \
		.dump = __cdada_map_autogen_dump_##TYPE, \
		}

/**
* Auto-generate (instantiate) new custom type map, with TYPE
*/
#define CDADA_MAP_CUSTOM_GEN(TYPE) 	\
	__CDADA_MAP_CUSTOM_CREATE_F(TYPE); \
	__CDADA_MAP_CUSTOM_DESTROY_F(TYPE); \
	__CDADA_MAP_CUSTOM_CLEAR_F(TYPE); \
	__CDADA_MAP_CUSTOM_EMPTY_F(TYPE); \
	__CDADA_MAP_CUSTOM_SIZE_F(TYPE); \
	__CDADA_MAP_CUSTOM_INSERT_F(TYPE); \
	__CDADA_MAP_CUSTOM_ERASE_F(TYPE); \
	__CDADA_MAP_CUSTOM_FIND_F(TYPE); \
	__CDADA_MAP_CUSTOM_FIRST_LAST_F(TYPE); \
	__CDADA_MAP_CUSTOM_TRAVERSE_F(TYPE); \
	__CDADA_MAP_CUSTOM_RTRAVERSE_F(TYPE); \
	__CDADA_MAP_CUSTOM_DUMP_F(TYPE); \
	__CDADA_MAP_CUSTOM_OPS(TYPE)

#undef __CDADA_INTERNAL_INCLUDE

#endif //__CDADA_MAP_CUSTOM_CC_H__
