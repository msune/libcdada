#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <cdada/stack.h>

int main(int args, char** argv){
	uint32_t item;
	cdada_stack_t* s = cdada_stack_create(uint32_t);

	//Push {1,3,5,4,6,5}
	item = 1;
	cdada_stack_push(s, &item);
	item = 3;
	cdada_stack_push(s, &item);
	item = 5;
	cdada_stack_push(s, &item);
	item = 4;
	cdada_stack_push(s, &item);
	item = 6;
	cdada_stack_push(s, &item);
	item = 5;
	cdada_stack_push(s, &item);

	fprintf(stdout, "The stack has a size of %u:\n", cdada_stack_size(s));

	uint32_t val;
	cdada_stack_top(s, &val);
	fprintf(stdout, "Popping %u off the stack:\n", val);
	cdada_stack_pop(s);

	fprintf(stdout, "After removal of top, the stack has a size of %u, contents:\n",
							cdada_stack_size(s));
	cdada_stack_print(s, stdout);

	//Don't leak
	cdada_stack_destroy(s);

	return EXIT_SUCCESS;
}
