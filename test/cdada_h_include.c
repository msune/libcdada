#include <stdlib.h>

#include "common.h"
#include "cdada.h"

int main(int args, char** argv){

	int rv;
	cdada_list_t* list;
	cdada_map_t* map;
	cdada_set_t* set;
	cdada_stack_t *stack;
	cdada_str_t* str;

	list = cdada_list_create(uint32_t);
	TEST_ASSERT(list != NULL);
	map = cdada_map_create(uint32_t);
	TEST_ASSERT(map != NULL);
	set = cdada_set_create(uint32_t);
	TEST_ASSERT(set != NULL);
	stack = cdada_stack_create(uint32_t);
	TEST_ASSERT(stack != NULL);
	str = cdada_str_create("");
	TEST_ASSERT(str != NULL);

	rv = cdada_list_destroy(list);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	rv = cdada_map_destroy(map);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	rv = cdada_set_destroy(set);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	rv = cdada_stack_destroy(stack);
	TEST_ASSERT(rv == CDADA_SUCCESS);
	rv = cdada_str_destroy(str);
	TEST_ASSERT(rv == CDADA_SUCCESS);

	//Add your test here, and return a code appropriately...
	return rv == 0? EXIT_SUCCESS : EXIT_FAILURE;
}
