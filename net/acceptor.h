/*
 * acceptor.h
 *
 * Created on: 2011-5-23
 * Author: freezezdj
 */

#ifndef NET_ACCEPTOR_H_
#define NET_ACCEPTOR_H_

#include <assert.h>

#include "net/socket.h"
#include "net/handler.h"
#include "net/reactor.h"
#include "net/net_types.h"
#include "net/net_exception.h"

namespace Water {

template<typename ProtocolT, typename HandlerT>
class Acceptor : public Handler {
public:
  Acceptor(Reactor* reactor);
  virtual ~Acceptor();

public:
  int Accept(const SocketAddress<ProtocolT>& address);
  int Accept(const string& ip, in_port_t port);
  int Accept(in_port_t port);

protected:
  virtual int HandleInput(int);

  virtual int MakeHandler(HandlerT*& handler);
  virtual int ActivateHandler(HandlerT* handler);

private:
  Socket<ProtocolT> socket_;
};

} // namespace Water

#include "acceptor-inl.h"

#endif // NET_ACCEPTOR_H_
