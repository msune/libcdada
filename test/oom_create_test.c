#include <stdint.h>
#include <stdlib.h>

#include "cdada/bbitmap.h"
#include "cdada/list.h"
#include "cdada/map.h"
#include "cdada/queue.h"
#include "cdada/set.h"
#include "cdada/stack.h"
#include "cdada/str.h"
#include "common.h"

static int g_fail_next_malloc = 0;

#ifdef __GLIBC__
extern void* __libc_malloc(size_t size);

void* malloc(size_t size){
	if(g_fail_next_malloc)
		return NULL;
	return __libc_malloc(size);
}
#endif

int main(int argc, char** argv){
	cdada_list_t* list;
	cdada_map_t* map;
	cdada_queue_t* queue;
	cdada_set_t* set;
	cdada_stack_t* stack;
	cdada_str_t* str;
	cdada_bbitmap_t* bbitmap;

	(void)argc;
	(void)argv;

	g_fail_next_malloc = 0;
	list = cdada_list_create(uint32_t);
	TEST_ASSERT(list != NULL);
	TEST_ASSERT(cdada_list_destroy(list) == CDADA_SUCCESS);

	g_fail_next_malloc = 1;
	list = cdada_list_create(uint32_t);
	g_fail_next_malloc = 0;
	TEST_ASSERT(list == NULL);

	g_fail_next_malloc = 0;
	map = cdada_map_create(uint32_t);
	TEST_ASSERT(map != NULL);
	TEST_ASSERT(cdada_map_destroy(map) == CDADA_SUCCESS);

	g_fail_next_malloc = 1;
	map = cdada_map_create(uint32_t);
	g_fail_next_malloc = 0;
	TEST_ASSERT(map == NULL);

	g_fail_next_malloc = 0;
	queue = cdada_queue_create(uint32_t);
	TEST_ASSERT(queue != NULL);
	TEST_ASSERT(cdada_queue_destroy(queue) == CDADA_SUCCESS);

	g_fail_next_malloc = 1;
	queue = cdada_queue_create(uint32_t);
	g_fail_next_malloc = 0;
	TEST_ASSERT(queue == NULL);

	g_fail_next_malloc = 0;
	set = cdada_set_create(uint32_t);
	TEST_ASSERT(set != NULL);
	TEST_ASSERT(cdada_set_destroy(set) == CDADA_SUCCESS);

	g_fail_next_malloc = 1;
	set = cdada_set_create(uint32_t);
	g_fail_next_malloc = 0;
	TEST_ASSERT(set == NULL);

	g_fail_next_malloc = 0;
	stack = cdada_stack_create(uint32_t);
	TEST_ASSERT(stack != NULL);
	TEST_ASSERT(cdada_stack_destroy(stack) == CDADA_SUCCESS);

	g_fail_next_malloc = 1;
	stack = cdada_stack_create(uint32_t);
	g_fail_next_malloc = 0;
	TEST_ASSERT(stack == NULL);

	g_fail_next_malloc = 0;
	str = cdada_str_create("oom");
	TEST_ASSERT(str != NULL);
	TEST_ASSERT(cdada_str_destroy(str) == CDADA_SUCCESS);

	g_fail_next_malloc = 1;
	str = cdada_str_create("oom");
	g_fail_next_malloc = 0;
	TEST_ASSERT(str == NULL);

	g_fail_next_malloc = 0;
	bbitmap = cdada_bbitmap_create(64);
	TEST_ASSERT(bbitmap != NULL);
	TEST_ASSERT(cdada_bbitmap_destroy(bbitmap) == CDADA_SUCCESS);

	g_fail_next_malloc = 1;
	bbitmap = cdada_bbitmap_create(64);
	g_fail_next_malloc = 0;
	TEST_ASSERT(bbitmap == NULL);

	return EXIT_SUCCESS;
}
