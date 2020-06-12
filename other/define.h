/*
 * define.h
 *
 *  Created on: 2013-5-20
 *      Author: zdj
 */

#ifndef DEFINE_H_
#define DEFINE_H_

#include<cstdint>

struct iovec {
	void* iov_base;    /* Starting address */
	size_t iov_len;     /* Number of bytes to transfer */
};

typedef int8_t Int8;
typedef uint8_t Uint8;
typedef int16_t Int16;
typedef uint16_t Uint16;
typedef int32_t Int32;
typedef uint32_t Uint32;
typedef int64_t Int64; 
typedef uint64_t Uint64; 

typedef uint8_t Byte;

typedef Uint16 StringLength;

#endif // DEFINE_H_