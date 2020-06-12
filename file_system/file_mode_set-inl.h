#ifndef FILE_SYSTEM_FILE_MODE_SET_INL_H_
#define FILE_SYSTEM_FILE_MODE_SET_INL_H_

namespace Water {

inline FileModeSet::FileModeSet()
    : file_mode_set_(0) {
}

inline FileModeSet::FileModeSet(mode_t file_mode_set)
    : file_mode_set_(file_mode_set) {
}

inline FileModeSet::FileModeSet(const FileModeSet& other)
    : file_mode_set_(other.GetFileMode()) {
}

inline FileModeSet::~FileModeSet() {
}

inline FileModeSet& FileModeSet::operator=(const FileModeSet& other) {
  file_mode_set_ = other.GetFileMode();
  return *this;
}

inline mode_t FileModeSet::GetFileMode() const {
  return file_mode_set_;
}

inline void FileModeSet::SetFileMode(mode_t file_mode_set) {
  file_mode_set_ = file_mode_set;
}

inline void FileModeSet::AddMode(FileMode file_mode) {
  file_mode_set_ |= file_mode;
}

inline bool FileModeSet::InFileModeSet(FileMode file_mode) const {
  return file_mode_set_ & file_mode;
}

inline void FileModeSet::ClearMode(FileMode file_mode) {
  file_mode_set_ &= (~file_mode);
}

inline void FileModeSet::ClearAllMode() {
  file_mode_set_ = 0;
}

} // namespace Water

#endif // FILE_SYSTEM_FILE_MODE_SET_INL_H_
