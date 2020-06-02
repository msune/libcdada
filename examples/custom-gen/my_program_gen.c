#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <cdada/list.h>
#include <cdada/map.h>

#include "foo.h"
#include "bar.h"

//Type fwd decl
CDADA_LIST_CUSTOM_TYPE_DECL(foo_t);
CDADA_MAP_CUSTOM_TYPE_DECL(bar_t);

int main(int args, char** argv){

	foo_t foo_key;
	bar_t bar_key;
	int i, rv, values[32];
	int* val;

	cdada_list_t* list;
	cdada_map_t* map;

	list = cdada_list_create_custom(foo_t);
	map = cdada_map_create_custom(bar_t);
        assert(list != NULL);
        assert(map != NULL);

	//
	//LIST
	//

	//Add elements in the list - !! always initialize all values
	memset(&foo_key, 0, sizeof(foo_key));
	foo_key.aa = 64ULL;
	foo_key.bb = 32ULL;
	cdada_list_push_back(list, &foo_key);

	foo_key.aa = 12ULL;
	foo_key.bb = 15ULL;
	cdada_list_push_back(list, &foo_key);
	fprintf(stdout, "The list has a size of %u, contents:\n", cdada_list_size(list));

	foo_key.aa = 64ULL;
	foo_key.bb = 32ULL;

	if(cdada_list_get(list, 0, &foo_key) != CDADA_SUCCESS){
		//libcdada has a bug
		exit(1);
	}
	assert(foo_key.aa == 64ULL);

	cdada_list_erase(list, 0);
	fprintf(stdout, "The list has a size of %u, contents:\n",
							cdada_list_size(list));

	//
	//MAP
	//
	memset(&bar_key, 0, sizeof(bar_key));
	for(i=0;i<32;++i){
		bar_key.aa = 2*i;
		bar_key.bb = 0.55;
		values[i] = i;
		cdada_map_insert(map, &bar_key, &values[i]);
	}

	bar_key.aa = 2*5;
	bar_key.bb = 0.55;
	rv = cdada_map_find(map, &bar_key, (void**)&val);
	if(rv != CDADA_SUCCESS){
		//libcdada has a bug
		exit(1);
	}

	assert(*val == 5);
	fprintf(stdout, "Value for aa: %u, bb: %f -> %d\n", bar_key.aa,
							bar_key.bb,
							*val);

	//Don't leak
	cdada_list_destroy(list);
	cdada_map_destroy(map);

	return EXIT_SUCCESS;
}
