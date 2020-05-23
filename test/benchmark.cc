#include <pthread.h>
#include <set>
#include <map>
#include <list>
#include <cdada/set.h>
#include <cdada/set_custom_cc.h>
#include <cdada/map.h>
#include <cdada/map_custom_cc.h>
#include <cdada/list.h>
#include <cdada/list_custom_cc.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include "u552.h"
#include "u3552.h"

//uint32_t
CDADA_LIST_CUSTOM_GEN(uint32_t);
CDADA_MAP_CUSTOM_GEN(uint32_t);
CDADA_SET_CUSTOM_GEN(uint32_t);

CDADA_LIST_CUSTOM_TYPE_DECL(uint32_t);
CDADA_MAP_CUSTOM_TYPE_DECL(uint32_t);
CDADA_SET_CUSTOM_TYPE_DECL(uint32_t);

//u552
CDADA_CUSTOM_GEN_MEMCP_OPERATORS(test_u552_t);

CDADA_LIST_CUSTOM_GEN(test_u552_t);
CDADA_MAP_CUSTOM_GEN(test_u552_t);
CDADA_SET_CUSTOM_GEN(test_u552_t);

CDADA_LIST_CUSTOM_TYPE_DECL(test_u552_t);
CDADA_MAP_CUSTOM_TYPE_DECL(test_u552_t);
CDADA_SET_CUSTOM_TYPE_DECL(test_u552_t);

//u3552
CDADA_CUSTOM_GEN_MEMCP_OPERATORS(test_u3552_t);

CDADA_LIST_CUSTOM_GEN(test_u3552_t);
CDADA_MAP_CUSTOM_GEN(test_u3552_t);
CDADA_SET_CUSTOM_GEN(test_u3552_t);

CDADA_LIST_CUSTOM_TYPE_DECL(test_u3552_t);
CDADA_MAP_CUSTOM_TYPE_DECL(test_u3552_t);
CDADA_SET_CUSTOM_TYPE_DECL(test_u3552_t);

#if 10

//Assembly to read rdtsc
static inline uint64_t RDTSC()
{
  unsigned int hi, lo;
  __asm__ volatile("rdtsc" : "=a" (lo), "=d" (hi));
  return ((uint64_t)hi << 32) | lo;
}
#else
#ifdef _MSC_VER
#include <intrin.h>
#else
#include <x86intrin.h>
#endif

#define RDTSC __rdtsc
#endif



uint32_t big_array[] = {
	//#include "array.s"
	#include "array.s3"
};

//
// uint32_t
//


//SET
void cpp_set_insert_erase_u32(uint64_t& ticks_insert, uint64_t& ticks_erase){

	uint32_t i;
	std::set<uint32_t> set;
	std::set<uint32_t>::iterator it;
	uint64_t begin, end;

	//Start
	begin = RDTSC();

	for(i=0;i<sizeof(big_array)/4;++i){
		it = set.find(big_array[i]);
		if(it != set.end())
			continue; //SIMULATE E_EXISTS behaviour of lcdada
		set.insert(it, big_array[i]);
	}

	//End
	end = RDTSC();

	ticks_insert += end-begin;

	begin = RDTSC();

	for(i=0;i<sizeof(big_array)/4;++i){
		it = set.find(big_array[i]);
		if(unlikely(it == set.end()))
			continue; //SIMULATE E_NOT_FOUND behaviour of lcdada
		set.erase(it);
	}

	//End
	end = RDTSC();

	ticks_erase += end-begin;

}

void cdada_set_insert_erase_u32(uint64_t& ticks_insert, uint64_t& ticks_erase,
							bool custom){

	uint32_t i;
	cdada_set_t* set = custom? cdada_set_create_custom(uint32_t) :
				cdada_set_create(sizeof(uint32_t));
	uint64_t begin, end;

	//Start
	begin = RDTSC();

	for(i=0;i<sizeof(big_array)/4;++i)
		cdada_set_insert(set, &big_array[i]);

	//End
	end = RDTSC();

	ticks_insert += end-begin;

	//Start
	begin = RDTSC();

	for(i=0;i<sizeof(big_array)/4;++i)
		cdada_set_erase(set, &big_array[i]);

	//End
	end = RDTSC();

	ticks_erase += end-begin;

	cdada_set_destroy(set);
}

//MAP
void cpp_map_insert_erase_u32(uint64_t& ticks_insert, uint64_t& ticks_erase){

	uint32_t i;
	std::map<uint32_t, void*> map;
	std::map<uint32_t, void*>::iterator it;
	uint64_t begin, end;

	//Start
	begin = RDTSC();

	for(i=0;i<sizeof(big_array)/4;++i){
		it = map.find(big_array[i]);
		if(unlikely(it != map.end()))
			continue; //SIMULATE E_EXISTS behaviour of lcdada
		map[big_array[i]] = (void*)&it;
	}

	//End
	end = RDTSC();

	ticks_insert += end-begin;

	begin = RDTSC();

	for(i=0;i<sizeof(big_array)/4;++i){
		it = map.find(big_array[i]);
		if(unlikely(it == map.end()))
			continue; //SIMULATE E_NOT_FOUND behaviour of lcdada
		map.erase(it);
	}

	//End
	end = RDTSC();

	ticks_erase += end-begin;

}

void cdada_map_insert_erase_u32(uint64_t& ticks_insert, uint64_t& ticks_erase,
							bool custom){

	uint32_t i;
	cdada_map_t* map  = custom? cdada_map_create_custom(uint32_t) :
					cdada_map_create(sizeof(uint32_t));
	uint64_t begin, end;

	//Start
	begin = RDTSC();

	for(i=0;i<sizeof(big_array)/4;++i)
		cdada_map_insert(map, &big_array[i], (void*)&i);

	//End
	end = RDTSC();

	ticks_insert += end-begin;

	//Start
	begin = RDTSC();

	for(i=0;i<sizeof(big_array)/4;++i)
		cdada_map_erase(map, &big_array[i]);

	//End
	end = RDTSC();

	ticks_erase += end-begin;

	cdada_map_destroy(map);
}

//LIST
void cpp_list_push_pop_u32(uint64_t& ticks_push_back, uint64_t& ticks_pop_back){

	uint32_t i;
	std::list<uint32_t> list;
	uint64_t begin, end;

	//Start
	begin = RDTSC();

	for(i=0;i<sizeof(big_array)/4;++i)
		list.push_back(big_array[i]);

	//End
	end = RDTSC();

	ticks_push_back += end-begin;

	begin = RDTSC();

	for(i=0;i<sizeof(big_array)/4;++i)
		list.pop_back();

	//End
	end = RDTSC();

	ticks_pop_back += end-begin;

}

void cdada_list_push_pop_u32(uint64_t& ticks_push_back, uint64_t& ticks_pop_back,
							bool custom){

	uint32_t i;
	cdada_list_t* list = custom? cdada_list_create_custom(uint32_t) :
				cdada_list_create(sizeof(uint32_t));
	uint64_t begin, end;

	//Start
	begin = RDTSC();

	for(i=0;i<sizeof(big_array)/4;++i)
		cdada_list_push_back(list, &big_array[i]);

	//End
	end = RDTSC();

	ticks_push_back += end-begin;

	//Start
	begin = RDTSC();

	for(i=0;i<sizeof(big_array)/4;++i)
		cdada_list_pop_back(list);

	//End
	end = RDTSC();

	ticks_pop_back += end-begin;

	cdada_list_destroy(list);
}

//
// test_u552_t
//


//SET
void cpp_set_insert_erase_u552(uint64_t& ticks_insert, uint64_t& ticks_erase){

	uint32_t i;
	std::set<test_u552_t> set;
	std::set<test_u552_t>::iterator it;
	uint64_t begin, end;

	test_u552_t* aux = (test_u552_t*)malloc(sizeof(test_u552_t)*
							sizeof(big_array)/4);

	for(i=0;i<sizeof(big_array)/4;++i){
		memset(&aux[i], 0, sizeof(test_u552_t));
		aux[i].mid = big_array[i];
	}

	//Start
	begin = RDTSC();

	for(i=0;i<sizeof(big_array)/4;++i){
		it = set.find(aux[i]);
		if(it != set.end())
			continue; //SIMULATE E_EXISTS behaviour of lcdada
		set.insert(it, aux[i]);
	}

	//End
	end = RDTSC();

	ticks_insert += end-begin;

	begin = RDTSC();

	for(i=0;i<sizeof(big_array)/4;++i){
		it = set.find(aux[i]);
		if(unlikely(it == set.end()))
			continue; //SIMULATE E_NOT_FOUND behaviour of lcdada
		set.erase(it);
	}

	//End
	end = RDTSC();

	ticks_erase += end-begin;

	free(aux);
}

void cdada_set_insert_erase_u552(uint64_t& ticks_insert, uint64_t& ticks_erase,
							bool custom){

	uint32_t i;
	cdada_set_t* set = custom? cdada_set_create_custom(test_u552_t) :
				cdada_set_create(sizeof(test_u552_t));
	uint64_t begin, end;

	test_u552_t* aux = (test_u552_t*)malloc(sizeof(test_u552_t)*
							sizeof(big_array)/4);

	for(i=0;i<sizeof(big_array)/4;++i){
		memset(&aux[i], 0, sizeof(test_u552_t));
		aux[i].mid = big_array[i];
	}

	//Start
	begin = RDTSC();

	for(i=0;i<sizeof(big_array)/4;++i)
		cdada_set_insert(set, &aux[i]);

	//End
	end = RDTSC();

	ticks_insert += end-begin;

	//Start
	begin = RDTSC();

	for(i=0;i<sizeof(big_array)/4;++i)
		cdada_set_erase(set, &aux[i]);

	//End
	end = RDTSC();

	ticks_erase += end-begin;

	cdada_set_destroy(set);

	free(aux);
}

//MAP
void cpp_map_insert_erase_u552(uint64_t& ticks_insert, uint64_t& ticks_erase){

	uint32_t i;
	std::map<test_u552_t, void*> map;
	std::map<test_u552_t, void*>::iterator it;
	uint64_t begin, end;

	test_u552_t* aux = (test_u552_t*)malloc(sizeof(test_u552_t)*
							sizeof(big_array)/4);

	for(i=0;i<sizeof(big_array)/4;++i){
		memset(&aux[i], 0, sizeof(test_u552_t));
		aux[i].mid = big_array[i];
	}

	//Start
	begin = RDTSC();

	for(i=0;i<sizeof(big_array)/4;++i){
		it = map.find(aux[i]);
		if(unlikely(it != map.end()))
			continue; //SIMULATE E_EXISTS behaviour of lcdada
		map[aux[i]] = (void*)&it;
	}

	//End
	end = RDTSC();

	ticks_insert += end-begin;

	begin = RDTSC();

	for(i=0;i<sizeof(big_array)/4;++i){
		it = map.find(aux[i]);
		if(unlikely(it == map.end()))
			continue; //SIMULATE E_NOT_FOUND behaviour of lcdada
		map.erase(it);
	}

	//End
	end = RDTSC();

	ticks_erase += end-begin;

	free(aux);
}

void cdada_map_insert_erase_u552(uint64_t& ticks_insert, uint64_t& ticks_erase,
							bool custom){

	uint32_t i;
	cdada_map_t* map  = custom? cdada_map_create_custom(test_u552_t) :
					cdada_map_create(sizeof(test_u552_t));
	uint64_t begin, end;

	test_u552_t* aux = (test_u552_t*)malloc(sizeof(test_u552_t)*
							sizeof(big_array)/4);

	for(i=0;i<sizeof(big_array)/4;++i){
		memset(&aux[i], 0, sizeof(test_u552_t));
		aux[i].mid = big_array[i];
	}

	//Start
	begin = RDTSC();

	for(i=0;i<sizeof(big_array)/4;++i)
		cdada_map_insert(map, &aux[i], (void*)&i);

	//End
	end = RDTSC();

	ticks_insert += end-begin;

	//Start
	begin = RDTSC();

	for(i=0;i<sizeof(big_array)/4;++i)
		cdada_map_erase(map, &aux[i]);

	//End
	end = RDTSC();

	ticks_erase += end-begin;

	cdada_map_destroy(map);
	free(aux);
}

//LIST
void cpp_list_push_pop_u552(uint64_t& ticks_push_back, uint64_t& ticks_pop_back){

	uint32_t i;
	std::list<test_u552_t> list;
	uint64_t begin, end;

	test_u552_t* aux = (test_u552_t*)malloc(sizeof(test_u552_t)*
							sizeof(big_array)/4);

	for(i=0;i<sizeof(big_array)/4;++i){
		memset(&aux[i], 0, sizeof(test_u552_t));
		aux[i].mid = big_array[i];
	}

	//Start
	begin = RDTSC();

	for(i=0;i<sizeof(big_array)/4;++i)
		list.push_back(aux[i]);

	//End
	end = RDTSC();

	ticks_push_back += end-begin;

	begin = RDTSC();

	for(i=0;i<sizeof(big_array)/4;++i)
		list.pop_back();

	//End
	end = RDTSC();

	ticks_pop_back += end-begin;

	free(aux);

}

void cdada_list_push_pop_u552(uint64_t& ticks_push_back,
						uint64_t& ticks_pop_back,
						bool custom){

	uint32_t i;
	cdada_list_t* list = custom? cdada_list_create_custom(test_u552_t) :
				cdada_list_create(sizeof(test_u552_t));
	uint64_t begin, end;

	test_u552_t* aux = (test_u552_t*)malloc(sizeof(test_u552_t)*
							sizeof(big_array)/4);

	for(i=0;i<sizeof(big_array)/4;++i){
		memset(&aux[i], 0, sizeof(test_u552_t));
		aux[i].mid = big_array[i];
	}

	//Start
	begin = RDTSC();

	for(i=0;i<sizeof(big_array)/4;++i)
		cdada_list_push_back(list, &aux[i]);

	//End
	end = RDTSC();

	ticks_push_back += end-begin;

	//Start
	begin = RDTSC();

	for(i=0;i<sizeof(big_array)/4;++i)
		cdada_list_pop_back(list);

	//End
	end = RDTSC();

	ticks_pop_back += end-begin;

	cdada_list_destroy(list);

	free(aux);
}

//
// test_u3552_t
//

//SET
void cpp_set_insert_erase_u3552(uint64_t& ticks_insert, uint64_t& ticks_erase){

	uint32_t i;
	std::set<test_u3552_t> set;
	std::set<test_u3552_t>::iterator it;
	uint64_t begin, end;

	test_u3552_t* aux = (test_u3552_t*)malloc(sizeof(test_u3552_t)*
							sizeof(big_array)/4);

	for(i=0;i<sizeof(big_array)/4;++i){
		memset(&aux[i], 0, sizeof(test_u3552_t));
		aux[i].mid = big_array[i];
	}

	//Start
	begin = RDTSC();

	for(i=0;i<sizeof(big_array)/4;++i){
		it = set.find(aux[i]);
		if(it != set.end())
			continue; //SIMULATE E_EXISTS behaviour of lcdada
		set.insert(it, aux[i]);
	}

	//End
	end = RDTSC();

	ticks_insert += end-begin;

	begin = RDTSC();

	for(i=0;i<sizeof(big_array)/4;++i){
		it = set.find(aux[i]);
		if(unlikely(it == set.end()))
			continue; //SIMULATE E_NOT_FOUND behaviour of lcdada
		set.erase(it);
	}

	//End
	end = RDTSC();

	ticks_erase += end-begin;

	free(aux);
}

void cdada_set_insert_erase_u3552(uint64_t& ticks_insert, uint64_t& ticks_erase,
							bool custom){

	uint32_t i;
	cdada_set_t* set = custom? cdada_set_create_custom(test_u3552_t) :
				cdada_set_create(sizeof(test_u3552_t));
	uint64_t begin, end;

	test_u3552_t* aux = (test_u3552_t*)malloc(sizeof(test_u3552_t)*
							sizeof(big_array)/4);

	for(i=0;i<sizeof(big_array)/4;++i){
		memset(&aux[i], 0, sizeof(test_u3552_t));
		aux[i].mid = big_array[i];
	}

	//Start
	begin = RDTSC();

	for(i=0;i<sizeof(big_array)/4;++i)
		cdada_set_insert(set, &aux[i]);

	//End
	end = RDTSC();

	ticks_insert += end-begin;

	//Start
	begin = RDTSC();

	for(i=0;i<sizeof(big_array)/4;++i)
		cdada_set_erase(set, &aux[i]);

	//End
	end = RDTSC();

	ticks_erase += end-begin;

	cdada_set_destroy(set);

	free(aux);
}

//MAP
void cpp_map_insert_erase_u3552(uint64_t& ticks_insert, uint64_t& ticks_erase){

	uint32_t i;
	std::map<test_u3552_t, void*> map;
	std::map<test_u3552_t, void*>::iterator it;
	uint64_t begin, end;

	test_u3552_t* aux = (test_u3552_t*)malloc(sizeof(test_u3552_t)*
							sizeof(big_array)/4);

	for(i=0;i<sizeof(big_array)/4;++i){
		memset(&aux[i], 0, sizeof(test_u3552_t));
		aux[i].mid = big_array[i];
	}

	//Start
	begin = RDTSC();

	for(i=0;i<sizeof(big_array)/4;++i){
		it = map.find(aux[i]);
		if(unlikely(it != map.end()))
			continue; //SIMULATE E_EXISTS behaviour of lcdada
		map[aux[i]] = (void*)&it;
	}

	//End
	end = RDTSC();

	ticks_insert += end-begin;

	begin = RDTSC();

	for(i=0;i<sizeof(big_array)/4;++i){
		it = map.find(aux[i]);
		if(unlikely(it == map.end()))
			continue; //SIMULATE E_NOT_FOUND behaviour of lcdada
		map.erase(it);
	}

	//End
	end = RDTSC();

	ticks_erase += end-begin;

	free(aux);
}

void cdada_map_insert_erase_u3552(uint64_t& ticks_insert, uint64_t& ticks_erase,
							bool custom){

	uint32_t i;
	cdada_map_t* map  = custom? cdada_map_create_custom(test_u3552_t) :
					cdada_map_create(sizeof(test_u3552_t));
	uint64_t begin, end;

	test_u3552_t* aux = (test_u3552_t*)malloc(sizeof(test_u3552_t)*
							sizeof(big_array)/4);

	for(i=0;i<sizeof(big_array)/4;++i){
		memset(&aux[i], 0, sizeof(test_u3552_t));
		aux[i].mid = big_array[i];
	}

	//Start
	begin = RDTSC();

	for(i=0;i<sizeof(big_array)/4;++i)
		cdada_map_insert(map, &aux[i], (void*)&i);

	//End
	end = RDTSC();

	ticks_insert += end-begin;

	//Start
	begin = RDTSC();

	for(i=0;i<sizeof(big_array)/4;++i)
		cdada_map_erase(map, &aux[i]);

	//End
	end = RDTSC();

	ticks_erase += end-begin;

	cdada_map_destroy(map);
	free(aux);
}

//LIST
void cpp_list_push_pop_u3552(uint64_t& ticks_push_back, uint64_t& ticks_pop_back){

	uint32_t i;
	std::list<test_u3552_t> list;
	uint64_t begin, end;

	test_u3552_t* aux = (test_u3552_t*)malloc(sizeof(test_u3552_t)*
							sizeof(big_array)/4);

	for(i=0;i<sizeof(big_array)/4;++i){
		memset(&aux[i], 0, sizeof(test_u3552_t));
		aux[i].mid = big_array[i];
	}

	//Start
	begin = RDTSC();

	for(i=0;i<sizeof(big_array)/4;++i)
		list.push_back(aux[i]);

	//End
	end = RDTSC();

	ticks_push_back += end-begin;

	begin = RDTSC();

	for(i=0;i<sizeof(big_array)/4;++i)
		list.pop_back();

	//End
	end = RDTSC();

	ticks_pop_back += end-begin;

	free(aux);

}

void cdada_list_push_pop_u3552(uint64_t& ticks_push_back,
						uint64_t& ticks_pop_back,
						bool custom){

	uint32_t i;
	cdada_list_t* list = custom? cdada_list_create_custom(test_u3552_t) :
				cdada_list_create(sizeof(test_u3552_t));
	uint64_t begin, end;

	test_u3552_t* aux = (test_u3552_t*)malloc(sizeof(test_u3552_t)*
							sizeof(big_array)/4);

	for(i=0;i<sizeof(big_array)/4;++i){
		memset(&aux[i], 0, sizeof(test_u3552_t));
		aux[i].mid = big_array[i];
	}

	//Start
	begin = RDTSC();

	for(i=0;i<sizeof(big_array)/4;++i)
		cdada_list_push_back(list, &aux[i]);

	//End
	end = RDTSC();

	ticks_push_back += end-begin;

	//Start
	begin = RDTSC();

	for(i=0;i<sizeof(big_array)/4;++i)
		cdada_list_pop_back(list);

	//End
	end = RDTSC();

	ticks_pop_back += end-begin;

	cdada_list_destroy(list);

	free(aux);
}

void print_summary(const char* test, float ticks_insert, float ticks_removal){
	uint64_t iterations = sizeof(big_array)*10/4;
	float i_op = (float)(ticks_insert)/iterations;
	float r_op = (float)(ticks_removal)/iterations;
	fprintf(stdout, "%s %.0f \t\t %.0f\n", test, i_op, r_op);
}

int main(int args, char** argv){

	uint64_t ticks_insert, ticks_erase;

	pthread_t this_thread = pthread_self();
	struct sched_param params;
	params.sched_priority = sched_get_priority_max(SCHED_FIFO);
	pthread_setschedparam(this_thread, SCHED_FIFO, &params);

	/**********************************************************************/
	/* uint32_t                                                           */
	/**********************************************************************/
	fprintf(stdout, "============================================================\n");
	fprintf(stdout, "Type: uint32_t\n");
	fprintf(stdout, "============================================================\n\n");

	//
	//SET insert/remove
	//

	fprintf(stdout, "SET\t\t\t\tinsert(ticks)\terase(ticks)\n");
	fprintf(stdout, "------------------------------------------------------------\n");

	ticks_insert = ticks_erase = 0ULL;
	for(int i =0; i<10; ++i)
		cpp_set_insert_erase_u32(ticks_insert, ticks_erase);
	print_summary("C++ set<uint32_t>\t\t", ticks_insert, ticks_erase);

	ticks_insert = ticks_erase = 0ULL;
	for(int i =0; i<10; ++i)
		cdada_set_insert_erase_u32(ticks_insert, ticks_erase, false);
	print_summary("C cdada_set(uint32_t)\t\t", ticks_insert, ticks_erase);

	ticks_insert = ticks_erase = 0ULL;
	for(int i =0; i<10; ++i)
		cdada_set_insert_erase_u32(ticks_insert, ticks_erase, true);
	print_summary("C cdada_set_custom(uint32_t)\t", ticks_insert, ticks_erase);

	fprintf(stdout, "\n\n");

	//
	//MAP insert/remove
	//

	fprintf(stdout, "MAP\t\t\t\tinsert(ticks)\terase(ticks)\n");
	fprintf(stdout, "------------------------------------------------------------\n");

	ticks_insert = ticks_erase = 0ULL;
	for(int i =0; i<10; ++i)
		cpp_map_insert_erase_u32(ticks_insert, ticks_erase);
	print_summary("C++ map<uint32_t, void*>\t", ticks_insert, ticks_erase);

	ticks_insert = ticks_erase = 0ULL;
	for(int i =0; i<10; ++i)
		cdada_map_insert_erase_u32(ticks_insert, ticks_erase, false);
	print_summary("C cdada_map(uint32_t)\t\t", ticks_insert, ticks_erase);

	ticks_insert = ticks_erase = 0ULL;
	for(int i =0; i<10; ++i)
		cdada_map_insert_erase_u32(ticks_insert, ticks_erase, true);
	print_summary("C cdada_map_custom(uint32_t)\t", ticks_insert, ticks_erase);

	fprintf(stdout, "\n\n");

	//
	//LIST push_back/pop_back
	//

	fprintf(stdout, "LIST\t\t\t\tinsert(ticks)\terase(ticks)\n");
	fprintf(stdout, "------------------------------------------------------------\n");

	ticks_insert = ticks_erase = 0ULL;
	for(int i =0; i<10; ++i)
		cpp_list_push_pop_u32(ticks_insert, ticks_erase);
	print_summary("C++ list<uint32_t>\t\t", ticks_insert, ticks_erase);

	ticks_insert = ticks_erase = 0ULL;
	for(int i =0; i<10; ++i)
		cdada_list_push_pop_u32(ticks_insert, ticks_erase, false);
	print_summary("C cdada_list(uint32_t)\t\t", ticks_insert, ticks_erase);

	ticks_insert = ticks_erase = 0ULL;
	for(int i =0; i<10; ++i)
		cdada_list_push_pop_u32(ticks_insert, ticks_erase, true);
	print_summary("C cdada_list_custom(uint32_t)\t", ticks_insert, ticks_erase);
	fprintf(stdout, "\n\n");

	/**********************************************************************/
	/* 69 byte type                                                       */
	/**********************************************************************/
	fprintf(stdout, "============================================================\n");
	fprintf(stdout, "Type: test_u552_t (69 bytes)\n");
	fprintf(stdout, "(Note: cdada non-custom containers will pad to 128bytes)\n");
	fprintf(stdout, "============================================================\n\n");

	//
	//SET insert/remove
	//

	fprintf(stdout, "SET\t\t\t\tinsert(ticks)\terase(ticks)\n");
	fprintf(stdout, "------------------------------------------------------------\n");

	ticks_insert = ticks_erase = 0ULL;
	for(int i =0; i<10; ++i)
		cpp_set_insert_erase_u552(ticks_insert, ticks_erase);
	print_summary("C++ set<test_u552_t>\t\t", ticks_insert, ticks_erase);

	//Note: will be padded to 128byte
	ticks_insert = ticks_erase = 0ULL;
	for(int i =0; i<10; ++i)
		cdada_set_insert_erase_u552(ticks_insert, ticks_erase, false);
	print_summary("C cdada_set(test_u552_t)\t", ticks_insert, ticks_erase);

	ticks_insert = ticks_erase = 0ULL;
	for(int i =0; i<10; ++i)
		cdada_set_insert_erase_u552(ticks_insert, ticks_erase, true);
	print_summary("C cdada_set_custom(test_u552_t)\t", ticks_insert, ticks_erase);

	fprintf(stdout, "\n\n");

	//
	//MAP insert/remove
	//

	fprintf(stdout, "MAP\t\t\t\tinsert(ticks)\terase(ticks)\n");
	fprintf(stdout, "------------------------------------------------------------\n");

	ticks_insert = ticks_erase = 0ULL;
	for(int i =0; i<10; ++i)
		cpp_map_insert_erase_u552(ticks_insert, ticks_erase);
	print_summary("C++ map<test_u552_t, void*> \t", ticks_insert, ticks_erase);

	//Note: will be padded to 128byte
	ticks_insert = ticks_erase = 0ULL;
	for(int i =0; i<10; ++i)
		cdada_map_insert_erase_u552(ticks_insert, ticks_erase, false);
	print_summary("C cdada_map(test_u552_t)\t", ticks_insert, ticks_erase);

	ticks_insert = ticks_erase = 0ULL;
	for(int i =0; i<10; ++i)
		cdada_map_insert_erase_u552(ticks_insert, ticks_erase, true);
	print_summary("C cdada_map_custom(test_u552_t)\t", ticks_insert, ticks_erase);

	fprintf(stdout, "\n\n");

	//
	//LIST push_back/pop_back
	//

	fprintf(stdout, "LIST\t\t\t\tinsert(ticks)\terase(ticks)\n");
	fprintf(stdout, "------------------------------------------------------------\n");

	ticks_insert = ticks_erase = 0ULL;
	for(int i =0; i<10; ++i)
		cpp_list_push_pop_u552(ticks_insert, ticks_erase);
	print_summary("C++ list<test_u552_t>\t\t", ticks_insert, ticks_erase);

	//Note: will be padded to 128byte
	ticks_insert = ticks_erase = 0ULL;
	for(int i =0; i<10; ++i)
		cdada_list_push_pop_u552(ticks_insert, ticks_erase, false);
	print_summary("C cdada_list(test_u552_t)\t", ticks_insert, ticks_erase);

	ticks_insert = ticks_erase = 0ULL;
	for(int i =0; i<10; ++i)
		cdada_list_push_pop_u552(ticks_insert, ticks_erase, true);
	print_summary("C cdada_list_custom(test_u552_t)", ticks_insert, ticks_erase);

	fprintf(stdout, "\n\n");

	/**********************************************************************/
	/* 444 byte type                                                      */
	/**********************************************************************/

	fprintf(stdout, "============================================================\n");
	fprintf(stdout, "Type: test_u3552_t (444 bytes)\n");
	fprintf(stdout, "(Note: cdada non-custom containers don't support >256 bytes)\n");
	fprintf(stdout, "============================================================\n\n");

	//
	//SET insert/remove
	//

	fprintf(stdout, "SET\t\t\t\tinsert(ticks)\terase(ticks)\n");
	fprintf(stdout, "------------------------------------------------------------\n");

	ticks_insert = ticks_erase = 0ULL;
	for(int i =0; i<10; ++i)
		cpp_set_insert_erase_u3552(ticks_insert, ticks_erase);
	print_summary("C++ set<test_u3552_t>\t\t", ticks_insert, ticks_erase);

	ticks_insert = ticks_erase = 0ULL;
	for(int i =0; i<10; ++i)
		cdada_set_insert_erase_u3552(ticks_insert, ticks_erase, true);
	print_summary("C cdada_set_custom(test_u3552_t)", ticks_insert, ticks_erase);
	fprintf(stdout, "\n\n");

	//
	//MAP insert/remove
	//

	fprintf(stdout, "MAP\t\t\t\tinsert(ticks)\terase(ticks)\n");
	fprintf(stdout, "------------------------------------------------------------\n");


	ticks_insert = ticks_erase = 0ULL;
	for(int i =0; i<10; ++i)
		cpp_map_insert_erase_u3552(ticks_insert, ticks_erase);
	print_summary("C++ map<test_u3552_t, void*> \t", ticks_insert, ticks_erase);

	ticks_insert = ticks_erase = 0ULL;
	for(int i =0; i<10; ++i)
		cdada_map_insert_erase_u3552(ticks_insert, ticks_erase, true);
	print_summary("C cdada_map_custom(test_u3552_t)", ticks_insert, ticks_erase);
	fprintf(stdout, "\n\n");

	//
	//LIST push_back/pop_back
	//

	fprintf(stdout, "LIST\t\t\t\tinsert(ticks)\terase(ticks)\n");
	fprintf(stdout, "------------------------------------------------------------\n");

	ticks_insert = ticks_erase = 0ULL;
	for(int i =0; i<10; ++i)
		cpp_list_push_pop_u3552(ticks_insert, ticks_erase);
	print_summary("C++ list<test_u3552_t>\t\t ", ticks_insert, ticks_erase);

	ticks_insert = ticks_erase = 0ULL;
	for(int i =0; i<10; ++i)
		cdada_list_push_pop_u3552(ticks_insert, ticks_erase, true);
	print_summary("C cdada_list_custom(test_u3552_t)", ticks_insert, ticks_erase);


	return EXIT_SUCCESS;
}
