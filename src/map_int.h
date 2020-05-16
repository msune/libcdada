/*
Copyright (c) 2015, Marc Sune Clos
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

#ifndef __CDATA_MAP_INT__
#define __CDATA_MAP_INT__

#include <stdbool.h>
#include <stdint.h>
#include "cdata/utils.h"
#include "common_int.h"
#include <map>

/**
* @file map_internal.h
* @author Marc Sune<marcdevel (at) gmail.com>
*
* @brief Internals of the map wrapper
*/
typedef struct{
	uint32_t magic_num;
	uint32_t user_key_len;
	uint32_t key_len;
	union {
		std::map<uint8_t, void*>* u8;
		std::map<uint16_t, void*>* u16;
		std::map<uint32_t, void*>* u32;
		std::map<uint64_t, void*>* u64;
		std::map<cdata_u128_t, void*>* u128;
		std::map<cdata_u256_t, void*>* u256;
		std::map<cdata_u512_t, void*>* u512;
		std::map<cdata_u1024_t, void*>* u1024;
		std::map<cdata_u2048_t, void*>* u2048;
		void* var;
	}map;
}__cdata_map_int_t;

#endif //__CDATA_MAP_INT__
