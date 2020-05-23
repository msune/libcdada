#include <stdlib.h>

#include "cdada/list.h"
#include "common.h"
#include <string.h>
#include "u552.h"
#include "u3552.h"

//Fwd decl
CDADA_LIST_CUSTOM_TYPE_DECL(test_u552_t);
CDADA_LIST_CUSTOM_TYPE_DECL(test_u3552_t);

static uint64_t opaque = 0ULL;
static cdada_list_t* list = NULL;

//{1, 0, 0, 0, 0, 0, 0}
void trav_u64(const cdada_list_t* s, const void* k, void* o){
	TEST_ASSERT(o == &opaque);
	TEST_ASSERT(list == s);
	uint64_t key = *(uint64_t*)k;
	switch(opaque){
		case 0:
			TEST_ASSERT(key == 1ULL);
			break;
		case 1:
		case 2:
		case 3:
		case 4:
		case 5:
			TEST_ASSERT(key == 0ULL);
			break;
		default:
			TEST_ASSERT(0);
			break;
	}

	opaque++;
}

void rtrav_u64(const cdada_list_t* s, const void* k, void* o){
	TEST_ASSERT(o == &opaque);
	TEST_ASSERT(list == s);
	uint64_t key = *(uint64_t*)k;
	switch(opaque){
		case 0:
		case 1:
		case 2:
		case 3:
		case 4:
			TEST_ASSERT(key == 0ULL);
			break;

		case 5:
			TEST_ASSERT(key == 1ULL);
			break;
		default:
			TEST_ASSERT(0);
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

	list = cdada_list_create(sizeof(key));
	TEST_ASSERT(list != NULL);

	TEST_ASSERT(cdada_list_size(list) == 0);
	TEST_ASSERT(cdada_list_empty(list) == true);
	TEST_ASSERT(cdada_list_first(list, &key) == CDADA_E_NOT_FOUND);
	TEST_ASSERT(cdada_list_last(list, &key) == CDADA_E_NOT_FOUND);

	//Add one key & get
	key = 0;
	rv = cdada_list_insert(list, &key, 0);
	TEST_ASSERT(rv == CDADA_SUCCESS);

	rv = cdada_list_first(list, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 0);
	rv = cdada_list_last(list, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 0);

	TEST_ASSERT(cdada_list_size(list) == 1);
	TEST_ASSERT(cdada_list_empty(list) == false);

	rv = cdada_list_get(list, 0, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 0);

	//Get a value > size shall fail
	rv = cdada_list_get(list, 1, &key);
	TEST_ASSERT(rv == CDADA_E_NOT_FOUND);
	rv = cdada_list_get(list, 222, &key);
	TEST_ASSERT(rv == CDADA_E_NOT_FOUND);

	//Add 1 after
	key = 1;
	rv = cdada_list_insert(list, &key, 1);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	rv = cdada_list_get(list, 0, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 0);
	rv = cdada_list_get(list, 1, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 1);
	rv = cdada_list_get(list, 222, &key);
	TEST_ASSERT(rv == CDADA_E_NOT_FOUND);
	TEST_ASSERT(key == 1);

	//PUSH tests resulting list should be {9, 0, 1, 7}
	key = 7;
	rv = cdada_list_push_back(list, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 7);
	key = 9;
	rv = cdada_list_push_front(list, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	rv = cdada_list_get(list, 0, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 9);
	rv = cdada_list_get(list, 1, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 0);
	rv = cdada_list_get(list, 2, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 1);
	rv = cdada_list_get(list, 3, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 7);
	rv = cdada_list_get(list, 4, &key);
	TEST_ASSERT(rv == CDADA_E_NOT_FOUND);
	rv = cdada_list_get(list, 222, &key);
	TEST_ASSERT(rv == CDADA_E_NOT_FOUND);
	TEST_ASSERT(key == 7);
	TEST_ASSERT(cdada_list_size(list) == 4);
	TEST_ASSERT(cdada_list_empty(list) == false);

	//Erase {9, 1, 7}
	rv = cdada_list_erase(list, 1);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	rv = cdada_list_get(list, 0, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 9);
	rv = cdada_list_get(list, 1, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 1);
	rv = cdada_list_get(list, 2, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 7);
	rv = cdada_list_get(list, 3, &key);
	TEST_ASSERT(rv == CDADA_E_NOT_FOUND);
	rv = cdada_list_get(list, 222, &key);
	TEST_ASSERT(rv == CDADA_E_NOT_FOUND);
	TEST_ASSERT(key == 7);
	TEST_ASSERT(cdada_list_size(list) == 3);
	TEST_ASSERT(cdada_list_empty(list) == false);

	//POP front {1,7}
	rv = cdada_list_pop_front(list);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	rv = cdada_list_get(list, 0, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 1);
	rv = cdada_list_get(list, 1, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 7);
	rv = cdada_list_get(list, 2, &key);
	TEST_ASSERT(rv == CDADA_E_NOT_FOUND);
	rv = cdada_list_get(list, 222, &key);
	TEST_ASSERT(rv == CDADA_E_NOT_FOUND);
	TEST_ASSERT(key == 7);
	TEST_ASSERT(cdada_list_size(list) == 2);
	TEST_ASSERT(cdada_list_empty(list) == false);


	//POP back {1}
	rv = cdada_list_pop_back(list);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	rv = cdada_list_get(list, 0, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 1);
	rv = cdada_list_get(list, 2, &key);
	TEST_ASSERT(rv == CDADA_E_NOT_FOUND);
	rv = cdada_list_get(list, 222, &key);
	TEST_ASSERT(rv == CDADA_E_NOT_FOUND);
	TEST_ASSERT(key == 1);
	TEST_ASSERT(cdada_list_size(list) == 1);
	TEST_ASSERT(cdada_list_empty(list) == false);

	//Add many 0s {1, 0, 0, 0, 0, 0}
	for(i=0;i<5; ++i){
		key = 0;
		rv = cdada_list_push_back(list, &key);
		TEST_ASSERT(rv == CDADA_SUCCESS);
		TEST_ASSERT(key == 0);
	}

	rv = cdada_list_first(list, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 1);

	rv = cdada_list_last(list, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 0);

	TEST_ASSERT(cdada_list_size(list) == 6);
	TEST_ASSERT(cdada_list_empty(list) == false);

	rv = cdada_list_get(list, 0, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 1);
	rv = cdada_list_get(list, 1, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 0);
	rv = cdada_list_get(list, 5, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 0);
	rv = cdada_list_get(list, 6, &key);
	TEST_ASSERT(rv == CDADA_E_NOT_FOUND);
	TEST_ASSERT(key == 0);

	//Sort {0, 0, 0, 0, 0, 1}
	rv = cdada_list_sort(list);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	rv = cdada_list_get(list, 0, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 0);
	rv = cdada_list_get(list, 1, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 0);
	rv = cdada_list_get(list, 5, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 1);
	rv = cdada_list_get(list, 6, &key);
	TEST_ASSERT(rv == CDADA_E_NOT_FOUND);
	TEST_ASSERT(key == 1);

	//Reverse {1, 0, 0, 0, 0, 0}
	rv = cdada_list_reverse(list);
	rv = cdada_list_get(list, 0, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 1);
	rv = cdada_list_get(list, 1, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 0);
	rv = cdada_list_get(list, 5, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 0);
	rv = cdada_list_get(list, 6, &key);
	TEST_ASSERT(rv == CDADA_E_NOT_FOUND);
	TEST_ASSERT(key == 0);

	//Unique {1, 0}
	rv = cdada_list_unique(list);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(cdada_list_size(list) == 2);
	TEST_ASSERT(cdada_list_empty(list) == false);
	rv = cdada_list_get(list, 0, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 1);
	rv = cdada_list_get(list, 1, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 0);
	rv = cdada_list_get(list, 2, &key);
	TEST_ASSERT(rv == CDADA_E_NOT_FOUND);
	TEST_ASSERT(key == 0);
	TEST_ASSERT(cdada_list_size(list) == 2);
	TEST_ASSERT(cdada_list_empty(list) == false);

	//Insert 5s {5, 1, 0, 5}
	key = 5;
	rv = cdada_list_insert(list, &key, 0);
	rv |= cdada_list_insert(list, &key, 4);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	rv = cdada_list_get(list, 0, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 5);
	rv = cdada_list_get(list, 1, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 1);
	rv = cdada_list_get(list, 2, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 0);
	rv = cdada_list_get(list, 3, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 5);
	TEST_ASSERT(cdada_list_size(list) == 4);
	TEST_ASSERT(cdada_list_empty(list) == false);

	//Remove API {1,0}
	rv = cdada_list_remove(list, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(cdada_list_size(list) == 2);
	TEST_ASSERT(cdada_list_empty(list) == false);
	rv = cdada_list_get(list, 0, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 1);
	rv = cdada_list_get(list, 1, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 0);
	rv = cdada_list_get(list, 2, &key);
	TEST_ASSERT(rv == CDADA_E_NOT_FOUND);
	TEST_ASSERT(key == 0);

	rv = cdada_list_clear(list);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(cdada_list_size(list) == 0);
	TEST_ASSERT(cdada_list_empty(list) == true);

	rv = cdada_list_destroy(list);
	TEST_ASSERT(rv == CDADA_SUCCESS);

	return 0;
}

//16
int test_u16_insert_removal(){

	int i, rv;
	uint16_t key;

	list = cdada_list_create(sizeof(key));
	TEST_ASSERT(list != NULL);

	TEST_ASSERT(cdada_list_size(list) == 0);
	TEST_ASSERT(cdada_list_empty(list) == true);
	TEST_ASSERT(cdada_list_first(list, &key) == CDADA_E_NOT_FOUND);
	TEST_ASSERT(cdada_list_last(list, &key) == CDADA_E_NOT_FOUND);

	//Add one key & get
	key = 0;
	rv = cdada_list_insert(list, &key, 0);
	TEST_ASSERT(rv == CDADA_SUCCESS);

	rv = cdada_list_first(list, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 0);
	rv = cdada_list_last(list, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 0);

	TEST_ASSERT(cdada_list_size(list) == 1);
	TEST_ASSERT(cdada_list_empty(list) == false);

	rv = cdada_list_get(list, 0, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 0);

	//Get a value > size shall fail
	rv = cdada_list_get(list, 1, &key);
	TEST_ASSERT(rv == CDADA_E_NOT_FOUND);
	rv = cdada_list_get(list, 222, &key);
	TEST_ASSERT(rv == CDADA_E_NOT_FOUND);

	//Add 1 after
	key = 1;
	rv = cdada_list_insert(list, &key, 1);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	rv = cdada_list_get(list, 0, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 0);
	rv = cdada_list_get(list, 1, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 1);
	rv = cdada_list_get(list, 222, &key);
	TEST_ASSERT(rv == CDADA_E_NOT_FOUND);
	TEST_ASSERT(key == 1);

	//PUSH tests resulting list should be {9, 0, 1, 7}
	key = 7;
	rv = cdada_list_push_back(list, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 7);
	key = 9;
	rv = cdada_list_push_front(list, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	rv = cdada_list_get(list, 0, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 9);
	rv = cdada_list_get(list, 1, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 0);
	rv = cdada_list_get(list, 2, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 1);
	rv = cdada_list_get(list, 3, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 7);
	rv = cdada_list_get(list, 4, &key);
	TEST_ASSERT(rv == CDADA_E_NOT_FOUND);
	rv = cdada_list_get(list, 222, &key);
	TEST_ASSERT(rv == CDADA_E_NOT_FOUND);
	TEST_ASSERT(key == 7);
	TEST_ASSERT(cdada_list_size(list) == 4);
	TEST_ASSERT(cdada_list_empty(list) == false);

	//Erase {9, 1, 7}
	rv = cdada_list_erase(list, 1);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	rv = cdada_list_get(list, 0, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 9);
	rv = cdada_list_get(list, 1, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 1);
	rv = cdada_list_get(list, 2, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 7);
	rv = cdada_list_get(list, 3, &key);
	TEST_ASSERT(rv == CDADA_E_NOT_FOUND);
	rv = cdada_list_get(list, 222, &key);
	TEST_ASSERT(rv == CDADA_E_NOT_FOUND);
	TEST_ASSERT(key == 7);
	TEST_ASSERT(cdada_list_size(list) == 3);
	TEST_ASSERT(cdada_list_empty(list) == false);

	//POP front {1,7}
	rv = cdada_list_pop_front(list);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	rv = cdada_list_get(list, 0, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 1);
	rv = cdada_list_get(list, 1, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 7);
	rv = cdada_list_get(list, 2, &key);
	TEST_ASSERT(rv == CDADA_E_NOT_FOUND);
	rv = cdada_list_get(list, 222, &key);
	TEST_ASSERT(rv == CDADA_E_NOT_FOUND);
	TEST_ASSERT(key == 7);
	TEST_ASSERT(cdada_list_size(list) == 2);
	TEST_ASSERT(cdada_list_empty(list) == false);


	//POP back {1}
	rv = cdada_list_pop_back(list);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	rv = cdada_list_get(list, 0, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 1);
	rv = cdada_list_get(list, 2, &key);
	TEST_ASSERT(rv == CDADA_E_NOT_FOUND);
	rv = cdada_list_get(list, 222, &key);
	TEST_ASSERT(rv == CDADA_E_NOT_FOUND);
	TEST_ASSERT(key == 1);
	TEST_ASSERT(cdada_list_size(list) == 1);
	TEST_ASSERT(cdada_list_empty(list) == false);

	//Add many 0s {1, 0, 0, 0, 0, 0}
	for(i=0;i<5; ++i){
		key = 0;
		rv = cdada_list_push_back(list, &key);
		TEST_ASSERT(rv == CDADA_SUCCESS);
		TEST_ASSERT(key == 0);
	}

	rv = cdada_list_first(list, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 1);

	rv = cdada_list_last(list, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 0);

	TEST_ASSERT(cdada_list_size(list) == 6);
	TEST_ASSERT(cdada_list_empty(list) == false);

	rv = cdada_list_get(list, 0, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 1);
	rv = cdada_list_get(list, 1, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 0);
	rv = cdada_list_get(list, 5, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 0);
	rv = cdada_list_get(list, 6, &key);
	TEST_ASSERT(rv == CDADA_E_NOT_FOUND);
	TEST_ASSERT(key == 0);

	//Sort {0, 0, 0, 0, 0, 1}
	rv = cdada_list_sort(list);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	rv = cdada_list_get(list, 0, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 0);
	rv = cdada_list_get(list, 1, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 0);
	rv = cdada_list_get(list, 5, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 1);
	rv = cdada_list_get(list, 6, &key);
	TEST_ASSERT(rv == CDADA_E_NOT_FOUND);
	TEST_ASSERT(key == 1);

	//Reverse {1, 0, 0, 0, 0, 0}
	rv = cdada_list_reverse(list);
	rv = cdada_list_get(list, 0, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 1);
	rv = cdada_list_get(list, 1, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 0);
	rv = cdada_list_get(list, 5, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 0);
	rv = cdada_list_get(list, 6, &key);
	TEST_ASSERT(rv == CDADA_E_NOT_FOUND);
	TEST_ASSERT(key == 0);

	//Unique {1, 0}
	rv = cdada_list_unique(list);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(cdada_list_size(list) == 2);
	TEST_ASSERT(cdada_list_empty(list) == false);
	rv = cdada_list_get(list, 0, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 1);
	rv = cdada_list_get(list, 1, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 0);
	rv = cdada_list_get(list, 2, &key);
	TEST_ASSERT(rv == CDADA_E_NOT_FOUND);
	TEST_ASSERT(key == 0);
	TEST_ASSERT(cdada_list_size(list) == 2);
	TEST_ASSERT(cdada_list_empty(list) == false);

	//Insert 5s {5, 1, 0, 5}
	key = 5;
	rv = cdada_list_insert(list, &key, 0);
	rv |= cdada_list_insert(list, &key, 4);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	rv = cdada_list_get(list, 0, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 5);
	rv = cdada_list_get(list, 1, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 1);
	rv = cdada_list_get(list, 2, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 0);
	rv = cdada_list_get(list, 3, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 5);
	TEST_ASSERT(cdada_list_size(list) == 4);
	TEST_ASSERT(cdada_list_empty(list) == false);

	//Remove API {1,0}
	rv = cdada_list_remove(list, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(cdada_list_size(list) == 2);
	TEST_ASSERT(cdada_list_empty(list) == false);
	rv = cdada_list_get(list, 0, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 1);
	rv = cdada_list_get(list, 1, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 0);
	rv = cdada_list_get(list, 2, &key);
	TEST_ASSERT(rv == CDADA_E_NOT_FOUND);
	TEST_ASSERT(key == 0);

	rv = cdada_list_clear(list);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(cdada_list_size(list) == 0);
	TEST_ASSERT(cdada_list_empty(list) == true);

	rv = cdada_list_destroy(list);
	TEST_ASSERT(rv == CDADA_SUCCESS);

	return 0;
}

//32
int test_u32_insert_removal(){

	int i, rv;
	uint32_t key;

	list = cdada_list_create(sizeof(key));
	TEST_ASSERT(list != NULL);

	TEST_ASSERT(cdada_list_size(list) == 0);
	TEST_ASSERT(cdada_list_empty(list) == true);
	TEST_ASSERT(cdada_list_first(list, &key) == CDADA_E_NOT_FOUND);
	TEST_ASSERT(cdada_list_last(list, &key) == CDADA_E_NOT_FOUND);

	//Add one key & get
	key = 0;
	rv = cdada_list_insert(list, &key, 0);
	TEST_ASSERT(rv == CDADA_SUCCESS);

	rv = cdada_list_first(list, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 0);
	rv = cdada_list_last(list, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 0);

	TEST_ASSERT(cdada_list_size(list) == 1);
	TEST_ASSERT(cdada_list_empty(list) == false);

	rv = cdada_list_get(list, 0, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 0);

	//Get a value > size shall fail
	rv = cdada_list_get(list, 1, &key);
	TEST_ASSERT(rv == CDADA_E_NOT_FOUND);
	rv = cdada_list_get(list, 222, &key);
	TEST_ASSERT(rv == CDADA_E_NOT_FOUND);

	//Add 1 after
	key = 1;
	rv = cdada_list_insert(list, &key, 1);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	rv = cdada_list_get(list, 0, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 0);
	rv = cdada_list_get(list, 1, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 1);
	rv = cdada_list_get(list, 222, &key);
	TEST_ASSERT(rv == CDADA_E_NOT_FOUND);
	TEST_ASSERT(key == 1);

	//PUSH tests resulting list should be {9, 0, 1, 7}
	key = 7;
	rv = cdada_list_push_back(list, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 7);
	key = 9;
	rv = cdada_list_push_front(list, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	rv = cdada_list_get(list, 0, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 9);
	rv = cdada_list_get(list, 1, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 0);
	rv = cdada_list_get(list, 2, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 1);
	rv = cdada_list_get(list, 3, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 7);
	rv = cdada_list_get(list, 4, &key);
	TEST_ASSERT(rv == CDADA_E_NOT_FOUND);
	rv = cdada_list_get(list, 222, &key);
	TEST_ASSERT(rv == CDADA_E_NOT_FOUND);
	TEST_ASSERT(key == 7);
	TEST_ASSERT(cdada_list_size(list) == 4);
	TEST_ASSERT(cdada_list_empty(list) == false);

	//Erase {9, 1, 7}
	rv = cdada_list_erase(list, 1);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	rv = cdada_list_get(list, 0, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 9);
	rv = cdada_list_get(list, 1, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 1);
	rv = cdada_list_get(list, 2, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 7);
	rv = cdada_list_get(list, 3, &key);
	TEST_ASSERT(rv == CDADA_E_NOT_FOUND);
	rv = cdada_list_get(list, 222, &key);
	TEST_ASSERT(rv == CDADA_E_NOT_FOUND);
	TEST_ASSERT(key == 7);
	TEST_ASSERT(cdada_list_size(list) == 3);
	TEST_ASSERT(cdada_list_empty(list) == false);

	//POP front {1,7}
	rv = cdada_list_pop_front(list);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	rv = cdada_list_get(list, 0, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 1);
	rv = cdada_list_get(list, 1, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 7);
	rv = cdada_list_get(list, 2, &key);
	TEST_ASSERT(rv == CDADA_E_NOT_FOUND);
	rv = cdada_list_get(list, 222, &key);
	TEST_ASSERT(rv == CDADA_E_NOT_FOUND);
	TEST_ASSERT(key == 7);
	TEST_ASSERT(cdada_list_size(list) == 2);
	TEST_ASSERT(cdada_list_empty(list) == false);


	//POP back {1}
	rv = cdada_list_pop_back(list);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	rv = cdada_list_get(list, 0, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 1);
	rv = cdada_list_get(list, 2, &key);
	TEST_ASSERT(rv == CDADA_E_NOT_FOUND);
	rv = cdada_list_get(list, 222, &key);
	TEST_ASSERT(rv == CDADA_E_NOT_FOUND);
	TEST_ASSERT(key == 1);
	TEST_ASSERT(cdada_list_size(list) == 1);
	TEST_ASSERT(cdada_list_empty(list) == false);

	//Add many 0s {1, 0, 0, 0, 0, 0}
	for(i=0;i<5; ++i){
		key = 0;
		rv = cdada_list_push_back(list, &key);
		TEST_ASSERT(rv == CDADA_SUCCESS);
		TEST_ASSERT(key == 0);
	}

	rv = cdada_list_first(list, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 1);

	rv = cdada_list_last(list, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 0);

	TEST_ASSERT(cdada_list_size(list) == 6);
	TEST_ASSERT(cdada_list_empty(list) == false);

	rv = cdada_list_get(list, 0, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 1);
	rv = cdada_list_get(list, 1, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 0);
	rv = cdada_list_get(list, 5, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 0);
	rv = cdada_list_get(list, 6, &key);
	TEST_ASSERT(rv == CDADA_E_NOT_FOUND);
	TEST_ASSERT(key == 0);

	//Sort {0, 0, 0, 0, 0, 1}
	rv = cdada_list_sort(list);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	rv = cdada_list_get(list, 0, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 0);
	rv = cdada_list_get(list, 1, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 0);
	rv = cdada_list_get(list, 5, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 1);
	rv = cdada_list_get(list, 6, &key);
	TEST_ASSERT(rv == CDADA_E_NOT_FOUND);
	TEST_ASSERT(key == 1);

	//Reverse {1, 0, 0, 0, 0, 0}
	rv = cdada_list_reverse(list);
	rv = cdada_list_get(list, 0, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 1);
	rv = cdada_list_get(list, 1, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 0);
	rv = cdada_list_get(list, 5, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 0);
	rv = cdada_list_get(list, 6, &key);
	TEST_ASSERT(rv == CDADA_E_NOT_FOUND);
	TEST_ASSERT(key == 0);

	//Unique {1, 0}
	rv = cdada_list_unique(list);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(cdada_list_size(list) == 2);
	TEST_ASSERT(cdada_list_empty(list) == false);
	rv = cdada_list_get(list, 0, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 1);
	rv = cdada_list_get(list, 1, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 0);
	rv = cdada_list_get(list, 2, &key);
	TEST_ASSERT(rv == CDADA_E_NOT_FOUND);
	TEST_ASSERT(key == 0);
	TEST_ASSERT(cdada_list_size(list) == 2);
	TEST_ASSERT(cdada_list_empty(list) == false);

	//Insert 5s {5, 1, 0, 5}
	key = 5;
	rv = cdada_list_insert(list, &key, 0);
	rv |= cdada_list_insert(list, &key, 4);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	rv = cdada_list_get(list, 0, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 5);
	rv = cdada_list_get(list, 1, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 1);
	rv = cdada_list_get(list, 2, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 0);
	rv = cdada_list_get(list, 3, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 5);
	TEST_ASSERT(cdada_list_size(list) == 4);
	TEST_ASSERT(cdada_list_empty(list) == false);

	//Remove API {1,0}
	rv = cdada_list_remove(list, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(cdada_list_size(list) == 2);
	TEST_ASSERT(cdada_list_empty(list) == false);
	rv = cdada_list_get(list, 0, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 1);
	rv = cdada_list_get(list, 1, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 0);
	rv = cdada_list_get(list, 2, &key);
	TEST_ASSERT(rv == CDADA_E_NOT_FOUND);
	TEST_ASSERT(key == 0);

	rv = cdada_list_clear(list);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(cdada_list_size(list) == 0);
	TEST_ASSERT(cdada_list_empty(list) == true);

	rv = cdada_list_destroy(list);
	TEST_ASSERT(rv == CDADA_SUCCESS);

	return 0;
}

//64
int test_u64_insert_removal_traverse(){

	int i, rv;
	uint64_t key;

	list = cdada_list_create(sizeof(key));
	TEST_ASSERT(list != NULL);

	TEST_ASSERT(cdada_list_size(list) == 0);
	TEST_ASSERT(cdada_list_empty(list) == true);
	TEST_ASSERT(cdada_list_first(list, &key) == CDADA_E_NOT_FOUND);
	TEST_ASSERT(cdada_list_last(list, &key) == CDADA_E_NOT_FOUND);


	//Add one key & get
	key = 0ULL;
	rv = cdada_list_insert(list, &key, 0);
	TEST_ASSERT(rv == CDADA_SUCCESS);

	rv = cdada_list_first(list, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 0ULL);
	rv = cdada_list_last(list, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 0ULL);

	TEST_ASSERT(cdada_list_size(list) == 1);
	TEST_ASSERT(cdada_list_empty(list) == false);

	rv = cdada_list_get(list, 0, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 0ULL);

	//Get a value > size shall fail
	rv = cdada_list_get(list, 1, &key);
	TEST_ASSERT(rv == CDADA_E_NOT_FOUND);
	rv = cdada_list_get(list, 222, &key);
	TEST_ASSERT(rv == CDADA_E_NOT_FOUND);

	//Add 1 after
	key = 1ULL;
	rv = cdada_list_insert(list, &key, 1);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	rv = cdada_list_get(list, 0, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 0ULL);
	rv = cdada_list_get(list, 1, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 1ULL);
	rv = cdada_list_get(list, 222, &key);
	TEST_ASSERT(rv == CDADA_E_NOT_FOUND);
	TEST_ASSERT(key == 1ULL);

	//PUSH tests resulting list should be {9, 0, 1, 7}
	key = 7ULL;
	rv = cdada_list_push_back(list, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 7ULL);
	key = 9ULL;
	rv = cdada_list_push_front(list, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	rv = cdada_list_get(list, 0, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 9ULL);
	rv = cdada_list_get(list, 1, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 0ULL);
	rv = cdada_list_get(list, 2, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 1ULL);
	rv = cdada_list_get(list, 3, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 7ULL);
	rv = cdada_list_get(list, 4, &key);
	TEST_ASSERT(rv == CDADA_E_NOT_FOUND);
	rv = cdada_list_get(list, 222, &key);
	TEST_ASSERT(rv == CDADA_E_NOT_FOUND);
	TEST_ASSERT(key == 7ULL);
	TEST_ASSERT(cdada_list_size(list) == 4);
	TEST_ASSERT(cdada_list_empty(list) == false);

	//Erase {9, 1, 7}
	rv = cdada_list_erase(list, 1);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	rv = cdada_list_get(list, 0, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 9ULL);
	rv = cdada_list_get(list, 1, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 1ULL);
	rv = cdada_list_get(list, 2, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 7ULL);
	rv = cdada_list_get(list, 3, &key);
	TEST_ASSERT(rv == CDADA_E_NOT_FOUND);
	rv = cdada_list_get(list, 222, &key);
	TEST_ASSERT(rv == CDADA_E_NOT_FOUND);
	TEST_ASSERT(key == 7ULL);
	TEST_ASSERT(cdada_list_size(list) == 3);
	TEST_ASSERT(cdada_list_empty(list) == false);

	//POP front {1,7}
	rv = cdada_list_pop_front(list);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	rv = cdada_list_get(list, 0, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 1ULL);
	rv = cdada_list_get(list, 1, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 7ULL);
	rv = cdada_list_get(list, 2, &key);
	TEST_ASSERT(rv == CDADA_E_NOT_FOUND);
	rv = cdada_list_get(list, 222, &key);
	TEST_ASSERT(rv == CDADA_E_NOT_FOUND);
	TEST_ASSERT(key == 7ULL);
	TEST_ASSERT(cdada_list_size(list) == 2);
	TEST_ASSERT(cdada_list_empty(list) == false);


	//POP back {1}
	rv = cdada_list_pop_back(list);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	rv = cdada_list_get(list, 0, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 1ULL);
	rv = cdada_list_get(list, 2, &key);
	TEST_ASSERT(rv == CDADA_E_NOT_FOUND);
	rv = cdada_list_get(list, 222, &key);
	TEST_ASSERT(rv == CDADA_E_NOT_FOUND);
	TEST_ASSERT(key == 1ULL);
	TEST_ASSERT(cdada_list_size(list) == 1);
	TEST_ASSERT(cdada_list_empty(list) == false);

	//Add many 0s {1, 0, 0, 0, 0, 0}
	for(i=0;i<5; ++i){
		key = 0ULL;
		rv = cdada_list_push_back(list, &key);
		TEST_ASSERT(rv == CDADA_SUCCESS);
		TEST_ASSERT(key == 0ULL);
	}

	rv = cdada_list_first(list, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 1ULL);

	rv = cdada_list_last(list, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 0ULL);

	TEST_ASSERT(cdada_list_size(list) == 6);
	TEST_ASSERT(cdada_list_empty(list) == false);

	rv = cdada_list_get(list, 0, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 1ULL);
	rv = cdada_list_get(list, 1, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 0ULL);
	rv = cdada_list_get(list, 5, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 0ULL);
	rv = cdada_list_get(list, 6, &key);
	TEST_ASSERT(rv == CDADA_E_NOT_FOUND);
	TEST_ASSERT(key == 0ULL);

	//Sort {0, 0, 0, 0, 0, 1}
	rv = cdada_list_sort(list);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	rv = cdada_list_get(list, 0, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 0ULL);
	rv = cdada_list_get(list, 1, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 0ULL);
	rv = cdada_list_get(list, 5, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 1ULL);
	rv = cdada_list_get(list, 6, &key);
	TEST_ASSERT(rv == CDADA_E_NOT_FOUND);
	TEST_ASSERT(key == 1ULL);

	//Reverse {1, 0, 0, 0, 0, 0}
	rv = cdada_list_reverse(list);
	rv = cdada_list_get(list, 0, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 1ULL);
	rv = cdada_list_get(list, 1, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 0ULL);
	rv = cdada_list_get(list, 5, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 0ULL);
	rv = cdada_list_get(list, 6, &key);
	TEST_ASSERT(rv == CDADA_E_NOT_FOUND);
	TEST_ASSERT(key == 0ULL);

	//Traverse
	opaque = 0ULL;
	cdada_list_traverse(list, &trav_u64, &opaque);
	opaque = 0ULL;
	cdada_list_rtraverse(list, &rtrav_u64, &opaque);

	//Unique {1, 0}
	rv = cdada_list_unique(list);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(cdada_list_size(list) == 2);
	TEST_ASSERT(cdada_list_empty(list) == false);
	rv = cdada_list_get(list, 0, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 1ULL);
	rv = cdada_list_get(list, 1, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 0ULL);
	rv = cdada_list_get(list, 2, &key);
	TEST_ASSERT(rv == CDADA_E_NOT_FOUND);
	TEST_ASSERT(key == 0ULL);
	TEST_ASSERT(cdada_list_size(list) == 2);
	TEST_ASSERT(cdada_list_empty(list) == false);

	//Insert 5s {5, 1, 0, 5}
	key = 5ULL;
	rv = cdada_list_insert(list, &key, 0);
	rv |= cdada_list_insert(list, &key, 4);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	rv = cdada_list_get(list, 0, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 5ULL);
	rv = cdada_list_get(list, 1, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 1ULL);
	rv = cdada_list_get(list, 2, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 0ULL);
	rv = cdada_list_get(list, 3, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 5ULL);
	TEST_ASSERT(cdada_list_size(list) == 4);
	TEST_ASSERT(cdada_list_empty(list) == false);

	//Remove API {1,0}
	rv = cdada_list_remove(list, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(cdada_list_size(list) == 2);
	TEST_ASSERT(cdada_list_empty(list) == false);
	rv = cdada_list_get(list, 0, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 1ULL);
	rv = cdada_list_get(list, 1, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 0ULL);
	rv = cdada_list_get(list, 2, &key);
	TEST_ASSERT(rv == CDADA_E_NOT_FOUND);
	TEST_ASSERT(key == 0ULL);

	rv = cdada_list_clear(list);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(cdada_list_size(list) == 0);
	TEST_ASSERT(cdada_list_empty(list) == true);

	rv = cdada_list_destroy(list);
	TEST_ASSERT(rv == CDADA_SUCCESS);

	return 0;
}

int test_basics(){

	int rv;

	void* ptr_not_null = (void*)0x123;

	//Create
	list = cdada_list_create(sizeof(int));
	TEST_ASSERT(list != NULL);

	TEST_ASSERT(cdada_list_size(list) == 0);
	TEST_ASSERT(cdada_list_empty(list) == true);

	//Try all APIs with a NULL list/key/val
	TEST_ASSERT(cdada_list_size(NULL) == 0);
	TEST_ASSERT(cdada_list_empty(NULL) == false);
	rv = cdada_list_destroy(NULL);
	TEST_ASSERT(rv == CDADA_E_INVALID);

	rv = cdada_list_traverse(NULL, ptr_not_null, NULL);
	TEST_ASSERT(rv == CDADA_E_INVALID);
	rv = cdada_list_traverse(list, NULL, NULL);
	TEST_ASSERT(rv == CDADA_E_INVALID);
	rv = cdada_list_rtraverse(NULL, ptr_not_null, NULL);
	TEST_ASSERT(rv == CDADA_E_INVALID);
	rv = cdada_list_rtraverse(list, NULL, NULL);
	TEST_ASSERT(rv == CDADA_E_INVALID);

	rv = cdada_list_insert(NULL, ptr_not_null, 0);
	TEST_ASSERT(rv == CDADA_E_INVALID);
	rv = cdada_list_insert(list, NULL, 0);
	TEST_ASSERT(rv == CDADA_E_INVALID);
	rv = cdada_list_erase(NULL, 0);
	TEST_ASSERT(rv == CDADA_E_INVALID);

	rv = cdada_list_clear(NULL);
	TEST_ASSERT(rv == CDADA_E_INVALID);
	rv = cdada_list_sort(NULL);
	TEST_ASSERT(rv == CDADA_E_INVALID);
	rv = cdada_list_reverse(NULL);
	TEST_ASSERT(rv == CDADA_E_INVALID);
	rv = cdada_list_unique(NULL);
	TEST_ASSERT(rv == CDADA_E_INVALID);

	rv = cdada_list_push_front(NULL, ptr_not_null);
	TEST_ASSERT(rv == CDADA_E_INVALID);
	rv = cdada_list_push_front(list, NULL);
	TEST_ASSERT(rv == CDADA_E_INVALID);
	rv = cdada_list_push_back(NULL, ptr_not_null);
	TEST_ASSERT(rv == CDADA_E_INVALID);
	rv = cdada_list_push_back(list, NULL);
	TEST_ASSERT(rv == CDADA_E_INVALID);

	rv = cdada_list_pop_front(NULL);
	TEST_ASSERT(rv == CDADA_E_INVALID);
	rv = cdada_list_pop_back(NULL);
	TEST_ASSERT(rv == CDADA_E_INVALID);

	rv = cdada_list_remove(NULL, ptr_not_null);
	TEST_ASSERT(rv == CDADA_E_INVALID);
	rv = cdada_list_remove(list, NULL);
	TEST_ASSERT(rv == CDADA_E_INVALID);


	//Now destroy
	rv = cdada_list_destroy(list);
	TEST_ASSERT(rv == CDADA_SUCCESS);

	//Create with valid and invalid
	list = cdada_list_create(256);
	TEST_ASSERT(list != NULL);
	rv = cdada_list_destroy(list);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	list = cdada_list_create(257);
	TEST_ASSERT(list == NULL);

	return 0;
}

//
// Key is not complete
//

void trav_u552(const cdada_list_t* s, const void* k, void* o){
	TEST_ASSERT(o == &opaque);
	TEST_ASSERT(list == s);
	test_u552_t key = *(test_u552_t*)k;
	switch(opaque){
		case 0:
			TEST_ASSERT(key.mid == 1ULL);
			break;
		case 1:
		case 2:
		case 3:
		case 4:
		case 5:
			TEST_ASSERT(key.mid == 0ULL);
			break;
		default:
			TEST_ASSERT(0);
			break;
	}

	opaque++;
}

void rtrav_u552(const cdada_list_t* s, const void* k, void* o){
	TEST_ASSERT(o == &opaque);
	TEST_ASSERT(list == s);
	test_u552_t key = *(test_u552_t*)k;
	switch(opaque){
		case 0:
		case 1:
		case 2:
		case 3:
		case 4:
			TEST_ASSERT(key.mid == 0ULL);
			break;

		case 5:
			TEST_ASSERT(key.mid == 1ULL);
			break;
		default:
			TEST_ASSERT(0);
			break;
	}

	opaque++;
}

int _test_u552_insert_removal_traverse(){

	int i, rv;
	test_u552_t key;

	memset(&key, 0, sizeof(key));

	TEST_ASSERT(cdada_list_size(list) == 0);
	TEST_ASSERT(cdada_list_empty(list) == true);
	TEST_ASSERT(cdada_list_first(list, &key) == CDADA_E_NOT_FOUND);
	TEST_ASSERT(cdada_list_last(list, &key) == CDADA_E_NOT_FOUND);

	//Add one key & get
	key.mid = 0;
	rv = cdada_list_insert(list, &key, 0);
	TEST_ASSERT(rv == CDADA_SUCCESS);

	rv = cdada_list_first(list, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key.mid == 0);
	rv = cdada_list_last(list, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key.mid == 0);

	TEST_ASSERT(cdada_list_size(list) == 1);
	TEST_ASSERT(cdada_list_empty(list) == false);

	rv = cdada_list_get(list, 0, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key.mid == 0);

	//Get a value > size shall fail
	rv = cdada_list_get(list, 1, &key);
	TEST_ASSERT(rv == CDADA_E_NOT_FOUND);
	rv = cdada_list_get(list, 222, &key);
	TEST_ASSERT(rv == CDADA_E_NOT_FOUND);

	//Add 1 after
	key.mid = 1;
	rv = cdada_list_insert(list, &key, 1);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	rv = cdada_list_get(list, 0, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key.mid == 0);
	rv = cdada_list_get(list, 1, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key.mid == 1);
	rv = cdada_list_get(list, 222, &key);
	TEST_ASSERT(rv == CDADA_E_NOT_FOUND);
	TEST_ASSERT(key.mid == 1);

	//PUSH tests resulting list should be {9, 0, 1, 7}
	key.mid = 7;
	rv = cdada_list_push_back(list, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key.mid == 7);
	key.mid = 9;
	rv = cdada_list_push_front(list, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	rv = cdada_list_get(list, 0, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key.mid == 9);
	rv = cdada_list_get(list, 1, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key.mid == 0);
	rv = cdada_list_get(list, 2, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key.mid == 1);
	rv = cdada_list_get(list, 3, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key.mid == 7);
	rv = cdada_list_get(list, 4, &key);
	TEST_ASSERT(rv == CDADA_E_NOT_FOUND);
	rv = cdada_list_get(list, 222, &key);
	TEST_ASSERT(rv == CDADA_E_NOT_FOUND);
	TEST_ASSERT(key.mid == 7);
	TEST_ASSERT(cdada_list_size(list) == 4);
	TEST_ASSERT(cdada_list_empty(list) == false);

	//Erase {9, 1, 7}
	rv = cdada_list_erase(list, 1);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	rv = cdada_list_get(list, 0, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key.mid == 9);
	rv = cdada_list_get(list, 1, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key.mid == 1);
	rv = cdada_list_get(list, 2, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key.mid == 7);
	rv = cdada_list_get(list, 3, &key);
	TEST_ASSERT(rv == CDADA_E_NOT_FOUND);
	rv = cdada_list_get(list, 222, &key);
	TEST_ASSERT(rv == CDADA_E_NOT_FOUND);
	TEST_ASSERT(key.mid == 7);
	TEST_ASSERT(cdada_list_size(list) == 3);
	TEST_ASSERT(cdada_list_empty(list) == false);

	//POP front {1,7}
	rv = cdada_list_pop_front(list);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	rv = cdada_list_get(list, 0, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key.mid == 1);
	rv = cdada_list_get(list, 1, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key.mid == 7);
	rv = cdada_list_get(list, 2, &key);
	TEST_ASSERT(rv == CDADA_E_NOT_FOUND);
	rv = cdada_list_get(list, 222, &key);
	TEST_ASSERT(rv == CDADA_E_NOT_FOUND);
	TEST_ASSERT(key.mid == 7);
	TEST_ASSERT(cdada_list_size(list) == 2);
	TEST_ASSERT(cdada_list_empty(list) == false);


	//POP back {1}
	rv = cdada_list_pop_back(list);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	rv = cdada_list_get(list, 0, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key.mid == 1);
	rv = cdada_list_get(list, 2, &key);
	TEST_ASSERT(rv == CDADA_E_NOT_FOUND);
	rv = cdada_list_get(list, 222, &key);
	TEST_ASSERT(rv == CDADA_E_NOT_FOUND);
	TEST_ASSERT(key.mid == 1);
	TEST_ASSERT(cdada_list_size(list) == 1);
	TEST_ASSERT(cdada_list_empty(list) == false);

	//Add many 0s {1, 0, 0, 0, 0, 0}
	for(i=0;i<5; ++i){
		key.mid = 0;
		rv = cdada_list_push_back(list, &key);
		TEST_ASSERT(rv == CDADA_SUCCESS);
		TEST_ASSERT(key.mid == 0);
	}

	rv = cdada_list_first(list, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key.mid == 1);

	rv = cdada_list_last(list, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key.mid == 0);

	TEST_ASSERT(cdada_list_size(list) == 6);
	TEST_ASSERT(cdada_list_empty(list) == false);

	rv = cdada_list_get(list, 0, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key.mid == 1);
	rv = cdada_list_get(list, 1, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key.mid == 0);
	rv = cdada_list_get(list, 5, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key.mid == 0);
	rv = cdada_list_get(list, 6, &key);
	TEST_ASSERT(rv == CDADA_E_NOT_FOUND);
	TEST_ASSERT(key.mid == 0);

	//Sort {0, 0, 0, 0, 0, 1}
	rv = cdada_list_sort(list);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	rv = cdada_list_get(list, 0, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key.mid == 0);
	rv = cdada_list_get(list, 1, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key.mid == 0);
	rv = cdada_list_get(list, 5, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key.mid == 1);
	rv = cdada_list_get(list, 6, &key);
	TEST_ASSERT(rv == CDADA_E_NOT_FOUND);
	TEST_ASSERT(key.mid == 1);

	//Reverse {1, 0, 0, 0, 0, 0}
	rv = cdada_list_reverse(list);
	rv = cdada_list_get(list, 0, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key.mid == 1);
	rv = cdada_list_get(list, 1, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key.mid == 0);
	rv = cdada_list_get(list, 5, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key.mid == 0);
	rv = cdada_list_get(list, 6, &key);
	TEST_ASSERT(rv == CDADA_E_NOT_FOUND);
	TEST_ASSERT(key.mid == 0);

	//Traverse
	opaque = 0;
	cdada_list_traverse(list, &trav_u552, &opaque);
	opaque = 0;
	cdada_list_rtraverse(list, &rtrav_u552, &opaque);

	//Unique {1, 0}
	rv = cdada_list_unique(list);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(cdada_list_size(list) == 2);
	TEST_ASSERT(cdada_list_empty(list) == false);
	rv = cdada_list_get(list, 0, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key.mid == 1);
	rv = cdada_list_get(list, 1, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key.mid == 0);
	rv = cdada_list_get(list, 2, &key);
	TEST_ASSERT(rv == CDADA_E_NOT_FOUND);
	TEST_ASSERT(key.mid == 0);
	TEST_ASSERT(cdada_list_size(list) == 2);
	TEST_ASSERT(cdada_list_empty(list) == false);

	//Insert 5s {5, 1, 0, 5}
	key.mid = 5;
	rv = cdada_list_insert(list, &key, 0);
	rv |= cdada_list_insert(list, &key, 4);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	rv = cdada_list_get(list, 0, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key.mid == 5);
	rv = cdada_list_get(list, 1, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key.mid == 1);
	rv = cdada_list_get(list, 2, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key.mid == 0);
	rv = cdada_list_get(list, 3, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key.mid == 5);
	TEST_ASSERT(cdada_list_size(list) == 4);
	TEST_ASSERT(cdada_list_empty(list) == false);

	//Remove API {1,0}
	rv = cdada_list_remove(list, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(cdada_list_size(list) == 2);
	TEST_ASSERT(cdada_list_empty(list) == false);
	rv = cdada_list_get(list, 0, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key.mid == 1);
	rv = cdada_list_get(list, 1, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key.mid == 0);
	rv = cdada_list_get(list, 2, &key);
	TEST_ASSERT(rv == CDADA_E_NOT_FOUND);
	TEST_ASSERT(key.mid == 0);

	rv = cdada_list_clear(list);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(cdada_list_size(list) == 0);
	TEST_ASSERT(cdada_list_empty(list) == true);

	rv = cdada_list_destroy(list);
	TEST_ASSERT(rv == CDADA_SUCCESS);

	return 0;
}

int test_u552_insert_removal_traverse(){
	list = cdada_list_create(sizeof(test_u552_t));
	TEST_ASSERT(list != NULL);

	return _test_u552_insert_removal_traverse();
}

int test_u552_insert_removal_traverse_custom(){
	list = cdada_list_create_custom(test_u552_t);
	TEST_ASSERT(list != NULL);

	return _test_u552_insert_removal_traverse();
}

int test_u3552_insert_removal_traverse_custom(){

	int i, rv;
	test_u3552_t key;

	list = cdada_list_create_custom(test_u3552_t);
	TEST_ASSERT(list != NULL);

	memset(&key, 0, sizeof(key));

	TEST_ASSERT(cdada_list_size(list) == 0);
	TEST_ASSERT(cdada_list_empty(list) == true);
	TEST_ASSERT(cdada_list_first(list, &key) == CDADA_E_NOT_FOUND);
	TEST_ASSERT(cdada_list_last(list, &key) == CDADA_E_NOT_FOUND);

	//Add one key & get
	key.mid = 0;
	rv = cdada_list_insert(list, &key, 0);
	TEST_ASSERT(rv == CDADA_SUCCESS);

	rv = cdada_list_first(list, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key.mid == 0);
	rv = cdada_list_last(list, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key.mid == 0);

	TEST_ASSERT(cdada_list_size(list) == 1);
	TEST_ASSERT(cdada_list_empty(list) == false);

	rv = cdada_list_get(list, 0, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key.mid == 0);

	//Get a value > size shall fail
	rv = cdada_list_get(list, 1, &key);
	TEST_ASSERT(rv == CDADA_E_NOT_FOUND);
	rv = cdada_list_get(list, 222, &key);
	TEST_ASSERT(rv == CDADA_E_NOT_FOUND);

	//Add 1 after
	key.mid = 1;
	rv = cdada_list_insert(list, &key, 1);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	rv = cdada_list_get(list, 0, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key.mid == 0);
	rv = cdada_list_get(list, 1, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key.mid == 1);
	rv = cdada_list_get(list, 222, &key);
	TEST_ASSERT(rv == CDADA_E_NOT_FOUND);
	TEST_ASSERT(key.mid == 1);

	//PUSH tests resulting list should be {9, 0, 1, 7}
	key.mid = 7;
	rv = cdada_list_push_back(list, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key.mid == 7);
	key.mid = 9;
	rv = cdada_list_push_front(list, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	rv = cdada_list_get(list, 0, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key.mid == 9);
	rv = cdada_list_get(list, 1, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key.mid == 0);
	rv = cdada_list_get(list, 2, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key.mid == 1);
	rv = cdada_list_get(list, 3, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key.mid == 7);
	rv = cdada_list_get(list, 4, &key);
	TEST_ASSERT(rv == CDADA_E_NOT_FOUND);
	rv = cdada_list_get(list, 222, &key);
	TEST_ASSERT(rv == CDADA_E_NOT_FOUND);
	TEST_ASSERT(key.mid == 7);
	TEST_ASSERT(cdada_list_size(list) == 4);
	TEST_ASSERT(cdada_list_empty(list) == false);

	//Erase {9, 1, 7}
	rv = cdada_list_erase(list, 1);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	rv = cdada_list_get(list, 0, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key.mid == 9);
	rv = cdada_list_get(list, 1, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key.mid == 1);
	rv = cdada_list_get(list, 2, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key.mid == 7);
	rv = cdada_list_get(list, 3, &key);
	TEST_ASSERT(rv == CDADA_E_NOT_FOUND);
	rv = cdada_list_get(list, 222, &key);
	TEST_ASSERT(rv == CDADA_E_NOT_FOUND);
	TEST_ASSERT(key.mid == 7);
	TEST_ASSERT(cdada_list_size(list) == 3);
	TEST_ASSERT(cdada_list_empty(list) == false);

	//POP front {1,7}
	rv = cdada_list_pop_front(list);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	rv = cdada_list_get(list, 0, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key.mid == 1);
	rv = cdada_list_get(list, 1, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key.mid == 7);
	rv = cdada_list_get(list, 2, &key);
	TEST_ASSERT(rv == CDADA_E_NOT_FOUND);
	rv = cdada_list_get(list, 222, &key);
	TEST_ASSERT(rv == CDADA_E_NOT_FOUND);
	TEST_ASSERT(key.mid == 7);
	TEST_ASSERT(cdada_list_size(list) == 2);
	TEST_ASSERT(cdada_list_empty(list) == false);


	//POP back {1}
	rv = cdada_list_pop_back(list);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	rv = cdada_list_get(list, 0, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key.mid == 1);
	rv = cdada_list_get(list, 2, &key);
	TEST_ASSERT(rv == CDADA_E_NOT_FOUND);
	rv = cdada_list_get(list, 222, &key);
	TEST_ASSERT(rv == CDADA_E_NOT_FOUND);
	TEST_ASSERT(key.mid == 1);
	TEST_ASSERT(cdada_list_size(list) == 1);
	TEST_ASSERT(cdada_list_empty(list) == false);

	//Add many 0s {1, 0, 0, 0, 0, 0}
	for(i=0;i<5; ++i){
		key.mid = 0;
		rv = cdada_list_push_back(list, &key);
		TEST_ASSERT(rv == CDADA_SUCCESS);
		TEST_ASSERT(key.mid == 0);
	}

	rv = cdada_list_first(list, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key.mid == 1);

	rv = cdada_list_last(list, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key.mid == 0);

	TEST_ASSERT(cdada_list_size(list) == 6);
	TEST_ASSERT(cdada_list_empty(list) == false);

	rv = cdada_list_get(list, 0, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key.mid == 1);
	rv = cdada_list_get(list, 1, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key.mid == 0);
	rv = cdada_list_get(list, 5, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key.mid == 0);
	rv = cdada_list_get(list, 6, &key);
	TEST_ASSERT(rv == CDADA_E_NOT_FOUND);
	TEST_ASSERT(key.mid == 0);

	//Sort {0, 0, 0, 0, 0, 1}
	rv = cdada_list_sort(list);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	rv = cdada_list_get(list, 0, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key.mid == 0);
	rv = cdada_list_get(list, 1, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key.mid == 0);
	rv = cdada_list_get(list, 5, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key.mid == 1);
	rv = cdada_list_get(list, 6, &key);
	TEST_ASSERT(rv == CDADA_E_NOT_FOUND);
	TEST_ASSERT(key.mid == 1);

	//Reverse {1, 0, 0, 0, 0, 0}
	rv = cdada_list_reverse(list);
	rv = cdada_list_get(list, 0, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key.mid == 1);
	rv = cdada_list_get(list, 1, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key.mid == 0);
	rv = cdada_list_get(list, 5, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key.mid == 0);
	rv = cdada_list_get(list, 6, &key);
	TEST_ASSERT(rv == CDADA_E_NOT_FOUND);
	TEST_ASSERT(key.mid == 0);

	//Traverse
	opaque = 0;
	cdada_list_traverse(list, &trav_u552, &opaque);
	opaque = 0;
	cdada_list_rtraverse(list, &rtrav_u552, &opaque);

	//Unique {1, 0}
	rv = cdada_list_unique(list);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(cdada_list_size(list) == 2);
	TEST_ASSERT(cdada_list_empty(list) == false);
	rv = cdada_list_get(list, 0, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key.mid == 1);
	rv = cdada_list_get(list, 1, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key.mid == 0);
	rv = cdada_list_get(list, 2, &key);
	TEST_ASSERT(rv == CDADA_E_NOT_FOUND);
	TEST_ASSERT(key.mid == 0);
	TEST_ASSERT(cdada_list_size(list) == 2);
	TEST_ASSERT(cdada_list_empty(list) == false);

	//Insert 5s {5, 1, 0, 5}
	key.mid = 5;
	rv = cdada_list_insert(list, &key, 0);
	rv |= cdada_list_insert(list, &key, 4);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	rv = cdada_list_get(list, 0, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key.mid == 5);
	rv = cdada_list_get(list, 1, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key.mid == 1);
	rv = cdada_list_get(list, 2, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key.mid == 0);
	rv = cdada_list_get(list, 3, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key.mid == 5);
	TEST_ASSERT(cdada_list_size(list) == 4);
	TEST_ASSERT(cdada_list_empty(list) == false);

	//Remove API {1,0}
	rv = cdada_list_remove(list, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(cdada_list_size(list) == 2);
	TEST_ASSERT(cdada_list_empty(list) == false);
	rv = cdada_list_get(list, 0, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key.mid == 1);
	rv = cdada_list_get(list, 1, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key.mid == 0);
	rv = cdada_list_get(list, 2, &key);
	TEST_ASSERT(rv == CDADA_E_NOT_FOUND);
	TEST_ASSERT(key.mid == 0);

	rv = cdada_list_clear(list);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(cdada_list_size(list) == 0);
	TEST_ASSERT(cdada_list_empty(list) == true);

	rv = cdada_list_destroy(list);
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
	rv |= test_u552_insert_removal_traverse_custom();
	rv |= test_u3552_insert_removal_traverse_custom();

	//Add your test here, and return a code appropriately...
	return rv == 0? EXIT_SUCCESS : EXIT_FAILURE;
}
