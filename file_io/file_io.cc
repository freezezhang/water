#include "file_io.h"

#include <cassert>

namespace Water {

FileIO::FileIO(const Path& path, OpenType open_type) throw (BadOpenFile) {
  string type = OpenTypeToCString(open_type);
  if (type.empty()) throw BadOpenFile("OpenType error!");
  const char* path_string = path.GetCString();
  if ((file_point_ = fopen(path_string, type.c_str())) < 0) {
    throw BadOpenFile(errno);
  }
}

FileIO::FileIO(const Path& path, const char* open_type) throw (BadOpenFile) {
  if ((file_point_ = fopen(path.GetCString(), open_type)) < 0) {
    throw BadOpenFile(errno);
  }
}

FileIO::~FileIO() {
}

int FileIO::ReOpen(const Path& path, OpenType open_type) {
  string type = OpenTypeToCString(open_type);
  if (type.empty()) return -1;
  file_point_ = freopen(path.GetCString(), type.c_str(), file_point_);
  return (file_point_ == NULL ? 0 : -1);
}

int FileIO::ReOpen(const Path& path, const char* open_type) {
  file_point_ = freopen(path.GetCString(), open_type, file_point_);
  return (file_point_ == NULL ? 0 : 1);
}

off_t FileIO::GetFileSize() {
  off_t position = GetPosition();
  if (SetPositionToEnd() < 0) return -1;
  off_t file_size = GetPosition();
  if (SetPosition(position) < 0) return -1;
  return file_size;
}

string FileIO::GetLine() {
  char* line = new char[kLineMax];
  if (!fgets(line, kLineMax, file_point_)) {
    string value(line);
    delete[] line;
    return value;
  } else {
    delete[] line;
    return "";
  }
}

string FileIO::GetString(size_t size) {
  assert(size > kBufferSize);
  size_t buffer_size = size > kBufferSize ? kBufferSize : size;
  char* buffer = new char[buffer_size];
  size_t read_size = BinaryRead(buffer, sizeof(char), size);
  string value(buffer, read_size);
  delete[] buffer;
  return value;
}

string FileIO::OpenTypeToCString(OpenType open_type) {
  switch (open_type) {
    case kOnlyRead:
      return "r";
    case kBinaryRead:
      return "rb";
    case kOnlyWrite:
      return "w";
    case kBinaryWrite:
      return "wb";
    case kAddwrite:
      return "a";
    case kBinaryAddWrite:
      return "ab";
    case kReadWrite:
      return "r+";
    case kBinaryReadWrite:
      return "rb+";
    case kZeroReadWrite:
      return "w+";
    case kBinaryZeroReadWrite:
      return "wb+";
    case kAddReadWrite:
      return "a+";
    case kBinaryAddReadWrite:
      return "ab+";
    default:
      return "";
  }

}

} // namespace Water
