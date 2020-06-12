/*
 * file_io-inl.h
 *
 *Created on: 2011-3-8
 *Author: freezezdj
 */

#ifndef FILE_IO_FILE_IO_INL_H_
#define FILE_IO_FILE_IO_INL_H_

namespace Water {

inline int FileIO::SetBuffer(BufferMode buffer_mode,
                             char* buffer,
                             size_t buffer_size) {
  return setvbuf(file_point_, buffer, buffer_mode, buffer_size);
}

inline int FileIO::SetLineBuffer(char* buffer, size_t buffer_size) {
  return setvbuf(file_point_, buffer, kLineBuffer, buffer_size);
}

inline int FileIO::SetFullBuffer(char* buffer, size_t buffer_size) {
  return setvbuf(file_point_, buffer, kFullBuffer, buffer_size);
}

inline int FileIO::SetNoBuffer() {
  return setvbuf(file_point_, NULL, kNoBuffer, 0);
}

inline int FileIO::FlushBuffer() {
  return fflush(file_point_);
}

inline size_t FileIO::BinaryRead(char* buffer,
                                 size_t object_size,
                                 size_t object_count) {
  return fread(buffer, object_size, object_count, file_point_);
}

inline size_t FileIO::BinaryWrite(const char* buffer,
                                  size_t object_size,
                                  size_t object_count) {
  return fwrite(buffer, object_size, object_count, file_point_);
}

inline off_t FileIO::GetPosition() {
  return ftell(file_point_);
}

inline int FileIO::SetPosition(off_t position) {
  return fseeko(file_point_, position, SEEK_SET);
}

inline int FileIO::OffsetPosition(off_t position) {
  return fseeko(file_point_, position, SEEK_CUR);
}

inline void FileIO::SetPositionToBegin() {
  return rewind(file_point_);
}

inline int FileIO::SetPositionToEnd() {
  return fseeko(file_point_, 0, SEEK_END);
}

inline void FileIO::Close() {
  fclose(file_point_);
}

inline int FileIO::GetChar() {
  return fgetc(file_point_);
}

inline GetCharError FileIO::GetCharErrorType() {
  if (feof(file_point_)) {
    return kGetCharEof;
  } else {
    return kGetCharError;
  }
}

inline int FileIO::PutCharToStream(char value) {
  return ungetc(value, file_point_);
}

inline int FileIO::PutLine(const string& value) {
  return fputs(value.c_str(), file_point_);
}

inline size_t FileIO::PutString(const string& value) {
  return BinaryWrite(value.c_str(), sizeof(char), value.size());
}

inline int FileIO::PutChar(char value) {
  return fputc(value, file_point_);
}

inline int FileIO::GetFileDescriptor() {
  return fileno(file_point_);
}

} // namespace Water

#endif // FILE_IO_FILE_IO_INL_H_
