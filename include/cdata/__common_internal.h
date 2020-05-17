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

#ifndef __CDATA_COMMON_INT__
#define __CDATA_COMMON_INT__

//Internal headers should never be directly included
#ifndef __CDATA_INTERNAL_INCLUDE
	#error CDATA internal headers shall not be directly included
#endif //__CDATA_INTERNAL_INCLUDE

//This header should _always_ be included from C++
#ifndef __cplusplus
	#error CDATA autogenreation headers shall be included only from C++ files
#endif //__cplusplus

#include <stdbool.h>
#include <stdint.h>
#include <assert.h>
#include <string.h>
#include "cdata/utils.h"
#include <map>

/**
* @file cdata/common_int.h
* @author Marc Sune<marcdevel (at) gmail.com>
*
* @brief Common MACROs and utility functions
*/

//Magic num
#define CDATA_MAGIC 0xCAFEBABE

//Branch prediction
#if defined(__GNUC__) || defined(__INTEL_COMPILER)
	#ifndef likely
		#define likely(x) __builtin_expect(((x)),1)
	#endif

	#ifndef unlikely
		#define unlikely(x) __builtin_expect(((x)),0)
	#endif
#else
	#ifndef likely
		#define likely(x) x
	#endif
	#ifndef unlikely
		#define unlikely(x) x
	#endif
#endif //GCC, ICC

#define CDATA_ASSERT(COND) assert(COND)

//Necessary types for key len rounding
typedef struct{
	uint64_t a[2];
} __attribute__((packed)) cdata_u128_t;

typedef struct{
	uint64_t a[4];
} __attribute__((packed)) cdata_u256_t;

typedef struct{
	uint64_t a[8];
} __attribute__((packed)) cdata_u512_t;

typedef struct{
	uint64_t a[16];
} __attribute__((packed)) cdata_u1024_t;

typedef struct{
	uint64_t a[32];
} __attribute__((packed)) cdata_u2048_t;


#define CDATA_CHECK_MAGIC(s) \
	if(unlikely(!m || m->magic_num != CDATA_MAGIC)) \
		return CDATA_E_INVALID

//Comparing methods for extended types
inline bool operator<(const cdata_u128_t& a1, const cdata_u128_t& a2){
	return memcmp((const void*)&a1, (const void*)&a2,
						sizeof(cdata_u128_t)) < 0;
}
inline bool operator<(const cdata_u256_t& a1, const cdata_u256_t& a2){
	return memcmp((const void*)&a1, (const void*)&a2,
						sizeof(cdata_u256_t)) < 0;
}
inline bool operator<(const cdata_u512_t& a1, const cdata_u512_t& a2){
	return memcmp((const void*)&a1, (const void*)&a2,
						sizeof(cdata_u512_t)) < 0;
}
inline bool operator<(const cdata_u1024_t& a1, const cdata_u1024_t& a2){
	return memcmp((const void*)&a1, (const void*)&a2,
						sizeof(cdata_u1024_t)) < 0;
}
inline bool operator<(const cdata_u2048_t& a1, const cdata_u2048_t& a2){
	return memcmp((const void*)&a1, (const void*)&a2,
						sizeof(cdata_u2048_t)) < 0;
}

//Comparing methods for extended types (std::list::unique)
inline bool operator==(const cdata_u128_t& a1, const cdata_u128_t& a2){
	return memcmp((const void*)&a1, (const void*)&a2,
						sizeof(cdata_u128_t)) == 0;
}
inline bool operator==(const cdata_u256_t& a1, const cdata_u256_t& a2){
	return memcmp((const void*)&a1, (const void*)&a2,
						sizeof(cdata_u256_t)) == 0;
}
inline bool operator==(const cdata_u512_t& a1, const cdata_u512_t& a2){
	return memcmp((const void*)&a1, (const void*)&a2,
						sizeof(cdata_u512_t)) == 0;
}
inline bool operator==(const cdata_u1024_t& a1, const cdata_u1024_t& a2){
	return memcmp((const void*)&a1, (const void*)&a2,
						sizeof(cdata_u1024_t)) == 0;
}
inline bool operator==(const cdata_u2048_t& a1, const cdata_u2048_t& a2){
	return memcmp((const void*)&a1, (const void*)&a2,
						sizeof(cdata_u2048_t)) == 0;
}

//Generators for custom types
/**
* @internal Default memcp comparison operator
*/
#define __CDATA_CUSTOM_GEN_MEMCP_LESS_OP(TYPE) \
	inline bool operator<(const TYPE & a1, const TYPE & a2){ \
		return memcmp((const void*)&a1, (const void*)&a2, \
						sizeof( TYPE )) < 0; \
	}
/**
* @internal Default memcp comparison operator
*/
#define __CDATA_CUSTOM_GEN_MEMCP_EQ_OP(TYPE) \
	inline bool operator==(const TYPE & a1, const TYPE & a2){ \
		return memcmp((const void*)&a1, (const void*)&a2, \
						sizeof( TYPE )) == 0; \
	}

#endif //__CDATA_COMMON_INT__
