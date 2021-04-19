#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <cdada/map.h>

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

void trav_print(const cdada_map_t* s, const void* k, void* v, void* opaque){

	my_key_t* key = (my_key_t*)k;
	my_val_t* val = (my_val_t*)v;

	fprintf(stdout, "\t[corridor: %s, shelf: %s, item: %s] = {%f, %f%%}\n",
						key->corridor,
						key->shelf,
						key->item,
						val->price,
						val->percentage_discount);
}

void print_inventory(cdada_map_t* m){
	fprintf(stdout, "Inventory size %u, contents:\n", cdada_map_size(m));
	cdada_map_traverse(m, &trav_print, NULL);
}

int main(int args, char** argv){
	my_key_t key;
	my_val_t* val;
	void* val_aux; //Avoid alias warnings

	cdada_map_t* m = cdada_map_create(my_key_t);

	fprintf(stdout, "Map %s (%u)\n",
				cdada_map_empty(m)? "is empty" : "has elements",
				cdada_map_size(m));

	//Key must have all bytes initialized(!)
	memset(&key, 0, sizeof(my_key_t));

	//Add inventory Apple MacBook Pro to inventory
	val = (my_val_t*)malloc(sizeof(my_val_t));
	snprintf(key.corridor, 20, "central");
	snprintf(key.shelf, 20, "2nd");
	snprintf(key.item, 24, "Apple MacBook Pro");
	val->price = 1500;
	val->percentage_discount = 0.0;
	cdada_map_insert(m, &key, val);

	print_inventory(m);

	//Attempt to add the same should yield E_EXISTS
	val = (my_val_t*)malloc(sizeof(my_val_t));
	int rv = cdada_map_insert(m, &key, val);
	if(rv != CDADA_E_EXISTS){
		fprintf(stderr, "libcdada has a bug!\n");
		return EXIT_FAILURE;
	}

	//Add another item
	memset(&key, 0, sizeof(my_key_t)); //Let's not leave trailing chars
	snprintf(key.corridor, 20, "left");
	snprintf(key.shelf, 20, "4th");
	snprintf(key.item, 24, "Lenovo T440s");
	val->price = 1300;
	val->percentage_discount = 15.0;
	rv = cdada_map_insert(m, &key, val);
	if(rv != CDADA_SUCCESS){
		fprintf(stderr, "libcdada has a bug!\n");
		return EXIT_FAILURE;
	}
	print_inventory(m);

	//Find an element
	memset(&key, 0, sizeof(my_key_t)); //Let's not leave trailing chars
	snprintf(key.corridor, 20, "central");
	snprintf(key.shelf, 20, "2nd");
	snprintf(key.item, 24, "Apple MacBook Pro");
	cdada_map_find(m, &key, &val_aux);
	val = (my_val_t*)val_aux;

	fprintf(stdout, "Macbook pro price: %f, discount: %f %%\n", val->price,
						val->percentage_discount);
	fprintf(stdout, "Map %s (%u)\n",
				cdada_map_empty(m)? "is empty" : "has elements",
				cdada_map_size(m));

	//Erase MacBook Pro from inventory
	cdada_map_erase(m, &key);
	free(val);
	fprintf(stdout, "Map %s (%u)\n",
				cdada_map_empty(m)? "is empty" : "has elements",
				cdada_map_size(m));

	//Cleanup
	while(cdada_map_first(m, &key, &val_aux) == CDADA_SUCCESS){
		free(val_aux);
		cdada_map_erase(m, &key);
	}

	//Don't leak
	cdada_map_destroy(m);

	return EXIT_SUCCESS;
}
