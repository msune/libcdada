#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <cdada/queue.h>

int main(int args, char** argv){
	uint32_t item;
	cdada_queue_t* q = cdada_queue_create(uint32_t);

	//Push {1,3,5,4,6,5}
	item = 1;
	cdada_queue_push(q, &item);
	item = 3;
	cdada_queue_push(q, &item);
	item = 5;
	cdada_queue_push(q, &item);
	item = 4;
	cdada_queue_push(q, &item);
	item = 6;
	cdada_queue_push(q, &item);
	item = 5;
	cdada_queue_push(q, &item);

	fprintf(stdout, "The queue has a size of %u:\n", cdada_queue_size(q));

	uint32_t val;
	cdada_queue_front(q, &val);
	fprintf(stdout, "Popping %u off the queue:\n", val);
	cdada_queue_pop(q);

	fprintf(stdout, "After removal of front, the queue has a size of %u, contents:\n",
							cdada_queue_size(q));
	cdada_queue_print(q, stdout);

	//Don't leak
	cdada_queue_destroy(q);

	return EXIT_SUCCESS;
}
