#ifndef FILE_SYSTEM_DIRECTORY_INL_H_
#define FILE_SYSTEM_DIRECTORY_INL_H_

namespace Water {

inline string Directory::GetNextItem() {
  dirent* dir = readdir(dp_);
  if (dir != NULL) {
    return string(dir->d_name);
  } else {
    return string("");
  }
}

inline void Directory::RewindIndex() const {
  rewinddir(dp_);
}

inline long Directory::GetCurrentIndex() const {
  return telldir(dp_);
}

inline void Directory::SetCurrentIndex(long item_index) const {
  seekdir(dp_, item_index);
}

} // namespace Water

#endif // FILE_SYSTEM_DIRECTORY_INL_H_
