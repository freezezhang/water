/*
 * path.h
 *
 * Created on: 2011-2-24
 * Author: freezezdj
 */

#ifndef FILE_SYSTEM_PATH_H_
#define FILE_SYSTEM_PATH_H_

#include <string>
using std::string;
using std::wstring;

#include <algorithm>

namespace Water {

template<typename StringT>
struct StringTraits {

};

template<>
struct StringTraits<string> {
  typedef char CharType;
  typedef string StringType;

  static CharType GetChar(char ch) {
    return ch;
  }

  static StringType GetNullString() {
    return "";
  }
};

template<>
struct StringTraits<wstring> {
  typedef wchar_t CharType;
  typedef wstring StringType;

  static CharType GetChar(char ch) {
    return wchar_t(ch);
  }

  static StringType GetNullString() {
    return L"";
  }
};

template<typename StringT, typename Traits>
class BasicPath {
public:
  typedef typename Traits::CharType CharType;
  typedef typename Traits::StringType StringType;

public:
  explicit BasicPath(const StringT& path);
  explicit BasicPath(const CharType* path);
  explicit BasicPath(const BasicPath& path);
  ~BasicPath();

public:
  // 路径字符串是否为空
  bool Empty() const;

  // 路径字符串长度
  size_t Length() const;

  // 路径所否存在扩展名
  bool HasExtension() const;
  // 路径所否存在目录
  bool HasDirectory() const;

  // 添加目录
  BasicPath& Append(const StringT& path);
  BasicPath& Append(const BasicPath& path);

  // 重新设置路径
  BasicPath& ReSetPath(const StringT& path);
  BasicPath& ReSetPath(const BasicPath& path);

  // 得到路径中的文件或目录名
  StringT GetFileName() const;

  // 得到路径中的文件或目录标题
  StringT GetFileTitle() const;

  // 得到路径中的文件扩展名，如果没有，返回“”
  StringT GetFileExtension() const;

  // 得到文件或目录的上级目录
  StringT GetParentsPath() const;

  BasicPath& operator=(const BasicPath& path);
  BasicPath& operator=(const StringT& path);

  bool operator==(const BasicPath& path);
  bool operator==(const StringT& path);
  bool operator!=(const BasicPath& path);
  bool operator!=(const StringT& path);

  BasicPath& operator+=(const BasicPath& path);
  BasicPath& operator+=(const StringT& path);
  BasicPath operator+(const BasicPath& path);
  BasicPath operator+(const StringT& path);

  // 得到记录路径的字符串
  StringT& GetString();
  const StringT& GetString() const;

  // 得到记录路径的C字符串，即char*，或wchar_t*
  const CharType* GetCString() const;

private:
  StringT path_;
};

template<typename StringT, typename Traits>
bool operator==(const StringT& path1, const BasicPath<StringT, Traits>& path2);

template<typename StringT, typename Traits>
bool operator!=(const StringT& path1, const BasicPath<StringT, Traits>& path2);

typedef BasicPath<string, StringTraits<string> > Path;
typedef BasicPath<wstring, StringTraits<wstring> > WPath;

} // namespace Water

#include "path-inl.h"

#endif // FILESYSTEM_PATH_H_
