#include <stdlib.h>

#include "cdata/list.h"
#include <assert.h>
#include <string.h>
#include "u552.h"


static uint64_t opaque = 0ULL;
static cdata_list_t* list = NULL;

//{1, 0, 0, 0, 0, 0, 0}
void trav_u64(const cdata_list_t* s, const void* k, void* o){
	assert(o == &opaque);
	assert(list == s);
	uint64_t key = *(uint64_t*)k;
	switch(opaque){
		case 0:
			assert(key == 1ULL);
			break;
		case 1:
		case 2:
		case 3:
		case 4:
		case 5:
			assert(key == 0ULL);
			break;
		default:
			assert(0);
			break;
	}

	opaque++;
}

void rtrav_u64(const cdata_list_t* s, const void* k, void* o){
	assert(o == &opaque);
	assert(list == s);
	uint64_t key = *(uint64_t*)k;
	switch(opaque){
		case 0:
		case 1:
		case 2:
		case 3:
		case 4:
			assert(key == 0ULL);
			break;

		case 5:
			assert(key == 1ULL);
			break;
		default:
			assert(0);
			break;
	}

	opaque++;
}


//
// Aligned types
//

//8
int test_u8_insert_removal(){

	int i, rv;
	uint8_t key;

	list = cdata_list_create(sizeof(key));
	assert(list != NULL);

	assert(cdata_list_size(list) == 0);
	assert(cdata_list_empty(list) == true);

	//Add one key & get
	key = 0;
	rv = cdata_list_insert(list, &key, 0);
	assert(rv == CDATA_SUCCESS);

	assert(cdata_list_size(list) == 1);
	assert(cdata_list_empty(list) == false);

	rv = cdata_list_get(list, 0, &key);
	assert(rv == CDATA_SUCCESS);
	assert(key == 0);

	//Get a value > size shall fail
	rv = cdata_list_get(list, 1, &key);
	assert(rv == CDATA_E_NOT_FOUND);
	rv = cdata_list_get(list, 222, &key);
	assert(rv == CDATA_E_NOT_FOUND);

	//Add 1 after
	key = 1;
	rv = cdata_list_insert(list, &key, 1);
	assert(rv == CDATA_SUCCESS);
	rv = cdata_list_get(list, 0, &key);
	assert(rv == CDATA_SUCCESS);
	assert(key == 0);
	rv = cdata_list_get(list, 1, &key);
	assert(rv == CDATA_SUCCESS);
	assert(key == 1);
	rv = cdata_list_get(list, 222, &key);
	assert(rv == CDATA_E_NOT_FOUND);
	assert(key == 1);

	//PUSH tests resulting list should be {9, 0, 1, 7}
	key = 7;
	rv = cdata_list_push_back(list, &key);
	assert(rv == CDATA_SUCCESS);
	assert(key == 7);
	key = 9;
	rv = cdata_list_push_front(list, &key);
	assert(rv == CDATA_SUCCESS);
	rv = cdata_list_get(list, 0, &key);
	assert(rv == CDATA_SUCCESS);
	assert(key == 9);
	rv = cdata_list_get(list, 1, &key);
	assert(rv == CDATA_SUCCESS);
	assert(key == 0);
	rv = cdata_list_get(list, 2, &key);
	assert(rv == CDATA_SUCCESS);
	assert(key == 1);
	rv = cdata_list_get(list, 3, &key);
	assert(rv == CDATA_SUCCESS);
	assert(key == 7);
	rv = cdata_list_get(list, 4, &key);
	assert(rv == CDATA_E_NOT_FOUND);
	rv = cdata_list_get(list, 222, &key);
	assert(rv == CDATA_E_NOT_FOUND);
	assert(key == 7);
	assert(cdata_list_size(list) == 4);
	assert(cdata_list_empty(list) == false);

	//Erase {9, 1, 7}
	rv = cdata_list_erase(list, 1);
	assert(rv == CDATA_SUCCESS);
	rv = cdata_list_get(list, 0, &key);
	assert(rv == CDATA_SUCCESS);
	assert(key == 9);
	rv = cdata_list_get(list, 1, &key);
	assert(rv == CDATA_SUCCESS);
	assert(key == 1);
	rv = cdata_list_get(list, 2, &key);
	assert(rv == CDATA_SUCCESS);
	assert(key == 7);
	rv = cdata_list_get(list, 3, &key);
	assert(rv == CDATA_E_NOT_FOUND);
	rv = cdata_list_get(list, 222, &key);
	assert(rv == CDATA_E_NOT_FOUND);
	assert(key == 7);
	assert(cdata_list_size(list) == 3);
	assert(cdata_list_empty(list) == false);

	//POP front {1,7}
	rv = cdata_list_pop_front(list);
	assert(rv == CDATA_SUCCESS);
	rv = cdata_list_get(list, 0, &key);
	assert(rv == CDATA_SUCCESS);
	assert(key == 1);
	rv = cdata_list_get(list, 1, &key);
	assert(rv == CDATA_SUCCESS);
	assert(key == 7);
	rv = cdata_list_get(list, 2, &key);
	assert(rv == CDATA_E_NOT_FOUND);
	rv = cdata_list_get(list, 222, &key);
	assert(rv == CDATA_E_NOT_FOUND);
	assert(key == 7);
	assert(cdata_list_size(list) == 2);
	assert(cdata_list_empty(list) == false);


	//POP back {1}
	rv = cdata_list_pop_back(list);
	assert(rv == CDATA_SUCCESS);
	rv = cdata_list_get(list, 0, &key);
	assert(rv == CDATA_SUCCESS);
	assert(key == 1);
	rv = cdata_list_get(list, 2, &key);
	assert(rv == CDATA_E_NOT_FOUND);
	rv = cdata_list_get(list, 222, &key);
	assert(rv == CDATA_E_NOT_FOUND);
	assert(key == 1);
	assert(cdata_list_size(list) == 1);
	assert(cdata_list_empty(list) == false);

	//Add many 0s {1, 0, 0, 0, 0, 0}
	for(i=0;i<5; ++i){
		key = 0;
		rv = cdata_list_push_back(list, &key);
		assert(rv == CDATA_SUCCESS);
		assert(key == 0);
	}
	assert(cdata_list_size(list) == 6);
	assert(cdata_list_empty(list) == false);

	rv = cdata_list_get(list, 0, &key);
	assert(rv == CDATA_SUCCESS);
	assert(key == 1);
	rv = cdata_list_get(list, 1, &key);
	assert(rv == CDATA_SUCCESS);
	assert(key == 0);
	rv = cdata_list_get(list, 5, &key);
	assert(rv == CDATA_SUCCESS);
	assert(key == 0);
	rv = cdata_list_get(list, 6, &key);
	assert(rv == CDATA_E_NOT_FOUND);
	assert(key == 0);

	//Sort {0, 0, 0, 0, 0, 1}
	rv = cdata_list_sort(list);
	assert(rv == CDATA_SUCCESS);
	rv = cdata_list_get(list, 0, &key);
	assert(rv == CDATA_SUCCESS);
	assert(key == 0);
	rv = cdata_list_get(list, 1, &key);
	assert(rv == CDATA_SUCCESS);
	assert(key == 0);
	rv = cdata_list_get(list, 5, &key);
	assert(rv == CDATA_SUCCESS);
	assert(key == 1);
	rv = cdata_list_get(list, 6, &key);
	assert(rv == CDATA_E_NOT_FOUND);
	assert(key == 1);

	//Reverse {1, 0, 0, 0, 0, 0}
	rv = cdata_list_reverse(list);
	rv = cdata_list_get(list, 0, &key);
	assert(rv == CDATA_SUCCESS);
	assert(key == 1);
	rv = cdata_list_get(list, 1, &key);
	assert(rv == CDATA_SUCCESS);
	assert(key == 0);
	rv = cdata_list_get(list, 5, &key);
	assert(rv == CDATA_SUCCESS);
	assert(key == 0);
	rv = cdata_list_get(list, 6, &key);
	assert(rv == CDATA_E_NOT_FOUND);
	assert(key == 0);

	//Unique {1, 0}
	rv = cdata_list_unique(list);
	assert(rv == CDATA_SUCCESS);
	assert(cdata_list_size(list) == 2);
	assert(cdata_list_empty(list) == false);
	rv = cdata_list_get(list, 0, &key);
	assert(rv == CDATA_SUCCESS);
	assert(key == 1);
	rv = cdata_list_get(list, 1, &key);
	assert(rv == CDATA_SUCCESS);
	assert(key == 0);
	rv = cdata_list_get(list, 2, &key);
	assert(rv == CDATA_E_NOT_FOUND);
	assert(key == 0);
	assert(cdata_list_size(list) == 2);
	assert(cdata_list_empty(list) == false);

	//Insert 5s {5, 1, 0, 5}
	key = 5;
	rv = cdata_list_insert(list, &key, 0);
	rv |= cdata_list_insert(list, &key, 4);
	assert(rv == CDATA_SUCCESS);
	rv = cdata_list_get(list, 0, &key);
	assert(rv == CDATA_SUCCESS);
	assert(key == 5);
	rv = cdata_list_get(list, 1, &key);
	assert(rv == CDATA_SUCCESS);
	assert(key == 1);
	rv = cdata_list_get(list, 2, &key);
	assert(rv == CDATA_SUCCESS);
	assert(key == 0);
	rv = cdata_list_get(list, 3, &key);
	assert(rv == CDATA_SUCCESS);
	assert(key == 5);
	assert(cdata_list_size(list) == 4);
	assert(cdata_list_empty(list) == false);

	//Remove API {1,0}
	rv = cdata_list_remove(list, &key);
	assert(rv == CDATA_SUCCESS);
	assert(cdata_list_size(list) == 2);
	assert(cdata_list_empty(list) == false);
	rv = cdata_list_get(list, 0, &key);
	assert(rv == CDATA_SUCCESS);
	assert(key == 1);
	rv = cdata_list_get(list, 1, &key);
	assert(rv == CDATA_SUCCESS);
	assert(key == 0);
	rv = cdata_list_get(list, 2, &key);
	assert(rv == CDATA_E_NOT_FOUND);
	assert(key == 0);

	rv = cdata_list_clear(list);
	assert(rv == CDATA_SUCCESS);
	assert(cdata_list_size(list) == 0);
	assert(cdata_list_empty(list) == true);

	rv = cdata_list_destroy(list);
	assert(rv == CDATA_SUCCESS);

	return 0;
}

//16
int test_u16_insert_removal(){

	int i, rv;
	uint16_t key;

	list = cdata_list_create(sizeof(key));
	assert(list != NULL);

	assert(cdata_list_size(list) == 0);
	assert(cdata_list_empty(list) == true);

	//Add one key & get
	key = 0;
	rv = cdata_list_insert(list, &key, 0);
	assert(rv == CDATA_SUCCESS);

	assert(cdata_list_size(list) == 1);
	assert(cdata_list_empty(list) == false);

	rv = cdata_list_get(list, 0, &key);
	assert(rv == CDATA_SUCCESS);
	assert(key == 0);

	//Get a value > size shall fail
	rv = cdata_list_get(list, 1, &key);
	assert(rv == CDATA_E_NOT_FOUND);
	rv = cdata_list_get(list, 222, &key);
	assert(rv == CDATA_E_NOT_FOUND);

	//Add 1 after
	key = 1;
	rv = cdata_list_insert(list, &key, 1);
	assert(rv == CDATA_SUCCESS);
	rv = cdata_list_get(list, 0, &key);
	assert(rv == CDATA_SUCCESS);
	assert(key == 0);
	rv = cdata_list_get(list, 1, &key);
	assert(rv == CDATA_SUCCESS);
	assert(key == 1);
	rv = cdata_list_get(list, 222, &key);
	assert(rv == CDATA_E_NOT_FOUND);
	assert(key == 1);

	//PUSH tests resulting list should be {9, 0, 1, 7}
	key = 7;
	rv = cdata_list_push_back(list, &key);
	assert(rv == CDATA_SUCCESS);
	assert(key == 7);
	key = 9;
	rv = cdata_list_push_front(list, &key);
	assert(rv == CDATA_SUCCESS);
	rv = cdata_list_get(list, 0, &key);
	assert(rv == CDATA_SUCCESS);
	assert(key == 9);
	rv = cdata_list_get(list, 1, &key);
	assert(rv == CDATA_SUCCESS);
	assert(key == 0);
	rv = cdata_list_get(list, 2, &key);
	assert(rv == CDATA_SUCCESS);
	assert(key == 1);
	rv = cdata_list_get(list, 3, &key);
	assert(rv == CDATA_SUCCESS);
	assert(key == 7);
	rv = cdata_list_get(list, 4, &key);
	assert(rv == CDATA_E_NOT_FOUND);
	rv = cdata_list_get(list, 222, &key);
	assert(rv == CDATA_E_NOT_FOUND);
	assert(key == 7);
	assert(cdata_list_size(list) == 4);
	assert(cdata_list_empty(list) == false);

	//Erase {9, 1, 7}
	rv = cdata_list_erase(list, 1);
	assert(rv == CDATA_SUCCESS);
	rv = cdata_list_get(list, 0, &key);
	assert(rv == CDATA_SUCCESS);
	assert(key == 9);
	rv = cdata_list_get(list, 1, &key);
	assert(rv == CDATA_SUCCESS);
	assert(key == 1);
	rv = cdata_list_get(list, 2, &key);
	assert(rv == CDATA_SUCCESS);
	assert(key == 7);
	rv = cdata_list_get(list, 3, &key);
	assert(rv == CDATA_E_NOT_FOUND);
	rv = cdata_list_get(list, 222, &key);
	assert(rv == CDATA_E_NOT_FOUND);
	assert(key == 7);
	assert(cdata_list_size(list) == 3);
	assert(cdata_list_empty(list) == false);

	//POP front {1,7}
	rv = cdata_list_pop_front(list);
	assert(rv == CDATA_SUCCESS);
	rv = cdata_list_get(list, 0, &key);
	assert(rv == CDATA_SUCCESS);
	assert(key == 1);
	rv = cdata_list_get(list, 1, &key);
	assert(rv == CDATA_SUCCESS);
	assert(key == 7);
	rv = cdata_list_get(list, 2, &key);
	assert(rv == CDATA_E_NOT_FOUND);
	rv = cdata_list_get(list, 222, &key);
	assert(rv == CDATA_E_NOT_FOUND);
	assert(key == 7);
	assert(cdata_list_size(list) == 2);
	assert(cdata_list_empty(list) == false);


	//POP back {1}
	rv = cdata_list_pop_back(list);
	assert(rv == CDATA_SUCCESS);
	rv = cdata_list_get(list, 0, &key);
	assert(rv == CDATA_SUCCESS);
	assert(key == 1);
	rv = cdata_list_get(list, 2, &key);
	assert(rv == CDATA_E_NOT_FOUND);
	rv = cdata_list_get(list, 222, &key);
	assert(rv == CDATA_E_NOT_FOUND);
	assert(key == 1);
	assert(cdata_list_size(list) == 1);
	assert(cdata_list_empty(list) == false);

	//Add many 0s {1, 0, 0, 0, 0, 0}
	for(i=0;i<5; ++i){
		key = 0;
		rv = cdata_list_push_back(list, &key);
		assert(rv == CDATA_SUCCESS);
		assert(key == 0);
	}
	assert(cdata_list_size(list) == 6);
	assert(cdata_list_empty(list) == false);

	rv = cdata_list_get(list, 0, &key);
	assert(rv == CDATA_SUCCESS);
	assert(key == 1);
	rv = cdata_list_get(list, 1, &key);
	assert(rv == CDATA_SUCCESS);
	assert(key == 0);
	rv = cdata_list_get(list, 5, &key);
	assert(rv == CDATA_SUCCESS);
	assert(key == 0);
	rv = cdata_list_get(list, 6, &key);
	assert(rv == CDATA_E_NOT_FOUND);
	assert(key == 0);

	//Sort {0, 0, 0, 0, 0, 1}
	rv = cdata_list_sort(list);
	assert(rv == CDATA_SUCCESS);
	rv = cdata_list_get(list, 0, &key);
	assert(rv == CDATA_SUCCESS);
	assert(key == 0);
	rv = cdata_list_get(list, 1, &key);
	assert(rv == CDATA_SUCCESS);
	assert(key == 0);
	rv = cdata_list_get(list, 5, &key);
	assert(rv == CDATA_SUCCESS);
	assert(key == 1);
	rv = cdata_list_get(list, 6, &key);
	assert(rv == CDATA_E_NOT_FOUND);
	assert(key == 1);

	//Reverse {1, 0, 0, 0, 0, 0}
	rv = cdata_list_reverse(list);
	rv = cdata_list_get(list, 0, &key);
	assert(rv == CDATA_SUCCESS);
	assert(key == 1);
	rv = cdata_list_get(list, 1, &key);
	assert(rv == CDATA_SUCCESS);
	assert(key == 0);
	rv = cdata_list_get(list, 5, &key);
	assert(rv == CDATA_SUCCESS);
	assert(key == 0);
	rv = cdata_list_get(list, 6, &key);
	assert(rv == CDATA_E_NOT_FOUND);
	assert(key == 0);

	//Unique {1, 0}
	rv = cdata_list_unique(list);
	assert(rv == CDATA_SUCCESS);
	assert(cdata_list_size(list) == 2);
	assert(cdata_list_empty(list) == false);
	rv = cdata_list_get(list, 0, &key);
	assert(rv == CDATA_SUCCESS);
	assert(key == 1);
	rv = cdata_list_get(list, 1, &key);
	assert(rv == CDATA_SUCCESS);
	assert(key == 0);
	rv = cdata_list_get(list, 2, &key);
	assert(rv == CDATA_E_NOT_FOUND);
	assert(key == 0);
	assert(cdata_list_size(list) == 2);
	assert(cdata_list_empty(list) == false);

	//Insert 5s {5, 1, 0, 5}
	key = 5;
	rv = cdata_list_insert(list, &key, 0);
	rv |= cdata_list_insert(list, &key, 4);
	assert(rv == CDATA_SUCCESS);
	rv = cdata_list_get(list, 0, &key);
	assert(rv == CDATA_SUCCESS);
	assert(key == 5);
	rv = cdata_list_get(list, 1, &key);
	assert(rv == CDATA_SUCCESS);
	assert(key == 1);
	rv = cdata_list_get(list, 2, &key);
	assert(rv == CDATA_SUCCESS);
	assert(key == 0);
	rv = cdata_list_get(list, 3, &key);
	assert(rv == CDATA_SUCCESS);
	assert(key == 5);
	assert(cdata_list_size(list) == 4);
	assert(cdata_list_empty(list) == false);

	//Remove API {1,0}
	rv = cdata_list_remove(list, &key);
	assert(rv == CDATA_SUCCESS);
	assert(cdata_list_size(list) == 2);
	assert(cdata_list_empty(list) == false);
	rv = cdata_list_get(list, 0, &key);
	assert(rv == CDATA_SUCCESS);
	assert(key == 1);
	rv = cdata_list_get(list, 1, &key);
	assert(rv == CDATA_SUCCESS);
	assert(key == 0);
	rv = cdata_list_get(list, 2, &key);
	assert(rv == CDATA_E_NOT_FOUND);
	assert(key == 0);

	rv = cdata_list_clear(list);
	assert(rv == CDATA_SUCCESS);
	assert(cdata_list_size(list) == 0);
	assert(cdata_list_empty(list) == true);

	rv = cdata_list_destroy(list);
	assert(rv == CDATA_SUCCESS);

	return 0;
}

//32
int test_u32_insert_removal(){

	int i, rv;
	uint32_t key;

	list = cdata_list_create(sizeof(key));
	assert(list != NULL);

	assert(cdata_list_size(list) == 0);
	assert(cdata_list_empty(list) == true);

	//Add one key & get
	key = 0;
	rv = cdata_list_insert(list, &key, 0);
	assert(rv == CDATA_SUCCESS);

	assert(cdata_list_size(list) == 1);
	assert(cdata_list_empty(list) == false);

	rv = cdata_list_get(list, 0, &key);
	assert(rv == CDATA_SUCCESS);
	assert(key == 0);

	//Get a value > size shall fail
	rv = cdata_list_get(list, 1, &key);
	assert(rv == CDATA_E_NOT_FOUND);
	rv = cdata_list_get(list, 222, &key);
	assert(rv == CDATA_E_NOT_FOUND);

	//Add 1 after
	key = 1;
	rv = cdata_list_insert(list, &key, 1);
	assert(rv == CDATA_SUCCESS);
	rv = cdata_list_get(list, 0, &key);
	assert(rv == CDATA_SUCCESS);
	assert(key == 0);
	rv = cdata_list_get(list, 1, &key);
	assert(rv == CDATA_SUCCESS);
	assert(key == 1);
	rv = cdata_list_get(list, 222, &key);
	assert(rv == CDATA_E_NOT_FOUND);
	assert(key == 1);

	//PUSH tests resulting list should be {9, 0, 1, 7}
	key = 7;
	rv = cdata_list_push_back(list, &key);
	assert(rv == CDATA_SUCCESS);
	assert(key == 7);
	key = 9;
	rv = cdata_list_push_front(list, &key);
	assert(rv == CDATA_SUCCESS);
	rv = cdata_list_get(list, 0, &key);
	assert(rv == CDATA_SUCCESS);
	assert(key == 9);
	rv = cdata_list_get(list, 1, &key);
	assert(rv == CDATA_SUCCESS);
	assert(key == 0);
	rv = cdata_list_get(list, 2, &key);
	assert(rv == CDATA_SUCCESS);
	assert(key == 1);
	rv = cdata_list_get(list, 3, &key);
	assert(rv == CDATA_SUCCESS);
	assert(key == 7);
	rv = cdata_list_get(list, 4, &key);
	assert(rv == CDATA_E_NOT_FOUND);
	rv = cdata_list_get(list, 222, &key);
	assert(rv == CDATA_E_NOT_FOUND);
	assert(key == 7);
	assert(cdata_list_size(list) == 4);
	assert(cdata_list_empty(list) == false);

	//Erase {9, 1, 7}
	rv = cdata_list_erase(list, 1);
	assert(rv == CDATA_SUCCESS);
	rv = cdata_list_get(list, 0, &key);
	assert(rv == CDATA_SUCCESS);
	assert(key == 9);
	rv = cdata_list_get(list, 1, &key);
	assert(rv == CDATA_SUCCESS);
	assert(key == 1);
	rv = cdata_list_get(list, 2, &key);
	assert(rv == CDATA_SUCCESS);
	assert(key == 7);
	rv = cdata_list_get(list, 3, &key);
	assert(rv == CDATA_E_NOT_FOUND);
	rv = cdata_list_get(list, 222, &key);
	assert(rv == CDATA_E_NOT_FOUND);
	assert(key == 7);
	assert(cdata_list_size(list) == 3);
	assert(cdata_list_empty(list) == false);

	//POP front {1,7}
	rv = cdata_list_pop_front(list);
	assert(rv == CDATA_SUCCESS);
	rv = cdata_list_get(list, 0, &key);
	assert(rv == CDATA_SUCCESS);
	assert(key == 1);
	rv = cdata_list_get(list, 1, &key);
	assert(rv == CDATA_SUCCESS);
	assert(key == 7);
	rv = cdata_list_get(list, 2, &key);
	assert(rv == CDATA_E_NOT_FOUND);
	rv = cdata_list_get(list, 222, &key);
	assert(rv == CDATA_E_NOT_FOUND);
	assert(key == 7);
	assert(cdata_list_size(list) == 2);
	assert(cdata_list_empty(list) == false);


	//POP back {1}
	rv = cdata_list_pop_back(list);
	assert(rv == CDATA_SUCCESS);
	rv = cdata_list_get(list, 0, &key);
	assert(rv == CDATA_SUCCESS);
	assert(key == 1);
	rv = cdata_list_get(list, 2, &key);
	assert(rv == CDATA_E_NOT_FOUND);
	rv = cdata_list_get(list, 222, &key);
	assert(rv == CDATA_E_NOT_FOUND);
	assert(key == 1);
	assert(cdata_list_size(list) == 1);
	assert(cdata_list_empty(list) == false);

	//Add many 0s {1, 0, 0, 0, 0, 0}
	for(i=0;i<5; ++i){
		key = 0;
		rv = cdata_list_push_back(list, &key);
		assert(rv == CDATA_SUCCESS);
		assert(key == 0);
	}
	assert(cdata_list_size(list) == 6);
	assert(cdata_list_empty(list) == false);

	rv = cdata_list_get(list, 0, &key);
	assert(rv == CDATA_SUCCESS);
	assert(key == 1);
	rv = cdata_list_get(list, 1, &key);
	assert(rv == CDATA_SUCCESS);
	assert(key == 0);
	rv = cdata_list_get(list, 5, &key);
	assert(rv == CDATA_SUCCESS);
	assert(key == 0);
	rv = cdata_list_get(list, 6, &key);
	assert(rv == CDATA_E_NOT_FOUND);
	assert(key == 0);

	//Sort {0, 0, 0, 0, 0, 1}
	rv = cdata_list_sort(list);
	assert(rv == CDATA_SUCCESS);
	rv = cdata_list_get(list, 0, &key);
	assert(rv == CDATA_SUCCESS);
	assert(key == 0);
	rv = cdata_list_get(list, 1, &key);
	assert(rv == CDATA_SUCCESS);
	assert(key == 0);
	rv = cdata_list_get(list, 5, &key);
	assert(rv == CDATA_SUCCESS);
	assert(key == 1);
	rv = cdata_list_get(list, 6, &key);
	assert(rv == CDATA_E_NOT_FOUND);
	assert(key == 1);

	//Reverse {1, 0, 0, 0, 0, 0}
	rv = cdata_list_reverse(list);
	rv = cdata_list_get(list, 0, &key);
	assert(rv == CDATA_SUCCESS);
	assert(key == 1);
	rv = cdata_list_get(list, 1, &key);
	assert(rv == CDATA_SUCCESS);
	assert(key == 0);
	rv = cdata_list_get(list, 5, &key);
	assert(rv == CDATA_SUCCESS);
	assert(key == 0);
	rv = cdata_list_get(list, 6, &key);
	assert(rv == CDATA_E_NOT_FOUND);
	assert(key == 0);

	//Unique {1, 0}
	rv = cdata_list_unique(list);
	assert(rv == CDATA_SUCCESS);
	assert(cdata_list_size(list) == 2);
	assert(cdata_list_empty(list) == false);
	rv = cdata_list_get(list, 0, &key);
	assert(rv == CDATA_SUCCESS);
	assert(key == 1);
	rv = cdata_list_get(list, 1, &key);
	assert(rv == CDATA_SUCCESS);
	assert(key == 0);
	rv = cdata_list_get(list, 2, &key);
	assert(rv == CDATA_E_NOT_FOUND);
	assert(key == 0);
	assert(cdata_list_size(list) == 2);
	assert(cdata_list_empty(list) == false);

	//Insert 5s {5, 1, 0, 5}
	key = 5;
	rv = cdata_list_insert(list, &key, 0);
	rv |= cdata_list_insert(list, &key, 4);
	assert(rv == CDATA_SUCCESS);
	rv = cdata_list_get(list, 0, &key);
	assert(rv == CDATA_SUCCESS);
	assert(key == 5);
	rv = cdata_list_get(list, 1, &key);
	assert(rv == CDATA_SUCCESS);
	assert(key == 1);
	rv = cdata_list_get(list, 2, &key);
	assert(rv == CDATA_SUCCESS);
	assert(key == 0);
	rv = cdata_list_get(list, 3, &key);
	assert(rv == CDATA_SUCCESS);
	assert(key == 5);
	assert(cdata_list_size(list) == 4);
	assert(cdata_list_empty(list) == false);

	//Remove API {1,0}
	rv = cdata_list_remove(list, &key);
	assert(rv == CDATA_SUCCESS);
	assert(cdata_list_size(list) == 2);
	assert(cdata_list_empty(list) == false);
	rv = cdata_list_get(list, 0, &key);
	assert(rv == CDATA_SUCCESS);
	assert(key == 1);
	rv = cdata_list_get(list, 1, &key);
	assert(rv == CDATA_SUCCESS);
	assert(key == 0);
	rv = cdata_list_get(list, 2, &key);
	assert(rv == CDATA_E_NOT_FOUND);
	assert(key == 0);

	rv = cdata_list_clear(list);
	assert(rv == CDATA_SUCCESS);
	assert(cdata_list_size(list) == 0);
	assert(cdata_list_empty(list) == true);

	rv = cdata_list_destroy(list);
	assert(rv == CDATA_SUCCESS);

	return 0;
}

//64
int test_u64_insert_removal_traverse(){

	int i, rv;
	uint64_t key;

	list = cdata_list_create(sizeof(key));
	assert(list != NULL);

	assert(cdata_list_size(list) == 0);
	assert(cdata_list_empty(list) == true);

	//Add one key & get
	key = 0ULL;
	rv = cdata_list_insert(list, &key, 0);
	assert(rv == CDATA_SUCCESS);

	assert(cdata_list_size(list) == 1);
	assert(cdata_list_empty(list) == false);

	rv = cdata_list_get(list, 0, &key);
	assert(rv == CDATA_SUCCESS);
	assert(key == 0ULL);

	//Get a value > size shall fail
	rv = cdata_list_get(list, 1, &key);
	assert(rv == CDATA_E_NOT_FOUND);
	rv = cdata_list_get(list, 222, &key);
	assert(rv == CDATA_E_NOT_FOUND);

	//Add 1 after
	key = 1ULL;
	rv = cdata_list_insert(list, &key, 1);
	assert(rv == CDATA_SUCCESS);
	rv = cdata_list_get(list, 0, &key);
	assert(rv == CDATA_SUCCESS);
	assert(key == 0ULL);
	rv = cdata_list_get(list, 1, &key);
	assert(rv == CDATA_SUCCESS);
	assert(key == 1ULL);
	rv = cdata_list_get(list, 222, &key);
	assert(rv == CDATA_E_NOT_FOUND);
	assert(key == 1ULL);

	//PUSH tests resulting list should be {9, 0, 1, 7}
	key = 7ULL;
	rv = cdata_list_push_back(list, &key);
	assert(rv == CDATA_SUCCESS);
	assert(key == 7ULL);
	key = 9ULL;
	rv = cdata_list_push_front(list, &key);
	assert(rv == CDATA_SUCCESS);
	rv = cdata_list_get(list, 0, &key);
	assert(rv == CDATA_SUCCESS);
	assert(key == 9ULL);
	rv = cdata_list_get(list, 1, &key);
	assert(rv == CDATA_SUCCESS);
	assert(key == 0ULL);
	rv = cdata_list_get(list, 2, &key);
	assert(rv == CDATA_SUCCESS);
	assert(key == 1ULL);
	rv = cdata_list_get(list, 3, &key);
	assert(rv == CDATA_SUCCESS);
	assert(key == 7ULL);
	rv = cdata_list_get(list, 4, &key);
	assert(rv == CDATA_E_NOT_FOUND);
	rv = cdata_list_get(list, 222, &key);
	assert(rv == CDATA_E_NOT_FOUND);
	assert(key == 7ULL);
	assert(cdata_list_size(list) == 4);
	assert(cdata_list_empty(list) == false);

	//Erase {9, 1, 7}
	rv = cdata_list_erase(list, 1);
	assert(rv == CDATA_SUCCESS);
	rv = cdata_list_get(list, 0, &key);
	assert(rv == CDATA_SUCCESS);
	assert(key == 9ULL);
	rv = cdata_list_get(list, 1, &key);
	assert(rv == CDATA_SUCCESS);
	assert(key == 1ULL);
	rv = cdata_list_get(list, 2, &key);
	assert(rv == CDATA_SUCCESS);
	assert(key == 7ULL);
	rv = cdata_list_get(list, 3, &key);
	assert(rv == CDATA_E_NOT_FOUND);
	rv = cdata_list_get(list, 222, &key);
	assert(rv == CDATA_E_NOT_FOUND);
	assert(key == 7ULL);
	assert(cdata_list_size(list) == 3);
	assert(cdata_list_empty(list) == false);

	//POP front {1,7}
	rv = cdata_list_pop_front(list);
	assert(rv == CDATA_SUCCESS);
	rv = cdata_list_get(list, 0, &key);
	assert(rv == CDATA_SUCCESS);
	assert(key == 1ULL);
	rv = cdata_list_get(list, 1, &key);
	assert(rv == CDATA_SUCCESS);
	assert(key == 7ULL);
	rv = cdata_list_get(list, 2, &key);
	assert(rv == CDATA_E_NOT_FOUND);
	rv = cdata_list_get(list, 222, &key);
	assert(rv == CDATA_E_NOT_FOUND);
	assert(key == 7ULL);
	assert(cdata_list_size(list) == 2);
	assert(cdata_list_empty(list) == false);


	//POP back {1}
	rv = cdata_list_pop_back(list);
	assert(rv == CDATA_SUCCESS);
	rv = cdata_list_get(list, 0, &key);
	assert(rv == CDATA_SUCCESS);
	assert(key == 1ULL);
	rv = cdata_list_get(list, 2, &key);
	assert(rv == CDATA_E_NOT_FOUND);
	rv = cdata_list_get(list, 222, &key);
	assert(rv == CDATA_E_NOT_FOUND);
	assert(key == 1ULL);
	assert(cdata_list_size(list) == 1);
	assert(cdata_list_empty(list) == false);

	//Add many 0s {1, 0, 0, 0, 0, 0}
	for(i=0;i<5; ++i){
		key = 0ULL;
		rv = cdata_list_push_back(list, &key);
		assert(rv == CDATA_SUCCESS);
		assert(key == 0ULL);
	}
	assert(cdata_list_size(list) == 6);
	assert(cdata_list_empty(list) == false);

	rv = cdata_list_get(list, 0, &key);
	assert(rv == CDATA_SUCCESS);
	assert(key == 1ULL);
	rv = cdata_list_get(list, 1, &key);
	assert(rv == CDATA_SUCCESS);
	assert(key == 0ULL);
	rv = cdata_list_get(list, 5, &key);
	assert(rv == CDATA_SUCCESS);
	assert(key == 0ULL);
	rv = cdata_list_get(list, 6, &key);
	assert(rv == CDATA_E_NOT_FOUND);
	assert(key == 0ULL);

	//Sort {0, 0, 0, 0, 0, 1}
	rv = cdata_list_sort(list);
	assert(rv == CDATA_SUCCESS);
	rv = cdata_list_get(list, 0, &key);
	assert(rv == CDATA_SUCCESS);
	assert(key == 0ULL);
	rv = cdata_list_get(list, 1, &key);
	assert(rv == CDATA_SUCCESS);
	assert(key == 0ULL);
	rv = cdata_list_get(list, 5, &key);
	assert(rv == CDATA_SUCCESS);
	assert(key == 1ULL);
	rv = cdata_list_get(list, 6, &key);
	assert(rv == CDATA_E_NOT_FOUND);
	assert(key == 1ULL);

	//Reverse {1, 0, 0, 0, 0, 0}
	rv = cdata_list_reverse(list);
	rv = cdata_list_get(list, 0, &key);
	assert(rv == CDATA_SUCCESS);
	assert(key == 1ULL);
	rv = cdata_list_get(list, 1, &key);
	assert(rv == CDATA_SUCCESS);
	assert(key == 0ULL);
	rv = cdata_list_get(list, 5, &key);
	assert(rv == CDATA_SUCCESS);
	assert(key == 0ULL);
	rv = cdata_list_get(list, 6, &key);
	assert(rv == CDATA_E_NOT_FOUND);
	assert(key == 0ULL);

	//Traverse
	opaque = 0ULL;
	cdata_list_traverse(list, &trav_u64, &opaque);
	opaque = 0ULL;
	cdata_list_rtraverse(list, &rtrav_u64, &opaque);

	//Unique {1, 0}
	rv = cdata_list_unique(list);
	assert(rv == CDATA_SUCCESS);
	assert(cdata_list_size(list) == 2);
	assert(cdata_list_empty(list) == false);
	rv = cdata_list_get(list, 0, &key);
	assert(rv == CDATA_SUCCESS);
	assert(key == 1ULL);
	rv = cdata_list_get(list, 1, &key);
	assert(rv == CDATA_SUCCESS);
	assert(key == 0ULL);
	rv = cdata_list_get(list, 2, &key);
	assert(rv == CDATA_E_NOT_FOUND);
	assert(key == 0ULL);
	assert(cdata_list_size(list) == 2);
	assert(cdata_list_empty(list) == false);

	//Insert 5s {5, 1, 0, 5}
	key = 5ULL;
	rv = cdata_list_insert(list, &key, 0);
	rv |= cdata_list_insert(list, &key, 4);
	assert(rv == CDATA_SUCCESS);
	rv = cdata_list_get(list, 0, &key);
	assert(rv == CDATA_SUCCESS);
	assert(key == 5ULL);
	rv = cdata_list_get(list, 1, &key);
	assert(rv == CDATA_SUCCESS);
	assert(key == 1ULL);
	rv = cdata_list_get(list, 2, &key);
	assert(rv == CDATA_SUCCESS);
	assert(key == 0ULL);
	rv = cdata_list_get(list, 3, &key);
	assert(rv == CDATA_SUCCESS);
	assert(key == 5ULL);
	assert(cdata_list_size(list) == 4);
	assert(cdata_list_empty(list) == false);

	//Remove API {1,0}
	rv = cdata_list_remove(list, &key);
	assert(rv == CDATA_SUCCESS);
	assert(cdata_list_size(list) == 2);
	assert(cdata_list_empty(list) == false);
	rv = cdata_list_get(list, 0, &key);
	assert(rv == CDATA_SUCCESS);
	assert(key == 1ULL);
	rv = cdata_list_get(list, 1, &key);
	assert(rv == CDATA_SUCCESS);
	assert(key == 0ULL);
	rv = cdata_list_get(list, 2, &key);
	assert(rv == CDATA_E_NOT_FOUND);
	assert(key == 0ULL);

	rv = cdata_list_clear(list);
	assert(rv == CDATA_SUCCESS);
	assert(cdata_list_size(list) == 0);
	assert(cdata_list_empty(list) == true);

	rv = cdata_list_destroy(list);
	assert(rv == CDATA_SUCCESS);

	return 0;
}

int test_basics(){

	int rv;

	void* ptr_not_null = (void*)0x123;

	//Create
	list = cdata_list_create(sizeof(int));
	assert(list != NULL);

	assert(cdata_list_size(list) == 0);
	assert(cdata_list_empty(list) == true);

	//Try all APIs with a NULL list/key/val
	assert(cdata_list_size(NULL) == 0);
	assert(cdata_list_empty(NULL) == false);
	rv = cdata_list_destroy(NULL);
	assert(rv == CDATA_E_INVALID);

	rv = cdata_list_traverse(NULL, ptr_not_null, NULL);
	assert(rv == CDATA_E_INVALID);
	rv = cdata_list_traverse(list, NULL, NULL);
	assert(rv == CDATA_E_INVALID);
	rv = cdata_list_rtraverse(NULL, ptr_not_null, NULL);
	assert(rv == CDATA_E_INVALID);
	rv = cdata_list_rtraverse(list, NULL, NULL);
	assert(rv == CDATA_E_INVALID);

	rv = cdata_list_insert(NULL, ptr_not_null, 0);
	assert(rv == CDATA_E_INVALID);
	rv = cdata_list_insert(list, NULL, 0);
	assert(rv == CDATA_E_INVALID);
	rv = cdata_list_erase(NULL, 0);
	assert(rv == CDATA_E_INVALID);

	rv = cdata_list_clear(NULL);
	assert(rv == CDATA_E_INVALID);
	rv = cdata_list_sort(NULL);
	assert(rv == CDATA_E_INVALID);
	rv = cdata_list_reverse(NULL);
	assert(rv == CDATA_E_INVALID);
	rv = cdata_list_unique(NULL);
	assert(rv == CDATA_E_INVALID);

	rv = cdata_list_push_front(NULL, ptr_not_null);
	assert(rv == CDATA_E_INVALID);
	rv = cdata_list_push_front(list, NULL);
	assert(rv == CDATA_E_INVALID);
	rv = cdata_list_push_back(NULL, ptr_not_null);
	assert(rv == CDATA_E_INVALID);
	rv = cdata_list_push_back(list, NULL);
	assert(rv == CDATA_E_INVALID);

	rv = cdata_list_pop_front(NULL);
	assert(rv == CDATA_E_INVALID);
	rv = cdata_list_pop_back(NULL);
	assert(rv == CDATA_E_INVALID);

	rv = cdata_list_remove(NULL, ptr_not_null);
	assert(rv == CDATA_E_INVALID);
	rv = cdata_list_remove(list, NULL);
	assert(rv == CDATA_E_INVALID);


	//Now destroy
	rv = cdata_list_destroy(list);
	assert(rv == CDATA_SUCCESS);

	//Create with valid and invalid
	list = cdata_list_create(256);
	assert(list != NULL);
	rv = cdata_list_destroy(list);
	assert(rv == CDATA_SUCCESS);
	list = cdata_list_create(257);
	assert(list == NULL);

	return 0;
}

//
// Key is not complete
//

void trav_u552(const cdata_list_t* s, const void* k, void* o){
	assert(o == &opaque);
	assert(list == s);
	test_u552_t key = *(test_u552_t*)k;
	switch(opaque){
		case 0:
			assert(key.mid == 1ULL);
			break;
		case 1:
		case 2:
		case 3:
		case 4:
		case 5:
			assert(key.mid == 0ULL);
			break;
		default:
			assert(0);
			break;
	}

	opaque++;
}

void rtrav_u552(const cdata_list_t* s, const void* k, void* o){
	assert(o == &opaque);
	assert(list == s);
	test_u552_t key = *(test_u552_t*)k;
	switch(opaque){
		case 0:
		case 1:
		case 2:
		case 3:
		case 4:
			assert(key.mid == 0ULL);
			break;

		case 5:
			assert(key.mid == 1ULL);
			break;
		default:
			assert(0);
			break;
	}

	opaque++;
}

int test_u552_insert_removal_traverse(){

	int i, rv;
	test_u552_t key;

	memset(&key, 0, sizeof(key));

	list = cdata_list_create(sizeof(key));
	assert(list != NULL);

	assert(cdata_list_size(list) == 0);
	assert(cdata_list_empty(list) == true);

	//Add one key & get
	key.mid = 0;
	rv = cdata_list_insert(list, &key, 0);
	assert(rv == CDATA_SUCCESS);

	assert(cdata_list_size(list) == 1);
	assert(cdata_list_empty(list) == false);

	rv = cdata_list_get(list, 0, &key);
	assert(rv == CDATA_SUCCESS);
	assert(key.mid == 0);

	//Get a value > size shall fail
	rv = cdata_list_get(list, 1, &key);
	assert(rv == CDATA_E_NOT_FOUND);
	rv = cdata_list_get(list, 222, &key);
	assert(rv == CDATA_E_NOT_FOUND);

	//Add 1 after
	key.mid = 1;
	rv = cdata_list_insert(list, &key, 1);
	assert(rv == CDATA_SUCCESS);
	rv = cdata_list_get(list, 0, &key);
	assert(rv == CDATA_SUCCESS);
	assert(key.mid == 0);
	rv = cdata_list_get(list, 1, &key);
	assert(rv == CDATA_SUCCESS);
	assert(key.mid == 1);
	rv = cdata_list_get(list, 222, &key);
	assert(rv == CDATA_E_NOT_FOUND);
	assert(key.mid == 1);

	//PUSH tests resulting list should be {9, 0, 1, 7}
	key.mid = 7;
	rv = cdata_list_push_back(list, &key);
	assert(rv == CDATA_SUCCESS);
	assert(key.mid == 7);
	key.mid = 9;
	rv = cdata_list_push_front(list, &key);
	assert(rv == CDATA_SUCCESS);
	rv = cdata_list_get(list, 0, &key);
	assert(rv == CDATA_SUCCESS);
	assert(key.mid == 9);
	rv = cdata_list_get(list, 1, &key);
	assert(rv == CDATA_SUCCESS);
	assert(key.mid == 0);
	rv = cdata_list_get(list, 2, &key);
	assert(rv == CDATA_SUCCESS);
	assert(key.mid == 1);
	rv = cdata_list_get(list, 3, &key);
	assert(rv == CDATA_SUCCESS);
	assert(key.mid == 7);
	rv = cdata_list_get(list, 4, &key);
	assert(rv == CDATA_E_NOT_FOUND);
	rv = cdata_list_get(list, 222, &key);
	assert(rv == CDATA_E_NOT_FOUND);
	assert(key.mid == 7);
	assert(cdata_list_size(list) == 4);
	assert(cdata_list_empty(list) == false);

	//Erase {9, 1, 7}
	rv = cdata_list_erase(list, 1);
	assert(rv == CDATA_SUCCESS);
	rv = cdata_list_get(list, 0, &key);
	assert(rv == CDATA_SUCCESS);
	assert(key.mid == 9);
	rv = cdata_list_get(list, 1, &key);
	assert(rv == CDATA_SUCCESS);
	assert(key.mid == 1);
	rv = cdata_list_get(list, 2, &key);
	assert(rv == CDATA_SUCCESS);
	assert(key.mid == 7);
	rv = cdata_list_get(list, 3, &key);
	assert(rv == CDATA_E_NOT_FOUND);
	rv = cdata_list_get(list, 222, &key);
	assert(rv == CDATA_E_NOT_FOUND);
	assert(key.mid == 7);
	assert(cdata_list_size(list) == 3);
	assert(cdata_list_empty(list) == false);

	//POP front {1,7}
	rv = cdata_list_pop_front(list);
	assert(rv == CDATA_SUCCESS);
	rv = cdata_list_get(list, 0, &key);
	assert(rv == CDATA_SUCCESS);
	assert(key.mid == 1);
	rv = cdata_list_get(list, 1, &key);
	assert(rv == CDATA_SUCCESS);
	assert(key.mid == 7);
	rv = cdata_list_get(list, 2, &key);
	assert(rv == CDATA_E_NOT_FOUND);
	rv = cdata_list_get(list, 222, &key);
	assert(rv == CDATA_E_NOT_FOUND);
	assert(key.mid == 7);
	assert(cdata_list_size(list) == 2);
	assert(cdata_list_empty(list) == false);


	//POP back {1}
	rv = cdata_list_pop_back(list);
	assert(rv == CDATA_SUCCESS);
	rv = cdata_list_get(list, 0, &key);
	assert(rv == CDATA_SUCCESS);
	assert(key.mid == 1);
	rv = cdata_list_get(list, 2, &key);
	assert(rv == CDATA_E_NOT_FOUND);
	rv = cdata_list_get(list, 222, &key);
	assert(rv == CDATA_E_NOT_FOUND);
	assert(key.mid == 1);
	assert(cdata_list_size(list) == 1);
	assert(cdata_list_empty(list) == false);

	//Add many 0s {1, 0, 0, 0, 0, 0}
	for(i=0;i<5; ++i){
		key.mid = 0;
		rv = cdata_list_push_back(list, &key);
		assert(rv == CDATA_SUCCESS);
		assert(key.mid == 0);
	}
	assert(cdata_list_size(list) == 6);
	assert(cdata_list_empty(list) == false);

	rv = cdata_list_get(list, 0, &key);
	assert(rv == CDATA_SUCCESS);
	assert(key.mid == 1);
	rv = cdata_list_get(list, 1, &key);
	assert(rv == CDATA_SUCCESS);
	assert(key.mid == 0);
	rv = cdata_list_get(list, 5, &key);
	assert(rv == CDATA_SUCCESS);
	assert(key.mid == 0);
	rv = cdata_list_get(list, 6, &key);
	assert(rv == CDATA_E_NOT_FOUND);
	assert(key.mid == 0);

	//Sort {0, 0, 0, 0, 0, 1}
	rv = cdata_list_sort(list);
	assert(rv == CDATA_SUCCESS);
	rv = cdata_list_get(list, 0, &key);
	assert(rv == CDATA_SUCCESS);
	assert(key.mid == 0);
	rv = cdata_list_get(list, 1, &key);
	assert(rv == CDATA_SUCCESS);
	assert(key.mid == 0);
	rv = cdata_list_get(list, 5, &key);
	assert(rv == CDATA_SUCCESS);
	assert(key.mid == 1);
	rv = cdata_list_get(list, 6, &key);
	assert(rv == CDATA_E_NOT_FOUND);
	assert(key.mid == 1);

	//Reverse {1, 0, 0, 0, 0, 0}
	rv = cdata_list_reverse(list);
	rv = cdata_list_get(list, 0, &key);
	assert(rv == CDATA_SUCCESS);
	assert(key.mid == 1);
	rv = cdata_list_get(list, 1, &key);
	assert(rv == CDATA_SUCCESS);
	assert(key.mid == 0);
	rv = cdata_list_get(list, 5, &key);
	assert(rv == CDATA_SUCCESS);
	assert(key.mid == 0);
	rv = cdata_list_get(list, 6, &key);
	assert(rv == CDATA_E_NOT_FOUND);
	assert(key.mid == 0);

	//Traverse
	opaque = 0;
	cdata_list_traverse(list, &trav_u552, &opaque);
	opaque = 0;
	cdata_list_rtraverse(list, &rtrav_u552, &opaque);

	//Unique {1, 0}
	rv = cdata_list_unique(list);
	assert(rv == CDATA_SUCCESS);
	assert(cdata_list_size(list) == 2);
	assert(cdata_list_empty(list) == false);
	rv = cdata_list_get(list, 0, &key);
	assert(rv == CDATA_SUCCESS);
	assert(key.mid == 1);
	rv = cdata_list_get(list, 1, &key);
	assert(rv == CDATA_SUCCESS);
	assert(key.mid == 0);
	rv = cdata_list_get(list, 2, &key);
	assert(rv == CDATA_E_NOT_FOUND);
	assert(key.mid == 0);
	assert(cdata_list_size(list) == 2);
	assert(cdata_list_empty(list) == false);

	//Insert 5s {5, 1, 0, 5}
	key.mid = 5;
	rv = cdata_list_insert(list, &key, 0);
	rv |= cdata_list_insert(list, &key, 4);
	assert(rv == CDATA_SUCCESS);
	rv = cdata_list_get(list, 0, &key);
	assert(rv == CDATA_SUCCESS);
	assert(key.mid == 5);
	rv = cdata_list_get(list, 1, &key);
	assert(rv == CDATA_SUCCESS);
	assert(key.mid == 1);
	rv = cdata_list_get(list, 2, &key);
	assert(rv == CDATA_SUCCESS);
	assert(key.mid == 0);
	rv = cdata_list_get(list, 3, &key);
	assert(rv == CDATA_SUCCESS);
	assert(key.mid == 5);
	assert(cdata_list_size(list) == 4);
	assert(cdata_list_empty(list) == false);

	//Remove API {1,0}
	rv = cdata_list_remove(list, &key);
	assert(rv == CDATA_SUCCESS);
	assert(cdata_list_size(list) == 2);
	assert(cdata_list_empty(list) == false);
	rv = cdata_list_get(list, 0, &key);
	assert(rv == CDATA_SUCCESS);
	assert(key.mid == 1);
	rv = cdata_list_get(list, 1, &key);
	assert(rv == CDATA_SUCCESS);
	assert(key.mid == 0);
	rv = cdata_list_get(list, 2, &key);
	assert(rv == CDATA_E_NOT_FOUND);
	assert(key.mid == 0);

	rv = cdata_list_clear(list);
	assert(rv == CDATA_SUCCESS);
	assert(cdata_list_size(list) == 0);
	assert(cdata_list_empty(list) == true);

	rv = cdata_list_destroy(list);
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
