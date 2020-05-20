#include <cdada/list_custom_cc.h>
#include <cdada/map_custom_cc.h>

#include "foo.h"
#include "bar.h"

//Autogen C++ comparison operators (once per user type)
CDADA_CUSTOM_GEN_MEMCP_OPERATORS(foo_t);
CDADA_CUSTOM_GEN_MEMCP_OPERATORS(bar_t);

//Autogenerate C++ code for the containers
CDADA_LIST_CUSTOM_GEN(foo_t);
CDADA_MAP_CUSTOM_GEN(bar_t);
