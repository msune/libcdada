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

#ifndef __CDADA_STACK_H__
#define __CDADA_STACK_H__

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <cdada/utils.h>

/**
* @file cdada/stack.h
* @author Peter Dobransky<pdobransky101 (at) gmail.com>
*
* @brief Stack data structure. Wraps std::stack data structure
*/

/**
* cdada stack structure
*/
typedef void cdada_stack_t;

//In case it's included from C++
CDADA_BEGIN_DECLS

//Fwd decl
struct __cdada_stack_ops;
cdada_stack_t* __cdada_stack_create(const uint16_t val_size,
						struct __cdada_stack_ops* ops);

/**
* @brief Create and initialize a stack data structure
*
* Allocate and initialize a stack structure (std::stack). Containers will perform
* better when TYPE has a size of {1,2,4,8,16,32,64,128,256} bytes
*
* For types > 256, use custom containers
*/
#define cdada_stack_create(TYPE) \
	__cdada_stack_create(sizeof( TYPE ), NULL)

/**
* Destroy a stack structure
*
* @param stack Stack pointer
*/
int cdada_stack_destroy(cdada_stack_t* stack);

//Stack properties

/**
* Is the stack empty
*
* @param stack Stack pointer
*/
bool cdada_stack_empty(const cdada_stack_t* stack);

/**
* Return the size (number of elements) in the stack
*
* @param stack Stack pointer
*/
uint32_t cdada_stack_size(const cdada_stack_t* stack);

/**
* Get the maximum capacity (0 if unlimited)
*
* @param stack Stack pointer
*
* @ret Will return the maximum capacity of the stack or 0 if unlimited
*/
uint64_t cdada_stack_get_max_capacity(const cdada_stack_t* stack);

/**
* @brief Set the maximum capacity
*
* This function sets the maximum capacity of the stack. It can be called
* at any time. If called when the stack has more elements than `limit`,
* exceeding elements won't be removed, but the stack won't be able to
* grow until the size is under the new set limit.
*
* Use the value 0 to remove the limit
*
* @param stack Stack pointer
* @param limit Limit of the capacity (set to 0 for unlimited)
*/
int cdada_stack_set_max_capacity(const cdada_stack_t* stack,
						const uint64_t limit);

//Element manipulation

/**
* Push front
*
* @param stack Stack pointer
* @param val Val. The val type _must_ have all bytes initialized
*/
int cdada_stack_push(cdada_stack_t* stack, const void* val);

/**
* Pop front
*
* @param stack Stack pointer
*/
int cdada_stack_pop(cdada_stack_t* stack);

/**
* Get the top element in the stack. The value pointer must
* be passed since the function cannot return multiple types.
* This differs from the libstdc++ stack implementation.
*
* @param stack Stack pointer
* @param val Value pointer
*/
int cdada_stack_top(const cdada_stack_t* stack, void *val);

//Dumpers

/**
* Dump to a string the contents of the stack
*
* @param stack Stack object
* @param size Size of the buffer
* @param buffer Buffer. If NULL, necessary bytes, including '\0' will be stack
*               in 'size_used'
* @param size_used If buffer != NULL, the number of bytes written else number of
*                  bytes necessary to write, including '\0'
*/
int cdada_stack_dump(cdada_stack_t* stack, uint32_t size, char* buffer,
							uint32_t* bytes_used);

/**
* @brief Print the contents of the stack
*
* @param stack Stack object
* @param stream stdout or stderr
*/
int cdada_stack_print(cdada_stack_t* stack, FILE *stream);

//Custom types

/**
* Forward declare custom time ops
*/
#define CDADA_STACK_CUSTOM_TYPE_DECL(TYPE) \
	extern struct __cdada_stack_ops __cdada_stack_autogen_##TYPE

/**
* @brief Create a stack with a custom type, with a dedicated std::stack
*
* Requires instantiating CDADA_STACK_CUSTOM_GEN() or
* CDADA_STACK_CUSTOM_GEN_NO_MEMCP() once in a C++ compilation unit
*/
#define cdada_stack_create_custom(TYPE) \
	__cdada_stack_create(sizeof( TYPE ), & __cdada_stack_autogen_##TYPE )

CDADA_END_DECLS

#endif //__CDADA_STACK_H__
