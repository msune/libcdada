/*
Copyright (c) 2020, Peter Dobransky
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

#ifndef __CDADA_QUEUE_CUSTOM_CC_H__
#define __CDADA_QUEUE_CUSTOM_CC_H__

//This header should _always_ be included from C++
#ifndef __cplusplus
	#error CDADA autogenreation headers shall be included only from C++ files
#endif //__cplusplus

#define __CDADA_INTERNAL_INCLUDE

#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include <cdada/queue.h>
#include <cdada/utils.h>
#include <cdada/__queue_internal.h>

/**
* @file cdada/queue_custom_cc.h
* @author Peter Dobransky<pdobransky101 (at) gmail.com>
*
* @brief This file needs to be included in a C++ file to autogenerate the
*        code necessary to use a custom type as a val/value for cdada structs.
*/

#define __CDADA_STD_QUEUE_TYPE(T) std::queue< T >

/**
* @internal Custom type create f
*/
#define __CDADA_QUEUE_CUSTOM_CREATE_F(TYPE) \
	void __cdada_queue_autogen_create_##TYPE (void* m){ \
		__cdada_queue_int_t* s = (__cdada_queue_int_t*)m; \
		s->queue.custom = (void*)new __CDADA_STD_QUEUE_TYPE(TYPE)(); \
	}

/**
* @internal Custom type destroy f
*/
#define __CDADA_QUEUE_CUSTOM_DESTROY_F(TYPE) \
	void __cdada_queue_autogen_destroy_##TYPE (void* m){ \
		__cdada_queue_int_t* s = (__cdada_queue_int_t*)m; \
		__CDADA_STD_QUEUE_TYPE(TYPE)* p = \
				(__CDADA_STD_QUEUE_TYPE(TYPE)*)s->queue.custom; \
		delete p; \
	}

/**
* @internal Custom type empty f
*/
#define __CDADA_QUEUE_CUSTOM_EMPTY_F(TYPE) \
	bool __cdada_queue_autogen_empty_##TYPE (const void* m){ \
		__cdada_queue_int_t* s = (__cdada_queue_int_t*)m; \
		__CDADA_STD_QUEUE_TYPE(TYPE)* p = \
				(__CDADA_STD_QUEUE_TYPE(TYPE)*)s->queue.custom; \
		return p->empty(); \
	}
/**
* @internal Custom type size f
*/
#define __CDADA_QUEUE_CUSTOM_SIZE_F(TYPE) \
	uint32_t __cdada_queue_autogen_size_##TYPE (const void* m){ \
		__cdada_queue_int_t* s = (__cdada_queue_int_t*)m; \
		__CDADA_STD_QUEUE_TYPE(TYPE)* p = \
				(__CDADA_STD_QUEUE_TYPE(TYPE)*)s->queue.custom; \
		return p->size(); \
	}

/**
* @internal Custom type push f
*/
#define __CDADA_QUEUE_CUSTOM_PUSH_F(TYPE) \
	int __cdada_queue_autogen_push_##TYPE (void* m, const void* val){ \
		__cdada_queue_int_t* s = (__cdada_queue_int_t*)m; \
		__CDADA_STD_QUEUE_TYPE(TYPE)* p = \
				(__CDADA_STD_QUEUE_TYPE(TYPE)*)s->queue.custom; \
		return cdada_queue_push_u< TYPE > (s, p, val);\
	}

/**
* @internal Custom type pop f
*/
#define __CDADA_QUEUE_CUSTOM_POP_F(TYPE) \
	int __cdada_queue_autogen_pop_##TYPE (void* m){ \
		__cdada_queue_int_t* s = (__cdada_queue_int_t*)m; \
		__CDADA_STD_QUEUE_TYPE(TYPE)* p = \
				(__CDADA_STD_QUEUE_TYPE(TYPE)*)s->queue.custom; \
		return cdada_queue_pop_u< TYPE > (s, p);\
	}

/**
* @internal Custom type front f
*/
#define __CDADA_QUEUE_CUSTOM_FRONT_F(TYPE) \
	int __cdada_queue_autogen_front_##TYPE (const void* m, void* val){ \
		__cdada_queue_int_t* s = (__cdada_queue_int_t*)m; \
		__CDADA_STD_QUEUE_TYPE(TYPE)* p = \
				(__CDADA_STD_QUEUE_TYPE(TYPE)*)s->queue.custom; \
		return cdada_queue_front_u< TYPE > (s, p, val);\
	}

/**
* @internal Custom type back f
*/
#define __CDADA_QUEUE_CUSTOM_BACK_F(TYPE) \
	int __cdada_queue_autogen_back_##TYPE (const void* m, void* val){ \
		__cdada_queue_int_t* s = (__cdada_queue_int_t*)m; \
		__CDADA_STD_QUEUE_TYPE(TYPE)* p = \
				(__CDADA_STD_QUEUE_TYPE(TYPE)*)s->queue.custom; \
		return cdada_queue_back_u< TYPE > (s, p, val);\
	}

/**
* @internal Custom type dump f
*/
#define __CDADA_QUEUE_CUSTOM_DUMP_F(TYPE) \
	void __cdada_queue_autogen_dump_##TYPE (const void* m, \
							std::stringstream& ss){\
		__cdada_queue_int_t* s = (__cdada_queue_int_t*)m; \
		__CDADA_STD_QUEUE_TYPE(TYPE)* p = \
				(__CDADA_STD_QUEUE_TYPE(TYPE)*)s->queue.custom;\
		return cdada_queue_dump_u< TYPE > (s, p, ss);\
	}

/**
* @internal Create ops func ptrs struct
*/
#define __CDADA_QUEUE_CUSTOM_OPS(TYPE) \
	__cdada_queue_ops_t __cdada_queue_autogen_##TYPE = { \
		.create  = __cdada_queue_autogen_create_##TYPE, \
		.destroy = __cdada_queue_autogen_destroy_##TYPE, \
		.empty = __cdada_queue_autogen_empty_##TYPE, \
		.size = __cdada_queue_autogen_size_##TYPE, \
		.push = __cdada_queue_autogen_push_##TYPE, \
		.pop = __cdada_queue_autogen_pop_##TYPE, \
		.front = __cdada_queue_autogen_front_##TYPE, \
		.back = __cdada_queue_autogen_back_##TYPE, \
		.dump = __cdada_queue_autogen_dump_##TYPE, \
		}

/**
* Auto-generate (instantiate) new custom type queue, with TYPE
*/
#define CDADA_QUEUE_CUSTOM_GEN(TYPE) 	\
	__CDADA_QUEUE_CUSTOM_CREATE_F(TYPE); \
	__CDADA_QUEUE_CUSTOM_DESTROY_F(TYPE); \
	__CDADA_QUEUE_CUSTOM_EMPTY_F(TYPE); \
	__CDADA_QUEUE_CUSTOM_SIZE_F(TYPE); \
	__CDADA_QUEUE_CUSTOM_PUSH_F(TYPE); \
	__CDADA_QUEUE_CUSTOM_POP_F(TYPE); \
	__CDADA_QUEUE_CUSTOM_FRONT_F(TYPE); \
	__CDADA_QUEUE_CUSTOM_BACK_F(TYPE); \
	__CDADA_QUEUE_CUSTOM_DUMP_F(TYPE); \
	__CDADA_QUEUE_CUSTOM_OPS(TYPE)

#undef __CDADA_INTERNAL_INCLUDE

#endif //__CDADA_QUEUE_CUSTOM_CC_H__
