#include <stdlib.h>

#include "cdata/list.h"
#include "cdata/map.h"
#include "cdata/set.h"
#include "common.h"
#include <string.h>
#include "u552.h"

//Fwd decl
CDATA_LIST_CUSTOM_TYPE_DECL(test_u552_t);
CDATA_MAP_CUSTOM_TYPE_DECL(test_u552_t);
CDATA_SET_CUSTOM_TYPE_DECL(test_u552_t);

int main(int args, char** argv){

	int rv;
	test_u552_t key;
	cdata_list_t* list;
	cdata_map_t* map;
	cdata_set_t* set;

	list = cdata_list_create_custom(test_u552_t);
	TEST_ASSERT(list != NULL);
	map = cdata_map_create_custom(test_u552_t);
	TEST_ASSERT(map != NULL);
	set = cdata_set_create(sizeof(key));
	TEST_ASSERT(set != NULL);

	rv = cdata_list_destroy(list);
	TEST_ASSERT(rv == CDATA_SUCCESS);
	rv = cdata_map_destroy(map);
	TEST_ASSERT(rv == CDATA_SUCCESS);
	rv = cdata_set_destroy(set);
	TEST_ASSERT(rv == CDATA_SUCCESS);

	//Add your test here, and return a code appropriately...
	return rv == 0? EXIT_SUCCESS : EXIT_FAILURE;
}
