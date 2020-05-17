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

#ifndef __CDATA_MAP_INT__
#define __CDATA_MAP_INT__

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
#include <cdata/utils.h>
#include <cdata/__common_internal.h>
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

template<typename T>
int cdata_map_insert_u(__cdata_map_int_t* m, std::map<T, void*>* m_u,
								const void* key,
								void* val){
	if(m->key_len == m->user_key_len){
		T* __attribute((__may_alias__)) aux;

		aux = (T*)key;

		if(m_u->find(*aux) != m_u->end())
			return CDATA_E_EXISTS;
		m_u->insert({*aux, val});

		return CDATA_SUCCESS;
	}

	//We have to pad the struct
	T aux = {0};
	memcpy(&aux, key, m->user_key_len);

	if(m_u->find(aux) != m_u->end())
		return CDATA_E_EXISTS;

	m_u->insert({aux, val});

	return CDATA_SUCCESS;
}

template<typename T>
int cdata_map_erase_u(__cdata_map_int_t* m, std::map<T, void*>* m_u,
							const void* key){
	if(m->key_len == m->user_key_len){
		T* __attribute((__may_alias__)) aux;

		aux = (T*)key;

		if(m_u->find(*aux) == m_u->end())
			return CDATA_E_NOT_FOUND;
		m_u->erase(*aux);

		return CDATA_SUCCESS;
	}

	//We have to pad the struct
	T aux = {0};
	memcpy(&aux, key, m->user_key_len);

	if(m_u->find(aux) == m_u->end())
		return CDATA_E_NOT_FOUND;

	m_u->erase(aux);

	return CDATA_SUCCESS;
}

template<typename T>
int cdata_map_find_u(__cdata_map_int_t* m, std::map<T, void*>* m_u,
							const void* key,
							void** val){
	typename std::map<T, void*>::iterator it;

	if(m->key_len == m->user_key_len){
		T* __attribute((__may_alias__)) aux;

		aux = (T*)key;
		it = m_u->find(*aux);

		if(it == m_u->end())
			return CDATA_E_NOT_FOUND;

		*val = it->second;

		return CDATA_SUCCESS;
	}

	//We have to pad the struct
	T aux = {0};
	memcpy(&aux, key, m->user_key_len);

	it = m_u->find(aux);
	if(it == m_u->end())
		return CDATA_E_NOT_FOUND;

	*val = it->second;

	return CDATA_SUCCESS;
}

template<typename T>
void cdata_map_traverse_u(const cdata_map_t* map, std::map<T, void*>* m_u,
							cdata_map_it f,
							void* opaque){

	typename std::map<T, void*>::const_iterator it;

	for(it = m_u->begin(); it != m_u->end(); ++it)
		(*f)(map, &it->first, it->second, opaque);
}

template<typename T>
void cdata_map_rtraverse_u(const cdata_map_t* map, std::map<T, void*>* m_u,
							cdata_map_it f,
							void* opaque){

	typename std::map<T, void*>::const_reverse_iterator it;

	for(it = m_u->rbegin(); it != m_u->rend(); ++it)
		(*f)(map, &it->first, it->second, opaque);
}


#endif //__CDATA_MAP_INT__
