/*
Copyright (c) 2020, Marc Sune
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

#ifndef __CDADA_QUEUE_H__
#define __CDADA_QUEUE_H__

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <cdada/utils.h>

/**
* @file cdada/queue.h
* @author Marc Sune<marcdevel (at) gmail.com>
*
* @brief Queue(FIFO) data structure.
*
* `cdada_queue` data structure is a queue(FIFO) of elements of type 'TYPE'.
* During insertions, a _copy_ of the element `val` will be stored in the queue.
* During accesses (e.g. `cdada_queue_front`), if found, a _copy_ of the value
* will be stored in the region of memory pointed by `val`.
*
* Uses std::queue as a backend
*/

/**
* cdada queue structure
*/
typedef void cdada_queue_t;

//In case it's included from C++
CDADA_BEGIN_DECLS

//Fwd decl
//See cdada_queue_create() for return codes
struct __cdada_queue_ops;
cdada_queue_t* __cdada_queue_create(const uint16_t val_size,
						struct __cdada_queue_ops* ops);

/**
* @brief Create and initialize a queue(FIFO) data structure
*
* Allocate and initialize a queue structure. Containers will perform better when
* TYPE has a size of {1,2,4,8,16,32,64,128,256} bytes
*
* For types > 256, use custom containers
*
* @returns Returns a cdada_queue object or NULL, if some error is found
*/
#define cdada_queue_create(TYPE) \
	__cdada_queue_create(sizeof( TYPE ), NULL)

/**
* Destroy a queue structure
*
* @param queue Queue pointer
*
* @returns Return codes:
*          CDADA_SUCCESS: queue was destroyed
*          CDADA_E_UNKNOWN: corrupted queue or internal error (bug)
*          CDADA_E_INVALID: queue is NULL or corrupted
*/
int cdada_queue_destroy(cdada_queue_t* queue);

//Queue properties

/**
* Is the queue empty
*
* @param queue Queue pointer
*
* @returns Returns true if queue is empty else (including invalid) false
*/
bool cdada_queue_empty(const cdada_queue_t* queue);

/**
* Return the size (number of elements) in the queue
*
* @param queue Queue pointer
*
* @returns Returns number of elements. If queue is NULL or corrupted, returns 0
*/
uint32_t cdada_queue_size(const cdada_queue_t* queue);

/**
* Get the maximum capacity (0 if unlimited)
*
* @param queue Queue pointer
*
* @returns Will return the maximum capacity of the queue or 0 if unlimited
*/
uint64_t cdada_queue_get_max_capacity(const cdada_queue_t* queue);

/**
* @brief Set the maximum capacity
*
* This function sets the maximum capacity of the queue. It can be called
* at any time. If called when the queue has more elements than `limit`,
* exceeding elements won't be removed, but the queue won't be able to
* grow until the size is under the new set limit.
*
* Use the value 0 to remove the limit
*
* @param queue Queue pointer
* @param limit Limit of the capacity (set to 0 for unlimited)
*
* @returns Return codes:
*          CDADA_SUCCESS: max capacity was successfully set
*          CDADA_E_UNKNOWN: corrupted queue or internal error (bug)
*          CDADA_E_INVALID: queue is NULL or corrupted
*/
int cdada_queue_set_max_capacity(const cdada_queue_t* queue,
						const uint64_t limit);

//Element manipulation

/**
* Push an element (a copy) at the end of the queue
*
* @param queue Queue pointer
* @param val Element to add
*
* @returns Return codes:
*          CDADA_SUCCESS: element is pushed
*          CDADA_E_FULL: queue is full
*          CDADA_E_MEM: out of memory
*          CDADA_E_UNKNOWN: corrupted queue or internal error (bug)
*          CDADA_E_INVALID: queue is NULL or corrupted
*/
int cdada_queue_push(cdada_queue_t* queue, const void* val);

/**
* Remove an element from the front of the queue (oldest)
*
* @param queue Queue pointer
*
* @returns Return codes:
*          CDADA_SUCCESS: element is popped
*          CDADA_E_EMPTY: queue is empty
*          CDADA_E_MEM: out of memory
*          CDADA_E_UNKNOWN: corrupted queue or internal error (bug)
*          CDADA_E_INVALID: queue is NULL or corrupted
*/
int cdada_queue_pop(cdada_queue_t* queue);

/**
* Get the first element (a copy) in the queue.
*
* @param queue Queue pointer
* @param val When the queue has elements, a copy of the front element will
*            be stored in *val
*
* @returns Return codes:
*          CDADA_SUCCESS: front element is retrieved
*          CDADA_E_EMPTY: queue has no elements
*          CDADA_E_UNKNOWN: corrupted queue or internal error (bug)
*          CDADA_E_INVALID: queue is NULL or corrupted
*/
int cdada_queue_front(const cdada_queue_t* queue, void *val);

/**
* Get the last element (a copy) in the queue.
*
* @param queue Queue pointer
* @param val When the queue has elements, a copy of the back element will
*            be stored in *val
*
* @returns Return codes:
*          CDADA_SUCCESS: back element is retrieved
*          CDADA_E_EMPTY: queue has no elements
*          CDADA_E_UNKNOWN: corrupted queue or internal error (bug)
*          CDADA_E_INVALID: queue is NULL or corrupted
*/
int cdada_queue_back(const cdada_queue_t* queue, void *val);


//Dumpers

/**
* Dump to a string the contents of the queue
*
* @param queue Queue object
* @param size Size of the buffer
* @param buffer Buffer. If NULL, necessary bytes, including '\0' will be queue
*               in 'size_used'
* @param size_used If buffer != NULL, the number of bytes written else number of
*                  bytes necessary to write, including '\0'
*
* @returns Return codes:
*          CDADA_SUCCESS: queue was dumped to buffer
*          CDADA_E_INCOMPLETE: not enough room in buffer
*          CDADA_E_MEM: out of memory
*          CDADA_E_UNKNOWN: corrupted queue or internal error (bug)
*          CDADA_E_INVALID: queue is NULL or corrupted
*/
int cdada_queue_dump(cdada_queue_t* queue, uint32_t size, char* buffer,
							uint32_t* bytes_used);

/**
* @brief Print the contents of the queue
*
* @param queue Queue object
* @param stream stdout or stderr
*
* @returns Return codes:
*          CDADA_SUCCESS: queue was dumped to `stream`
*          CDADA_E_MEM: out of memory
*          CDADA_E_UNKNOWN: corrupted queue or internal error (bug)
*          CDADA_E_INVALID: queue is NULL or corrupted
*/
int cdada_queue_print(cdada_queue_t* queue, FILE *stream);

//Custom types

/**
* Forward declare custom time ops
*/
#define CDADA_QUEUE_CUSTOM_TYPE_DECL(TYPE) \
	extern struct __cdada_queue_ops __cdada_queue_autogen_##TYPE

/**
* @brief Create a queue with a custom type, with a dedicated std::queue
*
* Requires instantiating CDADA_QUEUE_CUSTOM_GEN() or
* CDADA_QUEUE_CUSTOM_GEN_NO_MEMCP() once in a C++ compilation unit
*/
#define cdada_queue_create_custom(TYPE) \
	__cdada_queue_create(sizeof( TYPE ), & __cdada_queue_autogen_##TYPE )

CDADA_END_DECLS

#endif //__CDADA_QUEUE_H__
