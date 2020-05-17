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
#include <set>

/**
* @file cdata/set_internal.h
* @author Marc Sune<marcdevel (at) gmail.com>
*
* @brief Internals of the set wrapper
*/

/**
* Main internal structure
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
		std::set<cdata_u128_t>* u128;
		std::set<cdata_u256_t>* u256;
		std::set<cdata_u512_t>* u512;
		std::set<cdata_u1024_t>* u1024;
		std::set<cdata_u2048_t>* u2048;
		void* custom;
	}set;
	__cdata_set_ops_t* ops;
}__cdata_set_int_t;

template<typename T>
int cdata_set_insert_u(__cdata_set_int_t* m, std::set<T>* m_u,
							const void* key){
	if(m->key_len == m->user_key_len){
		T* __attribute((__may_alias__)) aux;

		aux = (T*)key;

		if(m_u->find(*aux) != m_u->end())
			return CDATA_E_EXISTS;
		m_u->insert(*aux);

		return CDATA_SUCCESS;
	}

	//Note: at this point it can only be a struct
	//We have to pad the struct
	T aux;
	memset(&aux, 0, sizeof(T));
	memcpy(&aux, key, m->user_key_len);

	if(m_u->find(aux) != m_u->end())
		return CDATA_E_EXISTS;

	m_u->insert(aux);

	return CDATA_SUCCESS;
}

template<typename T>
int cdata_set_erase_u(__cdata_set_int_t* m, std::set<T>* m_u,
							const void* key){
	if(m->key_len == m->user_key_len){
		T* __attribute((__may_alias__)) aux;

		aux = (T*)key;

		if(m_u->find(*aux) == m_u->end())
			return CDATA_E_NOT_FOUND;
		m_u->erase(*aux);

		return CDATA_SUCCESS;
	}

	//Note: at this point it can only be a struct
	//We have to pad the struct
	T aux;
	memset(&aux, 0, sizeof(T));
	memcpy(&aux, key, m->user_key_len);

	if(m_u->find(aux) == m_u->end())
		return CDATA_E_NOT_FOUND;

	m_u->erase(aux);

	return CDATA_SUCCESS;
}

template<typename T>
bool cdata_set_find_u(__cdata_set_int_t* m, std::set<T>* m_u,
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
void cdata_set_traverse_u(const cdata_set_t* set, std::set<T>* m_u,
							cdata_set_it f,
							void* opaque){

	typename std::set<T>::const_iterator it;

	for(it = m_u->begin(); it != m_u->end(); ++it){
		const T& t = *it;
		(*f)(set, &t, opaque);
	}
}

template<typename T>
void cdata_set_rtraverse_u(const cdata_set_t* set, std::set<T>* m_u,
							cdata_set_it f,
							void* opaque){

	typename std::set<T>::const_reverse_iterator it;

	for(it = m_u->rbegin(); it != m_u->rend(); ++it){
		const T& t = *it;
		(*f)(set, &t, opaque);
	}
}

#endif //__CDATA_LIST_INT__
