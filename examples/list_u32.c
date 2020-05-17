#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <cdata/list.h>

void trav_print_and_sum(const cdata_list_t* s, const void* k, void* opaque){

	uint32_t key = *(uint32_t*)k;
	uint32_t* o = (uint32_t*)opaque;

	*o += key;
	fprintf(stdout, "\t[%u] cnt=%u\n", key, *o);
}

int main(int args, char** argv){
	uint32_t item, counter;
	cdata_list_t* l = cdata_list_create(sizeof(uint32_t));

	//Add {1,3,5,4,6,5}
	item = 1;
	cdata_list_push_back(l, &item);
	item = 3;
	cdata_list_push_back(l, &item);
	item = 5;
	cdata_list_push_back(l, &item);
	item = 4;
	cdata_list_push_back(l, &item);
	item = 6;
	cdata_list_push_back(l, &item);
	item = 5;
	cdata_list_push_back(l, &item);

	fprintf(stdout, "The list has a size of %u, contents:\n", cdata_list_size(l));
	counter = 0;
	cdata_list_traverse(l, &trav_print_and_sum, &counter);
	fprintf(stdout, "TOTAL: %u\n", counter);

	//{{1,3,5,6,5}
	cdata_list_erase(l, 3);

	fprintf(stdout, "After removal of 4, the list has a size of %u, contents:\n",
							cdata_list_size(l));
	counter = 0;
	cdata_list_traverse(l, &trav_print_and_sum, &counter);
	fprintf(stdout, "TOTAL: %u\n", counter);

	//Remove front element and reverse {5,6,5,3}
	cdata_list_pop_front(l);
	cdata_list_reverse(l);
	cdata_list_get(l, 1, &item);
	fprintf(stdout, "After pop front and reverse, 2nd element is: %u, size: %u\n",
							item,
							cdata_list_size(l));
	//Sort and unique {3,5,6}
	cdata_list_sort(l);
	cdata_list_unique(l);
	fprintf(stdout, "After unique contents:\n");
	counter = 0;
	cdata_list_traverse(l, &trav_print_and_sum, &counter);
	fprintf(stdout, "TOTAL: %u\n", counter);

	//Don't leak
	cdata_list_destroy(l);

	return EXIT_SUCCESS;
}
