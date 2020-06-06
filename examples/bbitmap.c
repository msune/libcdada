#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <cdada/bbitmap.h>

int main(int args, char** argv){

	int rv;
	cdada_bbitmap_t* b = cdada_bbitmap_create(256);

	cdada_bbitmap_print(b, stdout);
	cdada_bbitmap_set(b, 113);

	fprintf(stdout, "\nAfter setting bit 113:\n");
	cdada_bbitmap_print(b, stdout);

	if(!cdada_bbitmap_is_set(b, 113)){
		fprintf(stderr, "libcdada has a bug!");
		exit(1);
	}

	cdada_bbitmap_set_all(b);
	fprintf(stdout, "\nAfter setting all bit:\n");
	if(!cdada_bbitmap_is_set(b, 113) || !cdada_bbitmap_is_set(b, 0) ||
					!cdada_bbitmap_is_set(b, 255)){
		fprintf(stderr, "libcdada has a bug!");
		exit(1);
	}
	cdada_bbitmap_print(b, stdout);

	cdada_bbitmap_clear(b, 113);
	if(cdada_bbitmap_is_set(b, 113) || !cdada_bbitmap_is_set(b, 0) ||
					!cdada_bbitmap_is_set(b, 255)){
		fprintf(stderr, "libcdada has a bug!");
		exit(1);
	}

	fprintf(stdout, "\nCleared bit 113:\n");
	cdada_bbitmap_print(b, stdout);

	//Use a buffer
	char buffer[1024];
	uint32_t used;

	//Calculate the number of bytes we need
	rv = cdada_bbitmap_dump(b, 0, NULL, &used);
	fprintf(stdout, "\nWe will need: %u bytes\n", used);

	rv = cdada_bbitmap_dump(b, 1024, buffer, &used);
	if(rv == CDADA_E_INCOMPLETE){
		fprintf(stderr, "Warning: dump was truncated\n");
	}

	fprintf(stdout, "\nFinal printf using dump() function, same state:\n%s\nEnd\n",
									buffer);


	//Don't leak
	cdada_bbitmap_destroy(b);

	return EXIT_SUCCESS;
}
