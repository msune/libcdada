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

#ifndef __CDADA_UTILS_H__
#define __CDADA_UTILS_H__

/**
* @file cdada_utils.h
* @author Marc Sune<marcdevel (at) gmail.com>
*
* @brief Several misc. utilities
*/

//Eror codes
#define CDADA_SUCCESS       0
#define CDADA_E_UNKNOWN     1
#define CDADA_E_INVALID     2
#define CDADA_E_NOT_FOUND   3
#define CDADA_E_EXISTS      4
#define CDADA_E_MEM         5
#define CDADA_E_UNSUPPORTED 6
#define CDADA_E_EMPTY       7
#define CDADA_E_INCOMPLETE  8
#define CDADA_E_FULL        9
#define CDADA_E_COUNT       10

#ifdef __cplusplus
	# define CDADA_BEGIN_DECLS extern "C" {
	# define CDADA_END_DECLS   }
#else
	# define CDADA_BEGIN_DECLS
	# define CDADA_END_DECLS
#endif //__cplusplus

CDADA_BEGIN_DECLS

/**
* Get a human-readable description for CDADA errors
*/
const char* cdada_strerr(int error);

CDADA_END_DECLS

#endif //__CDADA_UTILS_H__
