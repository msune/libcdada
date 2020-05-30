/*
Copyright (c) 2020, Marc Sune Clos
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

* Redistributions of source code must retain the above copyright notice, this
  list of conditions and the following disclaimer.

* Redistributions in binary form must reproduce the above copyright notice,
  this list of conditions and the following disclaimer in the documentation
  and/or other materials provided with the distribution.

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

#ifndef __CDADA_STRING_H__
#define __CDADA_STRING_H__

#include <stdbool.h>
#include <stdint.h>
#include <cdada/utils.h>

/**
* @file cdada/str.h
* @author Marc Sune<marcdevel (at) gmail.com>
*
* @brief String data structure. Wraps std::string data structure
*/

/**
* cdada str structure
*/
typedef void cdada_str_t;

CDADA_BEGIN_DECLS

/**
* cdada str structure iterator
*
* @param str String ptr
* @param key Key (immutable)
* @param opaque A pointer to an opaque object tat will be passed to the callback
*/
typedef void (*cdada_str_it)(const cdada_str_t* str, const char it,
								uint32_t pos,
								void* opaque);

/**
* Create a string data structure (in heap)
*/
cdada_str_t* cdada_str_create(const char* str);

/**
* Destroy a str structure
*/
int cdada_str_destroy(cdada_str_t* str);

/**
* Traverse string, char by char
*
* @param str String
* @param func Traverse function for this specific str
* @param opaque User data (opaque ptr)
*/
int cdada_str_traverse(const cdada_str_t* str, cdada_str_it func,
							void* opaque);

/**
* Reverse traverse str, char by char
*
* @param str String
* @param func Traverse function for this specific str
* @param opaque User data (opaque ptr)
*/
int cdada_str_rtraverse(const cdada_str_t* str, cdada_str_it func,
							void* opaque);

//String properties

/**
* Is the str empty string ("")
*/
bool cdada_str_empty(const cdada_str_t* str);

/**
* Return the length, excluding '\0'
*/
uint32_t cdada_str_length(const cdada_str_t* str);

//Access

/**
* Get the C string
*
* @param str String pointer
*/
const char* cdada_str(const cdada_str_t* str);

/**
* Find the first positon of the substring
*
* @param str String pointer
* @param substr Substring to match
* @param pos Position where to substring was found
*/
int cdada_str_find_first(const cdada_str_t* str, const char* substr,
						uint32_t* pos);

/**
* Find the last positon of the substring
*
* @param str String pointer
* @param substr Substring to match
* @param pos Position where to substring was found
*/
int cdada_str_find_last(const cdada_str_t* str, const char* substr,
						uint32_t* pos);

/**
* Get the number of times a substring is found in the str
*
* @param str String pointer
* @param substr Substring to match
* @param n Number of occurrences
*/
int cdada_str_find_count(const cdada_str_t* str, const char* substr,
						uint32_t* n);

/**
* @brief Find all occurrences of substring
*
* This function will return all the occurences of a substring in the str
*
* If the number of occurrances > pos_len, the function will return E_INCOMPLETE
*
* @param str String pointer
* @param substr Substring to match
* @param size Size of the array of occurences
* @param poss Array of positions
* @param cnt Number of find() occurrences
*/
int cdada_str_find_all(const cdada_str_t* str, const char* substr,
						const uint32_t size,
						uint32_t* poss,
						uint32_t* cnt);

/**
* Get the first char in the str
* @param str String pointer
* @param c char
*/
int cdada_str_first_c(const cdada_str_t* str, char* c);

/**
* Get the a char in the str
* @param str String pointer
* @param pos Position of the char
* @param c char
*/
int cdada_str_get_c(const cdada_str_t* str, const uint32_t pos, char* c);

/**
* Get the last char in the str
* @param str String pointer
* @param c char
*/
int cdada_str_last_c(const cdada_str_t* str, char* c);

//Manipulation

/**
* Set the contens of the string
*/
int cdada_str_set(cdada_str_t* str, const char* new_str);

/**
* Clears the contents of the str
*/
static inline int cdada_str_clear(cdada_str_t* str){
	return cdada_str_set(str, "");
}

/**
* Append a substring at the end of the str
*
* @param str String pointer
* @param substr Substring to insert
*/
int cdada_str_append(cdada_str_t* str, const char* substr);

/**
* Trim n characters from the end of the string
*
* @param str String pointer
* @param n Number of characters
*/
int cdada_str_trim(cdada_str_t* str, const uint32_t n);

/**
* Inserts a substring in a specific position of the string
*
* @param str String pointer
* @param pos Position where to inser the substring
* @param substr Substring to insert
*/
int cdada_str_insert(cdada_str_t* str, uint32_t pos, const char* substr);

/**
* Erase a substring starting at position [pos] element in the str
*
* @param str String pointer
* @param pos Position where to insert the substring
* @param substr_len Length of the substr
*/
int cdada_str_erase(cdada_str_t* str, const uint32_t pos,
						const uint32_t substr_len);

/**
* Convert string to all lower case
*
* @param str String pointer
*/
int cdada_str_lower(cdada_str_t* str);

/**
* Convert string to all upper case
*
* @param str String pointer
*/
int cdada_str_upper(cdada_str_t* str);

/**
* Replace all occurences of match with new_str
*
* @param str String pointer
* @param match Match substring
* @param new_str Substring to replace with
*/
int cdada_str_replace_all(cdada_str_t* str, const char* match,
							const char* new_str);

/**
* Replace first occurence of match with new_str, starting at position pos
*
* @param str String pointer
* @param match Match substring
* @param new_str Substring to replace with
* @param pos Start position
*/
int cdada_str_replace(cdada_str_t* str, const char* match, const char* new_str,
							const uint32_t pos);

CDADA_END_DECLS

#endif //__CDADA_STRING_H__
