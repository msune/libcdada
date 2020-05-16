#include <stdlib.h>

#include "cdata/set.h"
#include <assert.h>
#include <string.h>


static uint64_t opaque = 0ULL;
static cdata_set_t* set = NULL;

void trav_u64(const cdata_set_t* s, const void* k, void* o){
	assert(o == &opaque);
	assert(set == s);
	uint64_t key = *(uint64_t*)k;
	assert(opaque == key);
	opaque++;
}

void rtrav_u64(const cdata_set_t* s, const void* k, void* o){
	assert(o == &opaque);
	assert(set == s);
	uint64_t key = *(uint64_t*)k;
	assert(opaque == key);
	opaque--;
}


//
// Aligned types
//

//8
int test_u8_insert_removal(){

	int i, rv;
	uint8_t key;

	set = cdata_set_create(sizeof(key));
	assert(set != NULL);

	assert(cdata_set_size(set) == 0);
	assert(cdata_set_empty(set) == true);

	//Add one key & get
	key = 0;
	rv = cdata_set_insert(set, &key);
	assert(rv == CDATA_SUCCESS);

	assert(cdata_set_size(set) == 1);
	assert(cdata_set_empty(set) == false);

	assert(cdata_set_find(set, &key) == true);
	assert(key == 0); //Should never pollute

	//Find an invalid value
	key = 1;
	assert(cdata_set_find(set, &key) == false);

	//Trying to add the same key should return E_EXISTS, &repeat query
	key = 0;
	rv = cdata_set_insert(set, &key);
	assert(rv == CDATA_E_EXISTS);

	assert(cdata_set_find(set, &key) == true);
	assert(key == 0); //Should never pollute

	//Erase first an invalid
	key = 1;
	rv = cdata_set_erase(set, &key);
	assert(rv == CDATA_E_NOT_FOUND);

	key = 0;
	rv = cdata_set_erase(set, &key);
	assert(rv == CDATA_SUCCESS);

	assert(cdata_set_find(set, &key) == false);

	//Now add all objects
	for(i=0;i<32;++i){
		key = i;
		rv = cdata_set_insert(set, &key);
		assert(rv == CDATA_SUCCESS);
	}

	assert(cdata_set_size(set) == 32);
	assert(cdata_set_empty(set) == false);

	key = 22;
	assert(cdata_set_find(set, &key) == true);
	assert(key == 22); //Should never pollute

	rv = cdata_set_clear(set);
	assert(cdata_set_size(set) == 0);
	assert(cdata_set_empty(set) == true);

	rv = cdata_set_destroy(set);
	assert(rv == CDATA_SUCCESS);

	return 0;
}

//16
int test_u16_insert_removal(){

	int i, rv;
	uint16_t key;

	set = cdata_set_create(sizeof(key));
	assert(set != NULL);

	assert(cdata_set_size(set) == 0);
	assert(cdata_set_empty(set) == true);

	//Add one key & get
	key = 0;
	rv = cdata_set_insert(set, &key);
	assert(rv == CDATA_SUCCESS);

	assert(cdata_set_size(set) == 1);
	assert(cdata_set_empty(set) == false);

	assert(cdata_set_find(set, &key) == true);
	assert(key == 0); //Should never pollute

	//Find an invalid value
	key = 1;
	assert(cdata_set_find(set, &key) == false);

	//Trying to add the same key should return E_EXISTS, &repeat query
	key = 0;
	rv = cdata_set_insert(set, &key);
	assert(rv == CDATA_E_EXISTS);

	assert(cdata_set_find(set, &key) == true);
	assert(key == 0); //Should never pollute

	//Erase first an invalid
	key = 1;
	rv = cdata_set_erase(set, &key);
	assert(rv == CDATA_E_NOT_FOUND);

	key = 0;
	rv = cdata_set_erase(set, &key);
	assert(rv == CDATA_SUCCESS);

	assert(cdata_set_find(set, &key) == false);

	//Now add all objects
	for(i=0;i<32;++i){
		key = i;
		rv = cdata_set_insert(set, &key);
		assert(rv == CDATA_SUCCESS);
	}

	assert(cdata_set_size(set) == 32);
	assert(cdata_set_empty(set) == false);

	key = 22;
	assert(cdata_set_find(set, &key) == true);
	assert(key == 22); //Should never pollute

	rv = cdata_set_clear(set);
	assert(cdata_set_size(set) == 0);
	assert(cdata_set_empty(set) == true);

	rv = cdata_set_destroy(set);
	assert(rv == CDATA_SUCCESS);

	return 0;
}

//32
int test_u32_insert_removal(){

	int i, rv;
	uint32_t key;

	set = cdata_set_create(sizeof(key));
	assert(set != NULL);

	assert(cdata_set_size(set) == 0);
	assert(cdata_set_empty(set) == true);

	//Add one key & get
	key = 0;
	rv = cdata_set_insert(set, &key);
	assert(rv == CDATA_SUCCESS);

	assert(cdata_set_size(set) == 1);
	assert(cdata_set_empty(set) == false);

	assert(cdata_set_find(set, &key) == true);
	assert(key == 0); //Should never pollute

	//Find an invalid value
	key = 1;
	assert(cdata_set_find(set, &key) == false);

	//Trying to add the same key should return E_EXISTS, &repeat query
	key = 0;
	rv = cdata_set_insert(set, &key);
	assert(rv == CDATA_E_EXISTS);

	assert(cdata_set_find(set, &key) == true);
	assert(key == 0); //Should never pollute

	//Erase first an invalid
	key = 1;
	rv = cdata_set_erase(set, &key);
	assert(rv == CDATA_E_NOT_FOUND);

	key = 0;
	rv = cdata_set_erase(set, &key);
	assert(rv == CDATA_SUCCESS);

	assert(cdata_set_find(set, &key) == false);

	//Now add all objects
	for(i=0;i<32;++i){
		key = i;
		rv = cdata_set_insert(set, &key);
		assert(rv == CDATA_SUCCESS);
	}

	assert(cdata_set_size(set) == 32);
	assert(cdata_set_empty(set) == false);

	key = 22;
	assert(cdata_set_find(set, &key) == true);
	assert(key == 22); //Should never pollute

	rv = cdata_set_clear(set);
	assert(cdata_set_size(set) == 0);
	assert(cdata_set_empty(set) == true);

	rv = cdata_set_destroy(set);
	assert(rv == CDATA_SUCCESS);

	return 0;
}

//64
int test_u64_insert_removal_traverse(){

	int i, rv;
	uint64_t key;

	set = cdata_set_create(sizeof(key));
	assert(set != NULL);

	assert(cdata_set_size(set) == 0);
	assert(cdata_set_empty(set) == true);

	//Add one key & get
	key = 0ULL;
	rv = cdata_set_insert(set, &key);
	assert(rv == CDATA_SUCCESS);

	assert(cdata_set_size(set) == 1);
	assert(cdata_set_empty(set) == false);

	assert(cdata_set_find(set, &key) == true);
	assert(key == 0ULL); //Should never pollute

	//Find an invalid value
	key = 1ULL;
	assert(cdata_set_find(set, &key) == false);

	//Trying to add the same key should return E_EXISTS, &repeat query
	key = 0ULL;
	rv = cdata_set_insert(set, &key);
	assert(rv == CDATA_E_EXISTS);

	assert(cdata_set_find(set, &key) == true);
	assert(key == 0ULL); //Should never pollute

	//Erase first an invalid
	key = 1ULL;
	rv = cdata_set_erase(set, &key);
	assert(rv == CDATA_E_NOT_FOUND);

	key = 0ULL;
	rv = cdata_set_erase(set, &key);
	assert(rv == CDATA_SUCCESS);

	assert(cdata_set_find(set, &key) == false);

	//Now add all objects
	for(i=0;i<32;++i){
		key = i;
		rv = cdata_set_insert(set, &key);
		assert(rv == CDATA_SUCCESS);
	}

	assert(cdata_set_size(set) == 32);
	assert(cdata_set_empty(set) == false);

	key = 22ULL;
	assert(cdata_set_find(set, &key) == true);
	assert(key == 22ULL); //Should never pollute

	//Traverse
	opaque = 0ULL;
	cdata_set_traverse(set, &trav_u64, &opaque);

	opaque = 31ULL;
	cdata_set_rtraverse(set, &rtrav_u64, &opaque);

	rv = cdata_set_clear(set);
	assert(cdata_set_size(set) == 0);
	assert(cdata_set_empty(set) == true);

	rv = cdata_set_destroy(set);
	assert(rv == CDATA_SUCCESS);

	return 0;
}

int test_basics(){

	int rv;

	void* ptr_not_null = (void*)0x123;

	//Create
	set = cdata_set_create(sizeof(int));
	assert(set != NULL);

	assert(cdata_set_size(set) == 0);
	assert(cdata_set_empty(set) == true);

	//Try all APIs with a NULL set/key/val
	assert(cdata_set_size(NULL) == 0);
	assert(cdata_set_empty(NULL) == false);
	rv = cdata_set_destroy(NULL);
	assert(rv == CDATA_E_INVALID);

	rv = cdata_set_traverse(NULL, ptr_not_null, NULL);
	assert(rv == CDATA_E_INVALID);
	rv = cdata_set_traverse(set, NULL, NULL);
	assert(rv == CDATA_E_INVALID);
	rv = cdata_set_rtraverse(NULL, ptr_not_null, NULL);
	assert(rv == CDATA_E_INVALID);
	rv = cdata_set_rtraverse(set, NULL, NULL);
	assert(rv == CDATA_E_INVALID);

	rv = cdata_set_insert(NULL, ptr_not_null);
	assert(rv == CDATA_E_INVALID);
	rv = cdata_set_insert(set, NULL);
	assert(rv == CDATA_E_INVALID);
	rv = cdata_set_erase(NULL, ptr_not_null);
	assert(rv == CDATA_E_INVALID);
	rv = cdata_set_erase(set, NULL);
	assert(rv == CDATA_E_INVALID);
	assert(cdata_set_find(NULL, ptr_not_null) == false);
	assert(cdata_set_find(set, NULL) == false);

	//Now destroy
	rv = cdata_set_destroy(set);
	assert(rv == CDATA_SUCCESS);

	//Create with valid and invalid
	set = cdata_set_create(256);
	assert(set != NULL);
	rv = cdata_set_destroy(set);
	assert(rv == CDATA_SUCCESS);
	set = cdata_set_create(257);
	assert(set == NULL);

	return 0;
}

//
// Key is not complete
//
//69byte type
typedef struct{
	uint8_t front[38];
	uint8_t mid;
	uint8_t back[30];
} __attribute__((packed)) test_u552_t;

void trav_u552(const cdata_set_t* s, const void* k, void* o){
	assert(o == &opaque);
	assert(set == s);
	test_u552_t key = *(test_u552_t*)k;
	assert(opaque == key.mid);
	opaque++;
}

void rtrav_u552(const cdata_set_t* s, const void* k, void* o){
	assert(o == &opaque);
	assert(set == s);
	test_u552_t key = *(test_u552_t*)k;
	assert(opaque == key.mid);
	opaque--;
}

int test_u552_insert_removal_traverse(){

	int i, rv;
	test_u552_t key = {0};

	set = cdata_set_create(sizeof(key));
	assert(set != NULL);

	assert(cdata_set_size(set) == 0);
	assert(cdata_set_empty(set) == true);

	//Add one key & get
	key.mid = 0;
	rv = cdata_set_insert(set, &key);
	assert(rv == CDATA_SUCCESS);

	assert(cdata_set_size(set) == 1);
	assert(cdata_set_empty(set) == false);

	assert(cdata_set_find(set, &key) == true);
	assert(key.mid == 0); //Should never pollute

	//Find an invalid value
	key.mid = 1;
	assert(cdata_set_find(set, &key) == false);

	//Trying to add the same key should return E_EXISTS, &repeat query
	key.mid = 0;
	rv = cdata_set_insert(set, &key);
	assert(rv == CDATA_E_EXISTS);

	assert(cdata_set_find(set, &key) == true);
	assert(key.mid == 0); //Should never pollute

	//Erase first an invalid
	key.mid = 1;
	rv = cdata_set_erase(set, &key);
	assert(rv == CDATA_E_NOT_FOUND);

	key.mid = 0;
	rv = cdata_set_erase(set, &key);
	assert(rv == CDATA_SUCCESS);

	assert(cdata_set_find(set, &key) == false);

	//Now add all objects
	for(i=0;i<32;++i){
		key.mid = i;
		rv = cdata_set_insert(set, &key);
		assert(rv == CDATA_SUCCESS);
	}

	assert(cdata_set_size(set) == 32);
	assert(cdata_set_empty(set) == false);

	key.mid = 22;
	assert(cdata_set_find(set, &key) == true);
	assert(key.mid == 22); //Should never pollute

	//Traverse
	opaque = 0ULL;
	cdata_set_traverse(set, &trav_u552, &opaque);

	opaque = 31ULL;
	cdata_set_rtraverse(set, &rtrav_u552, &opaque);

	rv = cdata_set_clear(set);
	assert(cdata_set_size(set) == 0);
	assert(cdata_set_empty(set) == true);

	rv = cdata_set_destroy(set);
	assert(rv == CDATA_SUCCESS);

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

	//Add your test here, and return a code appropriately...
	return rv == 0? EXIT_SUCCESS : EXIT_FAILURE;
}
