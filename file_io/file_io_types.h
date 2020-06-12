/*
 * file_io_types.h
 *
 * Created on: 2011-3-3
 * Author: freezezdj
 */

#ifndef FILE_IO_FILE_IO_TYPES_H_
#define FILE_IO_FILE_IO_TYPES_H_

#include "water_types.h"

namespace Water {

enum OpenType {
	kOnlyRead = 0,
	kBinaryRead,
	kOnlyWrite,
	kBinaryWrite,
	kAddwrite,
	kBinaryAddWrite,
	kReadWrite,
	kBinaryReadWrite,
	kZeroReadWrite,
	kBinaryZeroReadWrite,
	kAddReadWrite,
	kBinaryAddReadWrite
};

enum BufferMode {
	kFullBuffer = _IOFBF,
	kLineBuffer = _IOLBF,
	kNoBuffer = _IONBF
};

enum GetCharError {
	kGetCharError = 1,
  kGetCharEof = 2
};

} // namespace Water

#endif // FILE_IO_FILE_IO_TYPES_H_
