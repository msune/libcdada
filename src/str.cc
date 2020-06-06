#include "cdada/str.h"
#include "cdada/__str_internal.h"

#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <algorithm>

using namespace std;

cdada_str_t* cdada_str_create(const char* str){

	__cdada_str_int_t* m = NULL;

	m = (__cdada_str_int_t*)malloc(sizeof(__cdada_str_int_t));
	if(!m)
		return NULL;

	try{
		m->magic_num = CDADA_MAGIC;
		m->str = new std::string(str);
	}catch(bad_alloc& e){
		free(m);
		return NULL;
	}catch(...){
		CDADA_ASSERT(0);
		return NULL;
	}

	return m;
}

int cdada_str_destroy(cdada_str_t* str){

	__cdada_str_int_t* m = (__cdada_str_int_t*)str;

	CDADA_CHECK_MAGIC(m);

	m->magic_num = 0x0;
	try{
		delete m->str;
	}catch(...){
		CDADA_ASSERT(0);
		return CDADA_E_UNKNOWN;
	}

	free(m);

	return CDADA_SUCCESS;
}

//Access

int cdada_str_traverse(const cdada_str_t* str, cdada_str_it func,
							void* opaque){
	__cdada_str_int_t* m = (__cdada_str_int_t*)str;

	CDADA_CHECK_MAGIC(m);

	if(!func)
		return CDADA_E_INVALID;

	std::string& s = *m->str;

	try{
		std::string::const_iterator it;
		uint32_t pos = 0;
		for(it = s.begin(); it != s.end(); ++it){
			(*func)(str, *it, pos, opaque);
			++pos;
		}
	}catch(...){
		CDADA_ASSERT(0);
		return CDADA_E_UNKNOWN;
	}

	return CDADA_SUCCESS;
}

int cdada_str_rtraverse(const cdada_str_t* str, cdada_str_it func,
							void* opaque){
	__cdada_str_int_t* m = (__cdada_str_int_t*)str;

	CDADA_CHECK_MAGIC(m);

	if(!func)
		return CDADA_E_INVALID;

	std::string& s = *m->str;

	try{
		std::string::const_reverse_iterator it;
		uint32_t pos = s.length()-1;
		for(it = s.rbegin(); it != s.rend(); ++it){
			(*func)(str, *it, pos, opaque);
			--pos;
		}
	}catch(...){
		CDADA_ASSERT(0);
		return CDADA_E_UNKNOWN;
	}

	return CDADA_SUCCESS;
}

bool cdada_str_empty(const cdada_str_t* str){

	__cdada_str_int_t* m = (__cdada_str_int_t*)str;

	if(!m || m->magic_num != CDADA_MAGIC)
		return false;

	try{
		return m->str->empty();
	}catch(...){
		CDADA_ASSERT(0);
	}

	return false;
}

uint32_t cdada_str_length(const cdada_str_t* str){

	__cdada_str_int_t* m = (__cdada_str_int_t*)str;

	if(!m || m->magic_num != CDADA_MAGIC)
		return 0;

	try{
		return m->str->length();
	}catch(...){
		CDADA_ASSERT(0);
	}

	return 0;
}

const char* cdada_str(const cdada_str_t* str){

	__cdada_str_int_t* m = (__cdada_str_int_t*)str;

	if(!m || m->magic_num != CDADA_MAGIC)
		return "";

	try{
		return m->str->c_str();
	}catch(...){
		CDADA_ASSERT(0);
	}

	return "";
}

int __cdada_str_find(const cdada_str_t* str, const char* substr, uint32_t* pos,
								bool first){
	__cdada_str_int_t* m = (__cdada_str_int_t*)str;

	CDADA_CHECK_MAGIC(m);

	if(!substr || !pos)
		return CDADA_E_INVALID;

	std::string& s = *m->str;

	if(s.length() == 0)
		return CDADA_E_NOT_FOUND;

	try{
		size_t p;

		if(first)
			p = s.find(substr);
		else
			p = s.rfind(substr);

		if(p == std::string::npos)
			return CDADA_E_NOT_FOUND;

		*pos = p;
	}catch(...){
		CDADA_ASSERT(0);
		return CDADA_E_UNKNOWN;
	}

	return CDADA_SUCCESS;
}

int cdada_str_find_first(const cdada_str_t* str, const char* substr,
						uint32_t* pos){
	return __cdada_str_find(str, substr, pos, true);
}

int cdada_str_find_last(const cdada_str_t* str, const char* substr,
						uint32_t* pos){
	return __cdada_str_find(str, substr, pos, false);
}

int cdada_str_find_count(const cdada_str_t* str, const char* substr,
						uint32_t* n){
	__cdada_str_int_t* m = (__cdada_str_int_t*)str;

	CDADA_CHECK_MAGIC(m);

	if(!substr || !n)
		return CDADA_E_INVALID;

	std::string& s = *m->str;

	try{
		size_t p, p_last;
		uint32_t& count = *n;

		count = 0;
		p_last = 0;

		while(true){
			p = s.find(substr, p_last);

			if(p == std::string::npos)
				break;

			p_last = p+1;
			++count;
		}
	}catch(...){
		CDADA_ASSERT(0);
		return CDADA_E_UNKNOWN;
	}

	return CDADA_SUCCESS;
}

int cdada_str_find_all(const cdada_str_t* str, const char* substr,
						const uint32_t size,
						uint32_t* poss,
						uint32_t* cnt){
	__cdada_str_int_t* m = (__cdada_str_int_t*)str;

	CDADA_CHECK_MAGIC(m);

	if(!substr || !poss || !size || !cnt)
		return CDADA_E_INVALID;

	std::string& s = *m->str;

	try{
		size_t p = 0;
		*cnt = 0;

		while(true){
			p = s.find(substr, p);
			if(p == std::string::npos)
				break;

			if((*cnt) == size)
				return CDADA_E_INCOMPLETE;

			poss[(*cnt)++] = p;
			p++;
		}
	}catch(...){
		CDADA_ASSERT(0);
		return CDADA_E_UNKNOWN;
	}

	return CDADA_SUCCESS;
}

int cdada_str_first_c(const cdada_str_t* str, char* c){

	__cdada_str_int_t* m = (__cdada_str_int_t*)str;

	CDADA_CHECK_MAGIC(m);

	if(!c)
		return CDADA_E_INVALID;

	std::string& s = *m->str;

	if(s.length() == 0)
		return CDADA_E_EMPTY;

	try{
		*c = *s.begin();
	}catch(...){
		CDADA_ASSERT(0);
		return CDADA_E_UNKNOWN;
	}

	return CDADA_SUCCESS;
}

int cdada_str_get_c(const cdada_str_t* str, const uint32_t pos, char* c){

	__cdada_str_int_t* m = (__cdada_str_int_t*)str;

	CDADA_CHECK_MAGIC(m);

	if(!c)
		return CDADA_E_INVALID;

	std::string& s = *m->str;

	if(s.length() == 0)
		return CDADA_E_EMPTY;

	if(pos >= s.length())
		return CDADA_E_INVALID;

	try{
		*c = s[pos];
	}catch(...){
		CDADA_ASSERT(0);
		return CDADA_E_UNKNOWN;
	}

	return CDADA_SUCCESS;
}

int cdada_str_last_c(const cdada_str_t* str, char* c){

	__cdada_str_int_t* m = (__cdada_str_int_t*)str;

	CDADA_CHECK_MAGIC(m);

	if(!c)
		return CDADA_E_INVALID;

	std::string& s = *m->str;

	if(s.length() == 0)
		return CDADA_E_EMPTY;

	try{
		*c = *s.rbegin();
	}catch(...){
		CDADA_ASSERT(0);
		return CDADA_E_UNKNOWN;
	}

	return CDADA_SUCCESS;
}

//Manipulation

int cdada_str_set(cdada_str_t* str, const char* substr){

	__cdada_str_int_t* m = (__cdada_str_int_t*)str;

	CDADA_CHECK_MAGIC(m);

	if(!substr)
		return CDADA_E_INVALID;

	std::string& s = *m->str;

	try{
		s = substr;
	}catch(bad_alloc& e){
		return CDADA_E_MEM;
	}catch(...){
		CDADA_ASSERT(0);
		return CDADA_E_UNKNOWN;
	}

	return CDADA_SUCCESS;
}

int cdada_str_append(cdada_str_t* str, const char* substr){

	__cdada_str_int_t* m = (__cdada_str_int_t*)str;

	CDADA_CHECK_MAGIC(m);

	if(!substr)
		return CDADA_E_INVALID;

	std::string& s = *m->str;

	try{
		s.append(substr);
	}catch(bad_alloc& e){
		return CDADA_E_MEM;
	}catch(...){
		CDADA_ASSERT(0);
		return CDADA_E_UNKNOWN;
	}

	return CDADA_SUCCESS;
}

int cdada_str_trim(cdada_str_t* str, const uint32_t n){

	__cdada_str_int_t* m = (__cdada_str_int_t*)str;

	CDADA_CHECK_MAGIC(m);

	if(!n)
		return CDADA_SUCCESS;

	std::string& s = *m->str;

	if(s.length() < n)
		return CDADA_E_INVALID;

	try{
		s.resize(s.length() - n);
	}catch(bad_alloc& e){
		return CDADA_E_MEM;
	}catch(...){
		CDADA_ASSERT(0);
		return CDADA_E_UNKNOWN;
	}

	return CDADA_SUCCESS;
}

int cdada_str_insert(cdada_str_t* str, uint32_t pos, const char* substr){

	__cdada_str_int_t* m = (__cdada_str_int_t*)str;

	CDADA_CHECK_MAGIC(m);

	if(!substr)
		return CDADA_E_INVALID;

	std::string& s = *m->str;

	if(pos > s.length())
		return CDADA_E_INVALID;

	try{
		s.insert(pos, substr);
	}catch(bad_alloc& e){
		return CDADA_E_MEM;
	}catch(...){
		CDADA_ASSERT(0);
		return CDADA_E_UNKNOWN;
	}

	return CDADA_SUCCESS;
}

int cdada_str_erase(cdada_str_t* str, const uint32_t pos,
						const uint32_t substr_len){

	__cdada_str_int_t* m = (__cdada_str_int_t*)str;

	CDADA_CHECK_MAGIC(m);

	if(!substr_len)
		return CDADA_SUCCESS;

	std::string& s = *m->str;

	if(pos > s.length() || (pos+substr_len) > s.length() )
		return CDADA_E_INVALID;

	try{
		s.erase(pos, substr_len);
	}catch(bad_alloc& e){
		return CDADA_E_MEM;
	}catch(...){
		CDADA_ASSERT(0);
		return CDADA_E_UNKNOWN;
	}

	return CDADA_SUCCESS;
}

int __cdada_str_lower_upper(cdada_str_t* str, bool lower){

	__cdada_str_int_t* m = (__cdada_str_int_t*)str;

	CDADA_CHECK_MAGIC(m);

	std::string& s = *m->str;

	try{
		if(lower)
			std::transform(s.begin(), s.end(), s.begin(),
								::tolower);
		else
			std::transform(s.begin(), s.end(), s.begin(),
								::toupper);
	}catch(bad_alloc& e){
		return CDADA_E_MEM;
	}catch(...){
		CDADA_ASSERT(0);
		return CDADA_E_UNKNOWN;
	}

	return CDADA_SUCCESS;
}

int cdada_str_lower(cdada_str_t* str){
	return __cdada_str_lower_upper(str, true);
}

int cdada_str_upper(cdada_str_t* str){
	return __cdada_str_lower_upper(str, false);
}

int cdada_str_replace_all(cdada_str_t* str, const char* match,
							const char* new_str){

	__cdada_str_int_t* m = (__cdada_str_int_t*)str;

	CDADA_CHECK_MAGIC(m);

	if(!match || !new_str)
		return CDADA_E_INVALID;

	std::string& s = *m->str;

	try{
		size_t pos = s.find(match);
		size_t l = strlen(match);

		while(pos != string::npos){
			s.replace(pos, l, new_str);
			pos += l;
			pos = s.find(match, pos);
		}
	}catch(bad_alloc& e){
		return CDADA_E_MEM;
	}catch(...){
		CDADA_ASSERT(0);
		return CDADA_E_UNKNOWN;
	}

	return CDADA_SUCCESS;
}

int cdada_str_replace(cdada_str_t* str, const char* match, const char* new_str,
							const uint32_t pos){

	__cdada_str_int_t* m = (__cdada_str_int_t*)str;

	CDADA_CHECK_MAGIC(m);

	if(!match || !new_str)
		return CDADA_E_INVALID;

	std::string& s = *m->str;
	size_t l = strlen(match);

	if(pos+l > s.length())
		return CDADA_E_INVALID;

	try{
		std::size_t it;
		it = s.find(match, pos);
		if(it != std::string::npos)
			s.replace(it, l, new_str);
	}catch(bad_alloc& e){
		return CDADA_E_MEM;
	}catch(...){
		CDADA_ASSERT(0);
		return CDADA_E_UNKNOWN;
	}

	return CDADA_SUCCESS;
}
