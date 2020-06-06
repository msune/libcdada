#include "cdada/utils.h"

static const char* cdada_err_str[CDADA_E_COUNT] = {
	"Success",
	"Unknown error",
	"Invalid input",
	"Not found",
	"Element exists",
	"Out of memory",
	"Feature unsupported",
	"Empty",
	"Incomplete"
};

const char* cdada_strerr(int err){
	return err >= CDADA_E_COUNT? "Invalid code" : cdada_err_str[err];
}
