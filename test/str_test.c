#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "common.h"
#include "cdada/str.h"
#include "cdada/version.h"

int last_pos;

void trav(const cdada_str_t* s, const char it, uint32_t pos, void* opaque){
	const char* t = "This is a test test";

	TEST_ASSERT(strcmp(cdada_str(s), "This is a test test") == 0);
	TEST_ASSERT(t[pos] == it);

	if(opaque == (void*)0x123){
		TEST_ASSERT(last_pos+1 == pos);
	}else if(opaque == (void*)0x321){
		//Reverse
		TEST_ASSERT(last_pos-1 == pos);
	}else{
		TEST_ASSERT(0);
	}

	last_pos = pos;
}

int test_access(){

	int rv;
	uint32_t pos;
	cdada_str_t * s;
	s = cdada_str_create("");
	TEST_ASSERT(s != NULL);

	TEST_ASSERT(cdada_str_empty(s) == true);

	rv = cdada_str_destroy(s);
	TEST_ASSERT(rv == CDADA_SUCCESS);

	s = cdada_str_create("This is a test test");
	TEST_ASSERT(s != NULL);
	TEST_ASSERT(cdada_str_empty(s) == false);
	TEST_ASSERT(cdada_str_length(s) == 19);

	fprintf(stdout, "%s\n", cdada_str(s));
	TEST_ASSERT(strcmp(cdada_str(s), "This is a test test") == 0);

	TEST_ASSERT(cdada_str_find_first(s, "this", &pos) == CDADA_E_NOT_FOUND);
	TEST_ASSERT(cdada_str_find_first(s, "This", &pos) == CDADA_SUCCESS);
	TEST_ASSERT(pos == 0);
	TEST_ASSERT(cdada_str_find_first(s, "T", &pos) == CDADA_SUCCESS);
	TEST_ASSERT(pos == 0);
	TEST_ASSERT(cdada_str_find_first(s, "test", &pos) == CDADA_SUCCESS);
	TEST_ASSERT(pos == 10);
	TEST_ASSERT(cdada_str_find_last(s, "test", &pos) == CDADA_SUCCESS);
	TEST_ASSERT(pos == 15);

	uint32_t count;
	TEST_ASSERT(cdada_str_find_count(s, "TTT", &count) == CDADA_SUCCESS);
	TEST_ASSERT(count == 0);
	TEST_ASSERT(cdada_str_find_count(s, "test", &count) == CDADA_SUCCESS);
	TEST_ASSERT(count == 2);

	uint32_t a[2] = {0, 0};
	TEST_ASSERT(cdada_str_find_all(s, "test", 2, a, &count)
							== CDADA_SUCCESS);
	TEST_ASSERT(count == 2);
	TEST_ASSERT(a[0] == 10);
	TEST_ASSERT(a[1] == 15);

	TEST_ASSERT(cdada_str_find_all(s, "testtttt", 2, a, &count)
							== CDADA_SUCCESS);
	TEST_ASSERT(count == 0);

	a[0] = a[1] = 1234;
	TEST_ASSERT(cdada_str_find_all(s, "test", 1, a, &count)
							== CDADA_E_INCOMPLETE);
	TEST_ASSERT(count == 1);
	TEST_ASSERT(a[0] == 10);
	TEST_ASSERT(a[1] == 1234);

	char c;
	TEST_ASSERT(cdada_str_first_c(s, &c) == CDADA_SUCCESS);
	TEST_ASSERT(c == 'T');
	TEST_ASSERT(cdada_str_last_c(s, &c) == CDADA_SUCCESS);
	TEST_ASSERT(c == 't');
	TEST_ASSERT(cdada_str_get_c(s, 1, &c) == CDADA_SUCCESS);
	TEST_ASSERT(c == 'h');
	TEST_ASSERT(cdada_str_get_c(s, 2, &c) == CDADA_SUCCESS);
	TEST_ASSERT(c == 'i');

	//Traverse
	last_pos = -1;
	rv = cdada_str_traverse(s, trav, (void*)0x123);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	last_pos = strlen(cdada_str(s));
	rv = cdada_str_rtraverse(s, trav, (void*)0x321);
	TEST_ASSERT(rv == CDADA_SUCCESS);

	rv = cdada_str_destroy(s);
	TEST_ASSERT(rv == CDADA_SUCCESS);

	return 0;
}

int test_basics(){

	int rv;
	cdada_str_t * s;
	const char* ptr;

	void* ptr_not_null = (void*)0x123;

	//Create
	s = cdada_str_create("HELLO");
	TEST_ASSERT(s != NULL);

	TEST_ASSERT(cdada_str_length(s) == 5);
	TEST_ASSERT(cdada_str_empty(s) == false);

	//Try all APIs with a NULL str/key/val
	rv = cdada_str_destroy(NULL);
	TEST_ASSERT(rv == CDADA_E_INVALID);
	rv = cdada_str_traverse(NULL, (cdada_str_it)ptr_not_null, NULL);
	TEST_ASSERT(rv == CDADA_E_INVALID);
	rv = cdada_str_traverse(s, NULL, NULL);
	TEST_ASSERT(rv == CDADA_E_INVALID);
	rv = cdada_str_rtraverse(NULL, (cdada_str_it)ptr_not_null, NULL);
	TEST_ASSERT(rv == CDADA_E_INVALID);
	rv = cdada_str_rtraverse(s, NULL, NULL);
	TEST_ASSERT(rv == CDADA_E_INVALID);

	TEST_ASSERT(cdada_str_empty(NULL) == false);
	TEST_ASSERT(cdada_str_length(NULL) == 0);

	ptr = cdada_str(NULL);
	TEST_ASSERT(strlen(ptr) == 0);

	rv = cdada_str_find_first(NULL, (const char*)ptr_not_null,
						(uint32_t*)ptr_not_null);
	TEST_ASSERT(rv == CDADA_E_INVALID);
	rv = cdada_str_find_first(s, (const char*)NULL,
						(uint32_t*)ptr_not_null);
	TEST_ASSERT(rv == CDADA_E_INVALID);
	rv = cdada_str_find_first(s, (const char*)ptr_not_null,
						(uint32_t*)NULL);
	TEST_ASSERT(rv == CDADA_E_INVALID);
	rv = cdada_str_find_last(NULL, (const char*)ptr_not_null,
						(uint32_t*)ptr_not_null);
	TEST_ASSERT(rv == CDADA_E_INVALID);
	rv = cdada_str_find_last(s, (const char*)NULL,
						(uint32_t*)ptr_not_null);
	TEST_ASSERT(rv == CDADA_E_INVALID);
	rv = cdada_str_find_last(s, (const char*)ptr_not_null,
						(uint32_t*)NULL);
	TEST_ASSERT(rv == CDADA_E_INVALID);
	rv = cdada_str_find_count(NULL, (const char*)ptr_not_null,
						(uint32_t*)ptr_not_null);
	TEST_ASSERT(rv == CDADA_E_INVALID);
	rv = cdada_str_find_count(s, (const char*)NULL,
						(uint32_t*)ptr_not_null);
	TEST_ASSERT(rv == CDADA_E_INVALID);
	rv = cdada_str_find_count(s, (const char*)ptr_not_null,
						(uint32_t*)NULL);
	TEST_ASSERT(rv == CDADA_E_INVALID);

	rv = cdada_str_find_all(NULL, (const char*)ptr_not_null, 123,
						(uint32_t*)ptr_not_null,
						(uint32_t*)ptr_not_null);
	TEST_ASSERT(rv == CDADA_E_INVALID);
	rv = cdada_str_find_all(s, (const char*)NULL, 123,
						(uint32_t*)ptr_not_null,
						(uint32_t*)ptr_not_null);
	TEST_ASSERT(rv == CDADA_E_INVALID);
	rv = cdada_str_find_all(s, (const char*)ptr_not_null, 0,
						(uint32_t*)ptr_not_null,
						(uint32_t*)ptr_not_null);
	TEST_ASSERT(rv == CDADA_E_INVALID);
	rv = cdada_str_find_all(s, (const char*)ptr_not_null, 123,
						(uint32_t*)NULL,
						(uint32_t*)ptr_not_null);
	TEST_ASSERT(rv == CDADA_E_INVALID);
	rv = cdada_str_find_all(s, (const char*)ptr_not_null, 123,
						(uint32_t*)ptr_not_null,
						(uint32_t*)NULL);
	TEST_ASSERT(rv == CDADA_E_INVALID);

	rv = cdada_str_first_c(NULL, (char*)ptr_not_null);
	TEST_ASSERT(rv == CDADA_E_INVALID);
	rv = cdada_str_first_c(s, (char*)NULL);
	TEST_ASSERT(rv == CDADA_E_INVALID);

	rv = cdada_str_get_c(NULL, 1, (char*)ptr_not_null);
	TEST_ASSERT(rv == CDADA_E_INVALID);
	rv = cdada_str_get_c(s, 123, (char*)ptr_not_null);
	TEST_ASSERT(rv == CDADA_E_INVALID);
	rv = cdada_str_get_c(s, 1, (char*)NULL);
	TEST_ASSERT(rv == CDADA_E_INVALID);

	rv = cdada_str_last_c(NULL, (char*)ptr_not_null);
	TEST_ASSERT(rv == CDADA_E_INVALID);
	rv = cdada_str_last_c(s, (char*)NULL);
	TEST_ASSERT(rv == CDADA_E_INVALID);

	rv = cdada_str_set(NULL, (const char*)ptr_not_null);
	TEST_ASSERT(rv == CDADA_E_INVALID);
	rv = cdada_str_set(s, (const char*)NULL);
	TEST_ASSERT(rv == CDADA_E_INVALID);
	rv = cdada_str_clear(NULL);
	TEST_ASSERT(rv == CDADA_E_INVALID);

	rv = cdada_str_append(NULL, (const char*)ptr_not_null);
	TEST_ASSERT(rv == CDADA_E_INVALID);
	rv = cdada_str_append(s, (const char*)NULL);
	TEST_ASSERT(rv == CDADA_E_INVALID);

	rv = cdada_str_trim(NULL, 2);
	TEST_ASSERT(rv == CDADA_E_INVALID);
	rv = cdada_str_trim(s, 66);
	TEST_ASSERT(rv == CDADA_E_INVALID);

	rv = cdada_str_insert(NULL, 2,  (const char*)ptr_not_null);
	TEST_ASSERT(rv == CDADA_E_INVALID);
	rv = cdada_str_insert(s, 66,  (const char*)ptr_not_null);
	TEST_ASSERT(rv == CDADA_E_INVALID);
	rv = cdada_str_insert(s, 2,  (const char*)NULL);
	TEST_ASSERT(rv == CDADA_E_INVALID);

	rv = cdada_str_erase(NULL, 2, 1);
	TEST_ASSERT(rv == CDADA_E_INVALID);
	rv = cdada_str_erase(s, 66, 1);
	TEST_ASSERT(rv == CDADA_E_INVALID);
	rv = cdada_str_erase(s, 2, 55);
	TEST_ASSERT(rv == CDADA_E_INVALID);

	rv = cdada_str_lower(NULL);
	TEST_ASSERT(rv == CDADA_E_INVALID);
	rv = cdada_str_upper(NULL);
	TEST_ASSERT(rv == CDADA_E_INVALID);

	rv = cdada_str_replace_all(NULL, (const char*)ptr_not_null,
						(const char*)ptr_not_null);
	TEST_ASSERT(rv == CDADA_E_INVALID);
	rv = cdada_str_replace_all(s, (const char*)NULL,
						(const char*)ptr_not_null);
	TEST_ASSERT(rv == CDADA_E_INVALID);
	rv = cdada_str_replace_all(s, (const char*)ptr_not_null,
						(const char*)NULL);
	TEST_ASSERT(rv == CDADA_E_INVALID);


	rv = cdada_str_replace(NULL, (const char*)ptr_not_null,
						(const char*)ptr_not_null, 1);
	TEST_ASSERT(rv == CDADA_E_INVALID);
	rv = cdada_str_replace(s, (const char*)NULL,
						(const char*)ptr_not_null, 1);
	TEST_ASSERT(rv == CDADA_E_INVALID);
	rv = cdada_str_replace(s, (const char*)ptr_not_null,
						(const char*)NULL, 1);
	TEST_ASSERT(rv == CDADA_E_INVALID);
	rv = cdada_str_replace(s, (const char*)ptr_not_null,
						(const char*)NULL, 555);
	TEST_ASSERT(rv == CDADA_E_INVALID);

	rv = cdada_str_destroy(s);
	TEST_ASSERT(rv == CDADA_SUCCESS);

	return 0;
}

int test_manipulation(){

	int rv;
	cdada_str_t * s;
	s = cdada_str_create("This is a test test");
	TEST_ASSERT(s != NULL);
	TEST_ASSERT(cdada_str_empty(s) == false);
	TEST_ASSERT(cdada_str_length(s) == 19);

	rv = cdada_str_set(s, "Another test");
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(cdada_str_length(s) == 12);
	TEST_ASSERT(cdada_str_empty(s) == false);

	rv = cdada_str_clear(s);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(cdada_str_empty(s) == true);

	rv = cdada_str_set(s, "Another test");
	TEST_ASSERT(rv == CDADA_SUCCESS);
	rv = cdada_str_append(s, " TEST tEsT");
	TEST_ASSERT(rv == CDADA_SUCCESS);
	fprintf(stdout, "%s\n", cdada_str(s));

	TEST_ASSERT(strcmp(cdada_str(s), "Another test TEST tEsT") == 0);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(cdada_str_length(s) == 22);
	TEST_ASSERT(cdada_str_trim(s, 4) == CDADA_SUCCESS);
	TEST_ASSERT(cdada_str_length(s) == 18);
	TEST_ASSERT(strcmp(cdada_str(s), "Another test TEST ") == 0);
	rv = cdada_str_append(s, " TEST tEsT");
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(strcmp(cdada_str(s), "Another test TEST  TEST tEsT") == 0);


	//Insert in position
	rv = cdada_str_set(s, "test");
	TEST_ASSERT(rv == CDADA_SUCCESS);
	rv = cdada_str_insert(s, 0, "XX");
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(strcmp(cdada_str(s), "XXtest") == 0);
	rv = cdada_str_insert(s, 1, "YY");
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(strcmp(cdada_str(s), "XYYXtest") == 0);
	rv = cdada_str_insert(s, 8, "ZZ");
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(strcmp(cdada_str(s), "XYYXtestZZ") == 0);
	rv = cdada_str_erase(s, 1, 2);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(strcmp(cdada_str(s), "XXtestZZ") == 0);
	rv = cdada_str_erase(s, 8, 2);
	TEST_ASSERT(rv == CDADA_E_INVALID);

	rv = cdada_str_set(s, "Another test TEST  TEST tEsT xx YYY XY");
	TEST_ASSERT(rv == CDADA_SUCCESS);
	rv = cdada_str_lower(s);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	fprintf(stdout, "%s\n", cdada_str(s));
	TEST_ASSERT(strcmp(cdada_str(s), "another test test  test test xx yyy xy") == 0);

	rv = cdada_str_upper(s);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(strcmp(cdada_str(s), "ANOTHER TEST TEST  TEST TEST XX YYY XY") == 0);

	rv = cdada_str_replace_all(s, "TEST", "HIGHFIVE");
	TEST_ASSERT(strcmp(cdada_str(s), "ANOTHER HIGHFIVE HIGHFIVE  HIGHFIVE HIGHFIVE XX YYY XY") == 0);

	rv = cdada_str_set(s, "Another test TEST  TEST tEsT xx YYY XY");
	TEST_ASSERT(rv == CDADA_SUCCESS);
	rv = cdada_str_replace(s, "TESTt", "HIGHFIVE", 13);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(strcmp(cdada_str(s), "Another test TEST  TEST tEsT xx YYY XY") == 0);

	rv = cdada_str_replace(s, "TEST", "HIGHFIVE", 13);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(strcmp(cdada_str(s), "Another test HIGHFIVE  TEST tEsT xx YYY XY") == 0);

	rv = cdada_str_replace(s, "TEST", "HIGHFIVE", 13);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	TEST_ASSERT(strcmp(cdada_str(s), "Another test HIGHFIVE  HIGHFIVE tEsT xx YYY XY") == 0);

	rv = cdada_str_destroy(s);
	TEST_ASSERT(rv == CDADA_SUCCESS);

	return 0;
}

int main(int args, char** argv){

	int rv;

	fprintf(stdout, "Running libcdada: %s, MAJOR: %s, MINOR: %s, PATCH: %s. Build '%s' \n",
							CDADA_VERSION,
							CDADA_VERSION_MAJOR,
							CDADA_VERSION_MINOR,
							CDADA_VERSION_PATCH,
							CDADA_BUILD);

	rv = test_basics();
	rv |= test_access();
	rv |= test_manipulation();

	//Add your test here, and return a code appropriately...
	return rv == 0? EXIT_SUCCESS : EXIT_FAILURE;
}
