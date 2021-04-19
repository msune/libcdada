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

#ifndef __CDADA_MAP_INT__
#define __CDADA_MAP_INT__

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
#include <cdada/utils.h>
#include <cdada/__common_internal.h>
#include <map>

/**
* @file map_internal.h
* @author Marc Sune<marcdevel (at) gmail.com>
*
* @brief Internals of the map wrapper
*/

/**
* @internal Function pointer struct for autogen types
*/
typedef struct __cdada_map_ops{
	void (*create)(cdada_map_t* map);
	void (*destroy)(cdada_map_t* map);
	void (*clear)(cdada_map_t* map);
	bool (*empty)(const cdada_map_t* map);
	uint32_t (*size)(const cdada_map_t* map);
	int (*insert)(cdada_map_t* map, const void* key, void* val);
	int (*erase)(cdada_map_t* map, const void* key);
	int (*find)(const cdada_map_t* map, const void* key, void** val);
	int (*first_last)(const cdada_map_t* map, bool first, void* key,
								void** val);
	void (*traverse)(const cdada_map_t* map, cdada_map_it f, void* opaque);
	void (*rtraverse)(const cdada_map_t* map, cdada_map_it f, void* opaque);
	void (*dump)(const cdada_map_t* m, std::stringstream& ss);
}__cdada_map_ops_t;


/**
* @internal Main internal structure
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
		std::map<cdada_u128_t, void*>* u128;
		std::map<cdada_u256_t, void*>* u256;
		std::map<cdada_u512_t, void*>* u512;
		std::map<cdada_u1024_t, void*>* u1024;
		std::map<cdada_u2048_t, void*>* u2048;
		void* custom;
	}map;
	__cdada_map_ops_t* ops;
}__cdada_map_int_t;

template<typename T>
int cdada_map_insert_u(__cdada_map_int_t* m, std::map<T, void*>* m_u,
								const void* key,
								void* val){
	typename std::map<T, void*>::iterator it;

	if(m->key_len == m->user_key_len){
		T* __attribute((__may_alias__)) aux;

		aux = (T*)key;

		it = m_u->find(*aux);
		if(unlikely(it != m_u->end()))
			return CDADA_E_EXISTS;
		m_u->insert(std::pair<T, void*>(*aux, val));

		return CDADA_SUCCESS;
	}

	//Note: at this point it can only be a struct
	//We have to pad the struct
	T aux;
	memset(&aux, 0, sizeof(T));
	memcpy(&aux, key, m->user_key_len);

	it = m_u->find(aux);
	if(unlikely(it != m_u->end()))
		return CDADA_E_EXISTS;

	m_u->insert(std::pair<T, void*>(aux, val));

	return CDADA_SUCCESS;
}

template<typename T>
int cdada_map_erase_u(__cdada_map_int_t* m, std::map<T, void*>* m_u,
							const void* key){
	typename std::map<T, void*>::iterator it;

	if(m->key_len == m->user_key_len){
		T* __attribute((__may_alias__)) aux;

		aux = (T*)key;

		it = m_u->find(*aux);
		if(unlikely(it == m_u->end()))
			return CDADA_E_NOT_FOUND;
		m_u->erase(*aux);

		return CDADA_SUCCESS;
	}

	//Note: at this point it can only be a struct
	//We have to pad the struct
	T aux;
	memset(&aux, 0, sizeof(T));
	memcpy(&aux, key, m->user_key_len);

	it = m_u->find(aux);
	if(unlikely(it == m_u->end()))
		return CDADA_E_NOT_FOUND;

	m_u->erase(aux);

	return CDADA_SUCCESS;
}

template<typename T>
int cdada_map_find_u(const __cdada_map_int_t* m, std::map<T, void*>* m_u,
							const void* key,
							void** val){
	typename std::map<T, void*>::const_iterator it;

	if(m->key_len == m->user_key_len){
		T* __attribute((__may_alias__)) aux;

		aux = (T*)key;
		it = m_u->find(*aux);

		if(unlikely(it == m_u->end()))
			return CDADA_E_NOT_FOUND;

		*val = it->second;

		return CDADA_SUCCESS;
	}

	//Note: at this point it can only be a struct
	//We have to pad the struct
	T aux;
	memset(&aux, 0, sizeof(T));
	memcpy(&aux, key, m->user_key_len);

	it = m_u->find(aux);
	if(unlikely(it == m_u->end()))
		return CDADA_E_NOT_FOUND;

	*val = it->second;

	return CDADA_SUCCESS;
}

template<typename T>
int cdada_map_first_last_u(const __cdada_map_int_t* m, std::map<T, void*>* m_u,
							bool first,
							void* key,
							void** val){
	T* __attribute((__may_alias__)) aux;
	aux = (T*)key;

	if(first){
		typename std::map<T, void*>::const_iterator it;
		it = m_u->begin();
		if(it == m_u->end())
			return CDADA_E_EMPTY;

		if(m->key_len == m->user_key_len)
			*aux = it->first;
		else
			memcpy(aux, &it->first, m->user_key_len);

		*val = it->second;
	}else{
		typename std::map<T, void*>::const_reverse_iterator rit;
		rit = m_u->rbegin();
		if(rit == m_u->rend())
			return CDADA_E_EMPTY;

		if(m->key_len == m->user_key_len)
			*aux = rit->first;
		else
			memcpy(aux, &rit->first, m->user_key_len);

		*val = rit->second;
	}

	return CDADA_SUCCESS;
}

template<typename T>
void cdada_map_traverse_u(const cdada_map_t* map, std::map<T, void*>* m_u,
							cdada_map_it f,
							void* opaque){

	typename std::map<T, void*>::const_iterator it;

	for(it = m_u->begin(); it != m_u->end(); ++it)
		(*f)(map, &it->first, it->second, opaque);
}

template<typename T>
void cdada_map_rtraverse_u(const cdada_map_t* map, std::map<T, void*>* m_u,
							cdada_map_it f,
							void* opaque){

	typename std::map<T, void*>::const_reverse_iterator it;

	for(it = m_u->rbegin(); it != m_u->rend(); ++it)
		(*f)(map, &it->first, it->second, opaque);
}

template<typename T>
void cdada_map_dump_u(const __cdada_map_int_t* map, std::map<T, void*>* m_u,
							std::stringstream& ss){

	typename std::map<T, void*>::const_iterator it;

	for(it = m_u->begin(); it != m_u->end();){
		__cdada_str_obj(ss, it->first, map->user_key_len);
		ss << " -> @" << it->second;
		++it;
		if(it != m_u->end())
			ss << ", ";
	}
}

#endif //__CDADA_MAP_INT__
