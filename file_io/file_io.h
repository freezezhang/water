/*
 * file_io.h
 *
 * Created on: 2011-3-3
 * Author: freezezdj
 */

#ifndef FILE_IO_FILE_IO_H_
#define FILE_IO_FILE_IO_H_

#include <cstdio>
#include <string>
using std::string;

#include "file_io/file_io_types.h"
#include "file_io/file_io_exception.h"

#include "file_system/path.h"

using Water::Path;

namespace Water {

// TODO: FileIO 未测试

class FileIO {
public:
  FileIO(const Path& path, OpenType open_type) throw (BadOpenFile);
  FileIO(const Path& path, const char* open_type) throw (BadOpenFile);
  virtual ~FileIO();

public:
  int ReOpen(const Path& path, OpenType open_type);
  int ReOpen(const Path& path, const char* open_type);

  // 注意，如果使用自己提供的buffer，就必须提供对应的buffer_size，不要使用默认值
  inline int SetBuffer(BufferMode buffer_mode,
                       char* buffer = NULL,
                       size_t buffer_size = kBufferSize);

  inline int SetLineBuffer(char* buffer = NULL,
                           size_t buffer_size = kBufferSize);

  inline int SetFullBuffer(char* buffer = NULL,
                           size_t buffer_size = kBufferSize);
  inline int SetNoBuffer();

  inline int FlushBuffer();

  inline size_t BinaryRead(char* buffer,
                           size_t object_size,
                           size_t object_count);

  inline size_t BinaryWrite(const char* buffer,
                            size_t object_size,
                            size_t object_count);

  inline off_t GetPosition();

  inline int SetPosition(off_t position);

  inline int OffsetPosition(off_t position);

  inline void SetPositionToBegin();
  inline int SetPositionToEnd();

  off_t GetFileSize();

  inline void Close();

  string GetLine();

  // 如果value > kBufferSize，则只可以取得kBufferSize大小的string。
  string GetString(size_t value);

  // if GetChar 返回-1，且需要明白得到-1原因，请继续调用GetCharErrorType();
  inline int GetChar();
  inline GetCharError GetCharErrorType();

  inline int PutLine(const string& value);

  inline size_t PutString(const string& value);

  // 成功返回value，失败返回EOF
  inline int PutChar(char value);

  inline int PutCharToStream(char value);

  /* 未实现
   int8 GetInt8();
   int16 GetInt16();
   int32 GetInt16();
   int64 GetInt64();

   uint8 GetInt8();
   uint16 GetInt16();
   uint32 GetInt16();
   uint64 GetInt64();

   float GetFloat();
   double GetDouble();

   void PutInt8(int8 value);
   void PutInt16(int16 value);
   void PutInt16(int32 value);
   void PutInt64(int64 value);

   void PutInt8(uint8 value);
   void PutInt16(uint16 value);
   void PutInt16(uint32 value);
   void PutInt64(uint64 value);

   void PutFloat(float value);
   void PutDouble(double value);
   */

  int GetFileDescriptor();

private:
  FileIO(const FileIO& other);
  FileIO& operator=(const FileIO& other);

private:
  string OpenTypeToCString(enum OpenType);

private:
  FILE* file_point_;
};

} // namespace Water

#include "file_io-inl.h"

#endif // FILE_IO_FILE_IO_H_
