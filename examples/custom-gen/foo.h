#ifndef FOO_H
#define FOO_H

#include <stdint.h>

//69byte type
typedef struct{
	uint64_t aa;
	uint64_t bb;
	uint8_t big[3000];
} __attribute__((packed)) foo_t; //MUST BE PACKED

#endif //FOO_H
