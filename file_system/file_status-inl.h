#ifndef FILE_SYSTEM_FILE_STATUS_INL_H_
#define FILE_SYSTEM_FILE_STATUS_INL_H_

namespace Water {

inline bool FileStatus::UpdateSucceed() const {
  return is_initialize_;
}

inline bool FileStatus::IsRegularFile() throw (BadUpdate) {
  UpdateStatus();
  return S_ISREG(file_status_.st_mode);
}

inline bool FileStatus::IsDirectory() throw (BadUpdate) {
  UpdateStatus();
  return S_ISDIR(file_status_.st_mode);
}

inline bool FileStatus::IsBlockSpecial() throw (BadUpdate) {
  UpdateStatus();
  return S_ISBLK(file_status_.st_mode);
}

inline bool FileStatus::IsCharacterSpecial() throw (BadUpdate) {
  UpdateStatus();
  return S_ISCHR(file_status_.st_mode);
}

inline bool FileStatus::IsFIFO() throw (BadUpdate) {
  UpdateStatus();
  return S_ISFIFO(file_status_.st_mode);
}

inline bool FileStatus::IsSocket() throw (BadUpdate) {
  UpdateStatus();
  return S_ISSOCK(file_status_.st_mode);
}

inline bool FileStatus::IsSymbolicLink() throw (BadUpdate) {
  UpdateStatus();
  return S_ISLNK(file_status_.st_mode);
}

inline bool FileStatus::IsMessageQueue() throw (BadUpdate) {
  UpdateStatus();
  return S_TYPEISMQ(&file_status_);
}

inline bool FileStatus::IsSemaphore() throw (BadUpdate) {
  UpdateStatus();
  return S_TYPEISSEM(&file_status_);
}

inline bool FileStatus::IsSharedMemory() throw (BadUpdate) {
  UpdateStatus();
  return S_TYPEISSHM(&file_status_);
}

inline bool FileStatus::IsSetAutoUserId() throw (BadUpdate) {
  UpdateStatus();
  return file_status_.st_mode & S_ISUID;
}

inline bool FileStatus::IsSetAutoGroupId() throw (BadUpdate) {
  UpdateStatus();
  return file_status_.st_mode & S_ISGID;
}

inline FileType FileStatus::GetFileType() throw (BadUpdate) {
  UpdateStatus();
  return static_cast<FileType>(file_status_.st_mode & kFileTypeMask);
}

inline FileModeSet FileStatus::GetFileMode() throw (BadUpdate) {
  UpdateStatus();
  return FileModeSet(file_status_.st_mode & kFileModeMask);
}

inline bool FileStatus::TestAccess(AccessMode access_mode) {
  UpdateStatus();
  if (access(file_path_.GetCString(), access_mode) == 0) {
    return true;
  }
  return false;
}

inline ino_t FileStatus::SerialNumber() throw (BadUpdate) {
  UpdateStatus();
  return file_status_.st_ino;
}

inline dev_t FileStatus::DeviceNumber() throw (BadUpdate) {
  UpdateStatus();
  return file_status_.st_dev;
}

inline dev_t FileStatus::SpecialDeviceNumber() throw (BadUpdate) {
  UpdateStatus();
  return file_status_.st_rdev;
}

inline nlink_t FileStatus::LinksNumber() throw (BadUpdate) {
  UpdateStatus();
  return file_status_.st_nlink;
}

inline uid_t FileStatus::UserId() throw (BadUpdate) {
  UpdateStatus();
  return file_status_.st_uid;
}

inline gid_t FileStatus::GroupId() throw (BadUpdate) {
  UpdateStatus();
  return file_status_.st_gid;
}

inline off_t FileStatus::FileSize() throw (BadUpdate) {
  UpdateStatus();
  return file_status_.st_size;
}

inline timespec&FileStatus::LastModificationTime() throw (BadUpdate) {
  UpdateStatus();
  return file_status_.st_mtim;
}

inline timespec&FileStatus::LastAccessTime() throw (BadUpdate) {
  UpdateStatus();
  return file_status_.st_atim;
}

inline timespec&FileStatus::LastStatusChangeTime() throw (BadUpdate) {
  UpdateStatus();
  return file_status_.st_ctim;
}

inline blksize_t FileStatus::BastIOBlockSize() throw (BadUpdate) {
  UpdateStatus();
  return file_status_.st_blksize;
}

inline blkcnt_t FileStatus::DiskBlockAllocatedNmmber() throw (BadUpdate) {
  UpdateStatus();
  return file_status_.st_blocks;
}

inline int FileStatus::SymbolicLink(const string& symbolic_name) const {
  return symlink(file_path_.GetCString(), symbolic_name.c_str());
}

inline int FileStatus::SymbolicLink(const Path& symbolic_path) const {
  return symlink(file_path_.GetCString(), symbolic_path.GetCString());
}

inline const Path& FileStatus::FilePath() {
  if (!path_initialize_) {
    PathByFileDescriptor();
  }
  return file_path_;
}

inline const string& FileStatus::FilePathString() const {
  return file_path_.GetString();
}

inline void FileStatus::FileStatusChange() {
  status_change_ = true;
}

inline void FileStatus::UpdateStatus() throw (BadUpdate) {
  try {
    UpdateFileStatus(is_symbolic_);
  } catch (BadUpdate) {
    throw;
  }
}

}   // namespace Water

#endif // FILE_SYSTEM_FILE_STATUS_INL_H_
