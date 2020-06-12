/*
 * file_system.h
 *
 * Created on: 2011-2-25
 * Author: freezezdj
 */

#ifndef FILE_SYSTEM_FILE_STATUS_H_
#define FILE_SYSTEM_FILE_STATUS_H_

#include <unistd.h>

#include "file_system/path.h"
#include "file_system/file_system_types.h"
#include "file_system/file_mode_set.h"
#include "file_system/file_system_exception.h"

namespace Water {

class FileStatus {
public:
  FileStatus(const Path& file_path, bool is_symbolic = false) throw (BadUpdate);
  explicit FileStatus(int file_descriptor) throw (BadUpdate);
  ~FileStatus();

public:
  inline bool UpdateSucceed() const;

  inline ino_t SerialNumber() throw (BadUpdate);
  inline dev_t DeviceNumber() throw (BadUpdate);
  inline dev_t SpecialDeviceNumber() throw (BadUpdate);
  inline nlink_t LinksNumber() throw (BadUpdate);
  inline uid_t UserId() throw (BadUpdate);
  inline gid_t GroupId() throw (BadUpdate);
  inline off_t FileSize() throw (BadUpdate);
  inline timespec& LastModificationTime() throw (BadUpdate);
  inline timespec& LastAccessTime() throw (BadUpdate);
  inline timespec& LastStatusChangeTime() throw (BadUpdate);
  inline blksize_t BastIOBlockSize() throw (BadUpdate);
  inline blkcnt_t DiskBlockAllocatedNmmber() throw (BadUpdate);

  inline FileType GetFileType() throw (BadUpdate);

  inline bool IsRegularFile() throw (BadUpdate);
  inline bool IsDirectory() throw (BadUpdate);
  inline bool IsBlockSpecial() throw (BadUpdate);
  inline bool IsCharacterSpecial() throw (BadUpdate);
  inline bool IsFIFO() throw (BadUpdate);
  inline bool IsSocket() throw (BadUpdate);
  inline bool IsSymbolicLink() throw (BadUpdate);

  inline bool IsMessageQueue() throw (BadUpdate);
  inline bool IsSemaphore() throw (BadUpdate);
  inline bool IsSharedMemory() throw (BadUpdate);

  inline bool IsSetAutoUserId() throw (BadUpdate);
  inline bool IsSetAutoGroupId() throw (BadUpdate);

  inline FileModeSet GetFileMode() throw (BadUpdate);

  // 测试访问权限
  inline bool TestAccess(AccessMode access_mode);

  // 将mode更改为参数值
  int ReSetFileMode(const FileModeSet& file_mode_set);

  // 将mode更改为当前值 & 参数值
  int SetFileMode(const FileModeSet& file_mode_set) throw (BadUpdate);

  // 参数is_add=true 为设置，is_add=false 为清除。
  int SetAutoUserId(bool is_add = true) throw (BadUpdate);
  int SetAutoGroupId(bool is_add = true) throw (BadUpdate);
  int SetStickyBit(bool is_add = true) throw (BadUpdate);

  // 需要超级用户权限
  int ChangeFileOwner(uid_t user_id, uid_t group_id);

  // 需要超级用户权限
  int ChangeUserId(uid_t user_id);
  // 需要超级用户权限
  int ChangeGroupId(uid_t group_id);

  int TruncateFile(off_t length);

  // new_name 为全路径名
  int ReName(const string& new_name);

  inline int SymbolicLink(const string& symbolic_name) const;
  inline int SymbolicLink(const Path& symbolic_path) const;

  // 由链接地址构造的对象调用 ReadSymbolic 可得到正确结果，其他类型返回 “”
  string ReadSymbolic() const;

  int SetFileTime(time_t access_time, time_t modification_time);

  inline const Path& FilePath();
  inline const string& FilePathString() const;

private:
  void UpdateFileStatus(bool is_symbolic = false) throw (BadUpdate);
  bool PathByFileDescriptor();
  inline void FileStatusChange();
  inline void UpdateStatus() throw (BadUpdate);

private:
  bool path_initialize_;
  bool is_symbolic_;
  bool is_initialize_;
  bool status_change_;
  Path file_path_;
  int file_descriptor_;
  struct stat file_status_;
};

} // namespace Water

#include "file_status-inl.h"

#endif // FILE_SYSTEM_FILE_STATUS_H_
