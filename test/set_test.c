#include <stdlib.h>

#include "cdata/set.h"
#include "common.h"
#include <string.h>
#include "u552.h"

//Fwd decl
CDATA_SET_CUSTOM_TYPE_DECL(test_u552_t);

static uint64_t opaque = 0ULL;
static cdata_set_t* set = NULL;

void trav_u64(const cdata_set_t* s, const void* k, void* o){
	TEST_ASSERT(o == &opaque);
	TEST_ASSERT(set == s);
	uint64_t key = *(uint64_t*)k;
	TEST_ASSERT(opaque == key);
	opaque++;
}

void rtrav_u64(const cdata_set_t* s, const void* k, void* o){
	TEST_ASSERT(o == &opaque);
	TEST_ASSERT(set == s);
	uint64_t key = *(uint64_t*)k;
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

	set = cdata_set_create(sizeof(key));
	TEST_ASSERT(set != NULL);

	TEST_ASSERT(cdata_set_size(set) == 0);
	TEST_ASSERT(cdata_set_empty(set) == true);

	//Add one key & get
	key = 0;
	rv = cdata_set_insert(set, &key);
	TEST_ASSERT(rv == CDATA_SUCCESS);

	TEST_ASSERT(cdata_set_size(set) == 1);
	TEST_ASSERT(cdata_set_empty(set) == false);

	TEST_ASSERT(cdata_set_find(set, &key) == true);
	TEST_ASSERT(key == 0); //Should never pollute

	//Find an invalid value
	key = 1;
	TEST_ASSERT(cdata_set_find(set, &key) == false);

	//Trying to add the same key should return E_EXISTS, &repeat query
	key = 0;
	rv = cdata_set_insert(set, &key);
	TEST_ASSERT(rv == CDATA_E_EXISTS);

	TEST_ASSERT(cdata_set_find(set, &key) == true);
	TEST_ASSERT(key == 0); //Should never pollute

	//Erase first an invalid
	key = 1;
	rv = cdata_set_erase(set, &key);
	TEST_ASSERT(rv == CDATA_E_NOT_FOUND);

	key = 0;
	rv = cdata_set_erase(set, &key);
	TEST_ASSERT(rv == CDATA_SUCCESS);

	TEST_ASSERT(cdata_set_find(set, &key) == false);

	//Now add all objects
	for(i=0;i<32;++i){
		key = i;
		rv = cdata_set_insert(set, &key);
		TEST_ASSERT(rv == CDATA_SUCCESS);
	}

	TEST_ASSERT(cdata_set_size(set) == 32);
	TEST_ASSERT(cdata_set_empty(set) == false);

	key = 22;
	TEST_ASSERT(cdata_set_find(set, &key) == true);
	TEST_ASSERT(key == 22); //Should never pollute

	rv = cdata_set_clear(set);
	TEST_ASSERT(cdata_set_size(set) == 0);
	TEST_ASSERT(cdata_set_empty(set) == true);

	rv = cdata_set_destroy(set);
	TEST_ASSERT(rv == CDATA_SUCCESS);

	return 0;
}

//16
int test_u16_insert_removal(){

	int i, rv;
	uint16_t key;

	set = cdata_set_create(sizeof(key));
	TEST_ASSERT(set != NULL);

	TEST_ASSERT(cdata_set_size(set) == 0);
	TEST_ASSERT(cdata_set_empty(set) == true);

	//Add one key & get
	key = 0;
	rv = cdata_set_insert(set, &key);
	TEST_ASSERT(rv == CDATA_SUCCESS);

	TEST_ASSERT(cdata_set_size(set) == 1);
	TEST_ASSERT(cdata_set_empty(set) == false);

	TEST_ASSERT(cdata_set_find(set, &key) == true);
	TEST_ASSERT(key == 0); //Should never pollute

	//Find an invalid value
	key = 1;
	TEST_ASSERT(cdata_set_find(set, &key) == false);

	//Trying to add the same key should return E_EXISTS, &repeat query
	key = 0;
	rv = cdata_set_insert(set, &key);
	TEST_ASSERT(rv == CDATA_E_EXISTS);

	TEST_ASSERT(cdata_set_find(set, &key) == true);
	TEST_ASSERT(key == 0); //Should never pollute

	//Erase first an invalid
	key = 1;
	rv = cdata_set_erase(set, &key);
	TEST_ASSERT(rv == CDATA_E_NOT_FOUND);

	key = 0;
	rv = cdata_set_erase(set, &key);
	TEST_ASSERT(rv == CDATA_SUCCESS);

	TEST_ASSERT(cdata_set_find(set, &key) == false);

	//Now add all objects
	for(i=0;i<32;++i){
		key = i;
		rv = cdata_set_insert(set, &key);
		TEST_ASSERT(rv == CDATA_SUCCESS);
	}

	TEST_ASSERT(cdata_set_size(set) == 32);
	TEST_ASSERT(cdata_set_empty(set) == false);

	key = 22;
	TEST_ASSERT(cdata_set_find(set, &key) == true);
	TEST_ASSERT(key == 22); //Should never pollute

	rv = cdata_set_clear(set);
	TEST_ASSERT(cdata_set_size(set) == 0);
	TEST_ASSERT(cdata_set_empty(set) == true);

	rv = cdata_set_destroy(set);
	TEST_ASSERT(rv == CDATA_SUCCESS);

	return 0;
}

//32
int test_u32_insert_removal(){

	int i, rv;
	uint32_t key;

	set = cdata_set_create(sizeof(key));
	TEST_ASSERT(set != NULL);

	TEST_ASSERT(cdata_set_size(set) == 0);
	TEST_ASSERT(cdata_set_empty(set) == true);

	//Add one key & get
	key = 0;
	rv = cdata_set_insert(set, &key);
	TEST_ASSERT(rv == CDATA_SUCCESS);

	TEST_ASSERT(cdata_set_size(set) == 1);
	TEST_ASSERT(cdata_set_empty(set) == false);

	TEST_ASSERT(cdata_set_find(set, &key) == true);
	TEST_ASSERT(key == 0); //Should never pollute

	//Find an invalid value
	key = 1;
	TEST_ASSERT(cdata_set_find(set, &key) == false);

	//Trying to add the same key should return E_EXISTS, &repeat query
	key = 0;
	rv = cdata_set_insert(set, &key);
	TEST_ASSERT(rv == CDATA_E_EXISTS);

	TEST_ASSERT(cdata_set_find(set, &key) == true);
	TEST_ASSERT(key == 0); //Should never pollute

	//Erase first an invalid
	key = 1;
	rv = cdata_set_erase(set, &key);
	TEST_ASSERT(rv == CDATA_E_NOT_FOUND);

	key = 0;
	rv = cdata_set_erase(set, &key);
	TEST_ASSERT(rv == CDATA_SUCCESS);

	TEST_ASSERT(cdata_set_find(set, &key) == false);

	//Now add all objects
	for(i=0;i<32;++i){
		key = i;
		rv = cdata_set_insert(set, &key);
		TEST_ASSERT(rv == CDATA_SUCCESS);
	}

	TEST_ASSERT(cdata_set_size(set) == 32);
	TEST_ASSERT(cdata_set_empty(set) == false);

	key = 22;
	TEST_ASSERT(cdata_set_find(set, &key) == true);
	TEST_ASSERT(key == 22); //Should never pollute

	rv = cdata_set_clear(set);
	TEST_ASSERT(cdata_set_size(set) == 0);
	TEST_ASSERT(cdata_set_empty(set) == true);

	rv = cdata_set_destroy(set);
	TEST_ASSERT(rv == CDATA_SUCCESS);

	return 0;
}

//64
int test_u64_insert_removal_traverse(){

	int i, rv;
	uint64_t key;

	set = cdata_set_create(sizeof(key));
	TEST_ASSERT(set != NULL);

	TEST_ASSERT(cdata_set_size(set) == 0);
	TEST_ASSERT(cdata_set_empty(set) == true);

	//Add one key & get
	key = 0ULL;
	rv = cdata_set_insert(set, &key);
	TEST_ASSERT(rv == CDATA_SUCCESS);

	TEST_ASSERT(cdata_set_size(set) == 1);
	TEST_ASSERT(cdata_set_empty(set) == false);

	TEST_ASSERT(cdata_set_find(set, &key) == true);
	TEST_ASSERT(key == 0ULL); //Should never pollute

	//Find an invalid value
	key = 1ULL;
	TEST_ASSERT(cdata_set_find(set, &key) == false);

	//Trying to add the same key should return E_EXISTS, &repeat query
	key = 0ULL;
	rv = cdata_set_insert(set, &key);
	TEST_ASSERT(rv == CDATA_E_EXISTS);

	TEST_ASSERT(cdata_set_find(set, &key) == true);
	TEST_ASSERT(key == 0ULL); //Should never pollute

	//Erase first an invalid
	key = 1ULL;
	rv = cdata_set_erase(set, &key);
	TEST_ASSERT(rv == CDATA_E_NOT_FOUND);

	key = 0ULL;
	rv = cdata_set_erase(set, &key);
	TEST_ASSERT(rv == CDATA_SUCCESS);

	TEST_ASSERT(cdata_set_find(set, &key) == false);

	//Now add all objects
	for(i=0;i<32;++i){
		key = i;
		rv = cdata_set_insert(set, &key);
		TEST_ASSERT(rv == CDATA_SUCCESS);
	}

	TEST_ASSERT(cdata_set_size(set) == 32);
	TEST_ASSERT(cdata_set_empty(set) == false);

	key = 22ULL;
	TEST_ASSERT(cdata_set_find(set, &key) == true);
	TEST_ASSERT(key == 22ULL); //Should never pollute

	//Traverse
	opaque = 0ULL;
	cdata_set_traverse(set, &trav_u64, &opaque);

	opaque = 31ULL;
	cdata_set_rtraverse(set, &rtrav_u64, &opaque);

	rv = cdata_set_clear(set);
	TEST_ASSERT(cdata_set_size(set) == 0);
	TEST_ASSERT(cdata_set_empty(set) == true);

	rv = cdata_set_destroy(set);
	TEST_ASSERT(rv == CDATA_SUCCESS);

	return 0;
}

int test_basics(){

	int rv;

	void* ptr_not_null = (void*)0x123;

	//Create
	set = cdata_set_create(sizeof(int));
	TEST_ASSERT(set != NULL);

	TEST_ASSERT(cdata_set_size(set) == 0);
	TEST_ASSERT(cdata_set_empty(set) == true);

	//Try all APIs with a NULL set/key/val
	TEST_ASSERT(cdata_set_size(NULL) == 0);
	TEST_ASSERT(cdata_set_empty(NULL) == false);
	rv = cdata_set_destroy(NULL);
	TEST_ASSERT(rv == CDATA_E_INVALID);

	rv = cdata_set_traverse(NULL, ptr_not_null, NULL);
	TEST_ASSERT(rv == CDATA_E_INVALID);
	rv = cdata_set_traverse(set, NULL, NULL);
	TEST_ASSERT(rv == CDATA_E_INVALID);
	rv = cdata_set_rtraverse(NULL, ptr_not_null, NULL);
	TEST_ASSERT(rv == CDATA_E_INVALID);
	rv = cdata_set_rtraverse(set, NULL, NULL);
	TEST_ASSERT(rv == CDATA_E_INVALID);

	rv = cdata_set_insert(NULL, ptr_not_null);
	TEST_ASSERT(rv == CDATA_E_INVALID);
	rv = cdata_set_insert(set, NULL);
	TEST_ASSERT(rv == CDATA_E_INVALID);
	rv = cdata_set_erase(NULL, ptr_not_null);
	TEST_ASSERT(rv == CDATA_E_INVALID);
	rv = cdata_set_erase(set, NULL);
	TEST_ASSERT(rv == CDATA_E_INVALID);
	TEST_ASSERT(cdata_set_find(NULL, ptr_not_null) == false);
	TEST_ASSERT(cdata_set_find(set, NULL) == false);

	//Now destroy
	rv = cdata_set_destroy(set);
	TEST_ASSERT(rv == CDATA_SUCCESS);

	//Create with valid and invalid
	set = cdata_set_create(256);
	TEST_ASSERT(set != NULL);
	rv = cdata_set_destroy(set);
	TEST_ASSERT(rv == CDATA_SUCCESS);
	set = cdata_set_create(257);
	TEST_ASSERT(set == NULL);

	return 0;
}

//
// Key is not complete
//
void trav_u552(const cdata_set_t* s, const void* k, void* o){
	TEST_ASSERT(o == &opaque);
	TEST_ASSERT(set == s);
	test_u552_t key = *(test_u552_t*)k;
	TEST_ASSERT(opaque == key.mid);
	opaque++;
}

void rtrav_u552(const cdata_set_t* s, const void* k, void* o){
	TEST_ASSERT(o == &opaque);
	TEST_ASSERT(set == s);
	test_u552_t key = *(test_u552_t*)k;
	TEST_ASSERT(opaque == key.mid);
	opaque--;
}

int _test_u552_insert_removal_traverse(){

	int i, rv;
	test_u552_t key;
	memset(&key, 0, sizeof(key));

	TEST_ASSERT(cdata_set_size(set) == 0);
	TEST_ASSERT(cdata_set_empty(set) == true);

	//Add one key & get
	key.mid = 0;
	rv = cdata_set_insert(set, &key);
	TEST_ASSERT(rv == CDATA_SUCCESS);

	TEST_ASSERT(cdata_set_size(set) == 1);
	TEST_ASSERT(cdata_set_empty(set) == false);

	TEST_ASSERT(cdata_set_find(set, &key) == true);
	TEST_ASSERT(key.mid == 0); //Should never pollute

	//Find an invalid value
	key.mid = 1;
	TEST_ASSERT(cdata_set_find(set, &key) == false);

	//Trying to add the same key should return E_EXISTS, &repeat query
	key.mid = 0;
	rv = cdata_set_insert(set, &key);
	TEST_ASSERT(rv == CDATA_E_EXISTS);

	TEST_ASSERT(cdata_set_find(set, &key) == true);
	TEST_ASSERT(key.mid == 0); //Should never pollute

	//Erase first an invalid
	key.mid = 1;
	rv = cdata_set_erase(set, &key);
	TEST_ASSERT(rv == CDATA_E_NOT_FOUND);

	key.mid = 0;
	rv = cdata_set_erase(set, &key);
	TEST_ASSERT(rv == CDATA_SUCCESS);

	TEST_ASSERT(cdata_set_find(set, &key) == false);

	//Now add all objects
	for(i=0;i<32;++i){
		key.mid = i;
		rv = cdata_set_insert(set, &key);
		TEST_ASSERT(rv == CDATA_SUCCESS);
	}

	TEST_ASSERT(cdata_set_size(set) == 32);
	TEST_ASSERT(cdata_set_empty(set) == false);

	key.mid = 22;
	TEST_ASSERT(cdata_set_find(set, &key) == true);
	TEST_ASSERT(key.mid == 22); //Should never pollute

	//Traverse
	opaque = 0ULL;
	cdata_set_traverse(set, &trav_u552, &opaque);

	opaque = 31ULL;
	cdata_set_rtraverse(set, &rtrav_u552, &opaque);

	rv = cdata_set_clear(set);
	TEST_ASSERT(cdata_set_size(set) == 0);
	TEST_ASSERT(cdata_set_empty(set) == true);

	rv = cdata_set_destroy(set);
	TEST_ASSERT(rv == CDATA_SUCCESS);

	return 0;
}

int test_u552_insert_removal_traverse(){
	set = cdata_set_create(sizeof(test_u552_t));
	TEST_ASSERT(set != NULL);

	return _test_u552_insert_removal_traverse();
}

int test_u552_insert_removal_traverse_custom(){
	set = cdata_set_create_custom(test_u552_t);
	TEST_ASSERT(set != NULL);

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

	//Custom type
	rv |= test_u552_insert_removal_traverse_custom();

	//Add your test here, and return a code appropriately...
	return rv == 0? EXIT_SUCCESS : EXIT_FAILURE;
}
