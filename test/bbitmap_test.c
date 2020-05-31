#include <stdlib.h>
#include <stdio.h>

#include "common.h"
#include "cdada/bbitmap.h"

int test_basics(){

	int rv, i;
	cdada_bbitmap_t* b = cdada_bbitmap_create(0);
	TEST_ASSERT(b == NULL);

	//6 bits (1 word)
	b = cdada_bbitmap_create(6);
	TEST_ASSERT(b != NULL);

	for(i=0; i<6; ++i)
		TEST_ASSERT(cdada_bbitmap_is_set(b, i) == false);

	//Beyond limit
	TEST_ASSERT(cdada_bbitmap_is_set(b, 7) == false);
	TEST_ASSERT(cdada_bbitmap_is_set(b, 12888) == false);

	//Set
	rv = cdada_bbitmap_set(b, 128);
	TEST_ASSERT(rv == CDADA_E_INVALID);
	rv = cdada_bbitmap_set(b, 2);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	for(i=0; i<6; ++i){
		if(i == 2){
			TEST_ASSERT(cdada_bbitmap_is_set(b, i) == true);
		}else{
			TEST_ASSERT(cdada_bbitmap_is_set(b, i) == false);
		}
	}
	rv = cdada_bbitmap_set(b, 3);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	for(i=0; i<6; ++i){
		if(i == 2 || i == 3){
			TEST_ASSERT(cdada_bbitmap_is_set(b, i) == true);
		}else{
			TEST_ASSERT(cdada_bbitmap_is_set(b, i) == false);
		}
	}
	rv = cdada_bbitmap_clear(b, 3);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	for(i=0; i<6; ++i){
		if(i == 2){
			TEST_ASSERT(cdada_bbitmap_is_set(b, i) == true);
		}else{
			TEST_ASSERT(cdada_bbitmap_is_set(b, i) == false);
		}
	}

	//Set them all
	rv = cdada_bbitmap_set_all(b);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	for(i=0; i<6; ++i){
		TEST_ASSERT(cdada_bbitmap_is_set(b, i) == true);
	}
	rv = cdada_bbitmap_clear_all(b);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	for(i=0; i<6; ++i){
		TEST_ASSERT(cdada_bbitmap_is_set(b, i) == false);
	}

	rv = cdada_bbitmap_destroy(b);
	TEST_ASSERT(rv == CDADA_SUCCESS);

	//
	//Try larger bitmaps
	//
	b = cdada_bbitmap_create(6533);
	TEST_ASSERT(b != NULL);
	TEST_ASSERT(b->n_words == 103);

	for(i=0; i<6533; ++i)
		TEST_ASSERT(cdada_bbitmap_is_set(b, i) == false);

	rv = cdada_bbitmap_set(b, 6733);
	TEST_ASSERT(rv == CDADA_E_INVALID);

	rv = cdada_bbitmap_set(b, 6532);
	TEST_ASSERT(rv == CDADA_SUCCESS);

	for(i=0; i<6533; ++i)
		TEST_ASSERT(cdada_bbitmap_is_set(b, i) == ((i==6532)? 1 : 0));

	//Dump to a buffer that is unable to contain dump
	char buffer[128];
	uint32_t used;
	rv = cdada_bbitmap_dump(b, 0, NULL, &used);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(used > 128);

	rv = cdada_bbitmap_dump(b, 128, buffer, &used);
	TEST_ASSERT(rv == CDADA_E_INCOMPLETE);
	fprintf(stderr, "%s\n", buffer);

	char buffer2[2048*16];
	rv = cdada_bbitmap_dump(b, 2048*16, buffer2, &used);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	fprintf(stderr, "%s\n", buffer2);
	rv = cdada_bbitmap_print(b, stdout);
	TEST_ASSERT(rv == CDADA_SUCCESS);

	//Beyond limit
	TEST_ASSERT(cdada_bbitmap_is_set(b, 12888) == false);

	rv = cdada_bbitmap_destroy(b);
	TEST_ASSERT(rv == CDADA_SUCCESS);

	//
	//Try exact multiple of words
	//
	b = cdada_bbitmap_create(64);
	TEST_ASSERT(b != NULL);
	TEST_ASSERT(b->n_words == 1);

	for(i=0; i<64; ++i)
		TEST_ASSERT(cdada_bbitmap_is_set(b, i) == false);
	rv = cdada_bbitmap_set_all(b);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	for(i=0; i<64; ++i)
		TEST_ASSERT(cdada_bbitmap_is_set(b, i) == true);
	rv = cdada_bbitmap_clear_all(b);
	for(i=0; i<64; ++i)
		TEST_ASSERT(cdada_bbitmap_is_set(b, i) == false);

	rv = cdada_bbitmap_set(b, 63);
	for(i=0; i<64; ++i)
		TEST_ASSERT(cdada_bbitmap_is_set(b, i) == ((i==63)? 1 : 0));

	rv = cdada_bbitmap_clear(b, 63);
	for(i=0; i<64; ++i)
		TEST_ASSERT(cdada_bbitmap_is_set(b, i) == false);

	rv = cdada_bbitmap_destroy(b);
	TEST_ASSERT(rv == CDADA_SUCCESS);

	return 0;
}

int main(int args, char** argv){

	int rv;

	rv = test_basics();

	//Add your test here, and return a code appropriately...
	return rv == 0? EXIT_SUCCESS : EXIT_FAILURE;
}
