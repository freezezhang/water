#include "file_status.h"

#include <cstring>
#include <cstdio>
#include <cassert>
#include <cerrno>
#include <utime.h>

namespace Water {

FileStatus::FileStatus(const Path& file_path,
                       bool is_symbolic) throw (BadUpdate)
    : file_path_(file_path),
      path_initialize_(true),
      is_symbolic_(is_symbolic),
      status_change_(true),
      file_descriptor_(0) {
  memset(&file_status_, 0, sizeof(file_status_));
  UpdateStatus();
}

FileStatus::FileStatus(int file_descriptor) throw (BadUpdate)
    : file_path_(""),
      path_initialize_(false),
      is_symbolic_(false),
      status_change_(true),
      file_descriptor_(file_descriptor) {
  memset(&file_status_, 0, sizeof(file_status_));
  UpdateStatus();
}

FileStatus::~FileStatus() {

}

int FileStatus::ReSetFileMode(const FileModeSet& file_mode_set) {
  int value = 0;
  if (path_initialize_) {
    value = chmod(file_path_.GetCString(), file_mode_set.GetFileMode());
  } else {
    value = fchmod(file_descriptor_, file_mode_set.GetFileMode());
  }
  FileStatusChange();
  return value;
}

int FileStatus::SetFileMode(const FileModeSet& file_mode_set) throw (BadUpdate) {
  UpdateStatus();
  int value = 0;
  mode_t mode = file_status_.st_mode | file_mode_set.GetFileMode();
  if (path_initialize_) {
    value = chmod(file_path_.GetCString(), mode);
  } else {
    value = fchmod(file_descriptor_, mode);
  }
  FileStatusChange();
  return value;
}

int FileStatus::SetAutoUserId(bool is_add) throw (BadUpdate) {
  UpdateStatus();
  int value = 0;
  mode_t mode =
      is_add ? file_status_.st_mode | S_ISUID : file_status_.st_mode & ~S_ISUID;
  if (path_initialize_) {
    value = chmod(file_path_.GetCString(), mode);
  } else {
    value = fchmod(file_descriptor_, mode);
  }
  FileStatusChange();
  return value;
}

int FileStatus::SetAutoGroupId(bool is_add) throw (BadUpdate) {
  UpdateStatus();
  int value = 0;
  mode_t mode =
      is_add ? file_status_.st_mode | S_ISGID : file_status_.st_mode & ~S_ISGID;
  if (path_initialize_) {
    value = chmod(file_path_.GetCString(), mode);
  } else {
    value = fchmod(file_descriptor_, mode);
  }
  FileStatusChange();
  return value;
}

int FileStatus::SetStickyBit(bool is_add) throw (BadUpdate) {
  UpdateStatus();
  int value = 0;
  mode_t mode =
      is_add ? file_status_.st_mode | S_ISVTX : file_status_.st_mode & ~S_ISVTX;
  if (path_initialize_) {
    value = chmod(file_path_.GetCString(), mode);
  } else {
    value = fchmod(file_descriptor_, mode);
  }

  FileStatusChange();
  return value;
}

int FileStatus::ChangeFileOwner(uid_t user_id, uid_t group_id) {
  int value = 0;
  if (path_initialize_) {
    if (!is_symbolic_) {
      value = chown(file_path_.GetCString(), user_id, group_id);
    } else {
      value = lchown(file_path_.GetCString(), user_id, group_id);
    }
  } else {
    value = fchown(file_descriptor_, user_id, group_id);
  }

  FileStatusChange();
  return value;
}

int FileStatus::ChangeUserId(uid_t user_id) {
  int value = 0;
  if (path_initialize_) {
    if (!is_symbolic_) {
      value = chown(file_path_.GetCString(), user_id, -1);
    } else {
      value = lchown(file_path_.GetCString(), user_id, -1);
    }
  } else {
    value = fchown(file_descriptor_, user_id, -1);
  }

  FileStatusChange();
  return value;
}

int FileStatus::ChangeGroupId(uid_t group_id) {
  int value = 0;
  if (path_initialize_) {
    if (!is_symbolic_) {
      value = chown(file_path_.GetCString(), -1, group_id);
    } else {
      value = lchown(file_path_.GetCString(), -1, group_id);
    }
  } else {
    value = fchown(file_descriptor_, -1, group_id);
  }

  FileStatusChange();
  return value;
}

int FileStatus::TruncateFile(off_t length) {
  int value = 0;
  if (path_initialize_) {
    value = truncate(file_path_.GetCString(), length);
  } else {
    value = ftruncate(file_descriptor_, length);
  }
  FileStatusChange();
  return value;
}

int FileStatus::ReName(const string& new_name) {
  int value = rename(file_path_.GetCString(), new_name.c_str());
  if (value == 0) {
    file_path_ = new_name;
  }
  return value;
}

string FileStatus::ReadSymbolic() const {
  if (is_symbolic_) {
    char link_buf[kPathCStringMax];
    ssize_t buf_size = readlink(file_path_.GetCString(),
                                link_buf,
                                kPathCStringMax);
    return string(link_buf, buf_size);
  } else {
    return "";
  }
}

int FileStatus::SetFileTime(time_t access_time, time_t modification_time) {
  utimbuf time_buf = {access_time, modification_time};
  int value = utime(file_path_.GetCString(), &time_buf);
  FileStatusChange();
  return value;
}

void FileStatus::UpdateFileStatus(bool is_symbolic) throw (BadUpdate) {
  if (!status_change_) {
    return;
  }

  if (path_initialize_) {
    if (is_symbolic) {
      if (lstat(file_path_.GetCString(), &file_status_) < 0) {
        is_initialize_ = false;
        throw BadUpdate(errno);
      }
    } else {
      if (stat(file_path_.GetCString(), &file_status_) < 0) {
        is_initialize_ = false;
        throw BadUpdate(errno);
      }
    }
  } else {
    if (fstat(file_descriptor_, &file_status_) < 0) {
      is_initialize_ = false;
      throw BadUpdate(errno);
    }
  }
  status_change_ = false;
  is_initialize_ = true;
}

bool FileStatus::PathByFileDescriptor() {
  char fd_name[kPathCStringMax];
  char path[kPathCStringMax];
  snprintf(fd_name,
           kPathCStringMax,
           "/proc/%ld/fd/%d",
           (long)getpid(),
           file_descriptor_);
  if (readlink(fd_name, path, kPathCStringMax) < 0) {
    file_path_ = "";
    return false;
  } else {
    file_path_ = fd_name;
    return true;
  }
}

} // namespace Water

