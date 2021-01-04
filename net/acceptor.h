/*
 * acceptor.h
 *
 * Created on: 2011-5-23
 * Author: freezezhang
 */

#ifndef NET_ACCEPTOR_H_
#define NET_ACCEPTOR_H_

#include <assert.h>

#include "net/handler.h"
#include "net/net_types.h"
#include "net/reactor.h"
#include "net/socket.h"
#include "net/net_error.h"

namespace Water {

template<typename ProtocolT, typename HandlerT>
class Acceptor : public Handler {
 public:
  Acceptor();
  virtual ~Acceptor();

 public:
  Int32 Init(Reactor* reactor);

 public:
  Int32 Accept(const SocketAddress<ProtocolT>& address);
  Int32 Accept(const string& ip, PortType port);
  Int32 Accept(PortType port);

 protected:
  virtual Int32 HandleInput(int);

  virtual HandlerT* MakeHandler();
  virtual Int32 ActivateHandler(HandlerT* handler);

 private:
  Socket<ProtocolT> socket_;
};

template<typename ProtocolT, typename HandlerT>
Acceptor<ProtocolT, HandlerT>::Acceptor() {
}

template<typename ProtocolT, typename HandlerT>
Acceptor<ProtocolT, HandlerT>::~Acceptor() {
  socket_.Close();
}

template<typename ProtocolT, typename HandlerT>
Int32 Acceptor<ProtocolT, HandlerT>::Init(Reactor* reactor) {
  assert(reactor);
  Int32 ret = socket_.Init();
  if (ret != 0) {
    return ret;
  }
  return Handler::Init(socket_.socket(), reactor);
}

template<typename ProtocolT, typename HandlerT>
inline Int32 Acceptor<ProtocolT, HandlerT>::Accept(const SocketAddress<ProtocolT>& address) {
  Handler::set_fd(socket_.socket());
  Int32 ret = 0;
  ret = socket_.SetReuseAddress();
  if (ret != 0)
    return ret;
  ret = socket_.SetNoBlock();
  if (ret != 0)
    return ret;
  ret = reactor()->RegisterHandler(this, kEventInput);
  if (ret != 0)
    return ret;
  ret = socket_.Bind(address);
  if (ret != 0)
    return ret;
  ret = socket_.Listen();
  if (ret != 0)
    return ret;
  return 0;
}

template <typename ProtocolT, typename HandlerT>
inline Int32 Acceptor<ProtocolT, HandlerT>::Accept(const string &ip, PortType port) {
  SocketAddress<ProtocolT> address;
  Int32 ret = address.Init(ip, port);
  if (ret != 0) {
    return ret;
  }
  return Accept(address);
}

template<typename ProtocolT, typename HandlerT>
inline Int32 Acceptor<ProtocolT, HandlerT>::Accept(PortType port) {
  SocketAddress<ProtocolT> address;
  Int32 ret = address.Init(port);
  if (ret != 0) {
    return ret;
  }
  return Accept(address);
}

template<typename ProtocolT, typename HandlerT>
inline Int32 Acceptor<ProtocolT, HandlerT>::HandleInput(int) {
  HandlerT* handler = MakeHandler();
  if (handler != nullptr) {
    return ActivateHandler(handler);
  }
  return kNetErrorMakeHadler;
}

template<typename ProtocolT, typename HandlerT>
HandlerT* Acceptor<ProtocolT, HandlerT>::MakeHandler() {
  Int32 connet_fd = socket_.Accept();
  if (connet_fd < 0)
    return nullptr;
  HandlerT* handler = new (std::nothrow) HandlerT();
  if (handler != nullptr) {
    Int32 ret = handler->Init(connet_fd, reactor());
    if (ret == 0)
      return handler;
  }
  return nullptr;
}

template<typename ProtocolT, typename HandlerT>
Int32 Acceptor<ProtocolT, HandlerT>::ActivateHandler(HandlerT* handler) {
  assert(handler);
  Int32 ret = handler->SetNoBlock();
  if (ret != 0) 
    return ret;
  ret = handler->HandleOpen();
  if (ret != 0) 
    return handler->HandleClose();
  return ret;
}

} // namespace Water

#endif // NET_ACCEPTOR_H_
