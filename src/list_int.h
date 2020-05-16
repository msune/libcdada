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

#ifndef __CDATA_LIST_INT__
#define __CDATA_LIST_INT__

#include <stdbool.h>
#include <stdint.h>
#include "cdata/utils.h"
#include "common_int.h"
#include <list>

/**
* @file list_internal.h
* @author Marc Sune<marcdevel (at) gmail.com>
*
* @brief Internals of the list wrapper
*/
typedef struct{
	uint32_t magic_num;
	uint32_t user_val_len;
	uint32_t val_len;
	union {
		std::list<uint8_t>* u8;
		std::list<uint16_t>* u16;
		std::list<uint32_t>* u32;
		std::list<uint64_t>* u64;
		std::list<cdata_u128_t>* u128;
		std::list<cdata_u256_t>* u256;
		std::list<cdata_u512_t>* u512;
		std::list<cdata_u1024_t>* u1024;
		std::list<cdata_u2048_t>* u2048;
		void* var;
	}list;
}__cdata_list_int_t;

#endif //__CDATA_LIST_INT__
