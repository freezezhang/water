#ifndef NET_CONNECTOR_INL_H_
#define NET_CONNECTOR_INL_H_

namespace Water {

template<typename ProtocolT, typename HandlerT>
Connector<ProtocolT, HandlerT>::Connector(Reactor* reactor)
    : Handler(-1, reactor) {
  assert(reactor);
}

template<typename ProtocolT, typename HandlerT>
Connector<ProtocolT, HandlerT>::~Connector() {
  socket_.Close();
}

template<typename ProtocolT, typename HandlerT>
int Connector<ProtocolT, HandlerT>::Connect(const SocketAddress<ProtocolT>& address) {
  Handler::set_fd(socket_.GetSocket());
  if (socket_.SetNoBlock() == -1) return -1;
  int result = socket_.Connect(address);
  if (result == -1) {
    if (errno != EINPROGRESS) {
      return -1;
    } else {
      if (reactor()->RegisterHandler(this, kEventOutput | kEventInput) == -1) return 0;
    }
  } else if (result == 0) {
    HandleOutput(socket_.GetSocket());
  } else {
    return -1;
  }
  return 0;
}

template<typename ProtocolT, typename HandlerT>
int Connector<ProtocolT, HandlerT>::Connect(const string& ip, in_port_t port) {
  SocketAddress<ProtocolT> address(ip, port);
  return Connect(address);
}

template<typename ProtocolT, typename HandlerT>
int Connector<ProtocolT, HandlerT>::HandleInput(int) {
  int error = 0;
  socklen_t length = 0;
  if (socket_.GetSocketOptions(SOL_SOCKET, SO_ERROR, &error, &length) < 0) {
    return -1;
  } else {
    if (error != 0) {
      errno = error;
      return -1;
    }
  }
  return 0;
}

template<typename ProtocolT, typename HandlerT>
int Connector<ProtocolT, HandlerT>::HandleOutput(int) {
  int error = 0;
  socklen_t length = 0;
  if (socket_.GetSocketOptions(SOL_SOCKET, SO_ERROR, &error, &length) < 0) {
    return -1;
  } else {
    if (error != 0) {
      errno = error;
      return -1;
    }
  }
  //socket_.UnSetNoBlock();
  HandlerT* handler = NULL;
  if (MakeHandler(handler) == -1) return -1;
  return ActivateHandler(handler);
}

template<typename ProtocolT, typename HandlerT>
int Connector<ProtocolT, HandlerT>::MakeHandler(HandlerT*& handler) {
  handler = new (std::nothrow) HandlerT(socket_.GetSocket(), reactor());
  if (handler == NULL) return -1;
  return 0;
}

template<typename ProtocolT, typename HandlerT>
int Connector<ProtocolT, HandlerT>::ActivateHandler(HandlerT* handler) {
  assert(handler);
  int result = handler->SetNoBlock();
  if (result != 0) return result;
  result = handler->HandleOpen();
  if (result != 0) handler->HandleClose();
  return result;
}

} // namespace Water

#endif // NET_CONNECTOR_INL_H_
