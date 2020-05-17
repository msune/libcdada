#ifndef TEST_COMMON_H
#define TEST_COMMON_H

#include <assert.h>

#ifndef DEBUG
#define TEST_ASSERT( exp ) \
	if( ! (exp) ) abort()
#else
#define TEST_ASSERT( exp ) assert(exp)
#endif //DEBUG

#endif //TEST_COMMON_H
