#include "cdada/utils.h"
#include "cdada/version.h"

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

const char* cdada_get_ver(){
	return CDADA_VERSION;
}

const char* cdada_get_ver_maj(){
	return CDADA_VERSION_MAJOR;
}

const char* cdada_get_ver_min(){
	return CDADA_VERSION_MINOR;
}

const char* cdada_get_ver_patch(){
	return CDADA_VERSION_PATCH;
}

const char* cdada_get_build(){
	return CDADA_BUILD;
}
