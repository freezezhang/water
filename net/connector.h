/*
 * Connector.h
 *
 * Created on: 2011-5-23
 * Author: freezezdj
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
  Connector(Reactor* reactor);
  virtual ~Connector();

public:
  int Connect(const SocketAddress<ProtocolT>& address);
  int Connect(const string& ip, in_port_t port);

protected:
  virtual int HandleInput(int);
  virtual int HandleOutput(int);

  virtual int MakeHandler(HandlerT*& handler);
  virtual int ActivateHandler(HandlerT* handler);

private:
  Socket<ProtocolT> socket_;
};

} // namespace Water

#include "connector-inl.h"

#endif // NET_CONNECTOR_H_
