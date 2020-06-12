#include "handler.h"

#include <unistd.h>

namespace Water {

Handler::Handler(int file_descriptor, Reactor* reactor)
	: fd_(file_descriptor)
	, reactor_(reactor)
	, is_pause_(false)
	, priority_(kNormalPriority) {
	assert(reactor);
}

Handler::~Handler() {
	close(fd_);
}

int Handler::HandleOpen() {
	return 0;
}

int Handler::HandleInput(int fd) {
	return 0;
}

int Handler::HandleOutput(int fd) {
	return 0;
}

int Handler::HandleTimeout() {
	return 0;
}

int Handler::HandleException() {
	return 0;
}

int Handler::HandleClose() {
	reactor_->RemoveHandler(this);
	delete this;
	return 0;
}

} // namespace Water
