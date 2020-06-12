#include "stream.h"
#include <cassert> 

EndLine endl;

BinaryStream::BinaryStream(Buffer* buffer) {
  buffer_ = buffer;
  assert(buffer_);
}

BinaryStream::~BinaryStream() {
}

void BinaryStream::ReadBool(bool* value) {
  buffer_->Read(value, sizeof(bool));
}

void BinaryStream::ReadInt8(Int8* value) {
  buffer_->Read(value, sizeof(Int8));
}

void BinaryStream::ReadUint8(Uint8* value) {
  buffer_->Read(value, sizeof(Uint8));
}

void BinaryStream::ReadInt16(Int16* value) {
  buffer_->Read(value, sizeof(Int16));
}

void BinaryStream::ReadUint16(Uint16* value) {
  buffer_->Read(value, sizeof(Uint16));
}

void BinaryStream::ReadInt32(Int32* value) {
  buffer_->Read(value, sizeof(Int32));
}

void BinaryStream::ReadUint32(Uint32* value) {
  buffer_->Read(value, sizeof(Uint32));
}

void BinaryStream::ReadInt64(Int64* value) {
  buffer_->Read(value, sizeof(Int64));
}

void BinaryStream::ReadUint64(Uint64* value) {
  buffer_->Read(value, sizeof(Uint64));
}

void BinaryStream::ReadFloat(float* value) {
  buffer_->Read(value, sizeof(float));
}

void BinaryStream::ReadDouble(double* value) {
  buffer_->Read(value, sizeof(double));
}

StringLength BinaryStream::ReadString(char* value, StringLength count) {
  StringLength length;
  buffer_->Read(&length, sizeof(length));
  StringLength string_length = length < count - 1 ? length : count - 1;
  size_t read_count = buffer_->Read(value, string_length);
  value[read_count] = '\0';
  return read_count;
}

void BinaryStream::ReadString(BufferString* value) {
  StringLength length;
  buffer_->Read(&length, sizeof(length));
  value->Reserve(length + 1);
  size_t read_count = buffer_->Read(value->Buffer(), length);
  value->SetLength(read_count);
}

void BinaryStream::ReadString(std::string* value) {
  BufferString buffer_string;
  ReadString(&buffer_string);
  value->clear();
  value->append(buffer_string.String());
}

void BinaryStream::WriteBool(bool value) {
  buffer_->Write(&value, sizeof(bool));
}

void BinaryStream::WriteInt8(Int8 value) {
  buffer_->Write(&value, sizeof(Int8));
}

void BinaryStream::WriteUint8(Uint8 value) {
  buffer_->Write(&value, sizeof(Uint8));
}

void BinaryStream::WriteInt16(Int16 value) {
  buffer_->Write(&value, sizeof(Int16));
}

void BinaryStream::WriteUint16(Uint16 value) {
  buffer_->Write(&value, sizeof(Uint16));
}

void BinaryStream::WriteInt32(Int32 value) {
  buffer_->Write(&value, sizeof(Int32));
}

void BinaryStream::WriteUint32(Uint32 value) {
  buffer_->Write(&value, sizeof(Uint32));
}

void BinaryStream::WriteInt64(Int64 value) {
  buffer_->Write(&value, sizeof(Int64));
}

void BinaryStream::WriteUint64(Uint64 value) {
  buffer_->Write(&value, sizeof(Uint64));
}

void BinaryStream::WriteFloat(float value) {
  buffer_->Write(&value, sizeof(float));
}

void BinaryStream::WriteDouble(double value) {
  buffer_->Write(&value, sizeof(double));
}

void BinaryStream::WriteString(const char* value) {
  StringLength length = strlen(value);
  buffer_->Write(&length, sizeof(length));
  buffer_->Write(value, length);
}

void BinaryStream::WriteString(const std::string& value) {
  WriteString(value.c_str());
}

void BinaryStream::WriteString(const BufferString& value) {
  WriteString(value.String());
}
BinaryStream& BinaryStream::operator<<(bool value) {
  WriteBool(value);
  return *this;
}

BinaryStream& BinaryStream::operator<<(Int8 value) {
  WriteInt8(value);
  return *this;
}

BinaryStream& BinaryStream::operator<<(Uint8 value) {
  WriteUint8(value);
  return *this;
}

BinaryStream& BinaryStream::operator<<(Int16 value) {
  WriteInt16(value);
  return *this;
}

BinaryStream& BinaryStream::operator<<(Uint16 value) {
  WriteUint16(value);
  return *this;
}

BinaryStream& BinaryStream::operator<<(Int32 value) {
  WriteInt32(value);
  return *this;
}

BinaryStream& BinaryStream::operator<<(Uint32 value) {
  WriteUint32(value);
  return *this;
}

BinaryStream& BinaryStream::operator<<(Int64 value) {
  WriteInt64(value);
  return *this;
}

BinaryStream& BinaryStream::operator<<(Uint64 value) {
  WriteUint64(value);
  return *this;
}

BinaryStream& BinaryStream::operator<<(float value) {
  WriteFloat(value);
  return *this;
}

BinaryStream& BinaryStream::operator<<(double value) {
  WriteDouble(value);
  return *this;
}

BinaryStream& BinaryStream::operator<<(const char* value) {
  WriteString(value);
  return *this;
}

BinaryStream& BinaryStream::operator<<(const std::string& value) {
  WriteString(value);
  return *this;
}

BinaryStream& BinaryStream::operator<<(const BufferString& value) {
  WriteString(value);
  return *this;
}

BinaryStream& BinaryStream::operator>>(bool& value) {
  ReadBool(&value);
  return *this;
}

BinaryStream& BinaryStream::operator>>(Int8& value){
  ReadInt8(&value);
  return *this;
}

BinaryStream& BinaryStream::operator>>(Uint8& value) {
  ReadUint8(&value);
  return *this;
}

BinaryStream& BinaryStream::operator>>(Int16& value) {
  ReadInt16(&value);
  return *this;
}

BinaryStream& BinaryStream::operator>>(Uint16& value) {
  ReadUint16(&value);
  return *this;
}

BinaryStream& BinaryStream::operator>>(Int32& value) {
  ReadInt32(&value);
  return *this;
}

BinaryStream& BinaryStream::operator>>(Uint32& value) {
  ReadUint32(&value);
  return *this;
}

BinaryStream& BinaryStream::operator>>(Int64& value) {
  ReadInt64(&value);
  return *this;
}

BinaryStream& BinaryStream::operator>>(Uint64& value) {
  ReadUint64(&value);
  return *this;
}

BinaryStream& BinaryStream::operator>>(float& value) {
  ReadFloat(&value);
  return *this;
}

BinaryStream& BinaryStream::operator>>(double& value) {
  ReadDouble(&value);
  return *this;
}

BinaryStream& BinaryStream::operator>>(std::string& value) {
  ReadString(&value);
  return *this;
}

BinaryStream& BinaryStream::operator>>(BufferString& value) {
  ReadString(&value);
  return *this;
}

StringStream::StringStream(Buffer* buffer) {
  buffer_ = buffer;
  assert(buffer_);
}

StringStream::~StringStream() {
}

StringStream& StringStream::operator<<(bool value) {
  if (value) {
    buffer_->Write("true", strlen("true"));
  } else {
    buffer_->Write("false", strlen("false"));
  }
  return *this;
}

StringStream& StringStream::operator<<(Int8 value) {
  *this << static_cast<Int32>(value);
  return *this;
}

StringStream& StringStream::operator<<(Uint8 value) {
  *this << static_cast<Int32>(value);
  return *this;
}

StringStream& StringStream::operator<<(Int16 value) {
  *this << static_cast<Int32>(value);
  return *this;
}

StringStream& StringStream::operator<<(Uint16 value) {
  *this << static_cast<Int32>(value);
  return *this;
}

StringStream& StringStream::operator<<(Int32 value) {
  char string[16];
  //TODO:linux  sprintf -> snprintf
  int length = sprintf(string, "%d", value);
  buffer_->Write(string, length);
  return *this;
}

StringStream& StringStream::operator<<(Uint32 value) {
  char string[16];
  int length = sprintf(string, "%u", value);
  buffer_->Write(string, length);
  return *this;
}

StringStream& StringStream::operator<<(Int64 value) {
  char string[32];
  int length = sprintf(string, "%l", value);
  buffer_->Write(string, length);
  return *this;
}

StringStream& StringStream::operator<<(Uint64 value) {
  char string[32];
  int length = sprintf(string, "%lu", value);
  buffer_->Write(string, length);
  return *this;
}

StringStream& StringStream::operator<<(float value) {
  char string[32];
  int length = sprintf(string, "%f", value);
  buffer_->Write(string, length);
  return *this;
}

StringStream& StringStream::operator<<(double value) {
  char string[32];
  int length = sprintf(string, "%f", value);
  buffer_->Write(string, length);
  return *this;
}

StringStream& StringStream::operator<<(const char* value) {
  buffer_->Write(value, strlen(value));
  return *this;
}

StringStream& StringStream::operator<<(const std::string& value) {
  buffer_->Write(value.c_str(), value.length());
  return *this;
}

StringStream& StringStream::operator<<(EndLine) {
  *this << "\n";
  return *this;
}

StringStream& StringStream::operator>>(BufferString& value) {
  buffer_->ReadLine(&value);
  return *this;
}

StringStream& StringStream::operator>>(std::string& value) {
  BufferString string;
  buffer_->ReadLine(&string);
  value.clear();
  value.append(string.String());
  return *this;
}

Buffer* StringStream::buffer() {
  return buffer_;
}