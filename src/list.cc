#include "cdada/list.h"
#include "cdada/__common_internal.h"
#include "cdada/__list_internal.h"

#include <stdlib.h>
#include <string.h>

using namespace std;

cdada_list_t* __cdada_list_create(const uint16_t val_size,
						__cdada_list_ops_t* ops){

	__cdada_list_int_t* m = NULL;

	if(unlikely(val_size == 0))
		return m;

	m = (__cdada_list_int_t*)malloc(sizeof(__cdada_list_int_t));
	memset(m, 0, sizeof(__cdada_list_int_t));
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
			m->list.u128 = new list<cdada_u128_t>();
			m->val_len = 16;
		}else if(val_size > 16 && val_size <= 32){
			m->list.u256 = new list<cdada_u256_t>();
			m->val_len = 32;
		}else if(val_size > 32 && val_size <= 64){
			m->list.u512 = new list<cdada_u512_t>();
			m->val_len = 64;
		}else if(val_size > 64 && val_size <= 128){
			m->list.u1024 = new list<cdada_u1024_t>();
			m->val_len = 128;
		}else if(val_size > 128 && val_size <= 256){
			m->list.u2048 = new list<cdada_u2048_t>();
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

cdada_list_t* cdada_list_create(const uint16_t val_size){
	return __cdada_list_create(val_size, NULL);
}

/**
* Destroy a list structure
*/
int cdada_list_destroy(cdada_list_t* list){

	__cdada_list_int_t* m = (__cdada_list_int_t*)list;

	CDADA_CHECK_MAGIC(m);

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
				CDADA_ASSERT(m->ops);
				(*m->ops->destroy)(m);
				break;
		}
	}catch(...){
		CDADA_ASSERT(0);
		return CDADA_E_UNKNOWN;
	}

	m->magic_num = 0x0;
	free(m);

	return CDADA_SUCCESS;
}

int cdada_list_clear(cdada_list_t* list){

	__cdada_list_int_t* m = (__cdada_list_int_t*)list;

	CDADA_CHECK_MAGIC(m);

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
				CDADA_ASSERT(m->ops);
				(*m->ops->clear)(m);
				break;
		}
	}catch(bad_alloc& e){
		return CDADA_E_MEM;
	}catch(...){
		CDADA_ASSERT(0);
		return CDADA_E_UNKNOWN;
	}

	return CDADA_SUCCESS;
}

bool cdada_list_empty(cdada_list_t* list){

	__cdada_list_int_t* m = (__cdada_list_int_t*)list;

	if(unlikely(!m || m->magic_num != CDADA_MAGIC))
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
				CDADA_ASSERT(m->ops);
				return (*m->ops->empty)(m);
		}
	}catch(...){
		CDADA_ASSERT(0);
		return false;
	}

	return false;
}

uint32_t cdada_list_size(cdada_list_t* list){

	__cdada_list_int_t* m = (__cdada_list_int_t*)list;

	if(unlikely(!m || m->magic_num != CDADA_MAGIC))
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
				CDADA_ASSERT(m->ops);
				return (*m->ops->size)(m);
		}
	}catch(...){
		CDADA_ASSERT(0);
		return 0;
	}

	return 0;
}

int cdada_list_insert(cdada_list_t* list, const void* val, const uint32_t pos){

	int rv;
	__cdada_list_int_t* m = (__cdada_list_int_t*)list;

	CDADA_CHECK_MAGIC(m);

	if(unlikely(!val))
		return CDADA_E_INVALID;

	//NOTE: we don't want std::list insert "replace semantics", so we return
	//E_EXISTS if val is present in the list
	try{
		switch(m->val_len){
			case 1:
				rv = cdada_list_insert_u<uint8_t>(m, m->list.u8,
								val, pos);
				break;
			case 2:
				rv = cdada_list_insert_u<uint16_t>(m,
								m->list.u16,
								val, pos);
				break;
			case 4:
				rv = cdada_list_insert_u<uint32_t>(m,
								m->list.u32,
								val, pos);
				break;
			case 8:
				rv = cdada_list_insert_u<uint64_t>(m,
								m->list.u64,
								val, pos);
				break;
			case 16:
				rv = cdada_list_insert_u<cdada_u128_t>(m,
							m->list.u128,
							val, pos);
				break;
			case 32:
				rv = cdada_list_insert_u<cdada_u256_t>(m,
							m->list.u256,
							val, pos);
				break;
			case 64:
				rv = cdada_list_insert_u<cdada_u512_t>(m,
							m->list.u512,
							val, pos);
				break;
			case 128:
				rv = cdada_list_insert_u<cdada_u1024_t>(m,
							m->list.u1024,
							val, pos);
				break;
			case 256:
				rv = cdada_list_insert_u<cdada_u2048_t>(m,
							m->list.u2048,
							val, pos);
				break;
			default:
				CDADA_ASSERT(m->ops);
				rv = (*m->ops->insert)(m, val, pos);
				break;
		}
	}catch(bad_alloc& e){
		return CDADA_E_MEM;
	}catch(...){
		CDADA_ASSERT(0);
		return CDADA_E_UNKNOWN;
	}

	return rv;
}

int cdada_list_get(cdada_list_t* list, const uint32_t pos, void* val){

	int rv;
	__cdada_list_int_t* m = (__cdada_list_int_t*)list;

	CDADA_CHECK_MAGIC(m);

	if(unlikely(!val))
		return CDADA_E_INVALID;

	//NOTE: we don't want std::list insert "replace semantics", so we return
	//E_EXISTS if val is present in the list
	try{
		switch(m->val_len){
			case 1:
				rv = cdada_list_get_u<uint8_t>(m, m->list.u8,
								pos, val);
				break;
			case 2:
				rv = cdada_list_get_u<uint16_t>(m,
								m->list.u16,
								pos, val);
				break;
			case 4:
				rv = cdada_list_get_u<uint32_t>(m,
								m->list.u32,
								pos, val);
				break;
			case 8:
				rv = cdada_list_get_u<uint64_t>(m,
								m->list.u64,
								pos, val);
				break;
			case 16:
				rv = cdada_list_get_u<cdada_u128_t>(m,
							m->list.u128,
							pos, val);
				break;
			case 32:
				rv = cdada_list_get_u<cdada_u256_t>(m,
							m->list.u256,
							pos, val);
				break;
			case 64:
				rv = cdada_list_get_u<cdada_u512_t>(m,
							m->list.u512,
							pos, val);
				break;
			case 128:
				rv = cdada_list_get_u<cdada_u1024_t>(m,
							m->list.u1024,
							pos, val);
				break;
			case 256:
				rv = cdada_list_get_u<cdada_u2048_t>(m,
							m->list.u2048,
							pos, val);
				break;
			default:
				CDADA_ASSERT(m->ops);
				rv = (*m->ops->get)(m, pos, val);
				break;
		}
	}catch(bad_alloc& e){
		return CDADA_E_MEM;
	}catch(...){
		CDADA_ASSERT(0);
		return CDADA_E_UNKNOWN;
	}

	return rv;
}

static int __cdada_list_first_last(cdada_list_t* list, bool first, void* key){

	int rv;
	__cdada_list_int_t* m = (__cdada_list_int_t*)list;

	if(unlikely(!m || m->magic_num != CDADA_MAGIC || !key))
		return false;

	try{
		int c = m->ops? 0 : m->val_len;
		switch(c){
			case 1:
				rv = cdada_list_first_last_u<uint8_t>(m,
								m->list.u8,
								first, key);
				break;
			case 2:
				rv = cdada_list_first_last_u<uint16_t>(m,
								m->list.u16,
								first, key);
				break;
			case 4:
				rv = cdada_list_first_last_u<uint32_t>(m,
								m->list.u32,
								first, key);
				break;
			case 8:
				rv = cdada_list_first_last_u<uint64_t>(m,
								m->list.u64,
								first, key);
				break;
			case 16:
				rv = cdada_list_first_last_u<cdada_u128_t>(m,
								m->list.u128,
								first, key);
				break;
			case 32:
				rv = cdada_list_first_last_u<cdada_u256_t>(m,
								m->list.u256,
								first, key);
				break;
			case 64:
				rv = cdada_list_first_last_u<cdada_u512_t>(m,
								m->list.u512,
								first, key);
				break;
			case 128:
				rv = cdada_list_first_last_u<cdada_u1024_t>(m,
								m->list.u1024,
								first, key);
				break;
			case 256:
				rv = cdada_list_first_last_u<cdada_u2048_t>(m,
								m->list.u2048,
								first, key);
				break;
			case 0:
				rv = (*m->ops->first_last)(m, first, key);
				break;
			default:
				CDADA_ASSERT(0);
				rv = CDADA_E_UNKNOWN;
				break;
		}
	}catch(...){
		CDADA_ASSERT(0);
		return false;
	}

	return rv;
}

int cdada_list_first(cdada_list_t* list, void* key){
	return __cdada_list_first_last(list, true, key);
}

int cdada_list_last(cdada_list_t* list, void* key){
	return __cdada_list_first_last(list, false, key);
}

int cdada_list_erase(cdada_list_t* list, const uint32_t pos){

	int rv;
	__cdada_list_int_t* m = (__cdada_list_int_t*)list;

	CDADA_CHECK_MAGIC(m);

	try{
		switch(m->val_len){
			case 1:
				rv = cdada_list_erase_u<uint8_t>(m, m->list.u8,
									pos);
				break;
			case 2:
				rv = cdada_list_erase_u<uint16_t>(m,
								m->list.u16,
								pos);
				break;
			case 4:
				rv = cdada_list_erase_u<uint32_t>(m,
								m->list.u32,
								pos);
				break;
			case 8:
				rv = cdada_list_erase_u<uint64_t>(m,
								m->list.u64,
								pos);
				break;
			case 16:
				rv = cdada_list_erase_u<cdada_u128_t>(m,
								m->list.u128,
								pos);
				break;
			case 32:
				rv = cdada_list_erase_u<cdada_u256_t>(m,
								m->list.u256,
								pos);
				break;
			case 64:
				rv = cdada_list_erase_u<cdada_u512_t>(m,
								m->list.u512,
								pos);
				break;
			case 128:
				rv = cdada_list_erase_u<cdada_u1024_t>(m,
								m->list.u1024,
								pos);
				break;
			case 256:
				rv = cdada_list_erase_u<cdada_u2048_t>(m,
								m->list.u2048,
								pos);
				break;
			default:
				CDADA_ASSERT(m->ops);
				rv = (*m->ops->erase)(m, pos);
				break;
		}
	}catch(bad_alloc& e){
		return CDADA_E_MEM;
	}catch(...){
		CDADA_ASSERT(0);
		return CDADA_E_UNKNOWN;
	}

	return rv;
}

int cdada_list_remove(cdada_list_t* list, const void* val){

	int rv;
	__cdada_list_int_t* m = (__cdada_list_int_t*)list;

	CDADA_CHECK_MAGIC(m);

	if(unlikely(!val))
		return CDADA_E_INVALID;

	//NOTE: we don't want std::list remove "replace semantics", so we return
	//E_EXISTS if val is present in the list
	try{
		switch(m->val_len){
			case 1:
				rv = cdada_list_remove_u<uint8_t>(m, m->list.u8,
								val);
				break;
			case 2:
				rv = cdada_list_remove_u<uint16_t>(m,
								m->list.u16,
								val);
				break;
			case 4:
				rv = cdada_list_remove_u<uint32_t>(m,
								m->list.u32,
								val);
				break;
			case 8:
				rv = cdada_list_remove_u<uint64_t>(m,
								m->list.u64,
								val);
				break;
			case 16:
				rv = cdada_list_remove_u<cdada_u128_t>(m,
							m->list.u128,
							val);
				break;
			case 32:
				rv = cdada_list_remove_u<cdada_u256_t>(m,
							m->list.u256,
							val);
				break;
			case 64:
				rv = cdada_list_remove_u<cdada_u512_t>(m,
							m->list.u512,
							val);
				break;
			case 128:
				rv = cdada_list_remove_u<cdada_u1024_t>(m,
							m->list.u1024,
							val);
				break;
			case 256:
				rv = cdada_list_remove_u<cdada_u2048_t>(m,
							m->list.u2048,
							val);
				break;
			default:
				CDADA_ASSERT(m->ops);
				rv = (*m->ops->remove)(m, val);
				break;
		}
	}catch(bad_alloc& e){
		return CDADA_E_MEM;
	}catch(...){
		CDADA_ASSERT(0);
		return CDADA_E_UNKNOWN;
	}

	return rv;
}

static int cdada_list_push_(cdada_list_t* list, const void* val, bool front){

	int rv;
	__cdada_list_int_t* m = (__cdada_list_int_t*)list;

	CDADA_CHECK_MAGIC(m);

	if(unlikely(!val))
		return CDADA_E_INVALID;

	try{
		switch(m->val_len){
			case 1:
				rv = cdada_list_push_u<uint8_t>(m, m->list.u8,
								val, front);
				break;
			case 2:
				rv = cdada_list_push_u<uint16_t>(m, m->list.u16,
								val, front);
				break;
			case 4:
				rv = cdada_list_push_u<uint32_t>(m, m->list.u32,
								val, front);
				break;
			case 8:
				rv = cdada_list_push_u<uint64_t>(m,m->list.u64,
							val, front);
				break;
			case 16:
				rv = cdada_list_push_u<cdada_u128_t>(m,
								m->list.u128,
								val, front);
				break;
			case 32:
				rv = cdada_list_push_u<cdada_u256_t>(m,
								m->list.u256,
								val, front);
				break;
			case 64:
				rv = cdada_list_push_u<cdada_u512_t>(m,
								m->list.u512,
								val, front);
				break;
			case 128:
				rv = cdada_list_push_u<cdada_u1024_t>(m,
								m->list.u1024,
								val, front);
				break;
			case 256:
				rv = cdada_list_push_u<cdada_u2048_t>(m,
								m->list.u2048,
								val, front);
				break;
			default:
				CDADA_ASSERT(m->ops);
				rv = (*m->ops->push)(m, val, front);
				break;
		}
	}catch(bad_alloc& e){
		return CDADA_E_MEM;
	}catch(...){
		CDADA_ASSERT(0);
		return CDADA_E_UNKNOWN;
	}

	return rv;
}

int cdada_list_push_front(cdada_list_t* list, const void* val){
	return cdada_list_push_(list, val, true);
}

int cdada_list_push_back(cdada_list_t* list, const void* val){
	return cdada_list_push_(list, val, false);
}

static int cdada_list_pop_(cdada_list_t* list, bool front){

	int rv;
	__cdada_list_int_t* m = (__cdada_list_int_t*)list;

	CDADA_CHECK_MAGIC(m);

	try{
		switch(m->val_len){
			case 1:
				rv = cdada_list_pop_u<uint8_t>(m, m->list.u8,
								front);
				break;
			case 2:
				rv = cdada_list_pop_u<uint16_t>(m, m->list.u16,
								front);
				break;
			case 4:
				rv = cdada_list_pop_u<uint32_t>(m, m->list.u32,
								front);
				break;
			case 8:
				rv = cdada_list_pop_u<uint64_t>(m,m->list.u64,
							front);
				break;
			case 16:
				rv = cdada_list_pop_u<cdada_u128_t>(m,
								m->list.u128,
								front);
				break;
			case 32:
				rv = cdada_list_pop_u<cdada_u256_t>(m,
								m->list.u256,
								front);
				break;
			case 64:
				rv = cdada_list_pop_u<cdada_u512_t>(m,
								m->list.u512,
								front);
				break;
			case 128:
				rv = cdada_list_pop_u<cdada_u1024_t>(m,
								m->list.u1024,
								front);
				break;
			case 256:
				rv = cdada_list_pop_u<cdada_u2048_t>(m,
								m->list.u2048,
								front);
				break;
			default:
				CDADA_ASSERT(m->ops);
				rv = (*m->ops->pop)(m, front);
				break;
		}
	}catch(bad_alloc& e){
		return CDADA_E_MEM;
	}catch(...){
		CDADA_ASSERT(0);
		return CDADA_E_UNKNOWN;
	}

	return rv;
}

int cdada_list_pop_front(cdada_list_t* list){
	return cdada_list_pop_(list, true);
}

int cdada_list_pop_back(cdada_list_t* list){
	return cdada_list_pop_(list, false);
}

int cdada_list_sort(cdada_list_t* list){

	__cdada_list_int_t* m = (__cdada_list_int_t*)list;

	if(unlikely(!m || m->magic_num != CDADA_MAGIC))
		return CDADA_E_INVALID;

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
				CDADA_ASSERT(m->ops);
				(*m->ops->sort)(m);
				break;
		}
	}catch(...){
		CDADA_ASSERT(0);
		return CDADA_E_UNKNOWN;
	}

	return CDADA_SUCCESS;
}

int cdada_list_reverse(cdada_list_t* list){

	__cdada_list_int_t* m = (__cdada_list_int_t*)list;

	if(unlikely(!m || m->magic_num != CDADA_MAGIC))
		return CDADA_E_INVALID;

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
				CDADA_ASSERT(m->ops);
				(*m->ops->reverse)(m);
				break;
		}
	}catch(...){
		CDADA_ASSERT(0);
		return CDADA_E_UNKNOWN;
	}

	return CDADA_SUCCESS;
}

int cdada_list_unique(cdada_list_t* list){

	__cdada_list_int_t* m = (__cdada_list_int_t*)list;

	if(unlikely(!m || m->magic_num != CDADA_MAGIC))
		return CDADA_E_INVALID;

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
				CDADA_ASSERT(m->ops);
				(*m->ops->unique)(m);
				break;
		}
	}catch(...){
		CDADA_ASSERT(0);
		return CDADA_E_UNKNOWN;
	}

	return CDADA_SUCCESS;
}

int cdada_list_traverse(const cdada_list_t* list, cdada_list_it f,
								void* opaque){

	__cdada_list_int_t* m = (__cdada_list_int_t*)list;

	CDADA_CHECK_MAGIC(m);

	if(unlikely(!f))
		return CDADA_E_INVALID;

	try{
		switch(m->val_len){
			case 1:
				cdada_list_traverse_u<uint8_t>(m, m->list.u8,
								f, opaque);
				break;
			case 2:
				cdada_list_traverse_u<uint16_t>(m, m->list.u16,
								f, opaque);
				break;
			case 4:
				cdada_list_traverse_u<uint32_t>(m, m->list.u32,
								f, opaque);
				break;
			case 8:
				cdada_list_traverse_u<uint64_t>(m, m->list.u64,
								f, opaque);
				break;
			case 16:
				cdada_list_traverse_u<cdada_u128_t>(m,
								m->list.u128, f,
								opaque);
				break;
			case 32:
				cdada_list_traverse_u<cdada_u256_t>(m,
								m->list.u256, f,
								opaque);
				break;
			case 64:
				cdada_list_traverse_u<cdada_u512_t>(m,
								m->list.u512, f,
								opaque);
				break;
			case 128:
				cdada_list_traverse_u<cdada_u1024_t>(m,
								m->list.u1024,
								f, opaque);
				break;
			case 256:
				cdada_list_traverse_u<cdada_u2048_t>(m,
								m->list.u2048,
								f, opaque);
				break;
			default:
				CDADA_ASSERT(m->ops);
				(*m->ops->traverse)(m, f, opaque);
				break;
		}
	}catch(...){
		CDADA_ASSERT(0);
		return CDADA_E_UNKNOWN;
	}

	return CDADA_SUCCESS;
}

int cdada_list_rtraverse(const cdada_list_t* list, cdada_list_it f,
								void* opaque){

	__cdada_list_int_t* m = (__cdada_list_int_t*)list;

	CDADA_CHECK_MAGIC(m);

	if(unlikely(!f))
		return CDADA_E_INVALID;

	try{
		switch(m->val_len){
			case 1:
				cdada_list_rtraverse_u<uint8_t>(m, m->list.u8,
								f, opaque);
				break;
			case 2:
				cdada_list_rtraverse_u<uint16_t>(m, m->list.u16,
								f, opaque);
				break;
			case 4:
				cdada_list_rtraverse_u<uint32_t>(m, m->list.u32,
								f, opaque);
				break;
			case 8:
				cdada_list_rtraverse_u<uint64_t>(m, m->list.u64,
								f, opaque);
				break;
			case 16:
				cdada_list_rtraverse_u<cdada_u128_t>(m,
								m->list.u128, f,
								opaque);
				break;
			case 32:
				cdada_list_rtraverse_u<cdada_u256_t>(m,
								m->list.u256, f,
								opaque);
				break;
			case 64:
				cdada_list_rtraverse_u<cdada_u512_t>(m,
								m->list.u512, f,
								opaque);
				break;
			case 128:
				cdada_list_rtraverse_u<cdada_u1024_t>(m,
								m->list.u1024,
								f, opaque);
				break;
			case 256:
				cdada_list_rtraverse_u<cdada_u2048_t>(m,
								m->list.u2048,
								f, opaque);
				break;
			default:
				CDADA_ASSERT(m->ops);
				(*m->ops->rtraverse)(m, f, opaque);
				break;
		}
	}catch(...){
		CDADA_ASSERT(0);
		return CDADA_E_UNKNOWN;
	}

	return CDADA_SUCCESS;
}
