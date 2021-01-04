#include "handler.h"

#include <unistd.h>

namespace Water {

Handler::Handler()
  : fd_(kInvalidFD)
  , reactor_(nullptr)
  , is_pause_(false)
  , priority_(kNormalPriority) {
}

Handler::~Handler() {
  close(fd_);
  reactor_ = nullptr;
}

Int32 Handler::HandleOpen() {
  return 0;
}

Int32 Handler::HandleInput(Int32 fd) {
  return 0;
}

Int32 Handler::HandleOutput(Int32 fd) {
  return 0;
}

Int32 Handler::HandleTimeout() {
  return 0;
}

Int32 Handler::HandleException() {
  return 0;
}

Int32 Handler::HandleClose() {
  reactor_->RemoveHandler(this);
  delete this;
  return 0;
}

} // namespace Water
