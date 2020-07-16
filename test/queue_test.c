#include <stdlib.h>

#include "cdada/queue.h"
#include "common.h"
#include <string.h>
#include "u552.h"
#include "u3552.h"

//Fwd decl
CDADA_QUEUE_CUSTOM_TYPE_DECL(test_u552_t);
CDADA_QUEUE_CUSTOM_TYPE_DECL(test_u3552_t);

//static uint64_t opaque = 0ULL;
static cdada_queue_t* queue = NULL;

//
// Aligned types
//

//8
int test_u8_push_pop(){

	int i, rv;
	uint8_t key;

	queue = cdada_queue_create(uint8_t);
	TEST_ASSERT(queue != NULL);

	TEST_ASSERT(cdada_queue_size(queue) == 0);
	TEST_ASSERT(cdada_queue_empty(queue) == true);
	TEST_ASSERT(cdada_queue_back(queue, &key) == CDADA_E_NOT_FOUND);

	//Add one key & get
	key = 0;
	rv = cdada_queue_push(queue, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	key = 0xff;
	rv = cdada_queue_back(queue, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 0);
	rv = cdada_queue_front(queue, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 0);
	TEST_ASSERT(cdada_queue_size(queue) == 1);
	TEST_ASSERT(cdada_queue_empty(queue) == false);

	//Add 1 on back
	key = 1;
	rv = cdada_queue_push(queue, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	key = 0xff;
	rv = cdada_queue_back(queue, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 1);
	rv = cdada_queue_front(queue, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 0);
	TEST_ASSERT(cdada_queue_size(queue) == 2);
	TEST_ASSERT(cdada_queue_empty(queue) == false);

	//PUSH tests resulting queue should be {0, 1, 7, 9}
	key = 7;
	rv = cdada_queue_push(queue, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 7);
	TEST_ASSERT(cdada_queue_size(queue) == 3);
	TEST_ASSERT(cdada_queue_empty(queue) == false);
	key = 0xff;
	rv = cdada_queue_back(queue, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 7);
	rv = cdada_queue_front(queue, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 0);

	key = 9;
	rv = cdada_queue_push(queue, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 9);
	TEST_ASSERT(cdada_queue_size(queue) == 4);
	TEST_ASSERT(cdada_queue_empty(queue) == false);
	rv = cdada_queue_front(queue, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 0);

	key = 0xff;
	rv = cdada_queue_back(queue, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 9);
	rv = cdada_queue_front(queue, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 0);
	rv = cdada_queue_pop(queue);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(cdada_queue_size(queue) == 3);
	TEST_ASSERT(cdada_queue_empty(queue) == false);

	key = 0xff;
	rv = cdada_queue_front(queue, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 1);
	rv = cdada_queue_back(queue, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 9);
	rv = cdada_queue_pop(queue);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(cdada_queue_size(queue) == 2);
	TEST_ASSERT(cdada_queue_empty(queue) == false);

	key = 0xff;
	rv = cdada_queue_front(queue, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 7);
	rv = cdada_queue_pop(queue);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(cdada_queue_size(queue) == 1);
	TEST_ASSERT(cdada_queue_empty(queue) == false);

	key = 0xff;
	rv = cdada_queue_back(queue, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 9);
	rv = cdada_queue_pop(queue);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	rv = cdada_queue_pop(queue);
	TEST_ASSERT(rv == CDADA_E_NOT_FOUND);
	TEST_ASSERT(cdada_queue_size(queue) == 0);
	TEST_ASSERT(cdada_queue_empty(queue) == true);

	//Add many 0s {1, 0, 0, 0, 0, 0}
	key = 1;
	rv = cdada_queue_push(queue, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 1);
	key = 0xff;
	rv = cdada_queue_back(queue, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 1);
	rv = cdada_queue_front(queue, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 1);

	for(i=0;i<5; ++i){
		key = 0;
		rv = cdada_queue_push(queue, &key);
		TEST_ASSERT(rv == CDADA_SUCCESS);
		TEST_ASSERT(key == 0);
		key = 0xff;
		rv = cdada_queue_back(queue, &key);
		TEST_ASSERT(rv == CDADA_SUCCESS);
		TEST_ASSERT(key == 0);
		rv = cdada_queue_front(queue, &key);
		TEST_ASSERT(rv == CDADA_SUCCESS);
		TEST_ASSERT(key == 1);
		TEST_ASSERT(cdada_queue_size(queue) == (i + 2));
		TEST_ASSERT(cdada_queue_empty(queue) == false);
	}

	//Dumpers
	rv = cdada_queue_print(queue, stdout);
	TEST_ASSERT(rv == CDADA_SUCCESS);

	char buffer[128];
	uint32_t used;
	rv = cdada_queue_dump(queue, 128, buffer, &used);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	fprintf(stdout, "%s\n", buffer);

	char buffer2[8];
	rv = cdada_queue_dump(queue, 8, buffer2, &used);
	TEST_ASSERT(rv == CDADA_E_INCOMPLETE);
	fprintf(stdout, "%s\n", buffer2);

	TEST_ASSERT(cdada_queue_size(queue) == 6);
	TEST_ASSERT(cdada_queue_empty(queue) == false);

	rv = cdada_queue_destroy(queue);
	TEST_ASSERT(rv == CDADA_SUCCESS);

	return 0;
}

//16
int test_u16_push_pop(){

	int i, rv;
	uint16_t key;

	queue = cdada_queue_create(uint16_t);
	TEST_ASSERT(queue != NULL);

	TEST_ASSERT(cdada_queue_size(queue) == 0);
	TEST_ASSERT(cdada_queue_empty(queue) == true);
	TEST_ASSERT(cdada_queue_back(queue, &key) == CDADA_E_NOT_FOUND);

	//Add one key & get
	key = 0;
	rv = cdada_queue_push(queue, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	key = 0xff;
	rv = cdada_queue_back(queue, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 0);
	rv = cdada_queue_front(queue, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 0);
	TEST_ASSERT(cdada_queue_size(queue) == 1);
	TEST_ASSERT(cdada_queue_empty(queue) == false);

	//Add 1 on back
	key = 1;
	rv = cdada_queue_push(queue, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	key = 0xff;
	rv = cdada_queue_back(queue, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 1);
	rv = cdada_queue_front(queue, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 0);
	TEST_ASSERT(cdada_queue_size(queue) == 2);
	TEST_ASSERT(cdada_queue_empty(queue) == false);

	//PUSH tests resulting queue should be {0, 1, 7, 9}
	key = 7;
	rv = cdada_queue_push(queue, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 7);
	TEST_ASSERT(cdada_queue_size(queue) == 3);
	TEST_ASSERT(cdada_queue_empty(queue) == false);
	key = 0xff;
	rv = cdada_queue_back(queue, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 7);
	rv = cdada_queue_front(queue, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 0);

	key = 9;
	rv = cdada_queue_push(queue, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 9);
	TEST_ASSERT(cdada_queue_size(queue) == 4);
	TEST_ASSERT(cdada_queue_empty(queue) == false);
	rv = cdada_queue_front(queue, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 0);

	key = 0xff;
	rv = cdada_queue_back(queue, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 9);
	rv = cdada_queue_front(queue, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 0);
	rv = cdada_queue_pop(queue);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(cdada_queue_size(queue) == 3);
	TEST_ASSERT(cdada_queue_empty(queue) == false);

	key = 0xff;
	rv = cdada_queue_front(queue, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 1);
	rv = cdada_queue_back(queue, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 9);
	rv = cdada_queue_pop(queue);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(cdada_queue_size(queue) == 2);
	TEST_ASSERT(cdada_queue_empty(queue) == false);

	key = 0xff;
	rv = cdada_queue_front(queue, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 7);
	rv = cdada_queue_pop(queue);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(cdada_queue_size(queue) == 1);
	TEST_ASSERT(cdada_queue_empty(queue) == false);

	key = 0xff;
	rv = cdada_queue_back(queue, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 9);
	rv = cdada_queue_pop(queue);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	rv = cdada_queue_pop(queue);
	TEST_ASSERT(rv == CDADA_E_NOT_FOUND);
	TEST_ASSERT(cdada_queue_size(queue) == 0);
	TEST_ASSERT(cdada_queue_empty(queue) == true);

	//Add many 0s {1, 0, 0, 0, 0, 0}
	key = 1;
	rv = cdada_queue_push(queue, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 1);
	key = 0xff;
	rv = cdada_queue_back(queue, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 1);
	rv = cdada_queue_front(queue, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 1);

	for(i=0;i<5; ++i){
		key = 0;
		rv = cdada_queue_push(queue, &key);
		TEST_ASSERT(rv == CDADA_SUCCESS);
		TEST_ASSERT(key == 0);
		key = 0xff;
		rv = cdada_queue_back(queue, &key);
		TEST_ASSERT(rv == CDADA_SUCCESS);
		TEST_ASSERT(key == 0);
		rv = cdada_queue_front(queue, &key);
		TEST_ASSERT(rv == CDADA_SUCCESS);
		TEST_ASSERT(key == 1);
		TEST_ASSERT(cdada_queue_size(queue) == (i + 2));
		TEST_ASSERT(cdada_queue_empty(queue) == false);
	}

	//Dumpers
	rv = cdada_queue_print(queue, stdout);
	TEST_ASSERT(rv == CDADA_SUCCESS);

	char buffer[128];
	uint32_t used;
	rv = cdada_queue_dump(queue, 128, buffer, &used);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	fprintf(stdout, "%s\n", buffer);

	char buffer2[8];
	rv = cdada_queue_dump(queue, 8, buffer2, &used);
	TEST_ASSERT(rv == CDADA_E_INCOMPLETE);
	fprintf(stdout, "%s\n", buffer2);

	TEST_ASSERT(cdada_queue_size(queue) == 6);
	TEST_ASSERT(cdada_queue_empty(queue) == false);

	rv = cdada_queue_destroy(queue);
	TEST_ASSERT(rv == CDADA_SUCCESS);

	return 0;

}

//32
int test_u32_push_pop(){

	int i, rv;
	uint32_t key;

	queue = cdada_queue_create(uint32_t);
	TEST_ASSERT(queue != NULL);

	TEST_ASSERT(cdada_queue_size(queue) == 0);
	TEST_ASSERT(cdada_queue_empty(queue) == true);
	TEST_ASSERT(cdada_queue_back(queue, &key) == CDADA_E_NOT_FOUND);

	//Add one key & get
	key = 0;
	rv = cdada_queue_push(queue, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	key = 0xff;
	rv = cdada_queue_back(queue, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 0);
	rv = cdada_queue_front(queue, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 0);
	TEST_ASSERT(cdada_queue_size(queue) == 1);
	TEST_ASSERT(cdada_queue_empty(queue) == false);

	//Add 1 on back
	key = 1;
	rv = cdada_queue_push(queue, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	key = 0xff;
	rv = cdada_queue_back(queue, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 1);
	rv = cdada_queue_front(queue, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 0);
	TEST_ASSERT(cdada_queue_size(queue) == 2);
	TEST_ASSERT(cdada_queue_empty(queue) == false);

	//PUSH tests resulting queue should be {0, 1, 7, 9}
	key = 7;
	rv = cdada_queue_push(queue, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 7);
	TEST_ASSERT(cdada_queue_size(queue) == 3);
	TEST_ASSERT(cdada_queue_empty(queue) == false);
	key = 0xff;
	rv = cdada_queue_back(queue, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 7);
	rv = cdada_queue_front(queue, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 0);

	key = 9;
	rv = cdada_queue_push(queue, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 9);
	TEST_ASSERT(cdada_queue_size(queue) == 4);
	TEST_ASSERT(cdada_queue_empty(queue) == false);
	rv = cdada_queue_front(queue, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 0);

	key = 0xff;
	rv = cdada_queue_back(queue, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 9);
	rv = cdada_queue_front(queue, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 0);
	rv = cdada_queue_pop(queue);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(cdada_queue_size(queue) == 3);
	TEST_ASSERT(cdada_queue_empty(queue) == false);

	key = 0xff;
	rv = cdada_queue_front(queue, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 1);
	rv = cdada_queue_back(queue, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 9);
	rv = cdada_queue_pop(queue);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(cdada_queue_size(queue) == 2);
	TEST_ASSERT(cdada_queue_empty(queue) == false);

	key = 0xff;
	rv = cdada_queue_front(queue, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 7);
	rv = cdada_queue_pop(queue);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(cdada_queue_size(queue) == 1);
	TEST_ASSERT(cdada_queue_empty(queue) == false);

	key = 0xff;
	rv = cdada_queue_back(queue, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 9);
	rv = cdada_queue_pop(queue);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	rv = cdada_queue_pop(queue);
	TEST_ASSERT(rv == CDADA_E_NOT_FOUND);
	TEST_ASSERT(cdada_queue_size(queue) == 0);
	TEST_ASSERT(cdada_queue_empty(queue) == true);

	//Add many 0s {1, 0, 0, 0, 0, 0}
	key = 1;
	rv = cdada_queue_push(queue, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 1);
	key = 0xff;
	rv = cdada_queue_back(queue, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 1);
	rv = cdada_queue_front(queue, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 1);

	for(i=0;i<5; ++i){
		key = 0;
		rv = cdada_queue_push(queue, &key);
		TEST_ASSERT(rv == CDADA_SUCCESS);
		TEST_ASSERT(key == 0);
		key = 0xff;
		rv = cdada_queue_back(queue, &key);
		TEST_ASSERT(rv == CDADA_SUCCESS);
		TEST_ASSERT(key == 0);
		rv = cdada_queue_front(queue, &key);
		TEST_ASSERT(rv == CDADA_SUCCESS);
		TEST_ASSERT(key == 1);
		TEST_ASSERT(cdada_queue_size(queue) == (i + 2));
		TEST_ASSERT(cdada_queue_empty(queue) == false);
	}

	//Dumpers
	rv = cdada_queue_print(queue, stdout);
	TEST_ASSERT(rv == CDADA_SUCCESS);

	char buffer[128];
	uint32_t used;
	rv = cdada_queue_dump(queue, 128, buffer, &used);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	fprintf(stdout, "%s\n", buffer);

	char buffer2[8];
	rv = cdada_queue_dump(queue, 8, buffer2, &used);
	TEST_ASSERT(rv == CDADA_E_INCOMPLETE);
	fprintf(stdout, "%s\n", buffer2);

	TEST_ASSERT(cdada_queue_size(queue) == 6);
	TEST_ASSERT(cdada_queue_empty(queue) == false);

	rv = cdada_queue_destroy(queue);
	TEST_ASSERT(rv == CDADA_SUCCESS);

	return 0;
}

//64
int test_u64_push_pop(){

	int i, rv;
	uint64_t key;

	queue = cdada_queue_create(uint64_t);
	TEST_ASSERT(queue != NULL);

	TEST_ASSERT(cdada_queue_size(queue) == 0);
	TEST_ASSERT(cdada_queue_empty(queue) == true);
	TEST_ASSERT(cdada_queue_back(queue, &key) == CDADA_E_NOT_FOUND);

	//Add one key & get
	key = 0ULL;
	rv = cdada_queue_push(queue, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	key = 0xffULL;
	rv = cdada_queue_back(queue, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 0ULL);
	rv = cdada_queue_front(queue, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 0ULL);
	TEST_ASSERT(cdada_queue_size(queue) == 1);
	TEST_ASSERT(cdada_queue_empty(queue) == false);

	//Add 1 on back
	key = 1ULL;
	rv = cdada_queue_push(queue, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	key = 0xffULL;
	rv = cdada_queue_back(queue, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 1ULL);
	rv = cdada_queue_front(queue, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 0ULL);
	TEST_ASSERT(cdada_queue_size(queue) == 2);
	TEST_ASSERT(cdada_queue_empty(queue) == false);

	//PUSH tests resulting queue should be {0, 1, 7, 9}
	key = 7ULL;
	rv = cdada_queue_push(queue, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 7ULL);
	TEST_ASSERT(cdada_queue_size(queue) == 3);
	TEST_ASSERT(cdada_queue_empty(queue) == false);
	key = 0xffULL;
	rv = cdada_queue_back(queue, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 7ULL);
	rv = cdada_queue_front(queue, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 0ULL);

	key = 9ULL;
	rv = cdada_queue_push(queue, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 9ULL);
	TEST_ASSERT(cdada_queue_size(queue) == 4);
	TEST_ASSERT(cdada_queue_empty(queue) == false);
	rv = cdada_queue_front(queue, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 0ULL);

	key = 0xffULL;
	rv = cdada_queue_back(queue, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 9ULL);
	rv = cdada_queue_front(queue, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 0ULL);
	rv = cdada_queue_pop(queue);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(cdada_queue_size(queue) == 3);
	TEST_ASSERT(cdada_queue_empty(queue) == false);

	key = 0xffULL;
	rv = cdada_queue_front(queue, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 1ULL);
	rv = cdada_queue_back(queue, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 9ULL);
	rv = cdada_queue_pop(queue);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(cdada_queue_size(queue) == 2);
	TEST_ASSERT(cdada_queue_empty(queue) == false);

	key = 0xffULL;
	rv = cdada_queue_front(queue, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 7ULL);
	rv = cdada_queue_pop(queue);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(cdada_queue_size(queue) == 1);
	TEST_ASSERT(cdada_queue_empty(queue) == false);

	key = 0xffULL;
	rv = cdada_queue_back(queue, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 9ULL);
	rv = cdada_queue_pop(queue);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	rv = cdada_queue_pop(queue);
	TEST_ASSERT(rv == CDADA_E_NOT_FOUND);
	TEST_ASSERT(cdada_queue_size(queue) == 0);
	TEST_ASSERT(cdada_queue_empty(queue) == true);

	//Add many 0s {1, 0, 0, 0, 0, 0}
	key = 1ULL;
	rv = cdada_queue_push(queue, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 1ULL);
	key = 0xffULL;
	rv = cdada_queue_back(queue, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 1ULL);
	rv = cdada_queue_front(queue, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 1ULL);

	for(i=0;i<5; ++i){
		key = 0ULL;
		rv = cdada_queue_push(queue, &key);
		TEST_ASSERT(rv == CDADA_SUCCESS);
		TEST_ASSERT(key == 0ULL);
		key = 0xffULL;
		rv = cdada_queue_back(queue, &key);
		TEST_ASSERT(rv == CDADA_SUCCESS);
		TEST_ASSERT(key == 0ULL);
		rv = cdada_queue_front(queue, &key);
		TEST_ASSERT(rv == CDADA_SUCCESS);
		TEST_ASSERT(key == 1ULL);
		TEST_ASSERT(cdada_queue_size(queue) == (i + 2));
		TEST_ASSERT(cdada_queue_empty(queue) == false);
	}

	//Dumpers
	rv = cdada_queue_print(queue, stdout);
	TEST_ASSERT(rv == CDADA_SUCCESS);

	char buffer[128];
	uint32_t used;
	rv = cdada_queue_dump(queue, 128, buffer, &used);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	fprintf(stdout, "%s\n", buffer);

	char buffer2[8];
	rv = cdada_queue_dump(queue, 8, buffer2, &used);
	TEST_ASSERT(rv == CDADA_E_INCOMPLETE);
	fprintf(stdout, "%s\n", buffer2);

	TEST_ASSERT(cdada_queue_size(queue) == 6);
	TEST_ASSERT(cdada_queue_empty(queue) == false);

	rv = cdada_queue_destroy(queue);
	TEST_ASSERT(rv == CDADA_SUCCESS);

	return 0;
}

int test_basics(){

	int rv;

	void* ptr_not_null = (void*)0x123;

	//Create
	queue = cdada_queue_create(int);
	TEST_ASSERT(queue != NULL);

	TEST_ASSERT(cdada_queue_size(queue) == 0);
	TEST_ASSERT(cdada_queue_empty(queue) == true);

	//Try all APIs with a NULL queue/key/val
	TEST_ASSERT(cdada_queue_size(NULL) == 0);
	TEST_ASSERT(cdada_queue_empty(NULL) == false);
	rv = cdada_queue_destroy(NULL);
	TEST_ASSERT(rv == CDADA_E_INVALID);

	rv = cdada_queue_push(NULL, ptr_not_null);
	TEST_ASSERT(rv == CDADA_E_INVALID);

	rv = cdada_queue_back(NULL, &ptr_not_null);
	TEST_ASSERT(rv == CDADA_E_INVALID);
	rv = cdada_queue_pop(NULL);
	TEST_ASSERT(rv == CDADA_E_INVALID);


	//Now destroy
	rv = cdada_queue_destroy(queue);
	TEST_ASSERT(rv == CDADA_SUCCESS);

	//Create with valid and invalid
	struct {
		char u[256];
	} c256;
	struct {
		char u[257];
	} c257;
	queue = cdada_queue_create(c256);
	TEST_ASSERT(queue != NULL);
	rv = cdada_queue_destroy(queue);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	queue = cdada_queue_create(c257);
	TEST_ASSERT(queue == NULL);

	return 0;
}

#include <unistd.h>

int _test_u552_push_pop(){

	int i, rv;
	test_u552_t key;

	memset(&key, 0, sizeof(key));

	TEST_ASSERT(cdada_queue_size(queue) == 0);
	TEST_ASSERT(cdada_queue_empty(queue) == true);
	TEST_ASSERT(cdada_queue_back(queue, &key) == CDADA_E_NOT_FOUND);

	//Add one key & get
	key.mid = 0;
	rv = cdada_queue_push(queue, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	key.mid = 0xff;
	rv = cdada_queue_back(queue, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key.mid == 0);
	rv = cdada_queue_front(queue, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key.mid == 0);
	TEST_ASSERT(cdada_queue_size(queue) == 1);
	TEST_ASSERT(cdada_queue_empty(queue) == false);

	//Add 1 on back
	key.mid = 1;
	rv = cdada_queue_push(queue, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	key.mid = 0xff;
	rv = cdada_queue_back(queue, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key.mid == 1);
	rv = cdada_queue_front(queue, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key.mid == 0);
	TEST_ASSERT(cdada_queue_size(queue) == 2);
	TEST_ASSERT(cdada_queue_empty(queue) == false);

	//PUSH tests resulting queue should be {0, 1, 7, 9}
	key.mid = 7;
	rv = cdada_queue_push(queue, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key.mid == 7);
	TEST_ASSERT(cdada_queue_size(queue) == 3);
	TEST_ASSERT(cdada_queue_empty(queue) == false);
	key.mid = 0xff;
	rv = cdada_queue_back(queue, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key.mid == 7);
	rv = cdada_queue_front(queue, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key.mid == 0);

	key.mid = 9;
	rv = cdada_queue_push(queue, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key.mid == 9);
	TEST_ASSERT(cdada_queue_size(queue) == 4);
	TEST_ASSERT(cdada_queue_empty(queue) == false);
	rv = cdada_queue_front(queue, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key.mid == 0);

	key.mid = 0xff;
	rv = cdada_queue_back(queue, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key.mid == 9);
	rv = cdada_queue_front(queue, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key.mid == 0);
	rv = cdada_queue_pop(queue);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(cdada_queue_size(queue) == 3);
	TEST_ASSERT(cdada_queue_empty(queue) == false);

	key.mid = 0xff;
	rv = cdada_queue_front(queue, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key.mid == 1);
	rv = cdada_queue_back(queue, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key.mid == 9);
	rv = cdada_queue_pop(queue);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(cdada_queue_size(queue) == 2);
	TEST_ASSERT(cdada_queue_empty(queue) == false);

	key.mid = 0xff;
	rv = cdada_queue_front(queue, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key.mid == 7);
	rv = cdada_queue_pop(queue);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(cdada_queue_size(queue) == 1);
	TEST_ASSERT(cdada_queue_empty(queue) == false);

	key.mid = 0xff;
	rv = cdada_queue_back(queue, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key.mid == 9);
	rv = cdada_queue_pop(queue);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	rv = cdada_queue_pop(queue);
	TEST_ASSERT(rv == CDADA_E_NOT_FOUND);
	TEST_ASSERT(cdada_queue_size(queue) == 0);
	TEST_ASSERT(cdada_queue_empty(queue) == true);

	//Add many 0s {1, 0, 0, 0, 0, 0}
	key.mid = 1;
	rv = cdada_queue_push(queue, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key.mid == 1);
	key.mid = 0xff;
	rv = cdada_queue_back(queue, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key.mid == 1);
	rv = cdada_queue_front(queue, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key.mid == 1);

	for(i=0;i<5; ++i){
		key.mid = 0;
		rv = cdada_queue_push(queue, &key);
		TEST_ASSERT(rv == CDADA_SUCCESS);
		TEST_ASSERT(key.mid == 0);
		key.mid = 0xff;
		rv = cdada_queue_back(queue, &key);
		TEST_ASSERT(rv == CDADA_SUCCESS);
		TEST_ASSERT(key.mid == 0);
		rv = cdada_queue_front(queue, &key);
		TEST_ASSERT(rv == CDADA_SUCCESS);
		TEST_ASSERT(key.mid == 1);
		TEST_ASSERT(cdada_queue_size(queue) == (i + 2));
		TEST_ASSERT(cdada_queue_empty(queue) == false);
	}

	//Dumpers
	rv = cdada_queue_print(queue, stdout);
	TEST_ASSERT(rv == CDADA_SUCCESS);

	char buffer[128*8];
	uint32_t used;
	rv = cdada_queue_dump(queue, 128*8, buffer, &used);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	fprintf(stdout, "%s\n", buffer);

	char buffer2[8];
	rv = cdada_queue_dump(queue, 8, buffer2, &used);
	TEST_ASSERT(rv == CDADA_E_INCOMPLETE);
	fprintf(stdout, "%s\n", buffer2);

	TEST_ASSERT(cdada_queue_size(queue) == 6);
	TEST_ASSERT(cdada_queue_empty(queue) == false);

	rv = cdada_queue_destroy(queue);
	TEST_ASSERT(rv == CDADA_SUCCESS);

	return 0;
}

int test_u552_push_pop(){
	queue = cdada_queue_create(test_u552_t);
	TEST_ASSERT(queue != NULL);

	return _test_u552_push_pop();
}

int test_u552_push_pop_custom(){
	queue = cdada_queue_create_custom(test_u552_t);
	TEST_ASSERT(queue != NULL);

	return _test_u552_push_pop();
}

int test_u3552_push_pop_custom(){

	int i, rv;
	test_u3552_t key;

	queue = cdada_queue_create_custom(test_u3552_t);
	TEST_ASSERT(queue != NULL);

	memset(&key, 0, sizeof(key));

	TEST_ASSERT(cdada_queue_size(queue) == 0);
	TEST_ASSERT(cdada_queue_empty(queue) == true);
	TEST_ASSERT(cdada_queue_back(queue, &key) == CDADA_E_NOT_FOUND);

	//Add one key & get
	key.mid = 0;
	rv = cdada_queue_push(queue, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	key.mid = 0xff;
	rv = cdada_queue_back(queue, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key.mid == 0);
	rv = cdada_queue_front(queue, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key.mid == 0);
	TEST_ASSERT(cdada_queue_size(queue) == 1);
	TEST_ASSERT(cdada_queue_empty(queue) == false);

	//Add 1 on back
	key.mid = 1;
	rv = cdada_queue_push(queue, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	key.mid = 0xff;
	rv = cdada_queue_back(queue, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key.mid == 1);
	rv = cdada_queue_front(queue, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key.mid == 0);
	TEST_ASSERT(cdada_queue_size(queue) == 2);
	TEST_ASSERT(cdada_queue_empty(queue) == false);

	//PUSH tests resulting queue should be {0, 1, 7, 9}
	key.mid = 7;
	rv = cdada_queue_push(queue, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key.mid == 7);
	TEST_ASSERT(cdada_queue_size(queue) == 3);
	TEST_ASSERT(cdada_queue_empty(queue) == false);
	key.mid = 0xff;
	rv = cdada_queue_back(queue, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key.mid == 7);
	rv = cdada_queue_front(queue, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key.mid == 0);

	key.mid = 9;
	rv = cdada_queue_push(queue, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key.mid == 9);
	TEST_ASSERT(cdada_queue_size(queue) == 4);
	TEST_ASSERT(cdada_queue_empty(queue) == false);
	rv = cdada_queue_front(queue, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key.mid == 0);

	key.mid = 0xff;
	rv = cdada_queue_back(queue, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key.mid == 9);
	rv = cdada_queue_front(queue, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key.mid == 0);
	rv = cdada_queue_pop(queue);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(cdada_queue_size(queue) == 3);
	TEST_ASSERT(cdada_queue_empty(queue) == false);

	key.mid = 0xff;
	rv = cdada_queue_front(queue, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key.mid == 1);
	rv = cdada_queue_back(queue, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key.mid == 9);
	rv = cdada_queue_pop(queue);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(cdada_queue_size(queue) == 2);
	TEST_ASSERT(cdada_queue_empty(queue) == false);

	key.mid = 0xff;
	rv = cdada_queue_front(queue, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key.mid == 7);
	rv = cdada_queue_pop(queue);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(cdada_queue_size(queue) == 1);
	TEST_ASSERT(cdada_queue_empty(queue) == false);

	key.mid = 0xff;
	rv = cdada_queue_back(queue, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key.mid == 9);
	rv = cdada_queue_pop(queue);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	rv = cdada_queue_pop(queue);
	TEST_ASSERT(rv == CDADA_E_NOT_FOUND);
	TEST_ASSERT(cdada_queue_size(queue) == 0);
	TEST_ASSERT(cdada_queue_empty(queue) == true);

	//Add many 0s {1, 0, 0, 0, 0, 0}
	key.mid = 1;
	rv = cdada_queue_push(queue, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key.mid == 1);
	key.mid = 0xff;
	rv = cdada_queue_back(queue, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key.mid == 1);
	rv = cdada_queue_front(queue, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key.mid == 1);

	for(i=0;i<5; ++i){
		key.mid = 0;
		rv = cdada_queue_push(queue, &key);
		TEST_ASSERT(rv == CDADA_SUCCESS);
		TEST_ASSERT(key.mid == 0);
		key.mid = 0xff;
		rv = cdada_queue_back(queue, &key);
		TEST_ASSERT(rv == CDADA_SUCCESS);
		TEST_ASSERT(key.mid == 0);
		rv = cdada_queue_front(queue, &key);
		TEST_ASSERT(rv == CDADA_SUCCESS);
		TEST_ASSERT(key.mid == 1);
		TEST_ASSERT(cdada_queue_size(queue) == (i + 2));
		TEST_ASSERT(cdada_queue_empty(queue) == false);
	}

	//Dumpers
	rv = cdada_queue_print(queue, stdout);
	TEST_ASSERT(rv == CDADA_SUCCESS);

	char buffer[128*64];
	uint32_t used;
	rv = cdada_queue_dump(queue, 128*64, buffer, &used);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	fprintf(stdout, "%s\n", buffer);

	char buffer2[8];
	rv = cdada_queue_dump(queue, 8, buffer2, &used);
	TEST_ASSERT(rv == CDADA_E_INCOMPLETE);
	fprintf(stdout, "%s\n", buffer2);

	TEST_ASSERT(cdada_queue_size(queue) == 6);
	TEST_ASSERT(cdada_queue_empty(queue) == false);

	rv = cdada_queue_destroy(queue);
	TEST_ASSERT(rv == CDADA_SUCCESS);

	return 0;
}

int main(int args, char** argv){

	int rv;

	rv = test_basics();

	//Complete
	rv |= test_u8_push_pop();
	rv |= test_u16_push_pop();
	rv |= test_u32_push_pop();
	rv |= test_u64_push_pop();

	//Incomplete
	rv |= test_u552_push_pop();
	rv |= test_u552_push_pop_custom();
	rv |= test_u3552_push_pop_custom();

	//Add your test here, and return a code appropriately...
	return rv == 0? EXIT_SUCCESS : EXIT_FAILURE;
}
