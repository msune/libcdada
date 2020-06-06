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

#ifndef __CDADA_COMMON_INT__
#define __CDADA_COMMON_INT__

//Internal headers should never be directly included
#ifndef __CDADA_INTERNAL_INCLUDE
	#error CDADA internal headers shall not be directly included
#endif //__CDADA_INTERNAL_INCLUDE

//This header should _always_ be included from C++
#ifndef __cplusplus
	#error CDADA autogenreation headers shall be included only from C++ files
#endif //__cplusplus

#include <stdbool.h>
#include <stdint.h>
#include <assert.h>
#include <string.h>
#include "cdada/utils.h"
#include <map>
#include <sstream>
#include <iostream>
#include <iomanip>

/**
* @file cdada/common_int.h
* @author Marc Sune<marcdevel (at) gmail.com>
*
* @brief Common MACROs and utility functions
*/

//Magic num
#define CDADA_MAGIC 0xCAFEBABE

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

#define CDADA_ASSERT(COND) assert(COND)

//Necessary types for key len rounding
typedef struct{
	uint64_t a[2];
} __attribute__((packed)) cdada_u128_t;

typedef struct{
	uint64_t a[4];
} __attribute__((packed)) cdada_u256_t;

typedef struct{
	uint64_t a[8];
} __attribute__((packed)) cdada_u512_t;

typedef struct{
	uint64_t a[16];
} __attribute__((packed)) cdada_u1024_t;

typedef struct{
	uint64_t a[32];
} __attribute__((packed)) cdada_u2048_t;


#define CDADA_CHECK_MAGIC(MM) \
	if(unlikely(!(MM) || (MM)->magic_num != CDADA_MAGIC)) \
		return CDADA_E_INVALID

//Comparing methods for extended types
inline bool operator<(const cdada_u128_t& a1, const cdada_u128_t& a2){
	return memcmp((const void*)&a1, (const void*)&a2,
						sizeof(cdada_u128_t)) < 0;
}
inline bool operator<(const cdada_u256_t& a1, const cdada_u256_t& a2){
	return memcmp((const void*)&a1, (const void*)&a2,
						sizeof(cdada_u256_t)) < 0;
}
inline bool operator<(const cdada_u512_t& a1, const cdada_u512_t& a2){
	return memcmp((const void*)&a1, (const void*)&a2,
						sizeof(cdada_u512_t)) < 0;
}
inline bool operator<(const cdada_u1024_t& a1, const cdada_u1024_t& a2){
	return memcmp((const void*)&a1, (const void*)&a2,
						sizeof(cdada_u1024_t)) < 0;
}
inline bool operator<(const cdada_u2048_t& a1, const cdada_u2048_t& a2){
	return memcmp((const void*)&a1, (const void*)&a2,
						sizeof(cdada_u2048_t)) < 0;
}

//Comparing methods for extended types (std::list::unique)
inline bool operator==(const cdada_u128_t& a1, const cdada_u128_t& a2){
	return memcmp((const void*)&a1, (const void*)&a2,
						sizeof(cdada_u128_t)) == 0;
}
inline bool operator==(const cdada_u256_t& a1, const cdada_u256_t& a2){
	return memcmp((const void*)&a1, (const void*)&a2,
						sizeof(cdada_u256_t)) == 0;
}
inline bool operator==(const cdada_u512_t& a1, const cdada_u512_t& a2){
	return memcmp((const void*)&a1, (const void*)&a2,
						sizeof(cdada_u512_t)) == 0;
}
inline bool operator==(const cdada_u1024_t& a1, const cdada_u1024_t& a2){
	return memcmp((const void*)&a1, (const void*)&a2,
						sizeof(cdada_u1024_t)) == 0;
}
inline bool operator==(const cdada_u2048_t& a1, const cdada_u2048_t& a2){
	return memcmp((const void*)&a1, (const void*)&a2,
						sizeof(cdada_u2048_t)) == 0;
}

//For dumpers

//Generic (hexdump)
template <typename T>
inline void __cdada_str_obj(std::stringstream& ss, const T& o,
							const uint32_t len){

	uint8_t* __attribute__((__may_alias__)) p = (uint8_t*)&o;
	for(uint32_t i=0;i<len;++i, ++p){
		ss << std::hex << std::setfill('0') << std::setw(2)
							<< (uint16_t)*p;
	}
	ss << std::dec;
}

template <>
inline void __cdada_str_obj<uint8_t>(std::stringstream& ss, const uint8_t& o,
							const uint32_t len){
	ss << (uint16_t)o;
}
template <>
inline void __cdada_str_obj<int8_t>(std::stringstream& ss, const int8_t& o,
							const uint32_t len){
	ss << (int16_t)o;
}
template <>
inline void __cdada_str_obj<uint16_t>(std::stringstream& ss, const uint16_t& o,
							const uint32_t len){
	ss << o;
}
template <>
inline void __cdada_str_obj<int16_t>(std::stringstream& ss, const int16_t& o,
							const uint32_t len){
	ss << o;
}
template <>
inline void __cdada_str_obj<uint32_t>(std::stringstream& ss, const uint32_t& o,
							const uint32_t len){
	ss << o;
}
template <>
inline void __cdada_str_obj<int32_t>(std::stringstream& ss, const int32_t& o,
							const uint32_t len){
	ss << o;
}
template <>
inline void __cdada_str_obj<uint64_t>(std::stringstream& ss, const uint64_t& o,
							const uint32_t len){
	ss << o;
}
template <>
inline void __cdada_str_obj<int64_t>(std::stringstream& ss, const int64_t& o,
							const uint32_t len){
	ss << o;
}
template <>
inline void __cdada_str_obj<float>(std::stringstream& ss, const float& o,
							const uint32_t len){
	ss << o;
}
template <>
inline void __cdada_str_obj<double>(std::stringstream& ss, const double& o,
							const uint32_t len){
	ss << o;
}

//Generators for custom types
/**
* @internal Default memcp comparison operator
*/
#define __CDADA_CUSTOM_GEN_MEMCP_LESS_OP(TYPE) \
	inline bool operator<(const TYPE & a1, const TYPE & a2){ \
		return memcmp((const void*)&a1, (const void*)&a2, \
						sizeof( TYPE )) < 0; \
	}
/**
* @internal Default memcp comparison operator
*/
#define __CDADA_CUSTOM_GEN_MEMCP_EQ_OP(TYPE) \
	inline bool operator==(const TYPE & a1, const TYPE & a2){ \
		return memcmp((const void*)&a1, (const void*)&a2, \
						sizeof( TYPE )) == 0; \
	}

/**
* @internal Default dumper operator
*/
#define __CDADA_CUSTOM_GEN_DUMP_OP(TYPE) \
	inline std::ostream& operator<<(std::ostream& os, const TYPE & a){ \
		uint8_t* __attribute__((__may_alias__)) p = (uint8_t*)&a; \
		os << std::hex << std::setfill('0') << std::setw(2); \
		for(uint32_t i=0;i<sizeof( TYPE );++i, ++p) \
			os << std::hex << std::setfill('0') << std::setw(2) \
							<< (uint16_t)*p; \
		os << std::dec; \
		return os; \
	}

/**
* Define C++ necessary operators for the type
*/
#define CDADA_CUSTOM_GEN_MEMCP_OPERATORS(TYPE) \
	__CDADA_CUSTOM_GEN_MEMCP_EQ_OP(TYPE); \
	__CDADA_CUSTOM_GEN_MEMCP_LESS_OP(TYPE); \
	__CDADA_CUSTOM_GEN_DUMP_OP(TYPE)

#endif //__CDADA_COMMON_INT__
