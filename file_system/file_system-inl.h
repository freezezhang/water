#ifndef FILE_SYSTEM_FILE_SYSTEM_INL_H_
#define FILE_SYSTEM_FILE_SYSTEM_INL_H_

namespace Water {

inline int FileSystem::TestAccess(const Path& path, AccessMode access_mode) {
  return access(path.GetCString(), access_mode);
}

inline mode_t FileSystem::SetFileModeMask(mode_t mask) {
  return umask(mask);
}

inline int FileSystem::ChangeFileMode(const Path& path,
                                      const FileModeSet& file_mode_set) {
  return chmod(path.GetCString(), file_mode_set.GetFileMode());
}

inline int FileSystem::ChangeFileMode(int file_descriptor,
                                      const FileModeSet& file_mode_set) {
  return fchmod(file_descriptor, file_mode_set.GetFileMode());
}

inline int FileSystem::ChangeFileOwner(const Path& path,
                                       uid_t user_id,
                                       uid_t group_id) {
  return chown(path.GetCString(), user_id, group_id);
}

inline int FileSystem::ChangeFileOwner(int file_descriptor,
                                       uid_t user_id,
                                       uid_t group_id) {
  return fchown(file_descriptor, user_id, group_id);
}

inline int FileSystem::ChangeFileUserId(const Path& path, uid_t user_id) {
  return chown(path.GetCString(), user_id, -1);
}

inline int FileSystem::ChangeFileUserId(int file_descriptor, uid_t user_id) {
  return fchown(file_descriptor, user_id, -1);
}

inline int FileSystem::ChangeFileGroupId(const Path& path, uid_t group_id) {
  return chown(path.GetCString(), -1, group_id);
}

inline int FileSystem::ChangeFileGroupId(int file_descriptor, uid_t group_id) {
  return fchown(file_descriptor, -1, group_id);
}

inline int FileSystem::ChangeSymbolicOwner(const Path& path,
                                           uid_t user_id,
                                           uid_t group_id) {
  return lchown(path.GetCString(), user_id, group_id);
}

inline int FileSystem::ChangeSymbolicUserId(const Path& path, uid_t user_id) {
  return lchown(path.GetCString(), user_id, -1);
}

inline int FileSystem::ChangeSymbolicGroupId(const Path& path, uid_t group_id) {
  return lchown(path.GetCString(), -1, group_id);
}

inline int FileSystem::TruncateFile(const Path& path, off_t length) {
  return truncate(path.GetCString(), length);
}

inline int FileSystem::TruncateFile(int file_descriptor, off_t length) {
  return ftruncate(file_descriptor, length);
}

inline int FileSystem::CreateHardLink(const Path& existing_path,
                                      const Path& new_path) {
  return link(existing_path.GetCString(), new_path.GetCString());
}

inline int FileSystem::RemoveHardLink(const Path& path) {
  return unlink(path.GetCString());
}

inline int FileSystem::RemoveFile(const Path& path) {
  return remove(path.GetCString());
}

inline int FileSystem::ReNameFile(const Path& old_name, const Path& new_name) {
  return rename(old_name.GetCString(), new_name.GetCString());
}

inline int FileSystem::CreateSymbolicLink(const Path& existing_path,
                                          const Path& new_path) {
  return symlink(existing_path.GetCString(), new_path.GetCString());
}

inline string FileSystem::ReadSymbolicLink(const Path& path) {
  char link_buf[kPathCStringMax];
  ssize_t buf_size = readlink(path.GetCString(), link_buf, kPathCStringMax);
  return string(link_buf, buf_size);
}

inline int FileSystem::MakeDirectory(const Path& path,
                                     const FileModeSet& file_mode_set) {
  return mkdir(path.GetCString(), file_mode_set.GetFileMode());
}

inline int FileSystem::RemoveDirectory(const Path& path) {
  return rmdir(path.GetCString());
}

inline string FileSystem::GetCurrentDirectory() {
  char current_derectory[kPathCStringMax];
  getcwd(current_derectory, kPathCStringMax);
  return string(current_derectory);
}

inline int FileSystem::ChangeCurrentDirectory(const Path& path) {
  return chdir(path.GetCString());
}

inline int FileSystem::ChangeCurrentDirectory(int file_descriptor) {
  return fchdir(file_descriptor);
}

} // namespace Water

#endif FILE_SYSTEM_FILE_SYSTEM_INL_H_
