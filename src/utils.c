#include "cdata/utils.h"

static const char* cdata_err_str[CDATA_E_COUNT] = {
	"Success",
	"Unknown error",
	"Invalid input",
	"Not found",
	"Element exists",
	"Out of memory",
	"Feature unsupported"
};

const char* cdata_strerr(int err){
	return err >= CDATA_E_COUNT? "Invalid code" : cdata_err_str[err];
}
