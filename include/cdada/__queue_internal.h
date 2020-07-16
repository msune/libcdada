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

#ifndef __CDADA_QUEUE_INT__
#define __CDADA_QUEUE_INT__

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
#include <queue>

/**
* @file cdada/__queue_internal.h
* @author Marc Sune<marcdevel (at) gmail.com>
*
* @brief Internals of the queue wrapper
*/

/**
* @internal Function pointer struct for autogen types
*/
typedef struct __cdada_queue_ops{
	void (*create)(cdada_queue_t* s);
	void (*destroy)(cdada_queue_t* s);
	bool (*empty)(const cdada_queue_t* s);
	uint32_t (*size)(const cdada_queue_t* s);
	int (*push)(cdada_queue_t* s, const void* val);
	int (*pop)(cdada_queue_t* s);
	int (*front)(const cdada_queue_t* s, void *val);
	int (*back)(const cdada_queue_t* s, void *val);
	void (*dump)(const cdada_queue_t* m, std::stringstream& ss);
}__cdada_queue_ops_t;

/**
* @internal Main internal structure
*/
typedef struct{
	uint32_t magic_num;
	uint32_t user_val_len;
	uint32_t val_len;
	uint64_t max_capacity;
	union {
		std::queue<uint8_t>* u8;
		std::queue<uint16_t>* u16;
		std::queue<uint32_t>* u32;
		std::queue<uint64_t>* u64;
		std::queue<cdada_u128_t>* u128;
		std::queue<cdada_u256_t>* u256;
		std::queue<cdada_u512_t>* u512;
		std::queue<cdada_u1024_t>* u1024;
		std::queue<cdada_u2048_t>* u2048;
		void* custom;
	}queue;
	__cdada_queue_ops_t* ops;
}__cdada_queue_int_t;

template<typename T>
int cdada_queue_push_u(__cdada_queue_int_t* m, std::queue<T>* m_u,
							const void* val){

	if(m->val_len == m->user_val_len){
		T* __attribute((__may_alias__)) aux;

		aux = (T*)val;

		m_u->push(*aux);

		return CDADA_SUCCESS;
	}

	//Note: at this point it can only be a struct
	//We have to pad the struct
	T aux;
	memset(&aux, 0, sizeof(T));
	memcpy(&aux, val, m->user_val_len);

	m_u->push(aux);

	return CDADA_SUCCESS;
}

template<typename T>
int cdada_queue_pop_u(__cdada_queue_int_t* m, std::queue<T>* m_u){

	int rv = CDADA_E_NOT_FOUND;

	if(!m_u->empty()){
		m_u->pop();
		rv = CDADA_SUCCESS;
	}

	return rv;
}

template<typename T>
int cdada_queue_front_u(__cdada_queue_int_t* m, std::queue<T>* m_u,
							void *val){

	T* __attribute((__may_alias__)) aux = (T*)val;
	int rv = CDADA_E_NOT_FOUND;

	if(!m_u->empty()){
		if(m->val_len == m->user_val_len){
			*aux = m_u->front();
			return CDADA_SUCCESS;
		}

		//Avoid padding from the wrapper
		aux = &(m_u->front());
		memcpy(val, aux, m->user_val_len);

		return CDADA_SUCCESS;
	}

	return rv;
}

template<typename T>
int cdada_queue_back_u(__cdada_queue_int_t* m, std::queue<T>* m_u,
							void *val){

	T* __attribute((__may_alias__)) aux = (T*)val;
	int rv = CDADA_E_NOT_FOUND;

	if(!m_u->empty()){
		if(m->val_len == m->user_val_len){
			*aux = m_u->back();
			return CDADA_SUCCESS;
		}

		//Avoid padding from the wrapper
		aux = &(m_u->back());
		memcpy(val, aux, m->user_val_len);

		return CDADA_SUCCESS;
	}

	return rv;
}

template<typename T>
bool cdada_queue_empty_u(__cdada_queue_int_t* m, std::queue<T>* m_u){

	return m_u->empty();
}

template<typename T>
void cdada_queue_dump_u(const __cdada_queue_int_t* queue, std::queue<T>* m_u,
							std::stringstream& ss){

	typename std::queue<T> aux;

	//No iterators in queue, ephemeral copy
	//TODO use extended queue class to avoid extra copy instead
	aux = *m_u;

	while(!aux.empty()){
		T& t = aux.front();
		__cdada_str_obj(ss, t, queue->user_val_len);
		aux.pop();

		if(!aux.empty())
			ss << ", ";
	}
}

#endif //__CDADA_QUEUE_INT__
