#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <cdada/str.h>
#include <cdada/version.h>

void trav(const cdada_str_t* str, const char it, uint32_t pos, void* opaque){
	fprintf(stdout, "%u: %c\n", pos, it);
}

int main(int args, char** argv){

	fprintf(stdout, "Running libcdada: %s, MAJOR: %s, MINOR: %s, PATCH: %s. Build '%s' \n",
							cdada_get_ver(),
							cdada_get_ver_maj(),
							cdada_get_ver_min(),
							cdada_get_ver_patch(),
							cdada_get_build());

	cdada_str_t* s = cdada_str_create("One string");
	fprintf(stdout, "%s\n", cdada_str(s));

	//Clear
	cdada_str_clear(s);
	fprintf(stdout, "%s\n", cdada_str(s));

	//Reset
	cdada_str_set(s, "This is a test");
	fprintf(stdout, "%s\n", cdada_str(s));

	cdada_str_append(s, " simple string");

	cdada_str_lower(s);
	cdada_str_replace_all(s, "test ", "");
	fprintf(stdout, "%s\n", cdada_str(s));

	//"THIS IS A SIMPLE STRING"
	cdada_str_upper(s);
	fprintf(stdout, "%s\n", cdada_str(s));

	//Insert in a position "THIS IS A _VERY_, _VERY_ SIMPLE STRING"
	cdada_str_insert(s, 10, "_VERY_, _VERY_ ");
	fprintf(stdout, "%s\n", cdada_str(s));

	//Replace first occurrence from char 11
	cdada_str_replace(s, "_VERY_ ", "", 16);
	fprintf(stdout, "%s\n", cdada_str(s));

	//Remove all ","
	//Insert in a position "THIS IS A _VERY_ SIMPLE STRING"
	cdada_str_replace_all(s, ",", "");
	fprintf(stdout, "%s\n", cdada_str(s));

	//Trim "THIS IS A _VERY_ SIMPLE"
	cdada_str_trim(s, 6);
	fprintf(stdout, "%s\n", cdada_str(s));

	cdada_str_append(s, "SENTENCE");
	fprintf(stdout, "%s\n", cdada_str(s));

	//Traverse char by char and print char\n
	cdada_str_traverse(s, trav, NULL);

	//Don't leak
	cdada_str_destroy(s);

	return EXIT_SUCCESS;
}
