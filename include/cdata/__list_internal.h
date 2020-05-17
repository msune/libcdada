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
#include <list>

/**
* @file list_internal.h
* @author Marc Sune<marcdevel (at) gmail.com>
*
* @brief Internals of the list wrapper
*/

/**
* Main internal structure
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
	__cdata_list_ops_t* ops;
}__cdata_list_int_t;

template<typename T>
int cdata_list_insert_u(__cdata_list_int_t* m, std::list<T>* m_u,
							const void* val,
							const uint32_t pos){

	int i = pos;
	typename std::list<T>::iterator it;

	it = m_u->begin();
	for(it = m_u->begin(); i>0; --i){
		if(++it == m_u->end())
			break;
	}

	if(m->val_len == m->user_val_len){
		T* __attribute((__may_alias__)) aux;

		aux = (T*)val;

		m_u->insert(it, *aux);

		return CDATA_SUCCESS;
	}

	//Note: at this point it can only be a struct
	//We have to pad the struct
	T aux;
	memset(&aux, 0, sizeof(T));
	memcpy(&aux, val, m->user_val_len);

	m_u->insert(it, aux);

	return CDATA_SUCCESS;
}

template<typename T>
int cdata_list_get_u(__cdata_list_int_t* m, std::list<T>* m_u,
							const uint32_t pos,
							void* val){

	int i = pos;
	typename std::list<T>::iterator it;
	T* __attribute((__may_alias__)) aux = (T*)val;

	it = m_u->begin();
	for(it = m_u->begin(); i>0; --i){
		if(++it == m_u->end())
			return CDATA_E_NOT_FOUND;
	}

	if(m->val_len == m->user_val_len){
		*aux = *it;
		return CDATA_SUCCESS;
	}

	//Avoid padding from the wrapper
	memcpy(aux, &(*it), m->user_val_len);

	return CDATA_SUCCESS;
}

template<typename T>
int cdata_list_erase_u(__cdata_list_int_t* m, std::list<T>* m_u,
							const uint32_t pos){
	int i = pos;
	typename std::list<T>::iterator it;

	it = m_u->begin();
	for(it = m_u->begin(); i>0; --i){
		if(++it == m_u->end())
			return CDATA_E_NOT_FOUND;
	}

	if(it == m_u->end())
		return CDATA_E_NOT_FOUND;

	m_u->erase(it);

	return CDATA_SUCCESS;
}

template<typename T>
int cdata_list_remove_u(__cdata_list_int_t* m, std::list<T>* m_u,
							const void* val){

	if(m->val_len == m->user_val_len){
		T* __attribute((__may_alias__)) aux;
		aux = (T*)val;
		m_u->remove(*aux);
		return CDATA_SUCCESS;
	}

	//Note: at this point it can only be a struct
	//We have to pad the struct
	T aux;
	memset(&aux, 0, sizeof(T));
	memcpy(&aux, val, m->user_val_len);

	m_u->remove(aux);

	return CDATA_SUCCESS;
}

template<typename T>
int cdata_list_push_u(__cdata_list_int_t* m, std::list<T>* m_u,
							const void* val,
							bool front){

	if(m->val_len == m->user_val_len){
		T* __attribute((__may_alias__)) aux;

		aux = (T*)val;

		if(front)
			m_u->push_front(*aux);
		else
			m_u->push_back(*aux);

		return CDATA_SUCCESS;
	}

	//Note: at this point it can only be a struct
	//We have to pad the struct
	T aux;
	memset(&aux, 0, sizeof(T));
	memcpy(&aux, val, m->user_val_len);


	if(front)
		m_u->push_front(aux);
	else
		m_u->push_back(aux);


	return CDATA_SUCCESS;
}

template<typename T>
int cdata_list_pop_u(__cdata_list_int_t* m, std::list<T>* m_u, bool front){

	if(front)
		m_u->pop_front();
	else
		m_u->pop_back();
	return CDATA_SUCCESS;
}

template<typename T>
void cdata_list_traverse_u(const cdata_list_t* list, std::list<T>* m_u,
							cdata_list_it f,
							void* opaque){

	typename std::list<T>::const_iterator it;

	for(it = m_u->begin(); it != m_u->end(); ++it){
		const T& t = *it;
		(*f)(list, &t, opaque);
	}
}

template<typename T>
void cdata_list_rtraverse_u(const cdata_list_t* list, std::list<T>* m_u,
							cdata_list_it f,
							void* opaque){

	typename std::list<T>::const_reverse_iterator it;

	for(it = m_u->rbegin(); it != m_u->rend(); ++it){
		const T& t = *it;
		(*f)(list, &t, opaque);
	}
}

#endif //__CDATA_LIST_INT__
