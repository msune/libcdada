#include <stdlib.h>

#include "cdada/stack.h"
#include "common.h"
#include <string.h>
#include "u552.h"
#include "u3552.h"

//Fwd decl
CDADA_STACK_CUSTOM_TYPE_DECL(test_u552_t);
CDADA_STACK_CUSTOM_TYPE_DECL(test_u3552_t);

//static uint64_t opaque = 0ULL;
static cdada_stack_t* stack = NULL;

//
// Aligned types
//

//8
int test_u8_push_pop(){

	int i, rv;
	uint8_t key;

	stack = cdada_stack_create(uint8_t);
	TEST_ASSERT(stack != NULL);

	TEST_ASSERT(cdada_stack_size(stack) == 0);
	TEST_ASSERT(cdada_stack_empty(stack) == true);
	TEST_ASSERT(cdada_stack_top(stack, &key) == CDADA_E_NOT_FOUND);

	//Add one key & get
	key = 0;
	rv = cdada_stack_push(stack, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	key = 0xff;
	rv = cdada_stack_top(stack, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 0);
	TEST_ASSERT(cdada_stack_size(stack) == 1);
	TEST_ASSERT(cdada_stack_empty(stack) == false);

	//Add 1 on top
	key = 1;
	rv = cdada_stack_push(stack, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	key = 0xff;
	rv = cdada_stack_top(stack, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 1);
	TEST_ASSERT(cdada_stack_size(stack) == 2);
	TEST_ASSERT(cdada_stack_empty(stack) == false);

	//PUSH tests resulting stack should be {9, 7, 1, 0}
	key = 7;
	rv = cdada_stack_push(stack, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 7);
	TEST_ASSERT(cdada_stack_size(stack) == 3);
	TEST_ASSERT(cdada_stack_empty(stack) == false);
	key = 0xff;
	rv = cdada_stack_top(stack, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 7);

	key = 9;
	rv = cdada_stack_push(stack, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 9);
	TEST_ASSERT(cdada_stack_size(stack) == 4);
	TEST_ASSERT(cdada_stack_empty(stack) == false);

	key = 0xff;
	rv = cdada_stack_top(stack, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 9);
	rv = cdada_stack_pop(stack);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(cdada_stack_size(stack) == 3);
	TEST_ASSERT(cdada_stack_empty(stack) == false);

	key = 0xff;
	rv = cdada_stack_top(stack, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 7);
	rv = cdada_stack_pop(stack);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(cdada_stack_size(stack) == 2);
	TEST_ASSERT(cdada_stack_empty(stack) == false);

	key = 0xff;
	rv = cdada_stack_top(stack, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 1);
	rv = cdada_stack_pop(stack);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(cdada_stack_size(stack) == 1);
	TEST_ASSERT(cdada_stack_empty(stack) == false);

	key = 0xff;
	rv = cdada_stack_top(stack, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 0);
	rv = cdada_stack_pop(stack);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	rv = cdada_stack_pop(stack);
	TEST_ASSERT(rv == CDADA_E_NOT_FOUND);
	TEST_ASSERT(cdada_stack_size(stack) == 0);
	TEST_ASSERT(cdada_stack_empty(stack) == true);

	//Add many 0s {0, 0, 0, 0, 0, 1}
	key = 1;
	rv = cdada_stack_push(stack, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 1);
	key = 0xff;
	rv = cdada_stack_top(stack, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 1);

	for(i=0;i<5; ++i){
		key = 0;
		rv = cdada_stack_push(stack, &key);
		TEST_ASSERT(rv == CDADA_SUCCESS);
		TEST_ASSERT(key == 0);
		key = 0xff;
		rv = cdada_stack_top(stack, &key);
		TEST_ASSERT(rv == CDADA_SUCCESS);
		TEST_ASSERT(key == 0);
		TEST_ASSERT(cdada_stack_size(stack) == (i + 2));
		TEST_ASSERT(cdada_stack_empty(stack) == false);
	}

	//Dumpers
	rv = cdada_stack_print(stack, stdout);
	TEST_ASSERT(rv == CDADA_SUCCESS);

	char buffer[128];
	uint32_t used;
	rv = cdada_stack_dump(stack, 128, buffer, &used);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	fprintf(stdout, "%s\n", buffer);

	char buffer2[8];
	rv = cdada_stack_dump(stack, 8, buffer2, &used);
	TEST_ASSERT(rv == CDADA_E_INCOMPLETE);
	fprintf(stdout, "%s\n", buffer2);

	TEST_ASSERT(cdada_stack_size(stack) == 6);
	TEST_ASSERT(cdada_stack_empty(stack) == false);

	rv = cdada_stack_destroy(stack);
	TEST_ASSERT(rv == CDADA_SUCCESS);

	return 0;
}

//16
int test_u16_push_pop(){

	int i, rv;
	uint16_t key;

	stack = cdada_stack_create(uint16_t);
	TEST_ASSERT(stack != NULL);

	TEST_ASSERT(cdada_stack_size(stack) == 0);
	TEST_ASSERT(cdada_stack_empty(stack) == true);
	TEST_ASSERT(cdada_stack_top(stack, &key) == CDADA_E_NOT_FOUND);

	//Add one key & get
	key = 0;
	rv = cdada_stack_push(stack, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	key = 0xff;
	rv = cdada_stack_top(stack, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 0);
	TEST_ASSERT(cdada_stack_size(stack) == 1);
	TEST_ASSERT(cdada_stack_empty(stack) == false);

	//Add 1 on top
	key = 1;
	rv = cdada_stack_push(stack, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	key = 0xff;
	rv = cdada_stack_top(stack, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 1);
	TEST_ASSERT(cdada_stack_size(stack) == 2);
	TEST_ASSERT(cdada_stack_empty(stack) == false);

	//PUSH tests resulting stack should be {9, 7, 1, 0}
	key = 7;
	rv = cdada_stack_push(stack, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 7);
	TEST_ASSERT(cdada_stack_size(stack) == 3);
	TEST_ASSERT(cdada_stack_empty(stack) == false);
	key = 0xff;
	rv = cdada_stack_top(stack, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 7);

	key = 9;
	rv = cdada_stack_push(stack, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 9);
	TEST_ASSERT(cdada_stack_size(stack) == 4);
	TEST_ASSERT(cdada_stack_empty(stack) == false);

	key = 0xff;
	rv = cdada_stack_top(stack, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 9);
	rv = cdada_stack_pop(stack);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(cdada_stack_size(stack) == 3);
	TEST_ASSERT(cdada_stack_empty(stack) == false);

	key = 0xff;
	rv = cdada_stack_top(stack, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 7);
	rv = cdada_stack_pop(stack);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(cdada_stack_size(stack) == 2);
	TEST_ASSERT(cdada_stack_empty(stack) == false);

	key = 0xff;
	rv = cdada_stack_top(stack, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 1);
	rv = cdada_stack_pop(stack);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(cdada_stack_size(stack) == 1);
	TEST_ASSERT(cdada_stack_empty(stack) == false);

	key = 0xff;
	rv = cdada_stack_top(stack, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 0);
	rv = cdada_stack_pop(stack);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	rv = cdada_stack_pop(stack);
	TEST_ASSERT(rv == CDADA_E_NOT_FOUND);
	TEST_ASSERT(cdada_stack_size(stack) == 0);
	TEST_ASSERT(cdada_stack_empty(stack) == true);

	//Add many 0s {0, 0, 0, 0, 0, 1}
	key = 1;
	rv = cdada_stack_push(stack, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 1);
	key = 0xff;
	rv = cdada_stack_top(stack, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 1);

	for(i=0;i<5; ++i){
		key = 0;
		rv = cdada_stack_push(stack, &key);
		TEST_ASSERT(rv == CDADA_SUCCESS);
		TEST_ASSERT(key == 0);
		key = 0xff;
		rv = cdada_stack_top(stack, &key);
		TEST_ASSERT(rv == CDADA_SUCCESS);
		TEST_ASSERT(key == 0);
		TEST_ASSERT(cdada_stack_size(stack) == (i + 2));
		TEST_ASSERT(cdada_stack_empty(stack) == false);
	}

	//Dumpers
	rv = cdada_stack_print(stack, stdout);
	TEST_ASSERT(rv == CDADA_SUCCESS);

	char buffer[128];
	uint32_t used;
	rv = cdada_stack_dump(stack, 128, buffer, &used);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	fprintf(stdout, "%s\n", buffer);

	char buffer2[8];
	rv = cdada_stack_dump(stack, 8, buffer2, &used);
	TEST_ASSERT(rv == CDADA_E_INCOMPLETE);
	fprintf(stdout, "%s\n", buffer2);

	TEST_ASSERT(cdada_stack_size(stack) == 6);
	TEST_ASSERT(cdada_stack_empty(stack) == false);

	rv = cdada_stack_destroy(stack);
	TEST_ASSERT(rv == CDADA_SUCCESS);

	return 0;
}

//32
int test_u32_push_pop(){

	int i, rv;
	uint32_t key;

	stack = cdada_stack_create(uint32_t);
	TEST_ASSERT(stack != NULL);

	TEST_ASSERT(cdada_stack_size(stack) == 0);
	TEST_ASSERT(cdada_stack_empty(stack) == true);
	TEST_ASSERT(cdada_stack_top(stack, &key) == CDADA_E_NOT_FOUND);

	//Add one key & get
	key = 0;
	rv = cdada_stack_push(stack, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	key = 0xff;
	rv = cdada_stack_top(stack, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 0);
	TEST_ASSERT(cdada_stack_size(stack) == 1);
	TEST_ASSERT(cdada_stack_empty(stack) == false);

	//Add 1 on top
	key = 1;
	rv = cdada_stack_push(stack, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	key = 0xff;
	rv = cdada_stack_top(stack, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 1);
	TEST_ASSERT(cdada_stack_size(stack) == 2);
	TEST_ASSERT(cdada_stack_empty(stack) == false);

	//PUSH tests resulting stack should be {9, 7, 1, 0}
	key = 7;
	rv = cdada_stack_push(stack, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 7);
	TEST_ASSERT(cdada_stack_size(stack) == 3);
	TEST_ASSERT(cdada_stack_empty(stack) == false);
	key = 0xff;
	rv = cdada_stack_top(stack, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 7);

	key = 9;
	rv = cdada_stack_push(stack, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 9);
	TEST_ASSERT(cdada_stack_size(stack) == 4);
	TEST_ASSERT(cdada_stack_empty(stack) == false);

	key = 0xff;
	rv = cdada_stack_top(stack, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 9);
	rv = cdada_stack_pop(stack);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(cdada_stack_size(stack) == 3);
	TEST_ASSERT(cdada_stack_empty(stack) == false);

	key = 0xff;
	rv = cdada_stack_top(stack, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 7);
	rv = cdada_stack_pop(stack);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(cdada_stack_size(stack) == 2);
	TEST_ASSERT(cdada_stack_empty(stack) == false);

	key = 0xff;
	rv = cdada_stack_top(stack, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 1);
	rv = cdada_stack_pop(stack);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(cdada_stack_size(stack) == 1);
	TEST_ASSERT(cdada_stack_empty(stack) == false);

	key = 0xff;
	rv = cdada_stack_top(stack, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 0);
	rv = cdada_stack_pop(stack);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	rv = cdada_stack_pop(stack);
	TEST_ASSERT(rv == CDADA_E_NOT_FOUND);
	TEST_ASSERT(cdada_stack_size(stack) == 0);
	TEST_ASSERT(cdada_stack_empty(stack) == true);

	//Add many 0s {0, 0, 0, 0, 0, 1}
	key = 1;
	rv = cdada_stack_push(stack, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 1);
	key = 0xff;
	rv = cdada_stack_top(stack, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 1);

	for(i=0;i<5; ++i){
		key = 0;
		rv = cdada_stack_push(stack, &key);
		TEST_ASSERT(rv == CDADA_SUCCESS);
		TEST_ASSERT(key == 0);
		key = 0xff;
		rv = cdada_stack_top(stack, &key);
		TEST_ASSERT(rv == CDADA_SUCCESS);
		TEST_ASSERT(key == 0);
		TEST_ASSERT(cdada_stack_size(stack) == (i + 2));
		TEST_ASSERT(cdada_stack_empty(stack) == false);
	}

	//Dumpers
	rv = cdada_stack_print(stack, stdout);
	TEST_ASSERT(rv == CDADA_SUCCESS);

	char buffer[128];
	uint32_t used;
	rv = cdada_stack_dump(stack, 128, buffer, &used);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	fprintf(stdout, "%s\n", buffer);

	char buffer2[8];
	rv = cdada_stack_dump(stack, 8, buffer2, &used);
	TEST_ASSERT(rv == CDADA_E_INCOMPLETE);
	fprintf(stdout, "%s\n", buffer2);

	TEST_ASSERT(cdada_stack_size(stack) == 6);
	TEST_ASSERT(cdada_stack_empty(stack) == false);

	rv = cdada_stack_destroy(stack);
	TEST_ASSERT(rv == CDADA_SUCCESS);

	return 0;
}

//64
int test_u64_push_pop(){

	int i, rv;
	uint64_t key;

	stack = cdada_stack_create(uint64_t);
	TEST_ASSERT(stack != NULL);

	TEST_ASSERT(cdada_stack_size(stack) == 0);
	TEST_ASSERT(cdada_stack_empty(stack) == true);
	TEST_ASSERT(cdada_stack_top(stack, &key) == CDADA_E_NOT_FOUND);

	//Add one key & get
	key = 0ULL;
	rv = cdada_stack_push(stack, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	key = 0xffULL;
	rv = cdada_stack_top(stack, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 0ULL);
	TEST_ASSERT(cdada_stack_size(stack) == 1);
	TEST_ASSERT(cdada_stack_empty(stack) == false);

	//Add 1 on top
	key = 1ULL;
	rv = cdada_stack_push(stack, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	key = 0xffULL;
	rv = cdada_stack_top(stack, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 1ULL);
	TEST_ASSERT(cdada_stack_size(stack) == 2);
	TEST_ASSERT(cdada_stack_empty(stack) == false);

	//PUSH tests resulting stack should be {9, 7, 1, 0}
	key = 7ULL;
	rv = cdada_stack_push(stack, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 7ULL);
	TEST_ASSERT(cdada_stack_size(stack) == 3);
	TEST_ASSERT(cdada_stack_empty(stack) == false);
	key = 0xffULL;
	rv = cdada_stack_top(stack, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 7ULL);

	key = 9ULL;
	rv = cdada_stack_push(stack, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 9ULL);
	TEST_ASSERT(cdada_stack_size(stack) == 4);
	TEST_ASSERT(cdada_stack_empty(stack) == false);

	key = 0xffULL;
	rv = cdada_stack_top(stack, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 9ULL);
	rv = cdada_stack_pop(stack);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(cdada_stack_size(stack) == 3);
	TEST_ASSERT(cdada_stack_empty(stack) == false);

	key = 0xffULL;
	rv = cdada_stack_top(stack, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 7ULL);
	rv = cdada_stack_pop(stack);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(cdada_stack_size(stack) == 2);
	TEST_ASSERT(cdada_stack_empty(stack) == false);

	key = 0xffULL;
	rv = cdada_stack_top(stack, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 1ULL);
	rv = cdada_stack_pop(stack);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(cdada_stack_size(stack) == 1);
	TEST_ASSERT(cdada_stack_empty(stack) == false);

	key = 0xffULL;
	rv = cdada_stack_top(stack, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 0ULL);
	rv = cdada_stack_pop(stack);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	rv = cdada_stack_pop(stack);
	TEST_ASSERT(rv == CDADA_E_NOT_FOUND);
	TEST_ASSERT(cdada_stack_size(stack) == 0);
	TEST_ASSERT(cdada_stack_empty(stack) == true);

	//Add many 0s {0, 0, 0, 0, 0, 1}
	key = 1ULL;
	rv = cdada_stack_push(stack, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 1ULL);
	key = 0xffULL;
	rv = cdada_stack_top(stack, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key == 1ULL);

	for(i=0;i<5; ++i){
		key = 0ULL;
		rv = cdada_stack_push(stack, &key);
		TEST_ASSERT(rv == CDADA_SUCCESS);
		TEST_ASSERT(key == 0ULL);
		key = 0xffULL;
		rv = cdada_stack_top(stack, &key);
		TEST_ASSERT(rv == CDADA_SUCCESS);
		TEST_ASSERT(key == 0ULL);
		TEST_ASSERT(cdada_stack_size(stack) == (i + 2));
		TEST_ASSERT(cdada_stack_empty(stack) == false);
	}

	//Dumpers
	rv = cdada_stack_print(stack, stdout);
	TEST_ASSERT(rv == CDADA_SUCCESS);

	char buffer[128];
	uint32_t used;
	rv = cdada_stack_dump(stack, 128, buffer, &used);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	fprintf(stdout, "%s\n", buffer);

	char buffer2[8];
	rv = cdada_stack_dump(stack, 8, buffer2, &used);
	TEST_ASSERT(rv == CDADA_E_INCOMPLETE);
	fprintf(stdout, "%s\n", buffer2);

	TEST_ASSERT(cdada_stack_size(stack) == 6);
	TEST_ASSERT(cdada_stack_empty(stack) == false);

	rv = cdada_stack_destroy(stack);
	TEST_ASSERT(rv == CDADA_SUCCESS);

	return 0;
}

int test_basics(){

	int rv;

	void* ptr_not_null = (void*)0x123;

	//Create
	stack = cdada_stack_create(int);
	TEST_ASSERT(stack != NULL);

	TEST_ASSERT(cdada_stack_size(stack) == 0);
	TEST_ASSERT(cdada_stack_empty(stack) == true);

	//Try all APIs with a NULL stack/key/val
	TEST_ASSERT(cdada_stack_size(NULL) == 0);
	TEST_ASSERT(cdada_stack_empty(NULL) == false);
	rv = cdada_stack_destroy(NULL);
	TEST_ASSERT(rv == CDADA_E_INVALID);

	rv = cdada_stack_push(NULL, ptr_not_null);
	TEST_ASSERT(rv == CDADA_E_INVALID);

	rv = cdada_stack_top(NULL, &ptr_not_null);
	TEST_ASSERT(rv == CDADA_E_INVALID);
	rv = cdada_stack_pop(NULL);
	TEST_ASSERT(rv == CDADA_E_INVALID);


	//Now destroy
	rv = cdada_stack_destroy(stack);
	TEST_ASSERT(rv == CDADA_SUCCESS);

	//Create with valid and invalid
	struct {
		char u[256];
	} c256;
	struct {
		char u[257];
	} c257;
	stack = cdada_stack_create(c256);
	TEST_ASSERT(stack != NULL);
	rv = cdada_stack_destroy(stack);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	stack = cdada_stack_create(c257);
	TEST_ASSERT(stack == NULL);

	return 0;
}

#include <unistd.h>

int _test_u552_push_pop(){

	int i, rv;
	test_u552_t key;

	memset(&key, 0, sizeof(key));

	TEST_ASSERT(cdada_stack_size(stack) == 0);
	TEST_ASSERT(cdada_stack_empty(stack) == true);
	TEST_ASSERT(cdada_stack_top(stack, &key) == CDADA_E_NOT_FOUND);

	//Add one key & get
	key.mid = 0;
	rv = cdada_stack_push(stack, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	key.mid = 0xff;
	rv = cdada_stack_top(stack, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key.mid == 0);
	TEST_ASSERT(cdada_stack_size(stack) == 1);
	TEST_ASSERT(cdada_stack_empty(stack) == false);

	//Add 1 on top
	key.mid = 1;
	rv = cdada_stack_push(stack, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	key.mid = 0xff;
	rv = cdada_stack_top(stack, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key.mid == 1);
	TEST_ASSERT(cdada_stack_size(stack) == 2);
	TEST_ASSERT(cdada_stack_empty(stack) == false);

	//PUSH tests resulting stack should be {9, 7, 1, 0}
	key.mid = 7;
	rv = cdada_stack_push(stack, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key.mid == 7);
	TEST_ASSERT(cdada_stack_size(stack) == 3);
	TEST_ASSERT(cdada_stack_empty(stack) == false);
	key.mid = 0xff;
	rv = cdada_stack_top(stack, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key.mid == 7);

	key.mid = 9;
	rv = cdada_stack_push(stack, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key.mid == 9);
	TEST_ASSERT(cdada_stack_size(stack) == 4);
	TEST_ASSERT(cdada_stack_empty(stack) == false);

	key.mid = 0xff;
	rv = cdada_stack_top(stack, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key.mid == 9);
	rv = cdada_stack_pop(stack);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(cdada_stack_size(stack) == 3);
	TEST_ASSERT(cdada_stack_empty(stack) == false);

	key.mid = 0xff;
	rv = cdada_stack_top(stack, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key.mid == 7);
	rv = cdada_stack_pop(stack);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(cdada_stack_size(stack) == 2);
	TEST_ASSERT(cdada_stack_empty(stack) == false);

	key.mid = 0xff;
	rv = cdada_stack_top(stack, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key.mid == 1);
	rv = cdada_stack_pop(stack);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(cdada_stack_size(stack) == 1);
	TEST_ASSERT(cdada_stack_empty(stack) == false);

	key.mid = 0xff;
	rv = cdada_stack_top(stack, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key.mid == 0);
	rv = cdada_stack_pop(stack);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	rv = cdada_stack_pop(stack);
	TEST_ASSERT(rv == CDADA_E_NOT_FOUND);
	TEST_ASSERT(cdada_stack_size(stack) == 0);
	TEST_ASSERT(cdada_stack_empty(stack) == true);

	//Add many 0s {0, 0, 0, 0, 0, 1}
	key.mid = 1;
	rv = cdada_stack_push(stack, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key.mid == 1);
	TEST_ASSERT(cdada_stack_size(stack) == 1);
	TEST_ASSERT(cdada_stack_empty(stack) == false);
	key.mid = 0xff;
	rv = cdada_stack_top(stack, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key.mid == 1);

	int jj;
	for(jj = 0, i=0;i<5; ++i, jj += 1){
		key.mid = 0;
		rv = cdada_stack_push(stack, &key);
		TEST_ASSERT(rv == CDADA_SUCCESS);
		TEST_ASSERT(key.mid == 0);
		key.mid = 0xff;
		rv = cdada_stack_top(stack, &key);
		TEST_ASSERT(rv == CDADA_SUCCESS);
		TEST_ASSERT(key.mid == 0);
		TEST_ASSERT(cdada_stack_size(stack) == (i + 2));
		TEST_ASSERT(cdada_stack_empty(stack) == false);
	}

	//Dumpers
	rv = cdada_stack_print(stack, stdout);
	TEST_ASSERT(rv == CDADA_SUCCESS);

	char buffer[128*8];
	uint32_t used;
	rv = cdada_stack_dump(stack, 128*8, buffer, &used);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	fprintf(stdout, "%s\n", buffer);

	char buffer2[8];
	rv = cdada_stack_dump(stack, 8, buffer2, &used);
	TEST_ASSERT(rv == CDADA_E_INCOMPLETE);
	fprintf(stdout, "%s\n", buffer2);

	TEST_ASSERT(cdada_stack_size(stack) == 6);
	TEST_ASSERT(cdada_stack_empty(stack) == false);

	rv = cdada_stack_destroy(stack);
	TEST_ASSERT(rv == CDADA_SUCCESS);

	return 0;
}

int test_u552_push_pop(){
	stack = cdada_stack_create(test_u552_t);
	TEST_ASSERT(stack != NULL);

	return _test_u552_push_pop();
}

int test_u552_push_pop_custom(){
	stack = cdada_stack_create_custom(test_u552_t);
	TEST_ASSERT(stack != NULL);

	return _test_u552_push_pop();
}

int test_u3552_push_pop_custom(){

	int i, rv;
	test_u3552_t key;

	stack = cdada_stack_create_custom(test_u3552_t);
	TEST_ASSERT(stack != NULL);

	memset(&key, 0, sizeof(key));

	TEST_ASSERT(cdada_stack_size(stack) == 0);
	TEST_ASSERT(cdada_stack_empty(stack) == true);
	TEST_ASSERT(cdada_stack_top(stack, &key) == CDADA_E_NOT_FOUND);

	//Add one key & get
	key.mid = 0;
	rv = cdada_stack_push(stack, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	key.mid = 0xff;
	rv = cdada_stack_top(stack, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key.mid == 0);
	TEST_ASSERT(cdada_stack_size(stack) == 1);
	TEST_ASSERT(cdada_stack_empty(stack) == false);

	//Add 1 on top
	key.mid = 1;
	rv = cdada_stack_push(stack, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	key.mid = 0xff;
	rv = cdada_stack_top(stack, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key.mid == 1);
	TEST_ASSERT(cdada_stack_size(stack) == 2);
	TEST_ASSERT(cdada_stack_empty(stack) == false);

	//PUSH tests resulting stack should be {9, 7, 1, 0}
	key.mid = 7;
	rv = cdada_stack_push(stack, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key.mid == 7);
	TEST_ASSERT(cdada_stack_size(stack) == 3);
	TEST_ASSERT(cdada_stack_empty(stack) == false);
	key.mid = 0xff;
	rv = cdada_stack_top(stack, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key.mid == 7);

	key.mid = 9;
	rv = cdada_stack_push(stack, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key.mid == 9);
	TEST_ASSERT(cdada_stack_size(stack) == 4);
	TEST_ASSERT(cdada_stack_empty(stack) == false);

	key.mid = 0xff;
	rv = cdada_stack_top(stack, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key.mid == 9);
	rv = cdada_stack_pop(stack);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(cdada_stack_size(stack) == 3);
	TEST_ASSERT(cdada_stack_empty(stack) == false);

	key.mid = 0xff;
	rv = cdada_stack_top(stack, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key.mid == 7);
	rv = cdada_stack_pop(stack);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(cdada_stack_size(stack) == 2);
	TEST_ASSERT(cdada_stack_empty(stack) == false);

	key.mid = 0xff;
	rv = cdada_stack_top(stack, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key.mid == 1);
	rv = cdada_stack_pop(stack);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(cdada_stack_size(stack) == 1);
	TEST_ASSERT(cdada_stack_empty(stack) == false);

	key.mid = 0xff;
	rv = cdada_stack_top(stack, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key.mid == 0);
	rv = cdada_stack_pop(stack);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	rv = cdada_stack_pop(stack);
	TEST_ASSERT(rv == CDADA_E_NOT_FOUND);
	TEST_ASSERT(cdada_stack_size(stack) == 0);
	TEST_ASSERT(cdada_stack_empty(stack) == true);

	//Add many 0s {0, 0, 0, 0, 0, 1}
	key.mid = 1;
	rv = cdada_stack_push(stack, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key.mid == 1);
	TEST_ASSERT(cdada_stack_size(stack) == 1);
	TEST_ASSERT(cdada_stack_empty(stack) == false);
	key.mid = 0xff;
	rv = cdada_stack_top(stack, &key);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(key.mid == 1);

	int jj;
	for(jj = 0, i=0;i<5; ++i, jj += 1){
		key.mid = 0;
		rv = cdada_stack_push(stack, &key);
		TEST_ASSERT(rv == CDADA_SUCCESS);
		TEST_ASSERT(key.mid == 0);
		key.mid = 0xff;
		rv = cdada_stack_top(stack, &key);
		TEST_ASSERT(rv == CDADA_SUCCESS);
		TEST_ASSERT(key.mid == 0);
		TEST_ASSERT(cdada_stack_size(stack) == (i + 2));
		TEST_ASSERT(cdada_stack_empty(stack) == false);
	}

	//Dumpers
	rv = cdada_stack_print(stack, stdout);
	TEST_ASSERT(rv == CDADA_SUCCESS);

	char buffer[128*64];
	uint32_t used;
	rv = cdada_stack_dump(stack, 128*64, buffer, &used);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	fprintf(stdout, "%s\n", buffer);

	char buffer2[8];
	rv = cdada_stack_dump(stack, 8, buffer2, &used);
	TEST_ASSERT(rv == CDADA_E_INCOMPLETE);
	fprintf(stdout, "%s\n", buffer2);

	TEST_ASSERT(cdada_stack_size(stack) == 6);
	TEST_ASSERT(cdada_stack_empty(stack) == false);

	rv = cdada_stack_destroy(stack);
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
