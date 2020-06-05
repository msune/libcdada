#include "cdada/map.h"
#include "cdada/__common_internal.h"
#include "cdada/__map_internal.h"

#include <stdlib.h>
#include <string.h>

using namespace std;

cdada_map_t* __cdada_map_create(const uint16_t key_size,
						__cdada_map_ops_t* ops){

	__cdada_map_int_t* m = NULL;

	if(unlikely(key_size == 0))
		return m;

	m = (__cdada_map_int_t*)malloc(sizeof(__cdada_map_int_t));
	memset(m, 0, sizeof(__cdada_map_int_t));
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

		if(key_size == 1){
			m->map.u8 = new map<uint8_t, void*>();
			m->key_len = 1;
		}else if(key_size == 2){
			m->map.u16 = new map<uint16_t, void*>();
			m->key_len = 2;
		}else if(key_size > 2 && key_size <= 4){
			m->map.u32 = new map<uint32_t, void*>();
			m->key_len = 4;
		}else if(key_size > 4 && key_size <= 8){
			m->map.u64 = new map<uint64_t, void*>();
			m->key_len = 8;
		}else if(key_size > 8 && key_size <= 16){
			m->map.u128 = new map<cdada_u128_t, void*>();
			m->key_len = 16;
		}else if(key_size > 16 && key_size <= 32){
			m->map.u256 = new map<cdada_u256_t, void*>();
			m->key_len = 32;
		}else if(key_size > 32 && key_size <= 64){
			m->map.u512 = new map<cdada_u512_t, void*>();
			m->key_len = 64;
		}else if(key_size > 64 && key_size <= 128){
			m->map.u1024 = new map<cdada_u1024_t, void*>();
			m->key_len = 128;
		}else if(key_size > 128 && key_size <= 256){
			m->map.u2048 = new map<cdada_u2048_t, void*>();
			m->key_len = 256;
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
* Destroy a map structure
*/
int cdada_map_destroy(cdada_map_t* map){

	__cdada_map_int_t* m = (__cdada_map_int_t*)map;

	CDADA_CHECK_MAGIC(m);

	try{
		int c = m->ops? 0 : m->key_len;
		switch(c){
			case 1:
				delete m->map.u8;
				break;
			case 2:
				delete m->map.u16;
				break;
			case 4:
				delete m->map.u32;
				break;
			case 8:
				delete m->map.u64;
				break;
			case 16:
				delete m->map.u128;
				break;
			case 32:
				delete m->map.u256;
				break;
			case 64:
				delete m->map.u512;
				break;
			case 128:
				delete m->map.u1024;
				break;
			case 256:
				delete m->map.u2048;
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

int cdada_map_clear(cdada_map_t* map){

	__cdada_map_int_t* m = (__cdada_map_int_t*)map;

	CDADA_CHECK_MAGIC(m);

	try{
		int c = m->ops? 0 : m->key_len;
		switch(c){
			case 1:
				m->map.u8->clear();
				break;
			case 2:
				m->map.u16->clear();
				break;
			case 4:
				m->map.u32->clear();
				break;
			case 8:
				m->map.u64->clear();
				break;
			case 16:
				m->map.u128->clear();
				break;
			case 32:
				m->map.u256->clear();
				break;
			case 64:
				m->map.u512->clear();
				break;
			case 128:
				m->map.u1024->clear();
				break;
			case 256:
				m->map.u2048->clear();
				break;
			case 0:
				CDADA_ASSERT(m->ops);
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

bool cdada_map_empty(const cdada_map_t* map){

	__cdada_map_int_t* m = (__cdada_map_int_t*)map;

	if(unlikely(!m || m->magic_num != CDADA_MAGIC))
		return false;

	try{
		int c = m->ops? 0 : m->key_len;
		switch(c){
			case 1:
				return m->map.u8->empty();
			case 2:
				return m->map.u16->empty();
			case 4:
				return m->map.u32->empty();
			case 8:
				return m->map.u64->empty();
			case 16:
				return m->map.u128->empty();
			case 32:
				return m->map.u256->empty();
			case 64:
				return m->map.u512->empty();
			case 128:
				return m->map.u1024->empty();
			case 256:
				return m->map.u2048->empty();
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

uint32_t cdada_map_size(const cdada_map_t* map){

	__cdada_map_int_t* m = (__cdada_map_int_t*)map;

	if(unlikely(!m || m->magic_num != CDADA_MAGIC))
		return 0;

	try{
		int c = m->ops? 0 : m->key_len;
		switch(c){
			case 1:
				return m->map.u8->size();
			case 2:
				return m->map.u16->size();
			case 4:
				return m->map.u32->size();
			case 8:
				return m->map.u64->size();
			case 16:
				return m->map.u128->size();
			case 32:
				return m->map.u256->size();
			case 64:
				return m->map.u512->size();
			case 128:
				return m->map.u1024->size();
			case 256:
				return m->map.u2048->size();
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

int cdada_map_insert(cdada_map_t* map, const void* key, void* val){

	__cdada_map_int_t* m = (__cdada_map_int_t*)map;

	CDADA_CHECK_MAGIC(m);

	if(unlikely(!key || !val))
		return CDADA_E_INVALID;

	//NOTE: we don't want std::map insert "replace semantics", so we return
	//E_EXISTS if key is present in the map
	try{
		int c = m->ops? 0 : m->key_len;
		switch(c){
			case 1:
				return cdada_map_insert_u<uint8_t>(m, m->map.u8,
									key,
									val);
			case 2:
				return cdada_map_insert_u<uint16_t>(m,
								m->map.u16,
								key,
								val);
			case 4:
				return cdada_map_insert_u<uint32_t>(m,
								m->map.u32,
								key,
								val);
			case 8:
				return cdada_map_insert_u<uint64_t>(m,
								m->map.u64,
								key,
								val);
			case 16:
				return cdada_map_insert_u<cdada_u128_t>(m,
								m->map.u128,
								key,
								val);
			case 32:
				return cdada_map_insert_u<cdada_u256_t>(m,
								m->map.u256,
								key,
								val);
			case 64:
				return cdada_map_insert_u<cdada_u512_t>(m,
								m->map.u512,
								key,
								val);
			case 128:
				return cdada_map_insert_u<cdada_u1024_t>(m,
								m->map.u1024,
								key,
								val);
			case 256:
				return cdada_map_insert_u<cdada_u2048_t>(m,
								m->map.u2048,
								key,
								val);
			case 0:
				CDADA_ASSERT(m->ops);
				return (*m->ops->insert)(m, key, val);
			default:
				break;
		}
	}catch(bad_alloc& e){
		return CDADA_E_MEM;
	}catch(...){}

	CDADA_ASSERT(0);
	return CDADA_E_UNKNOWN;
}

int cdada_map_erase(cdada_map_t* map, const void* key){

	__cdada_map_int_t* m = (__cdada_map_int_t*)map;

	CDADA_CHECK_MAGIC(m);

	if(unlikely(!key))
		return CDADA_E_INVALID;

	try{
		int c = m->ops? 0 : m->key_len;
		switch(c){
			case 1:
				return cdada_map_erase_u<uint8_t>(m, m->map.u8,
									key);
			case 2:
				return cdada_map_erase_u<uint16_t>(m,
								m->map.u16,
								key);
			case 4:
				return cdada_map_erase_u<uint32_t>(m,
								m->map.u32,
								key);
			case 8:
				return cdada_map_erase_u<uint64_t>(m,
								m->map.u64,
								key);
			case 16:
				return cdada_map_erase_u<cdada_u128_t>(m,
								m->map.u128,
								key);
			case 32:
				return cdada_map_erase_u<cdada_u256_t>(m,
								m->map.u256,
								key);
			case 64:
				return cdada_map_erase_u<cdada_u512_t>(m,
								m->map.u512,
								key);
			case 128:
				return cdada_map_erase_u<cdada_u1024_t>(m,
								m->map.u1024,
								key);
			case 256:
				return cdada_map_erase_u<cdada_u2048_t>(m,
								m->map.u2048,
								key);
			case 0:
				CDADA_ASSERT(m->ops);
				return (*m->ops->erase)(m, key);
			default:
				break;
		}
	}catch(bad_alloc& e){
		return CDADA_E_MEM;
	}catch(...){}

	CDADA_ASSERT(0);
	return CDADA_E_UNKNOWN;
}

int cdada_map_find(const cdada_map_t* map, const void* key, void** val){

	__cdada_map_int_t* m = (__cdada_map_int_t*)map;

	CDADA_CHECK_MAGIC(m);

	if(unlikely(!key || val == NULL))
		return CDADA_E_INVALID;

	try{
		int c = m->ops? 0 : m->key_len;
		switch(c){
			case 1:
				return cdada_map_find_u<uint8_t>(m, m->map.u8,
									key,
									val);
			case 2:
				return cdada_map_find_u<uint16_t>(m, m->map.u16,
									key,
									val);
			case 4:
				return cdada_map_find_u<uint32_t>(m, m->map.u32,
									key,
									val);
			case 8:
				return cdada_map_find_u<uint64_t>(m, m->map.u64,
									key,
									val);
			case 16:
				return cdada_map_find_u<cdada_u128_t>(m,
								m->map.u128,
								key,
								val);
			case 32:
				return cdada_map_find_u<cdada_u256_t>(m,
								m->map.u256,
								key,
								val);
			case 64:
				return cdada_map_find_u<cdada_u512_t>(m,
								m->map.u512,
								key,
								val);
			case 128:
				return cdada_map_find_u<cdada_u1024_t>(m,
								m->map.u1024,
								key,
								val);
			case 256:
				return cdada_map_find_u<cdada_u2048_t>(m,
								m->map.u2048,
								key,
								val);
				break;
			case 0:
				CDADA_ASSERT(m->ops);
				return (*m->ops->find)(m, key, val);
			default:
				break;
		}
	}catch(...){}

	CDADA_ASSERT(0);
	return CDADA_E_UNKNOWN;
}

static int __cdada_map_first_last(const cdada_map_t* map, bool first, void* key,
								void** val){

	__cdada_map_int_t* m = (__cdada_map_int_t*)map;

	CDADA_CHECK_MAGIC(m);

	if(unlikely(!key || val == NULL))
		return CDADA_E_INVALID;

	try{
		int c = m->ops? 0 : m->key_len;
		switch(c){
			case 1:
				return cdada_map_first_last_u<uint8_t>(m,
								m->map.u8,
								first,
								key,
								val);
			case 2:
				return cdada_map_first_last_u<uint16_t>(m,
								m->map.u16,
								first,
								key,
								val);
			case 4:
				return cdada_map_first_last_u<uint32_t>(m,
								m->map.u32,
								first,
								key,
								val);
			case 8:
				return cdada_map_first_last_u<uint64_t>(m,
								m->map.u64,
								first,
								key,
								val);
			case 16:
				return cdada_map_first_last_u<cdada_u128_t>(m,
								m->map.u128,
								first,
								key,
								val);
			case 32:
				return cdada_map_first_last_u<cdada_u256_t>(m,
								m->map.u256,
								first,
								key,
								val);
			case 64:
				return cdada_map_first_last_u<cdada_u512_t>(m,
								m->map.u512,
								first,
								key,
								val);
			case 128:
				return cdada_map_first_last_u<cdada_u1024_t>(m,
								m->map.u1024,
								first,
								key,
								val);
			case 256:
				return cdada_map_first_last_u<cdada_u2048_t>(m,
								m->map.u2048,
								first,
								key,
								val);
			case 0:
				CDADA_ASSERT(m->ops);
				return (*m->ops->first_last)(m, first, key,
								val);
			default:
				break;
		}
	}catch(...){}

	CDADA_ASSERT(0);
	return CDADA_E_UNKNOWN;
}

int cdada_map_first(const cdada_map_t* map, void* key, void** val){
	return __cdada_map_first_last(map, true, key, val);
}

int cdada_map_last(const cdada_map_t* map, void* key, void** val){
	return __cdada_map_first_last(map, false, key, val);
}

int cdada_map_traverse(const cdada_map_t* map, cdada_map_it f,
							void* opaque){

	__cdada_map_int_t* m = (__cdada_map_int_t*)map;

	CDADA_CHECK_MAGIC(m);

	if(unlikely(!f))
		return CDADA_E_INVALID;

	try{
		int c = m->ops? 0 : m->key_len;
		switch(c){
			case 1:
				cdada_map_traverse_u<uint8_t>(m, m->map.u8, f,
									opaque);
				break;
			case 2:
				cdada_map_traverse_u<uint16_t>(m, m->map.u16, f,
									opaque);
				break;
			case 4:
				cdada_map_traverse_u<uint32_t>(m, m->map.u32, f,
									opaque);
				break;
			case 8:
				cdada_map_traverse_u<uint64_t>(m, m->map.u64, f,
									opaque);
				break;
			case 16:
				cdada_map_traverse_u<cdada_u128_t>(m,
								m->map.u128, f,
								opaque);
				break;
			case 32:
				cdada_map_traverse_u<cdada_u256_t>(m,
								m->map.u256, f,
								opaque);
				break;
			case 64:
				cdada_map_traverse_u<cdada_u512_t>(m,
								m->map.u512, f,
								opaque);
				break;
			case 128:
				cdada_map_traverse_u<cdada_u1024_t>(m,
								m->map.u1024, f,
								opaque);
				break;
			case 256:
				cdada_map_traverse_u<cdada_u2048_t>(m,
								m->map.u2048, f,
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

int cdada_map_rtraverse(const cdada_map_t* map, cdada_map_it f,
							void* opaque){

	__cdada_map_int_t* m = (__cdada_map_int_t*)map;

	CDADA_CHECK_MAGIC(m);

	if(unlikely(!f))
		return CDADA_E_INVALID;

	try{
		int c = m->ops? 0 : m->key_len;
		switch(c){
			case 1:
				cdada_map_rtraverse_u<uint8_t>(m, m->map.u8, f,
									opaque);
				break;
			case 2:
				cdada_map_rtraverse_u<uint16_t>(m, m->map.u16,
									f,
									opaque);
				break;
			case 4:
				cdada_map_rtraverse_u<uint32_t>(m, m->map.u32,
									f,
									opaque);
				break;
			case 8:
				cdada_map_rtraverse_u<uint64_t>(m, m->map.u64,
									f,
									opaque);
				break;
			case 16:
				cdada_map_rtraverse_u<cdada_u128_t>(m,
								m->map.u128, f,
								opaque);
				break;
			case 32:
				cdada_map_rtraverse_u<cdada_u256_t>(m,
								m->map.u256, f,
								opaque);
				break;
			case 64:
				cdada_map_rtraverse_u<cdada_u512_t>(m,
								m->map.u512, f,
								opaque);
				break;
			case 128:
				cdada_map_rtraverse_u<cdada_u1024_t>(m,
								m->map.u1024, f,
								opaque);
				break;
			case 256:
				cdada_map_rtraverse_u<cdada_u2048_t>(m,
								m->map.u2048, f,
								opaque);
				break;
			case 0:
				CDADA_ASSERT(m->ops);
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

int cdada_map_dump(cdada_map_t* map, uint32_t size, char* buffer,
							uint32_t* size_used){

	__cdada_map_int_t* m = (__cdada_map_int_t*)map;
	CDADA_CHECK_MAGIC(m);

	if(!size_used || (buffer&&size ==0))
		return CDADA_E_INVALID;

	try{
		std::stringstream ss;
		ss << "{";

		int c = m->ops? 0 : m->key_len;
		switch(c){
			case 1:
				cdada_map_dump_u<uint8_t>(m, m->map.u8, ss);
				break;
			case 2:
				cdada_map_dump_u<uint16_t>(m, m->map.u16,
									ss);
				break;
			case 4:
				cdada_map_dump_u<uint32_t>(m, m->map.u32,
									ss);
				break;
			case 8:
				cdada_map_dump_u<uint64_t>(m, m->map.u64,
									ss);
				break;
			case 16:
				cdada_map_dump_u<cdada_u128_t>(m,
								m->map.u128,
								ss);
				break;
			case 32:
				cdada_map_dump_u<cdada_u256_t>(m,
								m->map.u256,
								ss);
				break;
			case 64:
				cdada_map_dump_u<cdada_u512_t>(m,
								m->map.u512,
								ss);
				break;
			case 128:
				cdada_map_dump_u<cdada_u1024_t>(m,
								m->map.u1024,
								ss);
				break;
			case 256:
				cdada_map_dump_u<cdada_u2048_t>(m,
								m->map.u2048,
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

int cdada_map_print(cdada_map_t* map, FILE *stream){

	__cdada_map_int_t* m = (__cdada_map_int_t*)map;
	CDADA_CHECK_MAGIC(m);

	try{
		std::stringstream ss;
		ss << "{";

		int c = m->ops? 0 : m->key_len;
		switch(c){
			case 1:
				cdada_map_dump_u<uint8_t>(m, m->map.u8, ss);
				break;
			case 2:
				cdada_map_dump_u<uint16_t>(m, m->map.u16,
									ss);
				break;
			case 4:
				cdada_map_dump_u<uint32_t>(m, m->map.u32,
									ss);
				break;
			case 8:
				cdada_map_dump_u<uint64_t>(m, m->map.u64,
									ss);
				break;
			case 16:
				cdada_map_dump_u<cdada_u128_t>(m,
								m->map.u128,
								ss);
				break;
			case 32:
				cdada_map_dump_u<cdada_u256_t>(m,
								m->map.u256,
								ss);
				break;
			case 64:
				cdada_map_dump_u<cdada_u512_t>(m,
								m->map.u512,
								ss);
				break;
			case 128:
				cdada_map_dump_u<cdada_u1024_t>(m,
								m->map.u1024,
								ss);
				break;
			case 256:
				cdada_map_dump_u<cdada_u2048_t>(m,
								m->map.u2048,
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
