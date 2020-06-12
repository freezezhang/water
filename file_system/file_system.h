/*
 * file_system.h
 *
 * Created on: 2011-3-1
 * Author: freezezdj
 */

#ifndef FILE_SYSTEM_FILE_SYSTEM_H_
#define FILE_SYSTEM_FILE_SYSTEM_H_

#include <stdio.h>

#include "path.h"
#include "file_system/file_system_types.h"
#include "file_system/file_mode_set.h"

namespace Water {

class FileSystem {
public:
  static inline int TestAccess(const Path& path, AccessMode access_mode);

  static inline mode_t SetFileModeMask(mode_t mask);

  static inline int ChangeFileMode(const Path& path,
                                   const FileModeSet& file_mode_set);
  static inline int ChangeFileMode(int file_descriptor,
                                   const FileModeSet& file_mode_set);

  static inline int ChangeFileOwner(const Path& path,
                                    uid_t user_id,
                                    uid_t group_id);
  static inline int ChangeFileOwner(int file_descriptor,
                                    uid_t user_id,
                                    uid_t group_id);

  static inline int ChangeFileUserId(const Path& path, uid_t user_id);
  static inline int ChangeFileUserId(int file_descriptor, uid_t user_id);

  static inline int ChangeFileGroupId(const Path& path, uid_t group_id);
  static inline int ChangeFileGroupId(int file_descriptor, uid_t group_id);

  static inline int ChangeSymbolicOwner(const Path& path,
                                        uid_t user_id,
                                        uid_t group_id);
  static inline int ChangeSymbolicUserId(const Path& path, uid_t user_id);
  static inline int ChangeSymbolicGroupId(const Path& path, uid_t group_id);

  static inline int TruncateFile(const Path& path, off_t length);
  static inline int TruncateFile(int file_descriptor, off_t length);

  static inline int CreateHardLink(const Path& existing_path,
                                   const Path& new_path);
  static inline int RemoveHardLink(const Path& path);

  static inline int RemoveFile(const Path& path);
  static inline int ReNameFile(const Path& old_name, const Path& new_name);

  static inline int CreateSymbolicLink(const Path& existing_path,
                                       const Path& new_path);
  static inline string ReadSymbolicLink(const Path& path);

  static inline int MakeDirectory(const Path& path,
                                  const FileModeSet& file_mode_set);
  static inline int RemoveDirectory(const Path& path);

  static inline string GetCurrentDirectory();

  static inline int ChangeCurrentDirectory(const Path& path);
  static inline int ChangeCurrentDirectory(int file_descriptor);

};
// class FileSystem

}// namespace Water

#include "file_system-inl.h"

#endif // FILE_SYSTEM_FILE_SYSTEM_H_
