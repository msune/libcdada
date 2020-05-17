#include "cdata/list.h"
#include "cdata/__common_internal.h"
#include "cdata/__list_internal.h"

#include <string.h>

using namespace std;

cdata_list_t* __cdata_list_create(const uint16_t val_size,
						__cdata_list_ops_t* ops){

	__cdata_list_int_t* m = NULL;

	if(unlikely(val_size == 0))
		return m;

	m = (__cdata_list_int_t*)malloc(sizeof(__cdata_list_int_t));
	memset(m, 0, sizeof(__cdata_list_int_t));
	m->magic_num = CDATA_MAGIC;
	m->user_val_len = val_size;

	try{
		if(val_size == 1){
			m->list.u8 = new list<uint8_t>();
			m->val_len = 1;
		}else if(val_size == 2){
			m->list.u16 = new list<uint16_t>();
			m->val_len = 2;
		}else if(val_size > 2 && val_size <= 4){
			m->list.u32 = new list<uint32_t>();
			m->val_len = 4;
		}else if(val_size > 4 && val_size <= 8){
			m->list.u64 = new list<uint64_t>();
			m->val_len = 8;
		}else if(val_size > 8 && val_size <= 16){
			m->list.u128 = new list<cdata_u128_t>();
			m->val_len = 16;
		}else if(val_size > 16 && val_size <= 32){
			m->list.u256 = new list<cdata_u256_t>();
			m->val_len = 32;
		}else if(val_size > 32 && val_size <= 64){
			m->list.u512 = new list<cdata_u512_t>();
			m->val_len = 64;
		}else if(val_size > 64 && val_size <= 128){
			m->list.u1024 = new list<cdata_u1024_t>();
			m->val_len = 128;
		}else if(val_size > 128 && val_size <= 256){
			m->list.u2048 = new list<cdata_u2048_t>();
			m->val_len = 256;
		}else{
			if(!ops)
				goto ROLLBACK;
			m->val_len = m->user_val_len = val_size;
			m->ops = ops;
			(*m->ops->create)(m);
		}
	}catch(bad_alloc& e){
		goto ROLLBACK;
	}catch(...){
		CDATA_ASSERT(0);
		goto ROLLBACK;
	}

	return m;

ROLLBACK:
	free(m);
	return NULL;
}

cdata_list_t* cdata_list_create(const uint16_t val_size){
	return __cdata_list_create(val_size, NULL);
}

/**
* Destroy a list structure
*/
int cdata_list_destroy(cdata_list_t* list){

	__cdata_list_int_t* m = (__cdata_list_int_t*)list;

	CDATA_CHECK_MAGIC(m);

	try{
		switch(m->val_len){
			case 1:
				delete m->list.u8;
				break;
			case 2:
				delete m->list.u16;
				break;
			case 4:
				delete m->list.u32;
				break;
			case 8:
				delete m->list.u64;
				break;
			case 16:
				delete m->list.u128;
				break;
			case 32:
				delete m->list.u256;
				break;
			case 64:
				delete m->list.u512;
				break;
			case 128:
				delete m->list.u1024;
				break;
			case 256:
				delete m->list.u2048;
				break;
			default:
				CDATA_ASSERT(m->ops);
				(*m->ops->destroy)(m);
				break;
		}
	}catch(...){
		CDATA_ASSERT(0);
		return CDATA_E_UNKNOWN;
	}

	m->magic_num = 0x0;
	free(m);

	return CDATA_SUCCESS;
}

int cdata_list_clear(cdata_list_t* list){

	__cdata_list_int_t* m = (__cdata_list_int_t*)list;

	CDATA_CHECK_MAGIC(m);

	try{
		switch(m->val_len){
			case 1:
				m->list.u8->clear();
				break;
			case 2:
				m->list.u16->clear();
				break;
			case 4:
				m->list.u32->clear();
				break;
			case 8:
				m->list.u64->clear();
				break;
			case 16:
				m->list.u128->clear();
				break;
			case 32:
				m->list.u256->clear();
				break;
			case 64:
				m->list.u512->clear();
				break;
			case 128:
				m->list.u1024->clear();
				break;
			case 256:
				m->list.u2048->clear();
				break;
			default:
				CDATA_ASSERT(m->ops);
				(*m->ops->clear)(m);
				break;
		}
	}catch(bad_alloc& e){
		return CDATA_E_MEM;
	}catch(...){
		CDATA_ASSERT(0);
		return CDATA_E_UNKNOWN;
	}

	return CDATA_SUCCESS;
}

bool cdata_list_empty(cdata_list_t* list){

	__cdata_list_int_t* m = (__cdata_list_int_t*)list;

	if(unlikely(!m || m->magic_num != CDATA_MAGIC))
		return false;

	try{
		switch(m->val_len){
			case 1:
				return m->list.u8->empty();
			case 2:
				return m->list.u16->empty();
			case 4:
				return m->list.u32->empty();
			case 8:
				return m->list.u64->empty();
			case 16:
				return m->list.u128->empty();
			case 32:
				return m->list.u256->empty();
			case 64:
				return m->list.u512->empty();
			case 128:
				return m->list.u1024->empty();
			case 256:
				return m->list.u2048->empty();
			default:
				CDATA_ASSERT(m->ops);
				return (*m->ops->empty)(m);
		}
	}catch(...){
		CDATA_ASSERT(0);
		return false;
	}

	return false;
}

uint32_t cdata_list_size(cdata_list_t* list){

	__cdata_list_int_t* m = (__cdata_list_int_t*)list;

	if(unlikely(!m || m->magic_num != CDATA_MAGIC))
		return 0;

	try{
		switch(m->val_len){
			case 1:
				return m->list.u8->size();
			case 2:
				return m->list.u16->size();
			case 4:
				return m->list.u32->size();
			case 8:
				return m->list.u64->size();
			case 16:
				return m->list.u128->size();
			case 32:
				return m->list.u256->size();
			case 64:
				return m->list.u512->size();
			case 128:
				return m->list.u1024->size();
			case 256:
				return m->list.u2048->size();
			default:
				CDATA_ASSERT(m->ops);
				return (*m->ops->size)(m);
		}
	}catch(...){
		CDATA_ASSERT(0);
		return 0;
	}

	return 0;
}

int cdata_list_insert(cdata_list_t* list, const void* val, const uint32_t pos){

	int rv;
	__cdata_list_int_t* m = (__cdata_list_int_t*)list;

	CDATA_CHECK_MAGIC(m);

	if(unlikely(!val))
		return CDATA_E_INVALID;

	//NOTE: we don't want std::list insert "replace semantics", so we return
	//E_EXISTS if val is present in the list
	try{
		switch(m->val_len){
			case 1:
				rv = cdata_list_insert_u<uint8_t>(m, m->list.u8,
								val, pos);
				break;
			case 2:
				rv = cdata_list_insert_u<uint16_t>(m,
								m->list.u16,
								val, pos);
				break;
			case 4:
				rv = cdata_list_insert_u<uint32_t>(m,
								m->list.u32,
								val, pos);
				break;
			case 8:
				rv = cdata_list_insert_u<uint64_t>(m,
								m->list.u64,
								val, pos);
				break;
			case 16:
				rv = cdata_list_insert_u<cdata_u128_t>(m,
							m->list.u128,
							val, pos);
				break;
			case 32:
				rv = cdata_list_insert_u<cdata_u256_t>(m,
							m->list.u256,
							val, pos);
				break;
			case 64:
				rv = cdata_list_insert_u<cdata_u512_t>(m,
							m->list.u512,
							val, pos);
				break;
			case 128:
				rv = cdata_list_insert_u<cdata_u1024_t>(m,
							m->list.u1024,
							val, pos);
				break;
			case 256:
				rv = cdata_list_insert_u<cdata_u2048_t>(m,
							m->list.u2048,
							val, pos);
				break;
			default:
				CDATA_ASSERT(m->ops);
				rv = (*m->ops->insert)(m, val, pos);
				break;
		}
	}catch(bad_alloc& e){
		return CDATA_E_MEM;
	}catch(...){
		CDATA_ASSERT(0);
		return CDATA_E_UNKNOWN;
	}

	return rv;
}

int cdata_list_get(cdata_list_t* list, const uint32_t pos, void* val){

	int rv;
	__cdata_list_int_t* m = (__cdata_list_int_t*)list;

	CDATA_CHECK_MAGIC(m);

	if(unlikely(!val))
		return CDATA_E_INVALID;

	//NOTE: we don't want std::list insert "replace semantics", so we return
	//E_EXISTS if val is present in the list
	try{
		switch(m->val_len){
			case 1:
				rv = cdata_list_get_u<uint8_t>(m, m->list.u8,
								pos, val);
				break;
			case 2:
				rv = cdata_list_get_u<uint16_t>(m,
								m->list.u16,
								pos, val);
				break;
			case 4:
				rv = cdata_list_get_u<uint32_t>(m,
								m->list.u32,
								pos, val);
				break;
			case 8:
				rv = cdata_list_get_u<uint64_t>(m,
								m->list.u64,
								pos, val);
				break;
			case 16:
				rv = cdata_list_get_u<cdata_u128_t>(m,
							m->list.u128,
							pos, val);
				break;
			case 32:
				rv = cdata_list_get_u<cdata_u256_t>(m,
							m->list.u256,
							pos, val);
				break;
			case 64:
				rv = cdata_list_get_u<cdata_u512_t>(m,
							m->list.u512,
							pos, val);
				break;
			case 128:
				rv = cdata_list_get_u<cdata_u1024_t>(m,
							m->list.u1024,
							pos, val);
				break;
			case 256:
				rv = cdata_list_get_u<cdata_u2048_t>(m,
							m->list.u2048,
							pos, val);
				break;
			default:
				CDATA_ASSERT(m->ops);
				rv = (*m->ops->get)(m, pos, val);
				break;
		}
	}catch(bad_alloc& e){
		return CDATA_E_MEM;
	}catch(...){
		CDATA_ASSERT(0);
		return CDATA_E_UNKNOWN;
	}

	return rv;
}

int cdata_list_erase(cdata_list_t* list, const uint32_t pos){

	int rv;
	__cdata_list_int_t* m = (__cdata_list_int_t*)list;

	CDATA_CHECK_MAGIC(m);

	try{
		switch(m->val_len){
			case 1:
				rv = cdata_list_erase_u<uint8_t>(m, m->list.u8,
									pos);
				break;
			case 2:
				rv = cdata_list_erase_u<uint16_t>(m,
								m->list.u16,
								pos);
				break;
			case 4:
				rv = cdata_list_erase_u<uint32_t>(m,
								m->list.u32,
								pos);
				break;
			case 8:
				rv = cdata_list_erase_u<uint64_t>(m,
								m->list.u64,
								pos);
				break;
			case 16:
				rv = cdata_list_erase_u<cdata_u128_t>(m,
								m->list.u128,
								pos);
				break;
			case 32:
				rv = cdata_list_erase_u<cdata_u256_t>(m,
								m->list.u256,
								pos);
				break;
			case 64:
				rv = cdata_list_erase_u<cdata_u512_t>(m,
								m->list.u512,
								pos);
				break;
			case 128:
				rv = cdata_list_erase_u<cdata_u1024_t>(m,
								m->list.u1024,
								pos);
				break;
			case 256:
				rv = cdata_list_erase_u<cdata_u2048_t>(m,
								m->list.u2048,
								pos);
				break;
			default:
				CDATA_ASSERT(m->ops);
				rv = (*m->ops->erase)(m, pos);
				break;
		}
	}catch(bad_alloc& e){
		return CDATA_E_MEM;
	}catch(...){
		CDATA_ASSERT(0);
		return CDATA_E_UNKNOWN;
	}

	return rv;
}

int cdata_list_remove(cdata_list_t* list, const void* val){

	int rv;
	__cdata_list_int_t* m = (__cdata_list_int_t*)list;

	CDATA_CHECK_MAGIC(m);

	if(unlikely(!val))
		return CDATA_E_INVALID;

	//NOTE: we don't want std::list remove "replace semantics", so we return
	//E_EXISTS if val is present in the list
	try{
		switch(m->val_len){
			case 1:
				rv = cdata_list_remove_u<uint8_t>(m, m->list.u8,
								val);
				break;
			case 2:
				rv = cdata_list_remove_u<uint16_t>(m,
								m->list.u16,
								val);
				break;
			case 4:
				rv = cdata_list_remove_u<uint32_t>(m,
								m->list.u32,
								val);
				break;
			case 8:
				rv = cdata_list_remove_u<uint64_t>(m,
								m->list.u64,
								val);
				break;
			case 16:
				rv = cdata_list_remove_u<cdata_u128_t>(m,
							m->list.u128,
							val);
				break;
			case 32:
				rv = cdata_list_remove_u<cdata_u256_t>(m,
							m->list.u256,
							val);
				break;
			case 64:
				rv = cdata_list_remove_u<cdata_u512_t>(m,
							m->list.u512,
							val);
				break;
			case 128:
				rv = cdata_list_remove_u<cdata_u1024_t>(m,
							m->list.u1024,
							val);
				break;
			case 256:
				rv = cdata_list_remove_u<cdata_u2048_t>(m,
							m->list.u2048,
							val);
				break;
			default:
				CDATA_ASSERT(m->ops);
				rv = (*m->ops->remove)(m, val);
				break;
		}
	}catch(bad_alloc& e){
		return CDATA_E_MEM;
	}catch(...){
		CDATA_ASSERT(0);
		return CDATA_E_UNKNOWN;
	}

	return rv;
}

static int cdata_list_push_(cdata_list_t* list, const void* val, bool front){

	int rv;
	__cdata_list_int_t* m = (__cdata_list_int_t*)list;

	CDATA_CHECK_MAGIC(m);

	if(unlikely(!val))
		return CDATA_E_INVALID;

	try{
		switch(m->val_len){
			case 1:
				rv = cdata_list_push_u<uint8_t>(m, m->list.u8,
								val, front);
				break;
			case 2:
				rv = cdata_list_push_u<uint16_t>(m, m->list.u16,
								val, front);
				break;
			case 4:
				rv = cdata_list_push_u<uint32_t>(m, m->list.u32,
								val, front);
				break;
			case 8:
				rv = cdata_list_push_u<uint64_t>(m,m->list.u64,
							val, front);
				break;
			case 16:
				rv = cdata_list_push_u<cdata_u128_t>(m,
								m->list.u128,
								val, front);
				break;
			case 32:
				rv = cdata_list_push_u<cdata_u256_t>(m,
								m->list.u256,
								val, front);
				break;
			case 64:
				rv = cdata_list_push_u<cdata_u512_t>(m,
								m->list.u512,
								val, front);
				break;
			case 128:
				rv = cdata_list_push_u<cdata_u1024_t>(m,
								m->list.u1024,
								val, front);
				break;
			case 256:
				rv = cdata_list_push_u<cdata_u2048_t>(m,
								m->list.u2048,
								val, front);
				break;
			default:
				CDATA_ASSERT(m->ops);
				rv = (*m->ops->push)(m, val, front);
				break;
		}
	}catch(bad_alloc& e){
		return CDATA_E_MEM;
	}catch(...){
		CDATA_ASSERT(0);
		return CDATA_E_UNKNOWN;
	}

	return rv;
}

int cdata_list_push_front(cdata_list_t* list, const void* val){
	return cdata_list_push_(list, val, true);
}

int cdata_list_push_back(cdata_list_t* list, const void* val){
	return cdata_list_push_(list, val, false);
}

static int cdata_list_pop_(cdata_list_t* list, bool front){

	int rv;
	__cdata_list_int_t* m = (__cdata_list_int_t*)list;

	CDATA_CHECK_MAGIC(m);

	try{
		switch(m->val_len){
			case 1:
				rv = cdata_list_pop_u<uint8_t>(m, m->list.u8,
								front);
				break;
			case 2:
				rv = cdata_list_pop_u<uint16_t>(m, m->list.u16,
								front);
				break;
			case 4:
				rv = cdata_list_pop_u<uint32_t>(m, m->list.u32,
								front);
				break;
			case 8:
				rv = cdata_list_pop_u<uint64_t>(m,m->list.u64,
							front);
				break;
			case 16:
				rv = cdata_list_pop_u<cdata_u128_t>(m,
								m->list.u128,
								front);
				break;
			case 32:
				rv = cdata_list_pop_u<cdata_u256_t>(m,
								m->list.u256,
								front);
				break;
			case 64:
				rv = cdata_list_pop_u<cdata_u512_t>(m,
								m->list.u512,
								front);
				break;
			case 128:
				rv = cdata_list_pop_u<cdata_u1024_t>(m,
								m->list.u1024,
								front);
				break;
			case 256:
				rv = cdata_list_pop_u<cdata_u2048_t>(m,
								m->list.u2048,
								front);
				break;
			default:
				CDATA_ASSERT(m->ops);
				rv = (*m->ops->pop)(m, front);
				break;
		}
	}catch(bad_alloc& e){
		return CDATA_E_MEM;
	}catch(...){
		CDATA_ASSERT(0);
		return CDATA_E_UNKNOWN;
	}

	return rv;
}

int cdata_list_pop_front(cdata_list_t* list){
	return cdata_list_pop_(list, true);
}

int cdata_list_pop_back(cdata_list_t* list){
	return cdata_list_pop_(list, false);
}

int cdata_list_sort(cdata_list_t* list){

	__cdata_list_int_t* m = (__cdata_list_int_t*)list;

	if(unlikely(!m || m->magic_num != CDATA_MAGIC))
		return CDATA_E_INVALID;

	try{
		switch(m->val_len){
			case 1:
				m->list.u8->sort();
				break;
			case 2:
				m->list.u16->sort();
				break;
			case 4:
				m->list.u32->sort();
				break;
			case 8:
				m->list.u64->sort();
				break;
			case 16:
				m->list.u128->sort();
				break;
			case 32:
				m->list.u256->sort();
				break;
			case 64:
				m->list.u512->sort();
				break;
			case 128:
				m->list.u1024->sort();
				break;
			case 256:
				m->list.u2048->sort();
				break;
			default:
				CDATA_ASSERT(m->ops);
				(*m->ops->sort)(m);
				break;
		}
	}catch(...){
		CDATA_ASSERT(0);
		return CDATA_E_UNKNOWN;
	}

	return CDATA_SUCCESS;
}

int cdata_list_reverse(cdata_list_t* list){

	__cdata_list_int_t* m = (__cdata_list_int_t*)list;

	if(unlikely(!m || m->magic_num != CDATA_MAGIC))
		return CDATA_E_INVALID;

	try{
		switch(m->val_len){
			case 1:
				m->list.u8->reverse();
				break;
			case 2:
				m->list.u16->reverse();
				break;
			case 4:
				m->list.u32->reverse();
				break;
			case 8:
				m->list.u64->reverse();
				break;
			case 16:
				m->list.u128->reverse();
				break;
			case 32:
				m->list.u256->reverse();
				break;
			case 64:
				m->list.u512->reverse();
				break;
			case 128:
				m->list.u1024->reverse();
				break;
			case 256:
				m->list.u2048->reverse();
				break;
			default:
				CDATA_ASSERT(m->ops);
				(*m->ops->reverse)(m);
				break;
		}
	}catch(...){
		CDATA_ASSERT(0);
		return CDATA_E_UNKNOWN;
	}

	return CDATA_SUCCESS;
}

int cdata_list_unique(cdata_list_t* list){

	__cdata_list_int_t* m = (__cdata_list_int_t*)list;

	if(unlikely(!m || m->magic_num != CDATA_MAGIC))
		return CDATA_E_INVALID;

	try{
		switch(m->val_len){
			case 1:
				m->list.u8->unique();
				break;
			case 2:
				m->list.u16->unique();
				break;
			case 4:
				m->list.u32->unique();
				break;
			case 8:
				m->list.u64->unique();
				break;
			case 16:
				m->list.u128->unique();
				break;
			case 32:
				m->list.u256->unique();
				break;
			case 64:
				m->list.u512->unique();
				break;
			case 128:
				m->list.u1024->unique();
				break;
			case 256:
				m->list.u2048->unique();
				break;
			default:
				CDATA_ASSERT(m->ops);
				(*m->ops->unique)(m);
				break;
		}
	}catch(...){
		CDATA_ASSERT(0);
		return CDATA_E_UNKNOWN;
	}

	return CDATA_SUCCESS;
}

int cdata_list_traverse(const cdata_list_t* list, cdata_list_it f,
								void* opaque){

	__cdata_list_int_t* m = (__cdata_list_int_t*)list;

	CDATA_CHECK_MAGIC(m);

	if(unlikely(!f))
		return CDATA_E_INVALID;

	try{
		switch(m->val_len){
			case 1:
				cdata_list_traverse_u<uint8_t>(m, m->list.u8,
								f, opaque);
				break;
			case 2:
				cdata_list_traverse_u<uint16_t>(m, m->list.u16,
								f, opaque);
				break;
			case 4:
				cdata_list_traverse_u<uint32_t>(m, m->list.u32,
								f, opaque);
				break;
			case 8:
				cdata_list_traverse_u<uint64_t>(m, m->list.u64,
								f, opaque);
				break;
			case 16:
				cdata_list_traverse_u<cdata_u128_t>(m,
								m->list.u128, f,
								opaque);
				break;
			case 32:
				cdata_list_traverse_u<cdata_u256_t>(m,
								m->list.u256, f,
								opaque);
				break;
			case 64:
				cdata_list_traverse_u<cdata_u512_t>(m,
								m->list.u512, f,
								opaque);
				break;
			case 128:
				cdata_list_traverse_u<cdata_u1024_t>(m,
								m->list.u1024,
								f, opaque);
				break;
			case 256:
				cdata_list_traverse_u<cdata_u2048_t>(m,
								m->list.u2048,
								f, opaque);
				break;
			default:
				CDATA_ASSERT(m->ops);
				(*m->ops->traverse)(m, f, opaque);
				break;
		}
	}catch(...){
		CDATA_ASSERT(0);
		return CDATA_E_UNKNOWN;
	}

	return CDATA_SUCCESS;
}

int cdata_list_rtraverse(const cdata_list_t* list, cdata_list_it f,
								void* opaque){

	__cdata_list_int_t* m = (__cdata_list_int_t*)list;

	CDATA_CHECK_MAGIC(m);

	if(unlikely(!f))
		return CDATA_E_INVALID;

	try{
		switch(m->val_len){
			case 1:
				cdata_list_rtraverse_u<uint8_t>(m, m->list.u8,
								f, opaque);
				break;
			case 2:
				cdata_list_rtraverse_u<uint16_t>(m, m->list.u16,
								f, opaque);
				break;
			case 4:
				cdata_list_rtraverse_u<uint32_t>(m, m->list.u32,
								f, opaque);
				break;
			case 8:
				cdata_list_rtraverse_u<uint64_t>(m, m->list.u64,
								f, opaque);
				break;
			case 16:
				cdata_list_rtraverse_u<cdata_u128_t>(m,
								m->list.u128, f,
								opaque);
				break;
			case 32:
				cdata_list_rtraverse_u<cdata_u256_t>(m,
								m->list.u256, f,
								opaque);
				break;
			case 64:
				cdata_list_rtraverse_u<cdata_u512_t>(m,
								m->list.u512, f,
								opaque);
				break;
			case 128:
				cdata_list_rtraverse_u<cdata_u1024_t>(m,
								m->list.u1024,
								f, opaque);
				break;
			case 256:
				cdata_list_rtraverse_u<cdata_u2048_t>(m,
								m->list.u2048,
								f, opaque);
				break;
			default:
				CDATA_ASSERT(m->ops);
				(*m->ops->rtraverse)(m, f, opaque);
				break;
		}
	}catch(...){
		CDATA_ASSERT(0);
		return CDATA_E_UNKNOWN;
	}

	return CDATA_SUCCESS;
}
