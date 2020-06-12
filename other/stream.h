/*
 * Stream.h
 *
 *  Created on: 2012-11-18
 *      Author: zdj
 */

#ifndef STREAM_H_
#define STREAM_H_

#include "buffer.h"

class EndLine { };
extern EndLine endl;

class BinaryStream {
public:
  BinaryStream (Buffer* buffer);
  ~BinaryStream ();

  void ReadBool(bool* value);
  void ReadInt8(Int8* value);
  void ReadUint8(Uint8* value);
  void ReadInt16(Int16* value);
  void ReadUint16(Uint16* value);
  void ReadInt32(Int32* value);
  void ReadUint32(Uint32* value);
  void ReadInt64(Int64* value);
  void ReadUint64(Uint64* value);
  void ReadFloat(float* value);
  void ReadDouble(double* value);
  StringLength ReadString(char* value, StringLength count);
  void ReadString(std::string* value);
  void ReadString(BufferString* value);

  void WriteBool(bool value);
  void WriteInt8(Int8 value);
  void WriteUint8(Uint8 value);
  void WriteInt16(Int16 value);
  void WriteUint16(Uint16 value);
  void WriteInt32(Int32 value);
  void WriteUint32(Uint32 value);
  void WriteInt64(Int64 value);
  void WriteUint64(Uint64 value);
  void WriteFloat(float value);
  void WriteDouble(double value);
  void WriteString(const char* value);
  void WriteString(const std::string& value);
  void WriteString(const BufferString& value);

  BinaryStream& operator<<(bool value);
  BinaryStream& operator<<(Int8 value);
  BinaryStream& operator<<(Uint8 value);
  BinaryStream& operator<<(Int16 value);
  BinaryStream& operator<<(Uint16 value);
  BinaryStream& operator<<(Int32 value);
  BinaryStream& operator<<(Uint32 value);
  BinaryStream& operator<<(Int64 value);
  BinaryStream& operator<<(Uint64 value);
  BinaryStream& operator<<(float value);
  BinaryStream& operator<<(double value);
  BinaryStream& operator<<(const char* value);
  BinaryStream& operator<<(const std::string& value);
  BinaryStream& operator<<(const BufferString& value);

  BinaryStream& operator>>(bool& value);
  BinaryStream& operator>>(Int8& value);
  BinaryStream& operator>>(Uint8& value);
  BinaryStream& operator>>(Int16& value);
  BinaryStream& operator>>(Uint16& value);
  BinaryStream& operator>>(Int32& value);
  BinaryStream& operator>>(Uint32& value);
  BinaryStream& operator>>(Int64& value);
  BinaryStream& operator>>(Uint64& value);
  BinaryStream& operator>>(float& value);
  BinaryStream& operator>>(double& value);
  BinaryStream& operator>>(std::string& value);
  BinaryStream& operator>>(BufferString& value);

private:
  Buffer* buffer_;
};

class StringStream {
public:
  StringStream(Buffer* buffer);
  ~StringStream ();

  StringStream& operator<<(bool value);
  StringStream& operator<<(Int8 value);
  StringStream& operator<<(Uint8 value);
  StringStream& operator<<(Int16 value);
  StringStream& operator<<(Uint16 value);
  StringStream& operator<<(Int32 value);
  StringStream& operator<<(Uint32 value);
  StringStream& operator<<(Int64 value);
  StringStream& operator<<(Uint64 value);
  StringStream& operator<<(float value);
  StringStream& operator<<(double value);
  StringStream& operator<<(const char* value);
  StringStream& operator<<(const std::string& value);
  StringStream& operator<<(EndLine);

  StringStream& operator>>(BufferString& value);
  StringStream& operator>>(std::string& value);
  
  Buffer* buffer();

private:
  Buffer* buffer_;
};

#endif // STREAM_H_