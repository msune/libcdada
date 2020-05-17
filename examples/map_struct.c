#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <cdata/map.h>

//Define the key type, with strings to make it fun
//Make sure it packed(!) and if possible align to power of 2
typedef struct{
	char corridor[20];
	char shelf[20];
	char item[24];
}__attribute__((packed)) my_key_t;

typedef struct{
	float price;
	float percentage_discount;
}my_val_t;

void trav_print(const cdata_map_t* s, const void* k, void* v, void* opaque){

	my_key_t* key = (my_key_t*)k;
	my_val_t* val = (my_val_t*)v;

	fprintf(stdout, "\t[corridor: %s, shelf: %s, item: %s] = {%f, %f%%}\n",
						key->corridor,
						key->shelf,
						key->item,
						val->price,
						val->percentage_discount);
}

void print_inventory(cdata_map_t* m){
	fprintf(stdout, "Inventory size %u, contents:\n", cdata_map_size(m));
	cdata_map_traverse(m, &trav_print, NULL);
}

int main(int args, char** argv){
	my_key_t key;
	my_val_t* val;

	cdata_map_t* m = cdata_map_create(sizeof(my_key_t));

	fprintf(stdout, "Map %s (%u)\n",
				cdata_map_empty(m)? "is empty" : "has elements",
				cdata_map_size(m));

	//Key must have all bytes initialized(!)
	memset(&key, 0, sizeof(my_key_t));

	//Add inventory Apple MacBook Pro to inventory
	val = (my_val_t*)malloc(sizeof(my_val_t));
	snprintf(key.corridor, 20, "central");
	snprintf(key.shelf, 20, "2nd");
	snprintf(key.item, 24, "Apple MacBook Pro");
	val->price = 1500;
	val->percentage_discount = 0.0;
	cdata_map_insert(m, &key, val);

	print_inventory(m);

	//Attempt to add the same should yield E_EXISTS
	val = (my_val_t*)malloc(sizeof(my_val_t));
	int rv = cdata_map_insert(m, &key, val);
	if(rv != CDATA_E_EXISTS){
		fprintf(stderr, "libcdata has a bug!\n");
		return EXIT_FAILURE;
	}

	//Add another item
	memset(&key, 0, sizeof(my_key_t)); //Let's not leave trailing chars
	snprintf(key.corridor, 20, "left");
	snprintf(key.shelf, 20, "4th");
	snprintf(key.item, 24, "Lenovo T440s");
	val->price = 1300;
	val->percentage_discount = 15.0;
	rv = cdata_map_insert(m, &key, val);
	if(rv != CDATA_SUCCESS){
		fprintf(stderr, "libcdata has a bug!\n");
		return EXIT_FAILURE;
	}
	print_inventory(m);

	//Find an element
	memset(&key, 0, sizeof(my_key_t)); //Let's not leave trailing chars
	snprintf(key.corridor, 20, "central");
	snprintf(key.shelf, 20, "2nd");
	snprintf(key.item, 24, "Apple MacBook Pro");
	cdata_map_find(m, &key, (void**)&val);

	fprintf(stdout, "Macbook pro price: %f, discount: %f %%\n", val->price,
						val->percentage_discount);
	fprintf(stdout, "Map %s (%u)\n",
				cdata_map_empty(m)? "is empty" : "has elements",
				cdata_map_size(m));

	//Erase MacBook Pro from inventory
	cdata_map_erase(m, &key);
	free(val);
	fprintf(stdout, "Map %s (%u)\n",
				cdata_map_empty(m)? "is empty" : "has elements",
				cdata_map_size(m));


	//Cleanup
	memset(&key, 0, sizeof(my_key_t)); //Let's not leave trailing chars
	snprintf(key.corridor, 20, "left");
	snprintf(key.shelf, 20, "4th");
	snprintf(key.item, 24, "Lenovo T440s");
	cdata_map_find(m, &key, (void**)&val);
	free(val);

	//Don't leak
	cdata_map_destroy(m);

	return EXIT_SUCCESS;
}
