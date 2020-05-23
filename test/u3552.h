#ifndef U3552_H
#define U3552_H

#include <stdint.h>

//444byte type
typedef struct{
	//Keep upper part common with u552
	uint8_t front[38];
	uint32_t mid;
	//Keep upper part common with u552

	uint8_t back[402];
} __attribute__((packed)) test_u3552_t;

#endif //U3552_H
