/*
 * directory.h
 *
 * Created on: 2011-3-18
 * Author: freezezdj
 */

#ifndef FILE_SYSTEM_DIRECTORY_H_
#define FILE_SYSTEM_DIRECTORY_H_

#include <dirent.h>

#include <string>
using std::string;

#include <vector>
using std::vector;

#include "file_system/path.h"
#include "file_system/file_system_exception.h"

namespace Water {

// TODO: Directory 未测试

class Directory {
public:
  explicit Directory(const Path& path) throw (BadOpenDirectory);
  virtual ~Directory();

public:
  const vector<string>& GetAllSubItem();
  bool SubItemExistence(const Path& path);

  inline string GetNextItem();
  inline void RewindIndex() const;
  inline long GetCurrentIndex() const;
  inline void SetCurrentIndex(long ItemIndex) const;

private:
  DIR* dp_;
  vector<string> sub_item_vector_;
};

} // namespace Water

#include "directory-inl.h"

#endif // FILE_SYSTEM_DIRECTORY_H_
