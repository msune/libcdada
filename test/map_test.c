#include <stdlib.h>

#include "cdada/map.h"
#include "common.h"
#include <string.h>
#include "u552.h"
#include "u3552.h"

//Fwd decl
CDADA_MAP_CUSTOM_TYPE_DECL(test_u552_t);
CDADA_MAP_CUSTOM_TYPE_DECL(test_u3552_t);

static uint64_t opaque = 0ULL;
static cdada_map_t* map = NULL;

void trav_u64(const cdada_map_t* m, const void* k,
						void* v,
						void* o){
	TEST_ASSERT(o == &opaque);
	TEST_ASSERT(map == m);

	uint64_t key = *(uint64_t*)k;
	uint32_t val = *(uint32_t*)v;

	TEST_ASSERT(val == (((uint32_t)key) | 0x1000));
	TEST_ASSERT(opaque == key);
	opaque++;
}

void rtrav_u64(const cdada_map_t* m, const void* k,
						void* v,
						void* o){
	TEST_ASSERT(o == &opaque);
	TEST_ASSERT(map == m);

	uint64_t key = *(uint64_t*)k;
	uint32_t val = *(uint32_t*)v;

	TEST_ASSERT(val == (((uint32_t)key) | 0x1000));
	TEST_ASSERT(opaque == key);
	opaque--;
}


//
// Aligned types
//

//8
int test_u8_insert_removal(){

	int i, rv;
	uint8_t key;
	uint32_t values[32];
	void* tmp;

	for(i=0;i<32;++i)
		values[i] = i | 0x1000;

	map = cdada_map_create(uint8_t);
	TEST_ASSERT(map != NULL);

	TEST_ASSERT(cdada_map_size(map) == 0);
	TEST_ASSERT(cdada_map_empty(map) == true);
	TEST_ASSERT(cdada_map_first(map, &key, &tmp) == CDADA_E_NOT_FOUND);
	TEST_ASSERT(cdada_map_last(map, &key, &tmp) == CDADA_E_NOT_FOUND);

	//Add one key & get
	key = 0;
	rv = cdada_map_insert(map, &key, &values[0]);
	TEST_ASSERT(rv == CDADA_SUCCESS);

	rv = cdada_map_first(map, &key, &tmp);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 0);
	TEST_ASSERT(tmp == &values[0]);
	rv = cdada_map_last(map, &key, &tmp);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 0);
	TEST_ASSERT(tmp == &values[0]);

	TEST_ASSERT(cdada_map_size(map) == 1);
	TEST_ASSERT(cdada_map_empty(map) == false);

	rv = cdada_map_find(map, &key, &tmp);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 0); //Should never pollute
	TEST_ASSERT(tmp == &values[0]);

	//Find an invalid value
	key = 1;
	rv = cdada_map_find(map, &key, &tmp);
	TEST_ASSERT(rv == CDADA_E_NOT_FOUND);

	//Trying to add the same key should return E_EXISTS, &repeat query
	key = 0;
	rv = cdada_map_insert(map, &key, &values[1]);
	TEST_ASSERT(rv == CDADA_E_EXISTS);

	rv = cdada_map_find(map, &key, &tmp);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 0); //Should never pollute
	TEST_ASSERT(tmp == &values[0]);

	//Erase first an invalid
	key = 1;
	rv = cdada_map_erase(map, &key);
	TEST_ASSERT(rv == CDADA_E_NOT_FOUND);

	key = 0;
	rv = cdada_map_erase(map, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);

	rv = cdada_map_find(map, &key, &tmp);
	TEST_ASSERT(rv == CDADA_E_NOT_FOUND);

	//Now add all objects
	for(i=0;i<32;++i){
		key = i;
		rv = cdada_map_insert(map, &key, &values[i]);
		TEST_ASSERT(rv == CDADA_SUCCESS);
	}

	rv = cdada_map_first(map, &key, &tmp);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 0);
	TEST_ASSERT(tmp == &values[0]);

	rv = cdada_map_last(map, &key, &tmp);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 31);
	TEST_ASSERT(tmp == &values[31]);

	TEST_ASSERT(cdada_map_size(map) == 32);
	TEST_ASSERT(cdada_map_empty(map) == false);

	key = 22;
	rv = cdada_map_find(map, &key, &tmp);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 22); //Should never pollute
	TEST_ASSERT(tmp == &values[22]);

	rv = cdada_map_clear(map);
	TEST_ASSERT(cdada_map_size(map) == 0);
	TEST_ASSERT(cdada_map_empty(map) == true);

	rv = cdada_map_destroy(map);
	TEST_ASSERT(rv == CDADA_SUCCESS);

	return 0;
}

//16
int test_u16_insert_removal(){

	int i, rv;
	uint16_t key;
	uint32_t values[32];
	void* tmp;

	for(i=0;i<32;++i)
		values[i] = i | 0x1000;

	map = cdada_map_create(uint16_t);
	TEST_ASSERT(map != NULL);

	TEST_ASSERT(cdada_map_size(map) == 0);
	TEST_ASSERT(cdada_map_empty(map) == true);
	TEST_ASSERT(cdada_map_first(map, &key, &tmp) == CDADA_E_NOT_FOUND);
	TEST_ASSERT(cdada_map_last(map, &key, &tmp) == CDADA_E_NOT_FOUND);

	//Add one key & get
	key = 0;
	rv = cdada_map_insert(map, &key, &values[0]);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	rv = cdada_map_first(map, &key, &tmp);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 0);
	TEST_ASSERT(tmp == &values[0]);
	rv = cdada_map_last(map, &key, &tmp);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 0);
	TEST_ASSERT(tmp == &values[0]);

	TEST_ASSERT(cdada_map_size(map) == 1);
	TEST_ASSERT(cdada_map_empty(map) == false);

	rv = cdada_map_find(map, &key, &tmp);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 0); //Should never pollute
	TEST_ASSERT(tmp == &values[0]);

	//Find an invalid value
	key = 1;
	rv = cdada_map_find(map, &key, &tmp);
	TEST_ASSERT(rv == CDADA_E_NOT_FOUND);

	//Trying to add the same key should return E_EXISTS, &repeat query
	key = 0;
	rv = cdada_map_insert(map, &key, &values[1]);
	TEST_ASSERT(rv == CDADA_E_EXISTS);

	rv = cdada_map_find(map, &key, &tmp);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 0); //Should never pollute
	TEST_ASSERT(tmp == &values[0]);

	//Erase first an invalid
	key = 1;
	rv = cdada_map_erase(map, &key);
	TEST_ASSERT(rv == CDADA_E_NOT_FOUND);

	key = 0;
	rv = cdada_map_erase(map, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);

	rv = cdada_map_find(map, &key, &tmp);
	TEST_ASSERT(rv == CDADA_E_NOT_FOUND);

	//Now add all objects
	for(i=0;i<32;++i){
		key = i;
		rv = cdada_map_insert(map, &key, &values[i]);
		TEST_ASSERT(rv == CDADA_SUCCESS);
	}

	rv = cdada_map_first(map, &key, &tmp);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 0);
	TEST_ASSERT(tmp == &values[0]);

	rv = cdada_map_last(map, &key, &tmp);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 31);
	TEST_ASSERT(tmp == &values[31]);

	TEST_ASSERT(cdada_map_size(map) == 32);
	TEST_ASSERT(cdada_map_empty(map) == false);

	key = 22;
	rv = cdada_map_find(map, &key, &tmp);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 22); //Should never pollute
	TEST_ASSERT(tmp == &values[22]);

	rv = cdada_map_clear(map);
	TEST_ASSERT(cdada_map_size(map) == 0);
	TEST_ASSERT(cdada_map_empty(map) == true);

	rv = cdada_map_destroy(map);
	TEST_ASSERT(rv == CDADA_SUCCESS);

	return 0;
}

//32
int test_u32_insert_removal(){

	int i, rv;
	uint32_t key;
	uint32_t values[32];
	void* tmp;

	for(i=0;i<32;++i)
		values[i] = i | 0x1000;

	map = cdada_map_create(uint32_t);
	TEST_ASSERT(map != NULL);

	TEST_ASSERT(cdada_map_size(map) == 0);
	TEST_ASSERT(cdada_map_empty(map) == true);
	TEST_ASSERT(cdada_map_first(map, &key, &tmp) == CDADA_E_NOT_FOUND);
	TEST_ASSERT(cdada_map_last(map, &key, &tmp) == CDADA_E_NOT_FOUND);

	//Add one key & get
	key = 0;
	rv = cdada_map_insert(map, &key, &values[0]);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	rv = cdada_map_first(map, &key, &tmp);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 0);
	TEST_ASSERT(tmp == &values[0]);
	rv = cdada_map_last(map, &key, &tmp);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 0);
	TEST_ASSERT(tmp == &values[0]);

	TEST_ASSERT(cdada_map_size(map) == 1);
	TEST_ASSERT(cdada_map_empty(map) == false);

	rv = cdada_map_find(map, &key, &tmp);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 0); //Should never pollute
	TEST_ASSERT(tmp == &values[0]);

	//Find an invalid value
	key = 1;
	rv = cdada_map_find(map, &key, &tmp);
	TEST_ASSERT(rv == CDADA_E_NOT_FOUND);

	//Trying to add the same key should return E_EXISTS, &repeat query
	key = 0;
	rv = cdada_map_insert(map, &key, &values[1]);
	TEST_ASSERT(rv == CDADA_E_EXISTS);

	rv = cdada_map_find(map, &key, &tmp);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 0); //Should never pollute
	TEST_ASSERT(tmp == &values[0]);

	//Erase first an invalid
	key = 1;
	rv = cdada_map_erase(map, &key);
	TEST_ASSERT(rv == CDADA_E_NOT_FOUND);

	key = 0;
	rv = cdada_map_erase(map, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);

	rv = cdada_map_find(map, &key, &tmp);
	TEST_ASSERT(rv == CDADA_E_NOT_FOUND);

	//Now add all objects
	for(i=0;i<32;++i){
		key = i;
		rv = cdada_map_insert(map, &key, &values[i]);
		TEST_ASSERT(rv == CDADA_SUCCESS);
	}

	rv = cdada_map_first(map, &key, &tmp);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 0);
	TEST_ASSERT(tmp == &values[0]);

	rv = cdada_map_last(map, &key, &tmp);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 31);
	TEST_ASSERT(tmp == &values[31]);

	TEST_ASSERT(cdada_map_size(map) == 32);
	TEST_ASSERT(cdada_map_empty(map) == false);

	key = 22;
	rv = cdada_map_find(map, &key, &tmp);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 22); //Should never pollute
	TEST_ASSERT(tmp == &values[22]);

	rv = cdada_map_clear(map);
	TEST_ASSERT(cdada_map_size(map) == 0);
	TEST_ASSERT(cdada_map_empty(map) == true);

	rv = cdada_map_destroy(map);
	TEST_ASSERT(rv == CDADA_SUCCESS);

	return 0;
}

//64
int test_u64_insert_removal_traverse(){

	int i, rv;
	uint64_t key;
	uint32_t values[32];
	void* tmp;

	for(i=0;i<32;++i)
		values[i] = i | 0x1000;

	map = cdada_map_create(uint64_t);
	TEST_ASSERT(map != NULL);

	TEST_ASSERT(cdada_map_size(map) == 0);
	TEST_ASSERT(cdada_map_empty(map) == true);
	TEST_ASSERT(cdada_map_first(map, &key, &tmp) == CDADA_E_NOT_FOUND);
	TEST_ASSERT(cdada_map_last(map, &key, &tmp) == CDADA_E_NOT_FOUND);

	//Add one key & get
	key = 0ULL;
	rv = cdada_map_insert(map, &key, &values[0]);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	rv = cdada_map_first(map, &key, &tmp);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 0ULL);
	TEST_ASSERT(tmp == &values[0]);
	rv = cdada_map_last(map, &key, &tmp);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 0ULL);
	TEST_ASSERT(tmp == &values[0]);

	TEST_ASSERT(cdada_map_size(map) == 1);
	TEST_ASSERT(cdada_map_empty(map) == false);

	rv = cdada_map_find(map, &key, &tmp);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 0ULL); //Should never pollute
	TEST_ASSERT(tmp == &values[0]);

	//Find an invalid value
	key = 1ULL;
	rv = cdada_map_find(map, &key, &tmp);
	TEST_ASSERT(rv == CDADA_E_NOT_FOUND);

	//Trying to add the same key should return E_EXISTS, &repeat query
	key = 0ULL;
	rv = cdada_map_insert(map, &key, &values[1]);
	TEST_ASSERT(rv == CDADA_E_EXISTS);

	rv = cdada_map_find(map, &key, &tmp);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 0ULL); //Should never pollute
	TEST_ASSERT(tmp == &values[0]);

	//Erase first an invalid
	key = 1ULL;
	rv = cdada_map_erase(map, &key);
	TEST_ASSERT(rv == CDADA_E_NOT_FOUND);

	key = 0ULL;
	rv = cdada_map_erase(map, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);

	rv = cdada_map_find(map, &key, &tmp);
	TEST_ASSERT(rv == CDADA_E_NOT_FOUND);

	//Now add all objects
	for(i=0;i<32;++i){
		key = i;
		rv = cdada_map_insert(map, &key, &values[i]);
		TEST_ASSERT(rv == CDADA_SUCCESS);
	}

	rv = cdada_map_first(map, &key, &tmp);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 0ULL);
	TEST_ASSERT(tmp == &values[0]);

	rv = cdada_map_last(map, &key, &tmp);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 31ULL);
	TEST_ASSERT(tmp == &values[31]);

	TEST_ASSERT(cdada_map_size(map) == 32);
	TEST_ASSERT(cdada_map_empty(map) == false);

	key = 22ULL;
	rv = cdada_map_find(map, &key, &tmp);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 22ULL); //Should never pollute
	TEST_ASSERT(tmp == &values[22]);

	//Traverse
	opaque = 0ULL;
	cdada_map_traverse(map, &trav_u64, &opaque);

	opaque = 31ULL;
	cdada_map_rtraverse(map, &rtrav_u64, &opaque);

	rv = cdada_map_clear(map);
	TEST_ASSERT(cdada_map_size(map) == 0);
	TEST_ASSERT(cdada_map_empty(map) == true);

	rv = cdada_map_destroy(map);
	TEST_ASSERT(rv == CDADA_SUCCESS);

	return 0;
}

int test_basics(){

	int rv;

	void* ptr_not_null = (void*)0x123;

	//Create
	map = cdada_map_create(int);
	TEST_ASSERT(map != NULL);

	TEST_ASSERT(cdada_map_size(map) == 0);
	TEST_ASSERT(cdada_map_empty(map) == true);

	//Try all APIs with a NULL map/key/val
	TEST_ASSERT(cdada_map_size(NULL) == 0);
	TEST_ASSERT(cdada_map_empty(NULL) == false);
	rv = cdada_map_destroy(NULL);
	TEST_ASSERT(rv == CDADA_E_INVALID);

	rv = cdada_map_traverse(NULL, ptr_not_null, NULL);
	TEST_ASSERT(rv == CDADA_E_INVALID);
	rv = cdada_map_traverse(map, NULL, NULL);
	TEST_ASSERT(rv == CDADA_E_INVALID);
	rv = cdada_map_rtraverse(NULL, ptr_not_null, NULL);
	TEST_ASSERT(rv == CDADA_E_INVALID);
	rv = cdada_map_rtraverse(map, NULL, NULL);
	TEST_ASSERT(rv == CDADA_E_INVALID);

	rv = cdada_map_insert(NULL, ptr_not_null, ptr_not_null);
	TEST_ASSERT(rv == CDADA_E_INVALID);
	rv = cdada_map_insert(map, NULL, ptr_not_null);
	TEST_ASSERT(rv == CDADA_E_INVALID);
	rv = cdada_map_erase(NULL, ptr_not_null);
	TEST_ASSERT(rv == CDADA_E_INVALID);
	rv = cdada_map_erase(map, NULL);
	TEST_ASSERT(rv == CDADA_E_INVALID);
	rv = cdada_map_find(NULL, ptr_not_null, ptr_not_null);
	TEST_ASSERT(rv == CDADA_E_INVALID);
	rv = cdada_map_find(map, NULL, ptr_not_null);
	TEST_ASSERT(rv == CDADA_E_INVALID);
	rv = cdada_map_find(map, ptr_not_null, NULL);
	TEST_ASSERT(rv == CDADA_E_INVALID);

	//Now destroy
	rv = cdada_map_destroy(map);
	TEST_ASSERT(rv == CDADA_SUCCESS);

	//Create with valid and invalid
	struct {
		char u[256];
	} c256;
	struct {
		char u[257];
	} c257;
	map = cdada_map_create(c256);
	TEST_ASSERT(map != NULL);
	rv = cdada_map_destroy(map);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	map = cdada_map_create(c257);
	TEST_ASSERT(map == NULL);

	return 0;
}

//
// Key is not complete
//
void trav_u552(const cdada_map_t* m, const void* k,
						void* v,
						void* o){
	TEST_ASSERT(o == &opaque);
	TEST_ASSERT(map == m);

	test_u552_t key = *(test_u552_t*)k;
	uint32_t val = *(uint32_t*)v;

	TEST_ASSERT(val == (((uint32_t)key.mid) | 0x1000));
	TEST_ASSERT(opaque == key.mid);
	opaque++;
}

void rtrav_u552(const cdada_map_t* m, const void* k,
						void* v,
						void* o){
	TEST_ASSERT(o == &opaque);
	TEST_ASSERT(map == m);

	test_u552_t key = *(test_u552_t*)k;
	uint32_t val = *(uint32_t*)v;

	TEST_ASSERT(val == (((uint32_t)key.mid) | 0x1000));
	TEST_ASSERT(opaque == key.mid);
	opaque--;
}

int _test_u552_insert_removal_traverse(){

	int i, rv;
	test_u552_t key;
	uint32_t values[32];
	void* tmp;

	TEST_ASSERT(sizeof(test_u552_t) == 69);

	for(i=0;i<32;++i)
		values[i] = i | 0x1000;

	TEST_ASSERT(cdada_map_size(map) == 0);
	TEST_ASSERT(cdada_map_empty(map) == true);
	TEST_ASSERT(cdada_map_first(map, &key, &tmp) == CDADA_E_NOT_FOUND);
	TEST_ASSERT(cdada_map_last(map, &key, &tmp) == CDADA_E_NOT_FOUND);

	//Add one key & get
	memset(&key, 0, sizeof(key));
	rv = cdada_map_insert(map, &key, &values[0]);
	TEST_ASSERT(rv == CDADA_SUCCESS);

	rv = cdada_map_first(map, &key, &tmp);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key.mid == 0);
	TEST_ASSERT(tmp == &values[0]);
	rv = cdada_map_last(map, &key, &tmp);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key.mid == 0);
	TEST_ASSERT(tmp == &values[0]);

	TEST_ASSERT(cdada_map_size(map) == 1);
	TEST_ASSERT(cdada_map_empty(map) == false);

	rv = cdada_map_find(map, &key, &tmp);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key.mid == 0); //Should never pollute
	TEST_ASSERT(tmp == &values[0]);

	//Find an invalid value
	key.mid = 1;
	rv = cdada_map_find(map, &key, &tmp);
	TEST_ASSERT(rv == CDADA_E_NOT_FOUND);

	//Trying to add the same key should return E_EXISTS, &repeat query
	key.mid = 0;
	rv = cdada_map_insert(map, &key, &values[1]);
	TEST_ASSERT(rv == CDADA_E_EXISTS);

	rv = cdada_map_find(map, &key, &tmp);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key.mid == 0); //Should never pollute
	TEST_ASSERT(tmp == &values[0]);

	//Erase first an invalid
	key.mid = 1;
	rv = cdada_map_erase(map, &key);
	TEST_ASSERT(rv == CDADA_E_NOT_FOUND);

	key.mid = 0;
	rv = cdada_map_erase(map, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);

	rv = cdada_map_find(map, &key, &tmp);
	TEST_ASSERT(rv == CDADA_E_NOT_FOUND);

	//Now add all objects
	for(i=0;i<32;++i){
		key.mid = i;
		rv = cdada_map_insert(map, &key, &values[i]);
		TEST_ASSERT(rv == CDADA_SUCCESS);
	}

	rv = cdada_map_first(map, &key, &tmp);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key.mid == 0);
	TEST_ASSERT(tmp == &values[0]);

	rv = cdada_map_last(map, &key, &tmp);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key.mid == 31);
	TEST_ASSERT(tmp == &values[31]);

	TEST_ASSERT(cdada_map_size(map) == 32);
	TEST_ASSERT(cdada_map_empty(map) == false);

	key.mid = 22;
	rv = cdada_map_find(map, &key, &tmp);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key.mid == 22); //Should never pollute
	TEST_ASSERT(tmp == &values[22]);

	//Traverse
	opaque = 0ULL;
	cdada_map_traverse(map, &trav_u552, &opaque);

	opaque = 31ULL;
	cdada_map_rtraverse(map, &rtrav_u552, &opaque);

	rv = cdada_map_clear(map);
	TEST_ASSERT(cdada_map_size(map) == 0);
	TEST_ASSERT(cdada_map_empty(map) == true);

	rv = cdada_map_destroy(map);
	TEST_ASSERT(rv == CDADA_SUCCESS);

	return 0;
}

int test_u552_insert_removal_traverse(){
	map = cdada_map_create(test_u552_t);
	TEST_ASSERT(map != NULL);

	return _test_u552_insert_removal_traverse();
}

int test_u552_insert_removal_traverse_custom(){
	map = cdada_map_create_custom(test_u552_t);
	TEST_ASSERT(map != NULL);

	return _test_u552_insert_removal_traverse();
}

int test_u3552_insert_removal_traverse_custom(){

	int i, rv;
	test_u3552_t key;
	uint32_t values[32];
	void* tmp;

	map = cdada_map_create_custom(test_u3552_t);
	TEST_ASSERT(map != NULL);

	TEST_ASSERT(sizeof(test_u3552_t) == 444);

	for(i=0;i<32;++i)
		values[i] = i | 0x1000;

	TEST_ASSERT(cdada_map_size(map) == 0);
	TEST_ASSERT(cdada_map_empty(map) == true);
	TEST_ASSERT(cdada_map_first(map, &key, &tmp) == CDADA_E_NOT_FOUND);
	TEST_ASSERT(cdada_map_last(map, &key, &tmp) == CDADA_E_NOT_FOUND);

	//Add one key & get
	memset(&key, 0, sizeof(key));
	rv = cdada_map_insert(map, &key, &values[0]);
	TEST_ASSERT(rv == CDADA_SUCCESS);

	rv = cdada_map_first(map, &key, &tmp);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key.mid == 0);
	TEST_ASSERT(tmp == &values[0]);
	rv = cdada_map_last(map, &key, &tmp);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key.mid == 0);
	TEST_ASSERT(tmp == &values[0]);

	TEST_ASSERT(cdada_map_size(map) == 1);
	TEST_ASSERT(cdada_map_empty(map) == false);

	rv = cdada_map_find(map, &key, &tmp);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key.mid == 0); //Should never pollute
	TEST_ASSERT(tmp == &values[0]);

	//Find an invalid value
	key.mid = 1;
	rv = cdada_map_find(map, &key, &tmp);
	TEST_ASSERT(rv == CDADA_E_NOT_FOUND);

	//Trying to add the same key should return E_EXISTS, &repeat query
	key.mid = 0;
	rv = cdada_map_insert(map, &key, &values[1]);
	TEST_ASSERT(rv == CDADA_E_EXISTS);

	rv = cdada_map_find(map, &key, &tmp);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key.mid == 0); //Should never pollute
	TEST_ASSERT(tmp == &values[0]);

	//Erase first an invalid
	key.mid = 1;
	rv = cdada_map_erase(map, &key);
	TEST_ASSERT(rv == CDADA_E_NOT_FOUND);

	key.mid = 0;
	rv = cdada_map_erase(map, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);

	rv = cdada_map_find(map, &key, &tmp);
	TEST_ASSERT(rv == CDADA_E_NOT_FOUND);

	//Now add all objects
	for(i=0;i<32;++i){
		key.mid = i;
		rv = cdada_map_insert(map, &key, &values[i]);
		TEST_ASSERT(rv == CDADA_SUCCESS);
	}

	rv = cdada_map_first(map, &key, &tmp);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key.mid == 0);
	TEST_ASSERT(tmp == &values[0]);

	rv = cdada_map_last(map, &key, &tmp);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key.mid == 31);
	TEST_ASSERT(tmp == &values[31]);

	TEST_ASSERT(cdada_map_size(map) == 32);
	TEST_ASSERT(cdada_map_empty(map) == false);

	key.mid = 22;
	rv = cdada_map_find(map, &key, &tmp);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key.mid == 22); //Should never pollute
	TEST_ASSERT(tmp == &values[22]);

	//Traverse
	opaque = 0ULL;
	cdada_map_traverse(map, &trav_u552, &opaque);

	opaque = 31ULL;
	cdada_map_rtraverse(map, &rtrav_u552, &opaque);

	rv = cdada_map_clear(map);
	TEST_ASSERT(cdada_map_size(map) == 0);
	TEST_ASSERT(cdada_map_empty(map) == true);

	rv = cdada_map_destroy(map);
	TEST_ASSERT(rv == CDADA_SUCCESS);

	return 0;
}

int main(int args, char** argv){

	int rv;

	rv = test_basics();

	//Complete
	rv |= test_u8_insert_removal();
	rv |= test_u16_insert_removal();
	rv |= test_u32_insert_removal();
	rv |= test_u64_insert_removal_traverse();

	//Incomplete
	rv |= test_u552_insert_removal_traverse();

	//Custom type
	rv |= test_u552_insert_removal_traverse_custom();
	rv |= test_u3552_insert_removal_traverse_custom();

	//Add your test here, and return a code appropriately...
	return rv == 0? EXIT_SUCCESS : EXIT_FAILURE;
}
