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

	//6,4,5,3,1}
	uint32_t val;
	fprintf(stdout, "Popping %u off the stack:\n",
			(cdada_stack_top(s, &val)? 0 : val));
	cdada_stack_pop(s);

	fprintf(stdout, "After removal of top, the stack has a size of %u, contents:\n",
							cdada_stack_size(s));

	//Don't leak
	cdada_stack_destroy(s);

	return EXIT_SUCCESS;
}
