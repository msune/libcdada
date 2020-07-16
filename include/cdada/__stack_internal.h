/*
Copyright (c) 2020, Peter Dobransky
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

#ifndef __CDADA_STACK_INT__
#define __CDADA_STACK_INT__

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
#include <stack>

/**
* @file cdada/__stack_internal.h
* @author Peter Dobransky<pdobransky101 (at) gmail.com>
*
* @brief Internals of the stack wrapper
*/

/**
* @internal Function pointer struct for autogen types
*/
typedef struct __cdada_stack_ops{
	void (*create)(cdada_stack_t* s);
	void (*destroy)(cdada_stack_t* s);
	bool (*empty)(const cdada_stack_t* s);
	uint32_t (*size)(const cdada_stack_t* s);
	int (*push)(cdada_stack_t* s, const void* val);
	int (*pop)(cdada_stack_t* s);
	int (*top)(const cdada_stack_t* s, void *val);
	void (*dump)(const cdada_stack_t* m, std::stringstream& ss);
}__cdada_stack_ops_t;

/**
* @internal Main internal structure
*/
typedef struct{
	uint32_t magic_num;
	uint32_t user_val_len;
	uint32_t val_len;
	uint64_t max_capacity;
	union {
		std::stack<uint8_t>* u8;
		std::stack<uint16_t>* u16;
		std::stack<uint32_t>* u32;
		std::stack<uint64_t>* u64;
		std::stack<cdada_u128_t>* u128;
		std::stack<cdada_u256_t>* u256;
		std::stack<cdada_u512_t>* u512;
		std::stack<cdada_u1024_t>* u1024;
		std::stack<cdada_u2048_t>* u2048;
		void* custom;
	}stack;
	__cdada_stack_ops_t* ops;
}__cdada_stack_int_t;

template<typename T>
int cdada_stack_push_u(__cdada_stack_int_t* m, std::stack<T>* m_u,
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
int cdada_stack_pop_u(__cdada_stack_int_t* m, std::stack<T>* m_u){

	int rv = CDADA_E_NOT_FOUND;

	if(!m_u->empty()){
		m_u->pop();
		rv = CDADA_SUCCESS;
	}

	return rv;
}

template<typename T>
int cdada_stack_top_u(__cdada_stack_int_t* m, std::stack<T>* m_u,
							void *val){

	T* __attribute((__may_alias__)) aux = (T*)val;
	int rv = CDADA_E_NOT_FOUND;

	if(!m_u->empty()){
		if(m->val_len == m->user_val_len){
			*aux = m_u->top();
			return CDADA_SUCCESS;
		}

		//Avoid padding from the wrapper
		aux = &(m_u->top());
		memcpy(val, aux, m->user_val_len);

		return CDADA_SUCCESS;
	}

	return rv;
}

template<typename T>
bool cdada_stack_empty_u(__cdada_stack_int_t* m, std::stack<T>* m_u){

	return m_u->empty();
}

template<typename T>
void cdada_stack_dump_u(const __cdada_stack_int_t* stack, std::stack<T>* m_u,
							std::stringstream& ss){

	typename std::stack<T> aux;

	//No iterators in stack, ephemeral copy
	//TODO use extended stack class to avoid extra copy instead
	aux = *m_u;

	while(!aux.empty()){
		T& t = aux.top();
		__cdada_str_obj(ss, t, stack->user_val_len);
		aux.pop();

		if(!aux.empty())
			ss << ", ";
	}
}

#endif //__CDADA_STACK_INT__
