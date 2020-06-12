#include "directory.h"

namespace Water {

Directory::Directory(const Path& path) throw (BadOpenDirectory) {
  dp_ = opendir(path.GetCString());
  if (dp_ == NULL) {
    throw BadOpenDirectory("Open Directroy Error!");
  }
}

Directory::~Directory() {

}

const vector<string>& Directory::GetAllSubItem() {
  sub_item_vector_.clear();
  long current_index = GetCurrentIndex();
  RewindIndex();
  string sub_item;
  while (true) {
    sub_item = GetNextItem();
    if (!sub_item.empty()) {
      sub_item_vector_.push_back(sub_item);
    } else {
      break;
    }
  }
  SetCurrentIndex(current_index);
  return sub_item_vector_;
}

bool Directory::SubItemExistence(const Path& path) {
  long current_index = GetCurrentIndex();
  RewindIndex();
  while (true) {
    if (GetNextItem() == path.GetString()) {
      return true;
    }
  }
  SetCurrentIndex(current_index);
  return false;
}

} // namespace Water
