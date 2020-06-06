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

#ifndef __CDADA_LIST_INT__
#define __CDADA_LIST_INT__

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
#include <list>
#include <sstream>

/**
* @file cdada/list_internal.h
* @author Marc Sune<marcdevel (at) gmail.com>
*
* @brief Internals of the list wrapper
*/

/**
* @internal Function pointer struct for autogen types
*/
typedef struct __cdada_list_ops{
	void (*create)(cdada_list_t* l);
	void (*destroy)(cdada_list_t* l);
	void (*clear)(cdada_list_t* l);
	bool (*empty)(const cdada_list_t* l);
	uint32_t (*size)(const cdada_list_t* l);
	int (*insert)(cdada_list_t* l, const void* val, const uint32_t pos);
	int (*get)(const cdada_list_t* l, const uint32_t pos, void* val);
	int (*first_last)(const cdada_list_t* l, bool first, void* val);
	int (*erase)(cdada_list_t* l, const uint32_t pos);
	int (*remove)(cdada_list_t* l, const void* val);
	int (*push)(cdada_list_t* l, const void* val, bool front);
	int (*pop)(cdada_list_t* l, bool front);
	void (*sort)(cdada_list_t* l);
	void (*reverse)(cdada_list_t* l);
	void (*unique)(cdada_list_t* l);
	void (*traverse)(const cdada_list_t* l, cdada_list_it f, void* opaque);
	void (*rtraverse)(const cdada_list_t* l, cdada_list_it f, void* opaque);
	void (*dump)(const cdada_list_t* m, std::stringstream& ss);
}__cdada_list_ops_t;

/**
* @internal Main internal structure
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
		std::list<cdada_u128_t>* u128;
		std::list<cdada_u256_t>* u256;
		std::list<cdada_u512_t>* u512;
		std::list<cdada_u1024_t>* u1024;
		std::list<cdada_u2048_t>* u2048;
		void* custom;
	}list;
	__cdada_list_ops_t* ops;
}__cdada_list_int_t;

template<typename T>
int cdada_list_insert_u(__cdada_list_int_t* m, std::list<T>* m_u,
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

		return CDADA_SUCCESS;
	}

	//Note: at this point it can only be a struct
	//We have to pad the struct
	T aux;
	memset(&aux, 0, sizeof(T));
	memcpy(&aux, val, m->user_val_len);

	m_u->insert(it, aux);

	return CDADA_SUCCESS;
}

template<typename T>
int cdada_list_get_u(const __cdada_list_int_t* m, std::list<T>* m_u,
							const uint32_t pos,
							void* val){

	int i = pos;
	typename std::list<T>::iterator it;
	T* __attribute((__may_alias__)) aux = (T*)val;

	it = m_u->begin();
	for(it = m_u->begin(); i>0; --i){
		if(++it == m_u->end())
			return CDADA_E_NOT_FOUND;
	}

	if(m->val_len == m->user_val_len){
		*aux = *it;
		return CDADA_SUCCESS;
	}

	//Avoid padding from the wrapper
	memcpy(aux, &(*it), m->user_val_len);

	return CDADA_SUCCESS;
}

template<typename T>
int cdada_list_first_last_u(const __cdada_list_int_t* m, std::list<T>* m_u,
							bool first,
							void* key){
	T* __attribute((__may_alias__)) aux;
	aux = (T*)key;

	if(first){
		typename std::list<T>::const_iterator it;
		it = m_u->begin();
		if(it == m_u->end())
			return CDADA_E_NOT_FOUND;

		if(m->val_len == m->user_val_len)
			*aux = *it;
		else
			memcpy(aux, &(*it), m->user_val_len);
	}else{
		typename std::list<T>::const_reverse_iterator rit;
		rit = m_u->rbegin();
		if(rit == m_u->rend())
			return CDADA_E_NOT_FOUND;

		if(m->val_len == m->user_val_len)
			*aux = *rit;
		else
			memcpy(aux, &(*rit), m->user_val_len);
	}

	return CDADA_SUCCESS;
}

template<typename T>
int cdada_list_erase_u(__cdada_list_int_t* m, std::list<T>* m_u,
							const uint32_t pos){
	int i = pos;
	typename std::list<T>::iterator it;

	it = m_u->begin();
	for(it = m_u->begin(); i>0; --i){
		if(++it == m_u->end())
			return CDADA_E_NOT_FOUND;
	}

	if(it == m_u->end())
		return CDADA_E_NOT_FOUND;

	m_u->erase(it);

	return CDADA_SUCCESS;
}

template<typename T>
int cdada_list_remove_u(__cdada_list_int_t* m, std::list<T>* m_u,
							const void* val){

	if(m->val_len == m->user_val_len){
		T* __attribute((__may_alias__)) aux;
		aux = (T*)val;
		m_u->remove(*aux);
		return CDADA_SUCCESS;
	}

	//Note: at this point it can only be a struct
	//We have to pad the struct
	T aux;
	memset(&aux, 0, sizeof(T));
	memcpy(&aux, val, m->user_val_len);

	m_u->remove(aux);

	return CDADA_SUCCESS;
}

template<typename T>
int cdada_list_push_u(__cdada_list_int_t* m, std::list<T>* m_u,
							const void* val,
							bool front){

	if(m->val_len == m->user_val_len){
		T* __attribute((__may_alias__)) aux;

		aux = (T*)val;

		if(front)
			m_u->push_front(*aux);
		else
			m_u->push_back(*aux);

		return CDADA_SUCCESS;
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


	return CDADA_SUCCESS;
}

template<typename T>
int cdada_list_pop_u(__cdada_list_int_t* m, std::list<T>* m_u, bool front){

	if(front)
		m_u->pop_front();
	else
		m_u->pop_back();
	return CDADA_SUCCESS;
}

template<typename T>
void cdada_list_traverse_u(const cdada_list_t* list, std::list<T>* m_u,
							cdada_list_it f,
							void* opaque){

	typename std::list<T>::const_iterator it;

	for(it = m_u->begin(); it != m_u->end(); ++it){
		const T& t = *it;
		(*f)(list, &t, opaque);
	}
}

template<typename T>
void cdada_list_rtraverse_u(const cdada_list_t* list, std::list<T>* m_u,
							cdada_list_it f,
							void* opaque){

	typename std::list<T>::const_reverse_iterator it;

	for(it = m_u->rbegin(); it != m_u->rend(); ++it){
		const T& t = *it;
		(*f)(list, &t, opaque);
	}
}

template<typename T>
void cdada_list_dump_u(const __cdada_list_int_t* list, std::list<T>* m_u,
							std::stringstream& ss){

	uint32_t i;
	typename std::list<T>::const_iterator it;

	for(it = m_u->begin(), i=0; it != m_u->end(); ++i){
		ss << "[" << i <<"]:";
		__cdada_str_obj(ss, *it, list->user_val_len);
		++it;

		if(it != m_u->end())
			ss << ", ";
	}
}

#endif //__CDADA_LIST_INT__
