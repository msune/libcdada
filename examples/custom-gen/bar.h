#ifndef BAR_H
#define BAR_H

#include <stdint.h>

//69byte type
typedef struct{
	uint16_t aa;
	float bb;
	uint8_t unaligned;
} __attribute__((packed)) bar_t; //MUST BE PACKED

#endif //BAR_H
