#include <algorithm>
#include "log.h"

template<typename T>
size_t IntToString(char* buffer, T value) {
	T i = value;
	char* p = buffer;
	do {
		int remainder = static_cast<int>(i % 10);
		i /= 10;
		*p++ = "0123456789"[remainder];
	} while (i != 0);
	if (value < 0) *p++ = '-';
	*p = '\0';
	std::reverse(buffer, p);
	return p - buffer;
}

size_t HexIntToString(char* buffer, uintptr_t value) {
	uintptr_t i = value;
	char* p = buffer;
	do {
		int remainder = i % 16;
		i /= 16;
		*p++ = "0123456789ABCDEF"[remainder];
	} while (i != 0);
	*p = '\0';
	std::reverse(buffer, p);
	return p - buffer;
}

Buffer Log::buffer_;

Log::Log(Level level)
    : stream_(&stream_buffer_)
    , level_(level) {
}

Log::~Log() {
  stream_ << endl;
  buffer_.Splice(stream_.buffer());
}