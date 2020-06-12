#ifndef NET_ACCEPTOR_INL_H_
#define NET_ACCEPTOR_INL_H_

namespace Water {
template<typename ProtocolT, typename HandlerT>
Acceptor<ProtocolT, HandlerT>::Acceptor(Reactor* reactor)
    : Handler(-1, reactor) {
  assert(reactor);
}

template<typename ProtocolT, typename HandlerT>
Acceptor<ProtocolT, HandlerT>::~Acceptor() {
  socket_.Close();
}

template<typename ProtocolT, typename HandlerT>
inline int Acceptor<ProtocolT, HandlerT>::Accept(const SocketAddress<ProtocolT>& address) {
  Handler::set_fd(socket_.GetSocket());
  if (socket_.SetReuseAddress() != 0) return -1;
  if (socket_.SetNoBlock() != 0) return -1;
  if (reactor()->RegisterHandler(this, kEventInput) != 0) return -1;
  if (socket_.Bind(address) != 0) return -1;
  if (socket_.Listen() != 0) return -1;
  return 0;
}

template<typename ProtocolT, typename HandlerT>
inline int Acceptor<ProtocolT, HandlerT>::Accept(const string& ip,
                                                 in_port_t port) {
  SocketAddress<ProtocolT> address(ip, port);
  return Accept(address);
}

template<typename ProtocolT, typename HandlerT>
inline int Acceptor<ProtocolT, HandlerT>::Accept(in_port_t port) {
  SocketAddress<ProtocolT> address(port);
  return Accept(address);
}

template<typename ProtocolT, typename HandlerT>
inline int Acceptor<ProtocolT, HandlerT>::HandleInput(int) {
  HandlerT* handler = NULL;
  if (MakeHandler(handler) == -1) return -1;
  return ActivateHandler(handler);
}

template<typename ProtocolT, typename HandlerT>
int Acceptor<ProtocolT, HandlerT>::MakeHandler(HandlerT*& handler) {
  int connet_fd = socket_.Accept();
  handler = new (std::nothrow) HandlerT(connet_fd, reactor());
  if (handler == NULL) return -1;
  return 0;
}

template<typename ProtocolT, typename HandlerT>
int Acceptor<ProtocolT, HandlerT>::ActivateHandler(HandlerT* handler) {
  assert(handler);
  int result = handler->SetNoBlock();
  if (result != 0) return result;
  result = handler->HandleOpen();
  if (result != 0) handler->HandleClose();
  return result;
}

} // namespace Water

#endif // NET_ACCEPTOR_INL_H_
