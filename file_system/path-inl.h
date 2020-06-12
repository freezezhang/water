#ifndef FILE_SYSTEM_PATH_INL_H_
#define FILE_SYSTEM_PATH_INL_H_

namespace Water {

template<typename StringT, typename Traits>
BasicPath<StringT, Traits>::BasicPath(const StringT &path)
    : path_(path) {
}

template<typename StringT, typename Traits>
BasicPath<StringT, Traits>::BasicPath(const CharType* path)
    : path_(path) {

}

template<typename StringT, typename Traits>
BasicPath<StringT, Traits>::BasicPath(const BasicPath& path)
    : path_(path.GetString()) {

}

template<typename StringT, typename Traits>
BasicPath<StringT, Traits>::~BasicPath() {
}

template<typename StringT, typename Traits>
bool BasicPath<StringT, Traits>::Empty() const {
  return path_.empty();
}

template<typename StringT, typename Traits>
size_t BasicPath<StringT, Traits>::Length() const {
  return path_.size();
}

template<typename StringT, typename Traits>
bool BasicPath<StringT, Traits>::HasExtension() const {
  size_t dot_index = path_.find_last_of(Traits::GetChar('.'));
  if (dot_index != StringT::npos) {
    size_t slash_index = path_.find_last_of(Traits::GetChar('/'));
    if (slash_index != StringT::npos) {
      if (dot_index > slash_index) return true;
    } else {
      return true;
    }
  }
  return false;
}

template<typename StringT, typename Traits>
bool BasicPath<StringT, Traits>::HasDirectory() const {
  return path_.find_last_of(Traits::GetChar('/')) != StringT::npos;
}

template<typename StringT, typename Traits>
BasicPath<StringT, Traits>& BasicPath<StringT, Traits>::Append(const StringT& path) {
  path_ += path;
  return *this;
}

template<typename StringT, typename Traits>
BasicPath<StringT, Traits>& BasicPath<StringT, Traits>::ReSetPath(const StringT& path) {
  path_ = path;
  return *this;
}

template<typename StringT, typename Traits>
BasicPath<StringT, Traits>& BasicPath<StringT, Traits>::ReSetPath(const BasicPath<
    StringT, Traits>& path) {
  path_ = path.GetString();
  return *this;
}

template<typename StringT, typename Traits>
BasicPath<StringT, Traits>& BasicPath<StringT, Traits>::Append(const BasicPath& path) {
  return path += path.GetString();
}

template<typename StringT, typename Traits>
StringT BasicPath<StringT, Traits>::GetFileName() const {
  size_t slash_index = path_.find_last_of(Traits::GetChar('/'));
  if (slash_index != StringT::npos) {
    return path_.substr(++slash_index);
  } else {
    return path_;
  }
}

template<typename StringT, typename Traits>
StringT BasicPath<StringT, Traits>::GetFileTitle() const {
  StringT file_name = GetFileName();
  size_t dot_index = file_name.find_last_of(Traits::GetChar('.'));
  if (dot_index != StringT::npos) {
    return file_name.substr(0, dot_index);
  } else {
    return file_name;
  }
}

template<typename StringT, typename Traits>
StringT BasicPath<StringT, Traits>::GetFileExtension() const {
  StringT file_name = GetFileName();
  size_t dot_index = file_name.find_last_of(Traits::GetChar('.'));
  if (dot_index != StringT::npos) {
    return file_name.substr(++dot_index);
  } else {
    return Traits::GetNullString();
  }
}

template<typename StringT, typename Traits>
StringT BasicPath<StringT, Traits>::GetParentsPath() const {
  size_t slash_index = path_.find_last_of(Traits::GetChar('/'));
  if (slash_index != StringT::npos) {
    return path_.substr(0, slash_index);
  } else {
    return Traits::GetNullString();
  }
}

template<typename StringT, typename Traits>
BasicPath<StringT, Traits>& BasicPath<StringT, Traits>::operator=(const BasicPath& path) {
  path_ = path.GetString();
  return *this;
}

template<typename StringT, typename Traits>
BasicPath<StringT, Traits>& BasicPath<StringT, Traits>::operator=(const StringT& path) {
  path_ = path;
  return *this;
}

template<typename StringT, typename Traits>
bool BasicPath<StringT, Traits>::operator==(const BasicPath<StringT, Traits>& path) {
  return path_ == path.GetString();
}

template<typename StringT, typename Traits>
bool BasicPath<StringT, Traits>::operator==(const StringT& path) {
  return path_ == path;
}

template<typename StringT, typename Traits>
bool BasicPath<StringT, Traits>::operator!=(const BasicPath<StringT, Traits>& path) {
  return path_ != path.GetString();
}

template<typename StringT, typename Traits>
bool BasicPath<StringT, Traits>::operator!=(const StringT& path) {
  return path_ != path;
}

template<typename StringT, typename Traits>
BasicPath<StringT, Traits>& BasicPath<StringT, Traits>::operator+=(const BasicPath<
    StringT, Traits>& path) {
  path_ += path.GetString();
  return *this;
}

template<typename StringT, typename Traits>
BasicPath<StringT, Traits>& BasicPath<StringT, Traits>::operator+=(const StringT& path) {
  path_ += path;
  return *this;
}

template<typename StringT, typename Traits>
BasicPath<StringT, Traits> BasicPath<StringT, Traits>::operator+(const BasicPath<
    StringT, Traits>& path) {
  return BasicPath<StringT, Traits>(path_ + path.GetString());
}

template<typename StringT, typename Traits>
BasicPath<StringT, Traits> BasicPath<StringT, Traits>::operator+(const StringT& path) {
  return BasicPath<StringT, Traits>(path_ + path);
}

template<typename StringT, typename Traits>
StringT& BasicPath<StringT, Traits>::GetString() {
  return path_;
}

template<typename StringT, typename Traits>
const StringT& BasicPath<StringT, Traits>::GetString() const {
  return path_;
}

template<typename StringT, typename Traits>
const typename BasicPath<StringT, Traits>::CharType*
BasicPath<StringT, Traits>::GetCString() const {
  return path_.c_str();
}

template<typename StringT, typename Traits>
bool operator==(const StringT& path1, const BasicPath<StringT, Traits>& path2) {
  return path1 == path2.GetString();
}

template<typename StringT, typename Traits>
bool operator!=(const StringT& path1, const BasicPath<StringT, Traits>& path2) {
  return path1 != path2.GetString();
}

} // namespace Water

#endif // FILE_SYSTEM_PATH_INL_H_
