/*
 * file_system_types.h
 *
 * Created on: 2011-2-25
 * Author: freezezdj
 */

#ifndef FILE_SYSTEM_FILE_SYSTEM_TYPES_H_
#define FILE_SYSTEM_FILE_SYSTEM_TYPES_H_

#include <sys/stat.h>
#include "water_types.h"

namespace Water {

enum FileTypeMask {
  kFileTypeMask = S_IFMT,
};

enum FileType {
  kRegularFile = S_IFREG,
  kDirectory = S_IFDIR,
  kBlockSpecial = S_IFBLK,
  kCharacterSpecial = S_IFCHR,
  kFIFO = S_IFIFO,
  kSocket = S_IFSOCK,
  ksymbolicLink = S_IFLNK,
};

enum FileModeMask {
  kFileModeMask = 07777,
};

enum FileMode {
  kUserRead = S_IRUSR,
  kUserWrite = S_IWUSR,
  KUserExecute = S_IXUSR,
  kUserRWX = S_IRWXU,
  kGroupRead = S_IRGRP,
  kGroupWrite = S_IWGRP,
  KGroupExecute = S_IXGRP,
  KGroupRWX = S_IRWXG,
  kOtherRead = S_IROTH,
  kOtherWrite = S_IWOTH,
  KOtherExecute = S_IXOTH,
  KOtherRWX = S_IRWXO,
  kSetUserId = S_ISUID,
  kSetGroupId = S_ISGID,
  kSetStickyBit = S_ISVTX
};

enum AccessMode {
  kReadOK = R_OK,
  kWriteOK = W_OK,
  kExecuteOK = X_OK,
  kFileExist = F_OK,
};

const size_t kPathMax = PATH_MAX;
const size_t kPathCStringMax = kPathMax + 1;

} // namespace Water

#endif // FILE_SYSTEM_FILE_SYSTEM_TYPES_H_
