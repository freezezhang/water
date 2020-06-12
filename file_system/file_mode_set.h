/*
 * file_mode_set.h
 *
 * Created on: 2011-2-25
 * Author: freezezdj
 */

#ifndef FILE_SYSTEM_FILE_MODE_SET_H_
#define FILE_SYSTEM_FILE_MODE_SET_H_

#include "file_system/file_system_types.h"

namespace Water {

//TODO FileModeSet ： 文件访问权限集

class FileModeSet {
public:
  FileModeSet();
  FileModeSet(mode_t file_mode_set);
  FileModeSet(const FileModeSet& file_mode_set);
  virtual ~FileModeSet();

public:
  inline FileModeSet& operator =(const FileModeSet& other);

public:
  inline mode_t GetFileMode() const;
  inline void SetFileMode(mode_t file_mode_set);
  inline void AddMode(FileMode file_mode);
  inline bool InFileModeSet(FileMode file_mode) const;
  inline void ClearMode(FileMode file_mode);
  inline void ClearAllMode();

private:
  mode_t file_mode_set_;
};

} // namespace Water

#include "file_mode_set-inl.h"

#endif // FILE_SYSTEM_FILE_MODE_SET_H_
