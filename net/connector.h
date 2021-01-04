/*
 * Connector.h
 *
 * Created on: 2011-5-23
 * Author: freezezhang
 */

#ifndef NET_CONNECTOR_H_
#define NET_CONNECTOR_H_

#include <assert.h>

#include "net/socket.h"
#include "net/handler.h"
#include "net/reactor.h"
#include "net/net_types.h"
#include "net/net_exception.h"

namespace Water {

template<typename ProtocolT, typename HandlerT>
class Connector : public Handler {
 public:
  Connector();
  virtual ~Connector();

 public:
  Int32 init(Reactor* reactor);

  Int32 Connect(const SocketAddress<ProtocolT>& address);
  Int32 Connect(const string& ip, PortType port);

protected:
  virtual Int32 HandleInput(int);
  virtual Int32 HandleOutput(int);

  virtual Handler* MakeHandler();
  virtual Int32 ActivateHandler(Handler* handler);

private:
  Socket<ProtocolT> socket_;
};

template<typename ProtocolT, typename HandlerT>
Connector<ProtocolT, HandlerT>::Connector()
    : Handler(kInvalidFD, nullptr) {
}

template<typename ProtocolT, typename HandlerT>
Connector<ProtocolT, HandlerT>::~Connector() {
  socket_.Close();
}

template<typename ProtocolT, typename HandlerT>
Int32 Connector<ProtocolT, HandlerT>::init(Reactor* reactor) {
  return Handler::init(kInvalidFD, reactor);
}

template<typename ProtocolT, typename HandlerT>
Int32 Connector<ProtocolT, HandlerT>::Connect(const SocketAddress<ProtocolT>& address) {
  Handler::set_fd(socket_.GetSocket());
  Int32 ret = 0;
  ret = socket_.SetNoBlock();
  if (ret != 0)
    return ret;
  ret = socket_.Connect(address);
  if (ret != 0) {
    if (errno != EINPROGRESS) {
      return -1;
    } else {
      if (reactor()->RegisterHandler(this, kEventOutput | kEventInput) == -1) return 0;
    }
  } else if (ret == 0) {
    HandleOutput(socket_.GetSocket());
  } else {
    return -1;
  }
  return 0;
}

template<typename ProtocolT, typename HandlerT>
Int32 Connector<ProtocolT, HandlerT>::Connect(const string& ip, in_port_t port) {
  SocketAddress<ProtocolT> address(ip, port);
  return Connect(address);
}

template<typename ProtocolT, typename HandlerT>
Int32 Connector<ProtocolT, HandlerT>::HandleInput(int) {
  Int32 error = 0;
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
Int32 Connector<ProtocolT, HandlerT>::HandleOutput(int) {
  Int32 error = 0;
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
  Handler* handler = MakeHandler();
  if (handler != nullptr)
    return ActivateHandler(handler);
  return 0;
}

template<typename ProtocolT, typename HandlerT>
Handler* Connector<ProtocolT, HandlerT>::MakeHandler() {
  return new (std::nothrow) HandlerT(socket_.GetSocket(), reactor());
}

template<typename ProtocolT, typename HandlerT>
Int32 Connector<ProtocolT, HandlerT>::ActivateHandler(Handler* handler) {
  assert(handler);
  Int32 ret = handler->SetNoBlock();
  if (ret != 0) 
    return ret;
  ret = handler->HandleOpen();
  if (ret != 0) 
    return handler->HandleClose();
  return 0;
}

} // namespace Water

#endif // NET_CONNECTOR_H_
