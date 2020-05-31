#include "cdada/set.h"
#include "cdada/__common_internal.h"
#include "cdada/__set_internal.h"

#include <stdlib.h>
#include <string.h>

using namespace std;

cdada_set_t* __cdada_set_create(const uint16_t key_size,
						__cdada_set_ops_t* ops){

	__cdada_set_int_t* m = NULL;

	if(unlikely(key_size == 0))
		return m;

	m = (__cdada_set_int_t*)malloc(sizeof(__cdada_set_int_t));
	memset(m, 0, sizeof(__cdada_set_int_t));
	m->magic_num = CDADA_MAGIC;
	m->user_key_len = key_size;

	try{
		//Custom type
		if(ops){
			m->key_len = m->user_key_len = key_size;
			m->ops = ops;
			(*m->ops->create)(m);
			return m;
		}

		//Regular
		if(key_size == 1){
			m->set.u8 = new set<uint8_t>();
			m->key_len = 1;
		}else if(key_size == 2){
			m->set.u16 = new set<uint16_t>();
			m->key_len = 2;
		}else if(key_size > 2 && key_size <= 4){
			m->set.u32 = new set<uint32_t>();
			m->key_len = 4;
		}else if(key_size > 4 && key_size <= 8){
			m->set.u64 = new set<uint64_t>();
			m->key_len = 8;
		}else if(key_size > 8 && key_size <= 16){
			m->set.u128 = new set<cdada_u128_t>();
			m->key_len = 16;
		}else if(key_size > 16 && key_size <= 32){
			m->set.u256 = new set<cdada_u256_t>();
			m->key_len = 32;
		}else if(key_size > 32 && key_size <= 64){
			m->set.u512 = new set<cdada_u512_t>();
			m->key_len = 64;
		}else if(key_size > 64 && key_size <= 128){
			m->set.u1024 = new set<cdada_u1024_t>();
			m->key_len = 128;
		}else if(key_size > 128 && key_size <= 256){
			m->set.u2048 = new set<cdada_u2048_t>();
			m->key_len = 256;
		}else{
			//Unsupported; use custom type
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
* Destroy a set structure
*/
int cdada_set_destroy(cdada_set_t* set){

	__cdada_set_int_t* m = (__cdada_set_int_t*)set;

	CDADA_CHECK_MAGIC(m);

	try{
		if(m->ops){
			(*m->ops->destroy)(m);
		}else{
			switch(m->key_len){
				case 1:
					delete m->set.u8;
					break;
				case 2:
					delete m->set.u16;
					break;
				case 4:
					delete m->set.u32;
					break;
				case 8:
					delete m->set.u64;
					break;
				case 16:
					delete m->set.u128;
					break;
				case 32:
					delete m->set.u256;
					break;
				case 64:
					delete m->set.u512;
					break;
				case 128:
					delete m->set.u1024;
					break;
				case 256:
					delete m->set.u2048;
					break;
				default:
					CDADA_ASSERT(0);
					break;
			}
		}
	}catch(...){
		CDADA_ASSERT(0);
		return CDADA_E_UNKNOWN;
	}

	m->magic_num = 0x0;
	free(m);

	return CDADA_SUCCESS;
}

int cdada_set_clear(cdada_set_t* set){

	__cdada_set_int_t* m = (__cdada_set_int_t*)set;

	CDADA_CHECK_MAGIC(m);

	try{
		int c = m->ops? 0 : m->key_len;
		switch(c){
			case 1:
				m->set.u8->clear();
				break;
			case 2:
				m->set.u16->clear();
				break;
			case 4:
				m->set.u32->clear();
				break;
			case 8:
				m->set.u64->clear();
				break;
			case 16:
				m->set.u128->clear();
				break;
			case 32:
				m->set.u256->clear();
				break;
			case 64:
				m->set.u512->clear();
				break;
			case 128:
				m->set.u1024->clear();
				break;
			case 256:
				m->set.u2048->clear();
				break;
			case 0:
				(*m->ops->clear)(m);
				break;
			default:
				CDADA_ASSERT(0);
				return CDADA_E_UNKNOWN;
		}
	}catch(bad_alloc& e){
		return CDADA_E_MEM;
	}catch(...){
		CDADA_ASSERT(0);
		return CDADA_E_UNKNOWN;
	}

	return CDADA_SUCCESS;
}

bool cdada_set_empty(const cdada_set_t* set){

	__cdada_set_int_t* m = (__cdada_set_int_t*)set;

	if(unlikely(!m || m->magic_num != CDADA_MAGIC))
		return false;

	try{
		int c = m->ops? 0 : m->key_len;
		switch(c){
			case 1:
				return m->set.u8->empty();
			case 2:
				return m->set.u16->empty();
			case 4:
				return m->set.u32->empty();
			case 8:
				return m->set.u64->empty();
			case 16:
				return m->set.u128->empty();
			case 32:
				return m->set.u256->empty();
			case 64:
				return m->set.u512->empty();
			case 128:
				return m->set.u1024->empty();
			case 256:
				return m->set.u2048->empty();
			case 0:
				CDADA_ASSERT(m->ops);
				return (*m->ops->empty)(m);
			default:
				CDADA_ASSERT(0);
				return false;
		}
	}catch(...){
		CDADA_ASSERT(0);
		return false;
	}

	return false;
}

uint32_t cdada_set_size(const cdada_set_t* set){

	__cdada_set_int_t* m = (__cdada_set_int_t*)set;

	if(unlikely(!m || m->magic_num != CDADA_MAGIC))
		return 0;

	try{
		int c = m->ops? 0 : m->key_len;
		switch(c){
			case 1:
				return m->set.u8->size();
			case 2:
				return m->set.u16->size();
			case 4:
				return m->set.u32->size();
			case 8:
				return m->set.u64->size();
			case 16:
				return m->set.u128->size();
			case 32:
				return m->set.u256->size();
			case 64:
				return m->set.u512->size();
			case 128:
				return m->set.u1024->size();
			case 256:
				return m->set.u2048->size();
			case 0:
				return (*m->ops->size)(m);
			default:
				CDADA_ASSERT(0);
				break;
		}
	}catch(...){
		CDADA_ASSERT(0);
		return 0;
	}

	return 0;
}

int cdada_set_insert(cdada_set_t* set, const void* key){

	__cdada_set_int_t* m = (__cdada_set_int_t*)set;

	CDADA_CHECK_MAGIC(m);

	if(unlikely(!key))
		return CDADA_E_INVALID;

	//NOTE: we don't want std::set insert "replace semantics", so we return
	//E_EXISTS if key is present in the set
	try{
		int c = m->ops? 0 : m->key_len;
		switch(c){
			case 1:
				return cdada_set_insert_u<uint8_t>(m,
								m->set.u8,
								key);
			case 2:
				return cdada_set_insert_u<uint16_t>(m,
								m->set.u16,
								key);
			case 4:
				return cdada_set_insert_u<uint32_t>(m,
								m->set.u32,
								key);
			case 8:
				return cdada_set_insert_u<uint64_t>(m,
								m->set.u64,
								key);
			case 16:
				return cdada_set_insert_u<cdada_u128_t>(m,
								m->set.u128,
								key);
			case 32:
				return cdada_set_insert_u<cdada_u256_t>(m,
								m->set.u256,
								key);
			case 64:
				return cdada_set_insert_u<cdada_u512_t>(m,
								m->set.u512,
								key);
			case 128:
				return cdada_set_insert_u<cdada_u1024_t>(m,
								m->set.u1024,
								key);
			case 256:
				return cdada_set_insert_u<cdada_u2048_t>(m,
								m->set.u2048,
								key);
			case 0:
				return (*m->ops->insert)(m, key);
			default:
				CDADA_ASSERT(0);
				return CDADA_E_UNKNOWN;
		}
	}catch(bad_alloc& e){
		return CDADA_E_MEM;
	}catch(...){}

	CDADA_ASSERT(0);
	return CDADA_E_UNKNOWN;
}

int cdada_set_erase(cdada_set_t* set, const void* key){

	__cdada_set_int_t* m = (__cdada_set_int_t*)set;

	CDADA_CHECK_MAGIC(m);

	if(unlikely(!key))
		return CDADA_E_INVALID;

	try{
		int c = m->ops? 0 : m->key_len;
		switch(c){
			case 1:
				return cdada_set_erase_u<uint8_t>(m, m->set.u8,
									key);
			case 2:
				return cdada_set_erase_u<uint16_t>(m,
								m->set.u16,
								key);
			case 4:
				return cdada_set_erase_u<uint32_t>(m,
								m->set.u32,
								key);
			case 8:
				return cdada_set_erase_u<uint64_t>(m,
								m->set.u64,
								key);
			case 16:
				return cdada_set_erase_u<cdada_u128_t>(m,
								m->set.u128,
								key);
				break;
			case 32:
				return cdada_set_erase_u<cdada_u256_t>(m,
								m->set.u256,
								key);
			case 64:
				return cdada_set_erase_u<cdada_u512_t>(m,
								m->set.u512,
								key);
			case 128:
				return cdada_set_erase_u<cdada_u1024_t>(m,
								m->set.u1024,
								key);
			case 256:
				return cdada_set_erase_u<cdada_u2048_t>(m,
								m->set.u2048,
								key);
			case 0:
				return (*m->ops->erase)(m, key);
			default:
				CDADA_ASSERT(0);
				return CDADA_E_UNKNOWN;
		}
	}catch(bad_alloc& e){
		return CDADA_E_MEM;
	}catch(...){}

	CDADA_ASSERT(0);
	return CDADA_E_UNKNOWN;
}

bool cdada_set_find(const cdada_set_t* set, const void* key){

	__cdada_set_int_t* m = (__cdada_set_int_t*)set;

	if(unlikely(!m || m->magic_num != CDADA_MAGIC || !key))
		return false;

	try{
		int c = m->ops? 0 : m->key_len;
		switch(c){
			case 1:
				return cdada_set_find_u<uint8_t>(m, m->set.u8,
									key);
			case 2:
				return cdada_set_find_u<uint16_t>(m, m->set.u16,
									key);
			case 4:
				return cdada_set_find_u<uint32_t>(m, m->set.u32,
									key);
			case 8:
				return cdada_set_find_u<uint64_t>(m, m->set.u64,
									key);
			case 16:
				return cdada_set_find_u<cdada_u128_t>(m,
								m->set.u128,
								key);
			case 32:
				return cdada_set_find_u<cdada_u256_t>(m,
								m->set.u256,
								key);
			case 64:
				return cdada_set_find_u<cdada_u512_t>(m,
								m->set.u512,
								key);
			case 128:
				return cdada_set_find_u<cdada_u1024_t>(m,
								m->set.u1024,
								key);
			case 256:
				return cdada_set_find_u<cdada_u2048_t>(m,
								m->set.u2048,
								key);
			case 0:
				return (*m->ops->find)(m, key);
			default:
				CDADA_ASSERT(0);
				return CDADA_E_UNKNOWN;
		}
	}catch(...){}

	CDADA_ASSERT(0);
	return false;
}

static int __cdada_set_first_last(const cdada_set_t* set, bool first,
								void* key){

	__cdada_set_int_t* m = (__cdada_set_int_t*)set;

	if(unlikely(!m || m->magic_num != CDADA_MAGIC || !key))
		return false;

	try{
		int c = m->ops? 0 : m->key_len;
		switch(c){
			case 1:
				return cdada_set_first_last_u<uint8_t>(m,
								m->set.u8,
								first, key);
			case 2:
				return cdada_set_first_last_u<uint16_t>(m,
								m->set.u16,
								first, key);
			case 4:
				return cdada_set_first_last_u<uint32_t>(m,
								m->set.u32,
								first, key);
			case 8:
				return cdada_set_first_last_u<uint64_t>(m,
								m->set.u64,
								first, key);
			case 16:
				return cdada_set_first_last_u<cdada_u128_t>(m,
								m->set.u128,
								first, key);
			case 32:
				return cdada_set_first_last_u<cdada_u256_t>(m,
								m->set.u256,
								first, key);
			case 64:
				return cdada_set_first_last_u<cdada_u512_t>(m,
								m->set.u512,
								first, key);
			case 128:
				return cdada_set_first_last_u<cdada_u1024_t>(m,
								m->set.u1024,
								first, key);
			case 256:
				return cdada_set_first_last_u<cdada_u2048_t>(m,
								m->set.u2048,
								first, key);
			case 0:
				return (*m->ops->first_last)(m, first, key);
			default:
				CDADA_ASSERT(0);
				return CDADA_E_UNKNOWN;
		}
	}catch(...){}

	CDADA_ASSERT(0);
	return false;
}

int cdada_set_first(const cdada_set_t* set, void* key){
	return __cdada_set_first_last(set, true, key);
}

int cdada_set_last(const cdada_set_t* set, void* key){
	return __cdada_set_first_last(set, false, key);
}

int cdada_set_traverse(const cdada_set_t* set, cdada_set_it f, void* opaque){

	__cdada_set_int_t* m = (__cdada_set_int_t*)set;

	CDADA_CHECK_MAGIC(m);

	if(unlikely(!f))
		return CDADA_E_INVALID;

	try{
		int c = m->ops? 0 : m->key_len;
		switch(c){
			case 1:
				cdada_set_traverse_u<uint8_t>(m, m->set.u8, f,
									opaque);
				break;
			case 2:
				cdada_set_traverse_u<uint16_t>(m, m->set.u16, f,
									opaque);
				break;
			case 4:
				cdada_set_traverse_u<uint32_t>(m, m->set.u32, f,
									opaque);
				break;
			case 8:
				cdada_set_traverse_u<uint64_t>(m, m->set.u64, f,
									opaque);
				break;
			case 16:
				cdada_set_traverse_u<cdada_u128_t>(m,
								m->set.u128, f,
								opaque);
				break;
			case 32:
				cdada_set_traverse_u<cdada_u256_t>(m,
								m->set.u256, f,
								opaque);
				break;
			case 64:
				cdada_set_traverse_u<cdada_u512_t>(m,
								m->set.u512, f,
								opaque);
				break;
			case 128:
				cdada_set_traverse_u<cdada_u1024_t>(m,
								m->set.u1024, f,
								opaque);
				break;
			case 256:
				cdada_set_traverse_u<cdada_u2048_t>(m,
								m->set.u2048, f,
								opaque);
				break;
			case 0:
				CDADA_ASSERT(m->ops);
				(*m->ops->traverse)(m, f, opaque);
				break;
			default:
				CDADA_ASSERT(0);
				return CDADA_E_UNKNOWN;
		}
	}catch(...){
		CDADA_ASSERT(0);
		return CDADA_E_UNKNOWN;
	}

	return CDADA_SUCCESS;
}

int cdada_set_rtraverse(const cdada_set_t* set, cdada_set_it f, void* opaque){

	__cdada_set_int_t* m = (__cdada_set_int_t*)set;

	CDADA_CHECK_MAGIC(m);

	if(unlikely(!f))
		return CDADA_E_INVALID;

	try{
		int c = m->ops? 0 : m->key_len;
		switch(c){
			case 1:
				cdada_set_rtraverse_u<uint8_t>(m, m->set.u8, f,
									opaque);
				break;
			case 2:
				cdada_set_rtraverse_u<uint16_t>(m, m->set.u16,
									f,
									opaque);
				break;
			case 4:
				cdada_set_rtraverse_u<uint32_t>(m, m->set.u32,
									f,
									opaque);
				break;
			case 8:
				cdada_set_rtraverse_u<uint64_t>(m, m->set.u64,
									f,
									opaque);
				break;
			case 16:
				cdada_set_rtraverse_u<cdada_u128_t>(m,
								m->set.u128, f,
								opaque);
				break;
			case 32:
				cdada_set_rtraverse_u<cdada_u256_t>(m,
								m->set.u256, f,
								opaque);
				break;
			case 64:
				cdada_set_rtraverse_u<cdada_u512_t>(m,
								m->set.u512, f,
								opaque);
				break;
			case 128:
				cdada_set_rtraverse_u<cdada_u1024_t>(m,
								m->set.u1024, f,
								opaque);
				break;
			case 256:
				cdada_set_rtraverse_u<cdada_u2048_t>(m,
								m->set.u2048, f,
								opaque);
				break;
			case 0:
				(*m->ops->rtraverse)(m, f, opaque);
				break;
			default:
				CDADA_ASSERT(0);
				return CDADA_E_UNKNOWN;
		}
	}catch(...){
		CDADA_ASSERT(0);
		return CDADA_E_UNKNOWN;
	}

	return CDADA_SUCCESS;
}

int cdada_set_dump(cdada_set_t* set, uint32_t size, char* buffer,
							uint32_t* size_used){

	__cdada_set_int_t* m = (__cdada_set_int_t*)set;
	CDADA_CHECK_MAGIC(m);

	if(!size_used || (buffer&&size ==0))
		return CDADA_E_INVALID;

	try{
		std::stringstream ss;
		ss << "{";

		int c = m->ops? 0 : m->key_len;
		switch(c){
			case 1:
				cdada_set_dump_u<uint8_t>(m, m->set.u8, ss);
				break;
			case 2:
				cdada_set_dump_u<uint16_t>(m, m->set.u16,
									ss);
				break;
			case 4:
				cdada_set_dump_u<uint32_t>(m, m->set.u32,
									ss);
				break;
			case 8:
				cdada_set_dump_u<uint64_t>(m, m->set.u64,
									ss);
				break;
			case 16:
				cdada_set_dump_u<cdada_u128_t>(m,
								m->set.u128,
								ss);
				break;
			case 32:
				cdada_set_dump_u<cdada_u256_t>(m,
								m->set.u256,
								ss);
				break;
			case 64:
				cdada_set_dump_u<cdada_u512_t>(m,
								m->set.u512,
								ss);
				break;
			case 128:
				cdada_set_dump_u<cdada_u1024_t>(m,
								m->set.u1024,
								ss);
				break;
			case 256:
				cdada_set_dump_u<cdada_u2048_t>(m,
								m->set.u2048,
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

int cdada_set_print(cdada_set_t* set, FILE *stream){

	__cdada_set_int_t* m = (__cdada_set_int_t*)set;
	CDADA_CHECK_MAGIC(m);

	try{
		std::stringstream ss;
		ss << "{";

		int c = m->ops? 0 : m->key_len;
		switch(c){
			case 1:
				cdada_set_dump_u<uint8_t>(m, m->set.u8, ss);
				break;
			case 2:
				cdada_set_dump_u<uint16_t>(m, m->set.u16,
									ss);
				break;
			case 4:
				cdada_set_dump_u<uint32_t>(m, m->set.u32,
									ss);
				break;
			case 8:
				cdada_set_dump_u<uint64_t>(m, m->set.u64,
									ss);
				break;
			case 16:
				cdada_set_dump_u<cdada_u128_t>(m,
								m->set.u128,
								ss);
				break;
			case 32:
				cdada_set_dump_u<cdada_u256_t>(m,
								m->set.u256,
								ss);
				break;
			case 64:
				cdada_set_dump_u<cdada_u512_t>(m,
								m->set.u512,
								ss);
				break;
			case 128:
				cdada_set_dump_u<cdada_u1024_t>(m,
								m->set.u1024,
								ss);
				break;
			case 256:
				cdada_set_dump_u<cdada_u2048_t>(m,
								m->set.u2048,
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
