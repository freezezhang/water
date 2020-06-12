/*
 * water_types.h
 *
 * Created on: 2011-2-24
 * Author: freezezdj
 */

#ifndef WATER_TYPES_H_
#define WATER_TYPES_H_

#include <sys/types.h>
#include <limits.h>
#include <cstdio>

namespace Water {

typedef __int64_t int64;
typedef __int32_t int32;
typedef __int16_t int16;
typedef __int8_t int8;

typedef __uint64_t u_int64;
typedef __uint32_t u_int32;
typedef __uint16_t u_int16;
typedef __uint8_t u_int8;

const size_t kBufferSize = BUFSIZ;
const size_t kLineMax = kBufferSize;

}	// namespace Water

#endif // WATER_TYPES_H_
