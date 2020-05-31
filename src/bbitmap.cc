#include "cdada/bbitmap.h"
#include "cdada/__common_internal.h"
#include <stdlib.h>
#include <sstream>

using namespace std;

cdada_bbitmap_t* cdada_bbitmap_create(uint32_t n_bits){

	cdada_bbitmap_t* b;

	if(n_bits == 0)
		return NULL;

	b = (cdada_bbitmap_t*)malloc(sizeof(cdada_bbitmap_t));
	if(!b)
		return NULL;

	b->magic_num = CDADA_MAGIC;
	b->n_words = (n_bits%64 > 0)? (n_bits/64)+1 : n_bits/64;
	b->ptr = (uint64_t*)malloc(b->n_words*8);
	if(!b->ptr){
		free(b);
		return NULL;
	}
	memset(b->ptr, 0, b->n_words*8);

	return b;
}

int cdada_bbitmap_destroy(cdada_bbitmap_t* b){

	CDADA_CHECK_MAGIC(b);

	b->magic_num = 0x0;
	free(b->ptr);
	free(b);

	return CDADA_SUCCESS;
}

int cdada_bbitmap_set(cdada_bbitmap_t* b, const uint32_t bit){

	CDADA_CHECK_MAGIC(b);

	if(bit >= (b->n_words*64))
		return CDADA_E_INVALID;

	b->ptr[bit/64] |= (1ULL << (bit%64));
	return CDADA_SUCCESS;
}

int cdada_bbitmap_set_all(cdada_bbitmap_t* b){
	CDADA_CHECK_MAGIC(b);
	memset(b->ptr, 0xFF, b->n_words*8);
	return CDADA_SUCCESS;
}

bool cdada_bbitmap_is_set(cdada_bbitmap_t* b, const uint32_t bit){

	CDADA_CHECK_MAGIC(b);

	if(bit >= (b->n_words*64))
		return false;

	return (b->ptr[bit/64] & (1ULL << (bit%64))) > 0ULL;
}

int cdada_bbitmap_clear(cdada_bbitmap_t* b, const uint32_t bit){

	CDADA_CHECK_MAGIC(b);

	if(bit >= (b->n_words*64))
		return CDADA_E_INVALID;

	b->ptr[bit/64] &= ~(1ULL << (bit%64));

	return CDADA_SUCCESS;
}

int cdada_bbitmap_clear_all(cdada_bbitmap_t* b){
	CDADA_CHECK_MAGIC(b);
	memset(b->ptr, 0x0, b->n_words*8);
	return CDADA_SUCCESS;
}

static inline void __cdada_bbitmap_dump_word(uint32_t word_index,
							uint64_t* word,
							stringstream& ss){
	uint8_t i;
	bool set;
	char c;

	for(i=0;i<64; ++i){
		set = (1ULL<<i) & *word;
		c = set? 'S' : '.';
		ss << c;
	}
	ss <<" " << word_index*64 << "-" << (word_index+1)*64 - 1 << std::endl;
}

int cdada_bbitmap_dump(cdada_bbitmap_t* b, uint32_t size, char* buffer,
							uint32_t* size_used){
	uint32_t i;

	CDADA_CHECK_MAGIC(b);

	if(!size_used || (buffer&&size ==0))
		return CDADA_E_INVALID;

	try{
		std::stringstream ss;
		for(i=0;i<b->n_words; ++i)
			__cdada_bbitmap_dump_word(i, &b->ptr[i], ss);

		if(!buffer){
			*size_used = ss.str().length()+1;
			return CDADA_SUCCESS;
		}

		snprintf(buffer, size, "%s", ss.str().c_str());
		if(ss.str().length()+1 > size)
			return CDADA_E_INCOMPLETE;
	}catch(bad_alloc& e){
		return CDADA_E_MEM;
	}catch(...){
		CDADA_ASSERT(0);
		return CDADA_E_UNKNOWN;
	}

	return CDADA_SUCCESS;
}

int cdada_bbitmap_print(cdada_bbitmap_t* b, FILE *stream){
	uint32_t i;

	CDADA_CHECK_MAGIC(b);

	try{
		std::stringstream ss;
		for(i=0;i<b->n_words; ++i)
			__cdada_bbitmap_dump_word(i, &b->ptr[i], ss);
		fprintf(stream, "%s", ss.str().c_str());
	}catch(bad_alloc& e){
		return CDADA_E_MEM;
	}catch(...){
		CDADA_ASSERT(0);
		return CDADA_E_UNKNOWN;
	}

	return CDADA_SUCCESS;
}
