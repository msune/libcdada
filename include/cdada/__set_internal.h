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

#ifndef __CDADA_SET_INT__
#define __CDADA_SET_INT__

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
#include <set>
#include <sstream>

/**
* @file cdada/set_internal.h
* @author Marc Sune<marcdevel (at) gmail.com>
*
* @brief Internals of the set wrapper
*/

/**
* @internal Function pointer struct for autogen types
*/
typedef struct __cdada_set_ops{
	void (*create)(cdada_set_t* m);
	void (*destroy)(cdada_set_t* m);
	void (*clear)(cdada_set_t* m);
	bool (*empty)(const cdada_set_t* m);
	uint32_t (*size)(const cdada_set_t* m);
	int (*insert)(cdada_set_t* m, const void* key);
	int (*erase)(cdada_set_t* m, const void* key);
	bool (*find)(const cdada_set_t* m, const void* key);
	int (*first_last)(const cdada_set_t* map, bool first, void* key);
	void (*traverse)(const cdada_set_t* m, cdada_set_it f, void* opaque);
	void (*rtraverse)(const cdada_set_t* m, cdada_set_it f, void* opaque);
	void (*dump)(const cdada_set_t* m, std::stringstream& ss);
}__cdada_set_ops_t;

/**
* @internal Main internal structure
*/
typedef struct{
	uint32_t magic_num;
	uint32_t user_key_len;
	uint32_t key_len;
	union {
		std::set<uint8_t>* u8;
		std::set<uint16_t>* u16;
		std::set<uint32_t>* u32;
		std::set<uint64_t>* u64;
		std::set<cdada_u128_t>* u128;
		std::set<cdada_u256_t>* u256;
		std::set<cdada_u512_t>* u512;
		std::set<cdada_u1024_t>* u1024;
		std::set<cdada_u2048_t>* u2048;
		void* custom;
	}set;
	__cdada_set_ops_t* ops;
}__cdada_set_int_t;

template<typename T>
int cdada_set_insert_u(__cdada_set_int_t* m, std::set<T>* m_u,
							const void* key){
	typename std::set<T>::iterator it;

	if(m->key_len == m->user_key_len){
		T* __attribute((__may_alias__)) aux;

		aux = (T*)key;

		it = m_u->find(*aux);
		if(it != m_u->end())
			return CDADA_E_EXISTS;
		m_u->insert(it, *aux);

		return CDADA_SUCCESS;
	}

	//Note: at this point it can only be a struct
	//We have to pad the struct
	T aux;
	memset(&aux, 0, sizeof(T));
	memcpy(&aux, key, m->user_key_len);

	it = m_u->find(aux);
	if(it != m_u->end())
		return CDADA_E_EXISTS;

	m_u->insert(it, aux);

	return CDADA_SUCCESS;
}

template<typename T>
int cdada_set_erase_u(__cdada_set_int_t* m, std::set<T>* m_u,
							const void* key){
	typename std::set<T>::iterator it;

	if(m->key_len == m->user_key_len){
		T* __attribute((__may_alias__)) aux;

		aux = (T*)key;

		it = m_u->find(*aux);
		if(it == m_u->end())
			return CDADA_E_NOT_FOUND;

		m_u->erase(it);

		return CDADA_SUCCESS;
	}

	//Note: at this point it can only be a struct
	//We have to pad the struct
	T aux;
	memset(&aux, 0, sizeof(T));
	memcpy(&aux, key, m->user_key_len);

	it = m_u->find(aux);
	if(it == m_u->end())
		return CDADA_E_NOT_FOUND;

	m_u->erase(it);

	return CDADA_SUCCESS;
}

template<typename T>
bool cdada_set_find_u(const __cdada_set_int_t* m, std::set<T>* m_u,
							const void* key){
	if(m->key_len == m->user_key_len){
		T* __attribute((__may_alias__)) aux;
		aux = (T*)key;
		return m_u->find(*aux) != m_u->end();
	}

	//Note: at this point it can only be a struct
	//We have to pad the struct
	T aux;
	memset(&aux, 0, sizeof(T));
	memcpy(&aux, key, m->user_key_len);

	return m_u->find(aux) != m_u->end();
}

template<typename T>
int cdada_set_first_last_u(const __cdada_set_int_t* m, std::set<T>* m_u,
							bool first,
							void* key){
	T* __attribute((__may_alias__)) aux;
	aux = (T*)key;

	if(first){
		typename std::set<T>::const_iterator it;
		it = m_u->begin();
		if(it == m_u->end())
			return CDADA_E_EMPTY;

		if(m->key_len == m->user_key_len)
			*aux = *it;
		else
			memcpy(aux, &(*it), m->user_key_len);
	}else{
		typename std::set<T>::const_reverse_iterator rit;
		rit = m_u->rbegin();
		if(rit == m_u->rend())
			return CDADA_E_EMPTY;

		if(m->key_len == m->user_key_len)
			*aux = *rit;
		else
			memcpy(aux, &(*rit), m->user_key_len);
	}

	return CDADA_SUCCESS;
}

template<typename T>
void cdada_set_traverse_u(const cdada_set_t* set, std::set<T>* m_u,
							cdada_set_it f,
							void* opaque){

	typename std::set<T>::const_iterator it;

	for(it = m_u->begin(); it != m_u->end(); ++it){
		const T& t = *it;
		(*f)(set, &t, opaque);
	}
}

template<typename T>
void cdada_set_rtraverse_u(const cdada_set_t* set, std::set<T>* m_u,
							cdada_set_it f,
							void* opaque){

	typename std::set<T>::const_reverse_iterator it;

	for(it = m_u->rbegin(); it != m_u->rend(); ++it){
		const T& t = *it;
		(*f)(set, &t, opaque);
	}
}

template<typename T>
void cdada_set_dump_u(const __cdada_set_int_t* set, std::set<T>* m_u,
							std::stringstream& ss){

	typename std::set<T>::const_iterator it;

	for(it = m_u->begin(); it != m_u->end();){
		__cdada_str_obj(ss, *it, set->user_key_len);
		++it;

		if(it != m_u->end())
			ss << ", ";
	}
}

#endif //__CDADA_SET_INT__
