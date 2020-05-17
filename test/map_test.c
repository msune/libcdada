#include <stdlib.h>

#include "cdata/map.h"
#include "common.h"
#include <string.h>
#include "u552.h"

//Fwd decl
CDATA_MAP_CUSTOM_TYPE_DECL(test_u552_t);

static uint64_t opaque = 0ULL;
static cdata_map_t* map = NULL;

void trav_u64(const cdata_map_t* m, const void* k,
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

void rtrav_u64(const cdata_map_t* m, const void* k,
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

	map = cdata_map_create(sizeof(key));
	TEST_ASSERT(map != NULL);

	TEST_ASSERT(cdata_map_size(map) == 0);
	TEST_ASSERT(cdata_map_empty(map) == true);

	//Add one key & get
	key = 0;
	rv = cdata_map_insert(map, &key, &values[0]);
	TEST_ASSERT(rv == CDATA_SUCCESS);

	TEST_ASSERT(cdata_map_size(map) == 1);
	TEST_ASSERT(cdata_map_empty(map) == false);

	rv = cdata_map_find(map, &key, &tmp);
	TEST_ASSERT(rv == CDATA_SUCCESS);
	TEST_ASSERT(key == 0); //Should never pollute
	TEST_ASSERT(tmp == &values[0]);

	//Find an invalid value
	key = 1;
	rv = cdata_map_find(map, &key, &tmp);
	TEST_ASSERT(rv == CDATA_E_NOT_FOUND);

	//Trying to add the same key should return E_EXISTS, &repeat query
	key = 0;
	rv = cdata_map_insert(map, &key, &values[1]);
	TEST_ASSERT(rv == CDATA_E_EXISTS);

	rv = cdata_map_find(map, &key, &tmp);
	TEST_ASSERT(rv == CDATA_SUCCESS);
	TEST_ASSERT(key == 0); //Should never pollute
	TEST_ASSERT(tmp == &values[0]);

	//Erase first an invalid
	key = 1;
	rv = cdata_map_erase(map, &key);
	TEST_ASSERT(rv == CDATA_E_NOT_FOUND);

	key = 0;
	rv = cdata_map_erase(map, &key);
	TEST_ASSERT(rv == CDATA_SUCCESS);

	rv = cdata_map_find(map, &key, &tmp);
	TEST_ASSERT(rv == CDATA_E_NOT_FOUND);

	//Now add all objects
	for(i=0;i<32;++i){
		key = i;
		rv = cdata_map_insert(map, &key, &values[i]);
		TEST_ASSERT(rv == CDATA_SUCCESS);
	}

	TEST_ASSERT(cdata_map_size(map) == 32);
	TEST_ASSERT(cdata_map_empty(map) == false);

	key = 22;
	rv = cdata_map_find(map, &key, &tmp);
	TEST_ASSERT(rv == CDATA_SUCCESS);
	TEST_ASSERT(key == 22); //Should never pollute
	TEST_ASSERT(tmp == &values[22]);

	rv = cdata_map_clear(map);
	TEST_ASSERT(cdata_map_size(map) == 0);
	TEST_ASSERT(cdata_map_empty(map) == true);

	rv = cdata_map_destroy(map);
	TEST_ASSERT(rv == CDATA_SUCCESS);

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

	map = cdata_map_create(sizeof(key));
	TEST_ASSERT(map != NULL);

	TEST_ASSERT(cdata_map_size(map) == 0);
	TEST_ASSERT(cdata_map_empty(map) == true);

	//Add one key & get
	key = 0;
	rv = cdata_map_insert(map, &key, &values[0]);
	TEST_ASSERT(rv == CDATA_SUCCESS);

	TEST_ASSERT(cdata_map_size(map) == 1);
	TEST_ASSERT(cdata_map_empty(map) == false);

	rv = cdata_map_find(map, &key, &tmp);
	TEST_ASSERT(rv == CDATA_SUCCESS);
	TEST_ASSERT(key == 0); //Should never pollute
	TEST_ASSERT(tmp == &values[0]);

	//Find an invalid value
	key = 1;
	rv = cdata_map_find(map, &key, &tmp);
	TEST_ASSERT(rv == CDATA_E_NOT_FOUND);

	//Trying to add the same key should return E_EXISTS, &repeat query
	key = 0;
	rv = cdata_map_insert(map, &key, &values[1]);
	TEST_ASSERT(rv == CDATA_E_EXISTS);

	rv = cdata_map_find(map, &key, &tmp);
	TEST_ASSERT(rv == CDATA_SUCCESS);
	TEST_ASSERT(key == 0); //Should never pollute
	TEST_ASSERT(tmp == &values[0]);

	//Erase first an invalid
	key = 1;
	rv = cdata_map_erase(map, &key);
	TEST_ASSERT(rv == CDATA_E_NOT_FOUND);

	key = 0;
	rv = cdata_map_erase(map, &key);
	TEST_ASSERT(rv == CDATA_SUCCESS);

	rv = cdata_map_find(map, &key, &tmp);
	TEST_ASSERT(rv == CDATA_E_NOT_FOUND);

	//Now add all objects
	for(i=0;i<32;++i){
		key = i;
		rv = cdata_map_insert(map, &key, &values[i]);
		TEST_ASSERT(rv == CDATA_SUCCESS);
	}

	TEST_ASSERT(cdata_map_size(map) == 32);
	TEST_ASSERT(cdata_map_empty(map) == false);

	key = 22;
	rv = cdata_map_find(map, &key, &tmp);
	TEST_ASSERT(rv == CDATA_SUCCESS);
	TEST_ASSERT(key == 22); //Should never pollute
	TEST_ASSERT(tmp == &values[22]);

	rv = cdata_map_clear(map);
	TEST_ASSERT(cdata_map_size(map) == 0);
	TEST_ASSERT(cdata_map_empty(map) == true);

	rv = cdata_map_destroy(map);
	TEST_ASSERT(rv == CDATA_SUCCESS);

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

	map = cdata_map_create(sizeof(key));
	TEST_ASSERT(map != NULL);

	TEST_ASSERT(cdata_map_size(map) == 0);
	TEST_ASSERT(cdata_map_empty(map) == true);

	//Add one key & get
	key = 0;
	rv = cdata_map_insert(map, &key, &values[0]);
	TEST_ASSERT(rv == CDATA_SUCCESS);

	TEST_ASSERT(cdata_map_size(map) == 1);
	TEST_ASSERT(cdata_map_empty(map) == false);

	rv = cdata_map_find(map, &key, &tmp);
	TEST_ASSERT(rv == CDATA_SUCCESS);
	TEST_ASSERT(key == 0); //Should never pollute
	TEST_ASSERT(tmp == &values[0]);

	//Find an invalid value
	key = 1;
	rv = cdata_map_find(map, &key, &tmp);
	TEST_ASSERT(rv == CDATA_E_NOT_FOUND);

	//Trying to add the same key should return E_EXISTS, &repeat query
	key = 0;
	rv = cdata_map_insert(map, &key, &values[1]);
	TEST_ASSERT(rv == CDATA_E_EXISTS);

	rv = cdata_map_find(map, &key, &tmp);
	TEST_ASSERT(rv == CDATA_SUCCESS);
	TEST_ASSERT(key == 0); //Should never pollute
	TEST_ASSERT(tmp == &values[0]);

	//Erase first an invalid
	key = 1;
	rv = cdata_map_erase(map, &key);
	TEST_ASSERT(rv == CDATA_E_NOT_FOUND);

	key = 0;
	rv = cdata_map_erase(map, &key);
	TEST_ASSERT(rv == CDATA_SUCCESS);

	rv = cdata_map_find(map, &key, &tmp);
	TEST_ASSERT(rv == CDATA_E_NOT_FOUND);

	//Now add all objects
	for(i=0;i<32;++i){
		key = i;
		rv = cdata_map_insert(map, &key, &values[i]);
		TEST_ASSERT(rv == CDATA_SUCCESS);
	}

	TEST_ASSERT(cdata_map_size(map) == 32);
	TEST_ASSERT(cdata_map_empty(map) == false);

	key = 22;
	rv = cdata_map_find(map, &key, &tmp);
	TEST_ASSERT(rv == CDATA_SUCCESS);
	TEST_ASSERT(key == 22); //Should never pollute
	TEST_ASSERT(tmp == &values[22]);

	rv = cdata_map_clear(map);
	TEST_ASSERT(cdata_map_size(map) == 0);
	TEST_ASSERT(cdata_map_empty(map) == true);

	rv = cdata_map_destroy(map);
	TEST_ASSERT(rv == CDATA_SUCCESS);

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

	map = cdata_map_create(sizeof(key));
	TEST_ASSERT(map != NULL);

	TEST_ASSERT(cdata_map_size(map) == 0);
	TEST_ASSERT(cdata_map_empty(map) == true);

	//Add one key & get
	key = 0ULL;
	rv = cdata_map_insert(map, &key, &values[0]);
	TEST_ASSERT(rv == CDATA_SUCCESS);

	TEST_ASSERT(cdata_map_size(map) == 1);
	TEST_ASSERT(cdata_map_empty(map) == false);

	rv = cdata_map_find(map, &key, &tmp);
	TEST_ASSERT(rv == CDATA_SUCCESS);
	TEST_ASSERT(key == 0ULL); //Should never pollute
	TEST_ASSERT(tmp == &values[0]);

	//Find an invalid value
	key = 1ULL;
	rv = cdata_map_find(map, &key, &tmp);
	TEST_ASSERT(rv == CDATA_E_NOT_FOUND);

	//Trying to add the same key should return E_EXISTS, &repeat query
	key = 0ULL;
	rv = cdata_map_insert(map, &key, &values[1]);
	TEST_ASSERT(rv == CDATA_E_EXISTS);

	rv = cdata_map_find(map, &key, &tmp);
	TEST_ASSERT(rv == CDATA_SUCCESS);
	TEST_ASSERT(key == 0ULL); //Should never pollute
	TEST_ASSERT(tmp == &values[0]);

	//Erase first an invalid
	key = 1ULL;
	rv = cdata_map_erase(map, &key);
	TEST_ASSERT(rv == CDATA_E_NOT_FOUND);

	key = 0ULL;
	rv = cdata_map_erase(map, &key);
	TEST_ASSERT(rv == CDATA_SUCCESS);

	rv = cdata_map_find(map, &key, &tmp);
	TEST_ASSERT(rv == CDATA_E_NOT_FOUND);

	//Now add all objects
	for(i=0;i<32;++i){
		key = i;
		rv = cdata_map_insert(map, &key, &values[i]);
		TEST_ASSERT(rv == CDATA_SUCCESS);
	}

	TEST_ASSERT(cdata_map_size(map) == 32);
	TEST_ASSERT(cdata_map_empty(map) == false);

	key = 22ULL;
	rv = cdata_map_find(map, &key, &tmp);
	TEST_ASSERT(rv == CDATA_SUCCESS);
	TEST_ASSERT(key == 22ULL); //Should never pollute
	TEST_ASSERT(tmp == &values[22]);

	//Traverse
	opaque = 0ULL;
	cdata_map_traverse(map, &trav_u64, &opaque);

	opaque = 31ULL;
	cdata_map_rtraverse(map, &rtrav_u64, &opaque);

	rv = cdata_map_clear(map);
	TEST_ASSERT(cdata_map_size(map) == 0);
	TEST_ASSERT(cdata_map_empty(map) == true);

	rv = cdata_map_destroy(map);
	TEST_ASSERT(rv == CDATA_SUCCESS);

	return 0;
}

int test_basics(){

	int rv;

	void* ptr_not_null = (void*)0x123;

	//Create
	map = cdata_map_create(sizeof(int));
	TEST_ASSERT(map != NULL);

	TEST_ASSERT(cdata_map_size(map) == 0);
	TEST_ASSERT(cdata_map_empty(map) == true);

	//Try all APIs with a NULL map/key/val
	TEST_ASSERT(cdata_map_size(NULL) == 0);
	TEST_ASSERT(cdata_map_empty(NULL) == false);
	rv = cdata_map_destroy(NULL);
	TEST_ASSERT(rv == CDATA_E_INVALID);

	rv = cdata_map_traverse(NULL, ptr_not_null, NULL);
	TEST_ASSERT(rv == CDATA_E_INVALID);
	rv = cdata_map_traverse(map, NULL, NULL);
	TEST_ASSERT(rv == CDATA_E_INVALID);
	rv = cdata_map_rtraverse(NULL, ptr_not_null, NULL);
	TEST_ASSERT(rv == CDATA_E_INVALID);
	rv = cdata_map_rtraverse(map, NULL, NULL);
	TEST_ASSERT(rv == CDATA_E_INVALID);

	rv = cdata_map_insert(NULL, ptr_not_null, ptr_not_null);
	TEST_ASSERT(rv == CDATA_E_INVALID);
	rv = cdata_map_insert(map, NULL, ptr_not_null);
	TEST_ASSERT(rv == CDATA_E_INVALID);
	rv = cdata_map_erase(NULL, ptr_not_null);
	TEST_ASSERT(rv == CDATA_E_INVALID);
	rv = cdata_map_erase(map, NULL);
	TEST_ASSERT(rv == CDATA_E_INVALID);
	rv = cdata_map_find(NULL, ptr_not_null, ptr_not_null);
	TEST_ASSERT(rv == CDATA_E_INVALID);
	rv = cdata_map_find(map, NULL, ptr_not_null);
	TEST_ASSERT(rv == CDATA_E_INVALID);
	rv = cdata_map_find(map, ptr_not_null, NULL);
	TEST_ASSERT(rv == CDATA_E_INVALID);

	//Now destroy
	rv = cdata_map_destroy(map);
	TEST_ASSERT(rv == CDATA_SUCCESS);

	//Create with valid and invalid
	map = cdata_map_create(256);
	TEST_ASSERT(map != NULL);
	rv = cdata_map_destroy(map);
	TEST_ASSERT(rv == CDATA_SUCCESS);
	map = cdata_map_create(257);
	TEST_ASSERT(map == NULL);

	return 0;
}

//
// Key is not complete
//
void trav_u552(const cdata_map_t* m, const void* k,
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

void rtrav_u552(const cdata_map_t* m, const void* k,
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

	TEST_ASSERT(cdata_map_size(map) == 0);
	TEST_ASSERT(cdata_map_empty(map) == true);

	//Add one key & get
	memset(&key, 0, sizeof(key));
	rv = cdata_map_insert(map, &key, &values[0]);
	TEST_ASSERT(rv == CDATA_SUCCESS);

	TEST_ASSERT(cdata_map_size(map) == 1);
	TEST_ASSERT(cdata_map_empty(map) == false);

	rv = cdata_map_find(map, &key, &tmp);
	TEST_ASSERT(rv == CDATA_SUCCESS);
	TEST_ASSERT(key.mid == 0); //Should never pollute
	TEST_ASSERT(tmp == &values[0]);

	//Find an invalid value
	key.mid = 1;
	rv = cdata_map_find(map, &key, &tmp);
	TEST_ASSERT(rv == CDATA_E_NOT_FOUND);

	//Trying to add the same key should return E_EXISTS, &repeat query
	key.mid = 0;
	rv = cdata_map_insert(map, &key, &values[1]);
	TEST_ASSERT(rv == CDATA_E_EXISTS);

	rv = cdata_map_find(map, &key, &tmp);
	TEST_ASSERT(rv == CDATA_SUCCESS);
	TEST_ASSERT(key.mid == 0); //Should never pollute
	TEST_ASSERT(tmp == &values[0]);

	//Erase first an invalid
	key.mid = 1;
	rv = cdata_map_erase(map, &key);
	TEST_ASSERT(rv == CDATA_E_NOT_FOUND);

	key.mid = 0;
	rv = cdata_map_erase(map, &key);
	TEST_ASSERT(rv == CDATA_SUCCESS);

	rv = cdata_map_find(map, &key, &tmp);
	TEST_ASSERT(rv == CDATA_E_NOT_FOUND);

	//Now add all objects
	for(i=0;i<32;++i){
		key.mid = i;
		rv = cdata_map_insert(map, &key, &values[i]);
		TEST_ASSERT(rv == CDATA_SUCCESS);
	}

	TEST_ASSERT(cdata_map_size(map) == 32);
	TEST_ASSERT(cdata_map_empty(map) == false);

	key.mid = 22;
	rv = cdata_map_find(map, &key, &tmp);
	TEST_ASSERT(rv == CDATA_SUCCESS);
	TEST_ASSERT(key.mid == 22); //Should never pollute
	TEST_ASSERT(tmp == &values[22]);

	//Traverse
	opaque = 0ULL;
	cdata_map_traverse(map, &trav_u552, &opaque);

	opaque = 31ULL;
	cdata_map_rtraverse(map, &rtrav_u552, &opaque);

	rv = cdata_map_clear(map);
	TEST_ASSERT(cdata_map_size(map) == 0);
	TEST_ASSERT(cdata_map_empty(map) == true);

	rv = cdata_map_destroy(map);
	TEST_ASSERT(rv == CDATA_SUCCESS);

	return 0;
}

int test_u552_insert_removal_traverse(){
	map = cdata_map_create(sizeof(test_u552_t));
	TEST_ASSERT(map != NULL);

	return _test_u552_insert_removal_traverse();
}

int test_u552_insert_removal_traverse_custom(){
	map = cdata_map_create_custom(test_u552_t);
	TEST_ASSERT(map != NULL);

	return _test_u552_insert_removal_traverse();
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
	rv |= test_u552_insert_removal_traverse_custom();

	//Add your test here, and return a code appropriately...
	return rv == 0? EXIT_SUCCESS : EXIT_FAILURE;
}
