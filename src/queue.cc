#include "cdada/queue.h"
#include "cdada/__common_internal.h"
#include "cdada/__queue_internal.h"

#include <stdlib.h>
#include <string.h>

using namespace std;

cdada_queue_t* __cdada_queue_create(const uint16_t val_size,
						__cdada_queue_ops_t* ops){

	__cdada_queue_int_t* m = NULL;

	if(unlikely(val_size == 0))
		return m;

	m = (__cdada_queue_int_t*)malloc(sizeof(__cdada_queue_int_t));
	memset(m, 0, sizeof(__cdada_queue_int_t));
	m->magic_num = CDADA_MAGIC;
	m->user_val_len = val_size;

	try{
		//Custom type
		if(ops){
			m->val_len = m->user_val_len = val_size;
			m->ops = ops;
			(*m->ops->create)(m);
			return m;
		}

		if(val_size == 1){
			m->queue.u8 = new queue<uint8_t>();
			m->val_len = 1;
		}else if(val_size == 2){
			m->queue.u16 = new queue<uint16_t>();
			m->val_len = 2;
		}else if(val_size > 2 && val_size <= 4){
			m->queue.u32 = new queue<uint32_t>();
			m->val_len = 4;
		}else if(val_size > 4 && val_size <= 8){
			m->queue.u64 = new queue<uint64_t>();
			m->val_len = 8;
		}else if(val_size > 8 && val_size <= 16){
			m->queue.u128 = new queue<cdada_u128_t>();
			m->val_len = 16;
		}else if(val_size > 16 && val_size <= 32){
			m->queue.u256 = new queue<cdada_u256_t>();
			m->val_len = 32;
		}else if(val_size > 32 && val_size <= 64){
			m->queue.u512 = new queue<cdada_u512_t>();
			m->val_len = 64;
		}else if(val_size > 64 && val_size <= 128){
			m->queue.u1024 = new queue<cdada_u1024_t>();
			m->val_len = 128;
		}else if(val_size > 128 && val_size <= 256){
			m->queue.u2048 = new queue<cdada_u2048_t>();
			m->val_len = 256;
		}else{
			goto ROLLBACK;
		}
	}catch(bad_alloc& e){
		goto ROLLBACK;
	}catch(...){
		CDADA_ASSERT(0);
		goto ROLLBACK;
	}

	return m;

ROLLBACK:
	free(m);
	return NULL;
}

/**
* Destroy a queue structure
*/
int cdada_queue_destroy(cdada_queue_t* queue){

	__cdada_queue_int_t* m = (__cdada_queue_int_t*)queue;

	CDADA_CHECK_MAGIC(m);

	try{
		int c = m->ops? 0 : m->val_len;
		switch(c){
			case 1:
				delete m->queue.u8;
				break;
			case 2:
				delete m->queue.u16;
				break;
			case 4:
				delete m->queue.u32;
				break;
			case 8:
				delete m->queue.u64;
				break;
			case 16:
				delete m->queue.u128;
				break;
			case 32:
				delete m->queue.u256;
				break;
			case 64:
				delete m->queue.u512;
				break;
			case 128:
				delete m->queue.u1024;
				break;
			case 256:
				delete m->queue.u2048;
				break;
			case 0:
				CDADA_ASSERT(m->ops);
				(*m->ops->destroy)(m);
				break;
			default:
				CDADA_ASSERT(0);
				return CDADA_E_UNKNOWN;
		}
	}catch(...){
		CDADA_ASSERT(0);
		return CDADA_E_UNKNOWN;
	}

	m->magic_num = 0x0;
	free(m);

	return CDADA_SUCCESS;
}

int cdada_queue_push(cdada_queue_t* queue, const void* val){

	__cdada_queue_int_t* m = (__cdada_queue_int_t*)queue;

	CDADA_CHECK_MAGIC(m);

	if(unlikely(!val))
		return CDADA_E_INVALID;

	if(m->max_capacity && cdada_queue_size(queue) >= m->max_capacity)
		return CDADA_E_FULL;

	try{
		int c = m->ops? 0 : m->val_len;
		switch(c){
			case 1:
				return cdada_queue_push_u<uint8_t>(m, m->queue.u8,
								val);
			case 2:
				return cdada_queue_push_u<uint16_t>(m,
								m->queue.u16,
								val);
			case 4:
				return cdada_queue_push_u<uint32_t>(m,
								m->queue.u32,
								val);
			case 8:
				return cdada_queue_push_u<uint64_t>(m,
								m->queue.u64,
								val);
			case 16:
				return cdada_queue_push_u<cdada_u128_t>(m,
								m->queue.u128,
								val);
			case 32:
				return cdada_queue_push_u<cdada_u256_t>(m,
								m->queue.u256,
								val);
			case 64:
				return cdada_queue_push_u<cdada_u512_t>(m,
								m->queue.u512,
								val);
			case 128:
				return cdada_queue_push_u<cdada_u1024_t>(m,
								m->queue.u1024,
								val);
			case 256:
				return cdada_queue_push_u<cdada_u2048_t>(m,
								m->queue.u2048,
								val);
			case 0:
				CDADA_ASSERT(m->ops);
				return (*m->ops->push)(m, val);
			default:
				break;
		}
	}catch(bad_alloc& e){
		return CDADA_E_MEM;
	}catch(...){}

	CDADA_ASSERT(0);
	return CDADA_E_UNKNOWN;
}

int cdada_queue_pop(cdada_queue_t* queue){

	__cdada_queue_int_t* m = (__cdada_queue_int_t*)queue;

	CDADA_CHECK_MAGIC(m);

	try{
		int c = m->ops? 0 : m->val_len;
		switch(c){
			case 1:
				return cdada_queue_pop_u<uint8_t>(m,
								m->queue.u8);
			case 2:
				return cdada_queue_pop_u<uint16_t>(m,
								m->queue.u16);
			case 4:
				return cdada_queue_pop_u<uint32_t>(m,
								m->queue.u32);
			case 8:
				return cdada_queue_pop_u<uint64_t>(m,
								m->queue.u64);
			case 16:
				return cdada_queue_pop_u<cdada_u128_t>(m,
								m->queue.u128);
			case 32:
				return cdada_queue_pop_u<cdada_u256_t>(m,
								m->queue.u256);
			case 64:
				return cdada_queue_pop_u<cdada_u512_t>(m,
								m->queue.u512);
			case 128:
				return cdada_queue_pop_u<cdada_u1024_t>(m,
								m->queue.u1024);
			case 256:
				return cdada_queue_pop_u<cdada_u2048_t>(m,
								m->queue.u2048);
			case 0:
				CDADA_ASSERT(m->ops);
				return (*m->ops->pop)(m);
			default:
				break;
		}
	}catch(...){}

	CDADA_ASSERT(0);
	return CDADA_E_UNKNOWN;
}

uint32_t cdada_queue_size(const cdada_queue_t* queue){

	__cdada_queue_int_t* m = (__cdada_queue_int_t*)queue;

	if(unlikely(!m || m->magic_num != CDADA_MAGIC))
		return 0;

	try{
		int c = m->ops? 0 : m->val_len;
		switch(c){
			case 1:
				return m->queue.u8->size();
			case 2:
				return m->queue.u16->size();
			case 4:
				return m->queue.u32->size();
			case 8:
				return m->queue.u64->size();
			case 16:
				return m->queue.u128->size();
			case 32:
				return m->queue.u256->size();
			case 64:
				return m->queue.u512->size();
			case 128:
				return m->queue.u1024->size();
			case 256:
				return m->queue.u2048->size();
			case 0:
				CDADA_ASSERT(m->ops);
				return (*m->ops->size)(m);
			default:
				break;
		}
	}catch(...){}

	CDADA_ASSERT(0);
	return 0;
}

int cdada_queue_front(const cdada_queue_t* queue, void* val){

	__cdada_queue_int_t* m = (__cdada_queue_int_t*)queue;

	CDADA_CHECK_MAGIC(m);

	if(unlikely(!val))
		return CDADA_E_INVALID;

	try{
		int c = m->ops? 0 : m->val_len;
		switch(c){
			case 1:
				return cdada_queue_front_u<uint8_t>(m,
								m->queue.u8,
								val);
			case 2:
				return cdada_queue_front_u<uint16_t>(m,
								m->queue.u16,
								val);
			case 4:
				return cdada_queue_front_u<uint32_t>(m,
								m->queue.u32,
								val);
			case 8:
				return cdada_queue_front_u<uint64_t>(m,
								m->queue.u64,
								val);
			case 16:
				return cdada_queue_front_u<cdada_u128_t>(m,
								m->queue.u128,
								val);
			case 32:
				return cdada_queue_front_u<cdada_u256_t>(m,
								m->queue.u256,
								val);
			case 64:
				return cdada_queue_front_u<cdada_u512_t>(m,
								m->queue.u512,
								val);
			case 128:
				return cdada_queue_front_u<cdada_u1024_t>(m,
								m->queue.u1024,
								val);
			case 256:
				return cdada_queue_front_u<cdada_u2048_t>(m,
								m->queue.u2048,
								val);
			case 0:
				CDADA_ASSERT(m->ops);
				return (*m->ops->front)(m, val);
			default:
				break;
		}
	}catch(bad_alloc& e){
		return CDADA_E_MEM;
	}catch(...){}

	CDADA_ASSERT(0);
	return CDADA_E_UNKNOWN;
}

int cdada_queue_back(const cdada_queue_t* queue, void* val){

	__cdada_queue_int_t* m = (__cdada_queue_int_t*)queue;

	CDADA_CHECK_MAGIC(m);

	if(unlikely(!val))
		return CDADA_E_INVALID;

	try{
		int c = m->ops? 0 : m->val_len;
		switch(c){
			case 1:
				return cdada_queue_back_u<uint8_t>(m,
								m->queue.u8,
								val);
			case 2:
				return cdada_queue_back_u<uint16_t>(m,
								m->queue.u16,
								val);
			case 4:
				return cdada_queue_back_u<uint32_t>(m,
								m->queue.u32,
								val);
			case 8:
				return cdada_queue_back_u<uint64_t>(m,
								m->queue.u64,
								val);
			case 16:
				return cdada_queue_back_u<cdada_u128_t>(m,
								m->queue.u128,
								val);
			case 32:
				return cdada_queue_back_u<cdada_u256_t>(m,
								m->queue.u256,
								val);
			case 64:
				return cdada_queue_back_u<cdada_u512_t>(m,
								m->queue.u512,
								val);
			case 128:
				return cdada_queue_back_u<cdada_u1024_t>(m,
								m->queue.u1024,
								val);
			case 256:
				return cdada_queue_back_u<cdada_u2048_t>(m,
								m->queue.u2048,
								val);
			case 0:
				CDADA_ASSERT(m->ops);
				return (*m->ops->back)(m, val);
			default:
				break;
		}
	}catch(bad_alloc& e){
		return CDADA_E_MEM;
	}catch(...){}

	CDADA_ASSERT(0);
	return CDADA_E_UNKNOWN;
}

bool cdada_queue_empty(const cdada_queue_t* queue){

	__cdada_queue_int_t* m = (__cdada_queue_int_t*)queue;

	if(unlikely(!m || m->magic_num != CDADA_MAGIC))
		return false;

	try{
		int c = m->ops? 0 : m->val_len;
		switch(c){
			case 1:
				return cdada_queue_empty_u<uint8_t>(m,
								m->queue.u8);
			case 2:
				return cdada_queue_empty_u<uint16_t>(m,
								m->queue.u16);
			case 4:
				return cdada_queue_empty_u<uint32_t>(m,
								m->queue.u32);
			case 8:
				return cdada_queue_empty_u<uint64_t>(m,
								m->queue.u64);
			case 16:
				return cdada_queue_empty_u<cdada_u128_t>(m,
								m->queue.u128);
			case 32:
				return cdada_queue_empty_u<cdada_u256_t>(m,
								m->queue.u256);
			case 64:
				return cdada_queue_empty_u<cdada_u512_t>(m,
								m->queue.u512);
			case 128:
				return cdada_queue_empty_u<cdada_u1024_t>(m,
								m->queue.u1024);
			case 256:
				return cdada_queue_empty_u<cdada_u2048_t>(m,
								m->queue.u2048);
			case 0:
				CDADA_ASSERT(m->ops);
				return (*m->ops->empty)(m);
			default:
				break;
		}
	}catch(...){}

	CDADA_ASSERT(0);
	return false;
}

uint64_t cdada_queue_get_max_capacity(const cdada_queue_t* queue){

	__cdada_queue_int_t* m = (__cdada_queue_int_t*)queue;

	if(unlikely(!(m) || m->magic_num != CDADA_MAGIC))
		return 0;

	return m->max_capacity;
}

int cdada_queue_set_max_capacity(const cdada_queue_t* queue,
						const uint64_t limit){
	__cdada_queue_int_t* m = (__cdada_queue_int_t*)queue;

	if(unlikely(!(m) || m->magic_num != CDADA_MAGIC))
		return CDADA_E_INVALID;

	m->max_capacity = limit;

	return CDADA_SUCCESS;
}

int cdada_queue_dump(cdada_queue_t* queue, uint32_t size, char* buffer,
							uint32_t* size_used){

	__cdada_queue_int_t* m = (__cdada_queue_int_t*)queue;
	CDADA_CHECK_MAGIC(m);

	if(!size_used || (buffer&&size ==0))
		return CDADA_E_INVALID;

	try{
		std::stringstream ss;
		ss << "{";

		int c = m->ops? 0 : m->val_len;
		switch(c){
			case 1:
				cdada_queue_dump_u<uint8_t>(m, m->queue.u8, ss);
				break;
			case 2:
				cdada_queue_dump_u<uint16_t>(m, m->queue.u16,
									ss);
				break;
			case 4:
				cdada_queue_dump_u<uint32_t>(m, m->queue.u32,
									ss);
				break;
			case 8:
				cdada_queue_dump_u<uint64_t>(m, m->queue.u64,
									ss);
				break;
			case 16:
				cdada_queue_dump_u<cdada_u128_t>(m,
								m->queue.u128,
								ss);
				break;
			case 32:
				cdada_queue_dump_u<cdada_u256_t>(m,
								m->queue.u256,
								ss);
				break;
			case 64:
				cdada_queue_dump_u<cdada_u512_t>(m,
								m->queue.u512,
								ss);
				break;
			case 128:
				cdada_queue_dump_u<cdada_u1024_t>(m,
								m->queue.u1024,
								ss);
				break;
			case 256:
				cdada_queue_dump_u<cdada_u2048_t>(m,
								m->queue.u2048,
								ss);
				break;
			case 0:
				CDADA_ASSERT(m->ops);
				(*m->ops->dump)(m, ss);
				break;
			default:
				CDADA_ASSERT(0);
				return CDADA_E_UNKNOWN;
		}

		ss << "}";

		*size_used = ss.str().length()+1;
		if(!buffer)
			return CDADA_SUCCESS;

		snprintf(buffer, size, "%s", ss.str().c_str());
		if(ss.str().length()+1 > size)
			return CDADA_E_INCOMPLETE;
	}catch(bad_alloc& e){
		return CDADA_E_MEM;
	}catch(...){
		CDADA_ASSERT(0);
		return CDADA_E_UNKNOWN;
	}

	return CDADA_SUCCESS;
}

int cdada_queue_print(cdada_queue_t* queue, FILE *stream){

	__cdada_queue_int_t* m = (__cdada_queue_int_t*)queue;
	CDADA_CHECK_MAGIC(m);

	try{
		std::stringstream ss;
		ss << "{";

		int c = m->ops? 0 : m->val_len;
		switch(c){
			case 1:
				cdada_queue_dump_u<uint8_t>(m, m->queue.u8, ss);
				break;
			case 2:
				cdada_queue_dump_u<uint16_t>(m, m->queue.u16,
									ss);
				break;
			case 4:
				cdada_queue_dump_u<uint32_t>(m, m->queue.u32,
									ss);
				break;
			case 8:
				cdada_queue_dump_u<uint64_t>(m, m->queue.u64,
									ss);
				break;
			case 16:
				cdada_queue_dump_u<cdada_u128_t>(m,
								m->queue.u128,
								ss);
				break;
			case 32:
				cdada_queue_dump_u<cdada_u256_t>(m,
								m->queue.u256,
								ss);
				break;
			case 64:
				cdada_queue_dump_u<cdada_u512_t>(m,
								m->queue.u512,
								ss);
				break;
			case 128:
				cdada_queue_dump_u<cdada_u1024_t>(m,
								m->queue.u1024,
								ss);
				break;
			case 256:
				cdada_queue_dump_u<cdada_u2048_t>(m,
								m->queue.u2048,
								ss);
				break;
			case 0:
				CDADA_ASSERT(m->ops);
				(*m->ops->dump)(m, ss);
				break;
			default:
				CDADA_ASSERT(0);
				return CDADA_E_UNKNOWN;
		}
		ss << "}\n";

		fprintf(stream, "%s", ss.str().c_str());
	}catch(bad_alloc& e){
		return CDADA_E_MEM;
	}catch(...){
		CDADA_ASSERT(0);
		return CDADA_E_UNKNOWN;
	}

	return CDADA_SUCCESS;
}
