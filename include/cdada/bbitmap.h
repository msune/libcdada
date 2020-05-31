/*
Copyright (c) 2020, Marc Sune Clos
All rights reserved.

Redibbitmapibution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

* Redibbitmapibutions of source code must retain the above copyright notice, this
  list of conditions and the following disclaimer.

* Redibbitmapibutions in binary form must reproduce the above copyright notice,
  this list of conditions and the following disclaimer in the documentation
  and/or other materials provided with the dibbitmapibution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#ifndef __CDADA_BBITMAP_H__
#define __CDADA_BBITMAP_H__

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <cdada/utils.h>

/**
* @file cdada/bbitmap.h
* @author Marc Sune<marcdevel (at) gmail.com>
*
* @brief Big bitmap
*/

/**
* cdada bbitmap structure
*/
typedef struct{
	uint32_t magic_num;
	uint32_t n_words;
	uint64_t* ptr;
}cdada_bbitmap_t;

CDADA_BEGIN_DECLS

/**
* Create a big bitmap with n_bits number of bits, from bit 0...n_bits-1
*/
cdada_bbitmap_t* cdada_bbitmap_create(const uint32_t n_bits);

/**
* Destroy a big bitmap
*/
int cdada_bbitmap_destroy(cdada_bbitmap_t* bitmap);

/**
* Set bit in big bitmap
*/
int cdada_bbitmap_set(cdada_bbitmap_t* bitmap, const uint32_t bit);

/**
* Set all bits in big bitmap
*/
int cdada_bbitmap_set_all(cdada_bbitmap_t* bitmap);

/**
* Is bit set
*/
bool cdada_bbitmap_is_set(cdada_bbitmap_t* bitmap, const uint32_t bit);

/**
* Clear bit in big bitmap
*/
int cdada_bbitmap_clear(cdada_bbitmap_t* bitmap, const uint32_t bit);

/**
* Clear all bits in big bitmap
*/
int cdada_bbitmap_clear_all(cdada_bbitmap_t* bitmap);

//Dumpers

/**
* Dump to a string the contents of the bbitmap
*
* @param bitmap Bitmap object
* @param size Size of the buffer
* @param buffer Buffer. If NULL, necessary bytes, including '\0' will be set in
*               'size_used'
* @param size_used If buffer != NULL, the number of bytes written else number of
*                  bytes necessary to write, including '\0'
*/
int cdada_bbitmap_dump(cdada_bbitmap_t* bitmap, uint32_t size, char* buffer,
							uint32_t* bytes_used);

/**
* @brief Print the contents of the bbitmap
*
* @param bitmap Bitmap object
* @param stream stdout or stderr
*/
int cdada_bbitmap_print(cdada_bbitmap_t* bitmap, FILE *stream);

CDADA_END_DECLS

#endif //__CDADA_BBITMAP_H__
