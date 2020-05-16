#include "cdata/map.h"
#include "common_int.h"
#include "map_int.h"

#include <string.h>

using namespace std;

cdata_map_t* cdata_map_create(const uint16_t key_size){

	__cdata_map_int_t* m = NULL;

	if(key_size == 0)
		return m;

	m = (__cdata_map_int_t*)malloc(sizeof(__cdata_map_int_t));
	memset(m, 0, sizeof(__cdata_map_int_t));
	m->magic_num = CDATA_MAGIC;
	m->user_key_len = key_size;

	try{
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
			m->map.u128 = new map<cdata_u128_t, void*>();
			m->key_len = 16;
		}else if(key_size > 16 && key_size <= 32){
			m->map.u256 = new map<cdata_u256_t, void*>();
			m->key_len = 32;
		}else if(key_size > 32 && key_size <= 64){
			m->map.u512 = new map<cdata_u512_t, void*>();
			m->key_len = 64;
		}else if(key_size > 64 && key_size <= 128){
			m->map.u1024 = new map<cdata_u1024_t, void*>();
			m->key_len = 128;
		}else if(key_size > 128 && key_size <= 256){
			m->map.u2048 = new map<cdata_u2048_t, void*>();
			m->key_len = 256;
		}else{
			//Variable
			//TODO
			goto ROLLBACK;
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
};

/**
* Destroy a map structure
*/
int cdata_map_destroy(cdata_map_t* map){

	__cdata_map_int_t* m = (__cdata_map_int_t*)map;

	CDATA_CHECK_MAGIC(m);

	try{
		switch(m->key_len){
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
			default:
				//TODO
				CDATA_ASSERT(0);
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

int cdata_map_clear(cdata_map_t* map){

	__cdata_map_int_t* m = (__cdata_map_int_t*)map;

	CDATA_CHECK_MAGIC(m);

	try{
		if(m->key_len == 1){
			m->map.u8->clear();
		}else if(m->key_len ==  2){
			m->map.u16->clear();
		}else if(m->key_len > 2 && m->key_len <= 4){
			m->map.u32->clear();
		}else if(m->key_len > 4 && m->key_len <= 8){
			m->map.u64->clear();
		}else if(m->key_len > 8 && m->key_len <= 16){
			m->map.u128->clear();
		}else if(m->key_len > 16 && m->key_len <= 32){
			m->map.u256->clear();
		}else if(m->key_len > 32 && m->key_len <= 64){
			m->map.u512->clear();
		}else if(m->key_len > 64 && m->key_len <= 128){
			m->map.u1024->clear();
		}else if(m->key_len > 128 && m->key_len <= 256){
			m->map.u2048->clear();
		}else{
			//Variable
			//TODO
			return CDATA_E_UNSUPPORTED;
		}
	}catch(bad_alloc& e){
		return CDATA_E_MEM;
	}catch(...){
		CDATA_ASSERT(0);
		return CDATA_E_UNKNOWN;
	}

	return CDATA_SUCCESS;
}

bool cdata_map_empty(cdata_map_t* map){

	__cdata_map_int_t* m = (__cdata_map_int_t*)map;

	if(!m || m->magic_num != CDATA_MAGIC)
		return false;

	try{
		switch(m->key_len){
			case 1:
				return m->map.u8->empty();
			case 2:
				return m->map.u16->empty();
			case 3:
				return m->map.u32->empty();
			case 4:
				return m->map.u64->empty();
			case 8:
				return m->map.u128->empty();
			case 16:
				return m->map.u256->empty();
			case 32:
				return m->map.u512->empty();
			case 64:
				return m->map.u1024->empty();
			case 128:
				return m->map.u2048->empty();
			default:
				//Variable
				//TODO
				return false;
		}
	}catch(...){
		CDATA_ASSERT(0);
		return false;
	}

	return false;
}

uint32_t cdata_map_size(cdata_map_t* map){

	__cdata_map_int_t* m = (__cdata_map_int_t*)map;

	if(!m || m->magic_num != CDATA_MAGIC)
		return 0;

	try{
		switch(m->key_len){
			case 1:
				return m->map.u8->size();
			case 2:
				return m->map.u16->size();
			case 3:
				return m->map.u32->size();
			case 4:
				return m->map.u64->size();
			case 8:
				return m->map.u128->size();
			case 16:
				return m->map.u256->size();
			case 32:
				return m->map.u512->size();
			case 64:
				return m->map.u1024->size();
			case 128:
				return m->map.u2048->size();
			default:
				//Variable
				//TODO
				return 0;
		}
	}catch(...){
		CDATA_ASSERT(0);
		return 0;
	}

	return 0;
}

template<typename T>
int cdata_map_insert_u(__cdata_map_int_t* m, std::map<T, void*>* m_u,
								const void* key,
								void* val){
	if(m->key_len == m->user_key_len){
		T* __attribute((__may_alias__)) aux;

		aux = (T*)key;

		if(m_u->find(*aux) != m_u->end())
			return CDATA_E_EXISTS;
		m_u->insert({*aux, val});

		return CDATA_SUCCESS;
	}

	//We have to pad the struct
	T aux = {0};
	memcpy(&aux, key, m->user_key_len);

	if(m_u->find(aux) != m_u->end())
		return CDATA_E_EXISTS;

	m_u->insert({aux, val});

	return CDATA_SUCCESS;
}

int cdata_map_insert(cdata_map_t* map, const void* key, void* val){

	int rv;
	__cdata_map_int_t* m = (__cdata_map_int_t*)map;

	CDATA_CHECK_MAGIC(m);

	if(!key || !val)
		return CDATA_E_INVALID;

	//NOTE: we don't want std::map insert "replace semantics", so we return
	//E_EXISTS if key is present in the map
	try{
		switch(m->key_len){
			case 1:
				rv = cdata_map_insert_u<uint8_t>(m, m->map.u8,
									key,
									val);
				break;
			case 2:
				rv = cdata_map_insert_u<uint16_t>(m, m->map.u16,
									key,
									val);
				break;
			case 4:
				rv = cdata_map_insert_u<uint32_t>(m, m->map.u32,
									key,
									val);
				break;
			case 8:
				rv = cdata_map_insert_u<uint64_t>(m, m->map.u64,
									key,
									val);
				break;
			case 16:
				rv = cdata_map_insert_u<cdata_u128_t>(m,
								m->map.u128,
								key,
								val);
				break;
			case 32:
				rv = cdata_map_insert_u<cdata_u256_t>(m,
								m->map.u256,
								key,
								val);
				break;
			case 64:
				rv = cdata_map_insert_u<cdata_u512_t>(m,
								m->map.u512,
								key,
								val);
				break;
			case 128:
				rv = cdata_map_insert_u<cdata_u1024_t>(m,
								m->map.u1024,
								key,
								val);
				break;
			case 256:
				rv = cdata_map_insert_u<cdata_u2048_t>(m,
								m->map.u2048,
								key,
								val);
				break;
			default:
				//Variable
				//TODO
				return CDATA_E_UNSUPPORTED;
		}
	}catch(bad_alloc& e){
		return CDATA_E_MEM;
	}catch(...){
		CDATA_ASSERT(0);
		return CDATA_E_UNKNOWN;
	}

	return rv;
}

template<typename T>
int cdata_map_erase_u(__cdata_map_int_t* m, std::map<T, void*>* m_u,
							const void* key){
	if(m->key_len == m->user_key_len){
		T* __attribute((__may_alias__)) aux;

		aux = (T*)key;

		if(m_u->find(*aux) == m_u->end())
			return CDATA_E_NOT_FOUND;
		m_u->erase(*aux);

		return CDATA_SUCCESS;
	}

	//We have to pad the struct
	T aux = {0};
	memcpy(&aux, key, m->user_key_len);

	if(m_u->find(aux) == m_u->end())
		return CDATA_E_NOT_FOUND;

	m_u->erase(aux);

	return CDATA_SUCCESS;
}

int cdata_map_erase(cdata_map_t* map, const void* key){

	int rv;
	__cdata_map_int_t* m = (__cdata_map_int_t*)map;

	CDATA_CHECK_MAGIC(m);

	if(!key)
		return CDATA_E_INVALID;

	try{
		switch(m->key_len){
			case 1:
				rv = cdata_map_erase_u<uint8_t>(m, m->map.u8,
									key);
				break;
			case 2:
				rv = cdata_map_erase_u<uint16_t>(m, m->map.u16,
									key);
				break;
			case 4:
				rv = cdata_map_erase_u<uint32_t>(m, m->map.u32,
									key);
				break;
			case 8:
				rv = cdata_map_erase_u<uint64_t>(m, m->map.u64,
									key);
				break;
			case 16:
				rv = cdata_map_erase_u<cdata_u128_t>(m,
								m->map.u128,
								key);
				break;
			case 32:
				rv = cdata_map_erase_u<cdata_u256_t>(m,
								m->map.u256,
								key);
				break;
			case 64:
				rv = cdata_map_erase_u<cdata_u512_t>(m,
								m->map.u512,
								key);
				break;
			case 128:
				rv = cdata_map_erase_u<cdata_u1024_t>(m,
								m->map.u1024,
								key);
				break;
			case 256:
				rv = cdata_map_erase_u<cdata_u2048_t>(m,
								m->map.u2048,
								key);
				break;
			default:
				//Variable
				//TODO
				return CDATA_E_UNSUPPORTED;
		}
	}catch(bad_alloc& e){
		return CDATA_E_MEM;
	}catch(...){
		CDATA_ASSERT(0);
		return CDATA_E_UNKNOWN;
	}

	return rv;
}


template<typename T>
int cdata_map_find_u(__cdata_map_int_t* m, std::map<T, void*>* m_u,
							const void* key,
							void** val){
	typename std::map<T, void*>::iterator it;

	if(m->key_len == m->user_key_len){
		T* __attribute((__may_alias__)) aux;

		aux = (T*)key;
		it = m_u->find(*aux);

		if(it == m_u->end())
			return CDATA_E_NOT_FOUND;

		*val = it->second;

		return CDATA_SUCCESS;
	}

	//We have to pad the struct
	T aux = {0};
	memcpy(&aux, key, m->user_key_len);

	it = m_u->find(aux);
	if(it == m_u->end())
		return CDATA_E_NOT_FOUND;

	*val = it->second;

	return CDATA_SUCCESS;
}


int cdata_map_find(cdata_map_t* map, const void* key, void** val){

	int rv;
	__cdata_map_int_t* m = (__cdata_map_int_t*)map;

	CDATA_CHECK_MAGIC(m);

	if(!key || val == NULL)
		return CDATA_E_INVALID;

	try{
		switch(m->key_len){
			case 1:
				rv = cdata_map_find_u<uint8_t>(m, m->map.u8,
									key,
									val);
				break;
			case 2:
				rv = cdata_map_find_u<uint16_t>(m, m->map.u16,
									key,
									val);
				break;
			case 4:
				rv = cdata_map_find_u<uint32_t>(m, m->map.u32,
									key,
									val);
				break;
			case 8:
				rv = cdata_map_find_u<uint64_t>(m, m->map.u64,
									key,
									val);
				break;
			case 16:
				rv = cdata_map_find_u<cdata_u128_t>(m,
								m->map.u128,
								key,
								val);
				break;
			case 32:
				rv = cdata_map_find_u<cdata_u256_t>(m,
								m->map.u256,
								key,
								val);
				break;
			case 64:
				rv = cdata_map_find_u<cdata_u512_t>(m,
								m->map.u512,
								key,
								val);
				break;
			case 128:
				rv = cdata_map_find_u<cdata_u1024_t>(m,
								m->map.u1024,
								key,
								val);
				break;
			case 256:
				rv = cdata_map_find_u<cdata_u2048_t>(m,
								m->map.u2048,
								key,
								val);
				break;
			default:
				//Variable
				//TODO
				return CDATA_E_UNSUPPORTED;
		}
	}catch(...){
		CDATA_ASSERT(0);
		return CDATA_E_UNKNOWN;
	}

	return rv;
}

template<typename T>
void cdata_map_traverse_u(const cdata_map_t* map, std::map<T, void*>* m_u,
							cdata_map_it f,
							void* opaque){

	typename std::map<T, void*>::const_iterator it;

	for(it = m_u->begin(); it != m_u->end(); ++it)
		(*f)(map, &it->first, it->second, opaque);
}

int cdata_map_traverse(const cdata_map_t* map, cdata_map_it f,
							void* opaque){

	__cdata_map_int_t* m = (__cdata_map_int_t*)map;

	CDATA_CHECK_MAGIC(m);

	if(!f)
		return CDATA_E_INVALID;

	try{
		switch(m->key_len){
			case 1:
				cdata_map_traverse_u<uint8_t>(m, m->map.u8, f,
									opaque);
				break;
			case 2:
				cdata_map_traverse_u<uint16_t>(m, m->map.u16, f,
									opaque);
				break;
			case 4:
				cdata_map_traverse_u<uint32_t>(m, m->map.u32, f,
									opaque);
				break;
			case 8:
				cdata_map_traverse_u<uint64_t>(m, m->map.u64, f,
									opaque);
				break;
			case 16:
				cdata_map_traverse_u<cdata_u128_t>(m,
								m->map.u128, f,
								opaque);
				break;
			case 32:
				cdata_map_traverse_u<cdata_u256_t>(m,
								m->map.u256, f,
								opaque);
				break;
			case 64:
				cdata_map_traverse_u<cdata_u512_t>(m,
								m->map.u512, f,
								opaque);
				break;
			case 128:
				cdata_map_traverse_u<cdata_u1024_t>(m,
								m->map.u1024, f,
								opaque);
				break;
			case 256:
				cdata_map_traverse_u<cdata_u2048_t>(m,
								m->map.u2048, f,
								opaque);
				break;
			default:
				//Variable
				//TODO
				return CDATA_E_UNSUPPORTED;
		}
	}catch(...){
		CDATA_ASSERT(0);
		return CDATA_E_UNKNOWN;
	}

	return CDATA_SUCCESS;
}

template<typename T>
void cdata_map_rtraverse_u(const cdata_map_t* map, std::map<T, void*>* m_u,
							cdata_map_it f,
							void* opaque){

	typename std::map<T, void*>::const_reverse_iterator it;

	for(it = m_u->rbegin(); it != m_u->rend(); ++it)
		(*f)(map, &it->first, it->second, opaque);
}

int cdata_map_rtraverse(const cdata_map_t* map, cdata_map_it f,
							void* opaque){

	__cdata_map_int_t* m = (__cdata_map_int_t*)map;

	CDATA_CHECK_MAGIC(m);

	if(!f)
		return CDATA_E_INVALID;

	try{
		switch(m->key_len){
			case 1:
				cdata_map_rtraverse_u<uint8_t>(m, m->map.u8, f,
									opaque);
				break;
			case 2:
				cdata_map_rtraverse_u<uint16_t>(m, m->map.u16,
									f,
									opaque);
				break;
			case 4:
				cdata_map_rtraverse_u<uint32_t>(m, m->map.u32,
									f,
									opaque);
				break;
			case 8:
				cdata_map_rtraverse_u<uint64_t>(m, m->map.u64,
									f,
									opaque);
				break;
			case 16:
				cdata_map_rtraverse_u<cdata_u128_t>(m,
								m->map.u128, f,
								opaque);
				break;
			case 32:
				cdata_map_rtraverse_u<cdata_u256_t>(m,
								m->map.u256, f,
								opaque);
				break;
			case 64:
				cdata_map_rtraverse_u<cdata_u512_t>(m,
								m->map.u512, f,
								opaque);
				break;
			case 128:
				cdata_map_rtraverse_u<cdata_u1024_t>(m,
								m->map.u1024, f,
								opaque);
				break;
			case 256:
				cdata_map_rtraverse_u<cdata_u2048_t>(m,
								m->map.u2048, f,
								opaque);
				break;
			default:
				//Variable
				//TODO
				return CDATA_E_UNSUPPORTED;
		}
	}catch(...){
		CDATA_ASSERT(0);
		return CDATA_E_UNKNOWN;
	}

	return CDATA_SUCCESS;
}
