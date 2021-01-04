/*
 * socket.h
 *
 * Created on: 2011-5-18
 * Author: freezezhang
 */

#ifndef NET_SOCKET_H_
#define NET_SOCKET_H_

#include <assert.h>
#include <fcntl.h>
#include <unistd.h>

#include "net/net_error.h"
#include "net/net_types.h"
#include "net/socket_address.h"

namespace Water {

template <typename ProtocolT> 
class Socket {
public:
  Socket();
  virtual ~Socket();

 public:
  Int32 Init();

 public:
  void set_socket(Int32 socket);
  inline Int32 socket() const;

 public: // socket API
  inline Int32 Connect(const SocketAddress<ProtocolT> &address) const;
  inline Int32 Connect(const string &ip, PortType port) const;

  inline Int32 Bind(const SocketAddress<ProtocolT> &address) const;
  inline Int32 Bind(const string &ip, PortType port) const;
  inline Int32 Bind(PortType port) const;

  inline Int32 Listen(int backlog = kBackLog) const;

  inline Int32 Accept() const;
  inline Int32 Accept(SocketAddress<ProtocolT> &address) const;
  inline Int32 Accept(string &ip, PortType &port) const;

  // socket 为引用类型，在函数体内被赋值为Accept返回的Socket对象
  inline Int32 Accept(Socket &socket) const;
  inline Int32 Accept(SocketAddress<ProtocolT> &address, Socket &socket) const;
  inline Int32 Accept(string &ip, PortType &port, Socket &socket) const;

  inline void Close() const;

  inline Int32 Shutdown(ShutdownType shutdown_type) const;
  inline Int32 ShutdownRead() const;
  inline Int32 ShutdownWrite() const;
  inline Int32 ShutdownBoth() const;

  inline Int32 SetNoBlock() const;
  inline Int32 UnSetNoBlock() const;

  inline Int32 SetReuseAddress() const;

  inline Int32 GetSocketOptions(int level, int options_name, void *optins_value,
                                SockLengthType *optins_length) const;

  inline Int32 SetSocketOptions(int level, int options_name,
                                const void *optins_value,
                                SockLengthType optins_length) const;
  /*  TODO: 未实现
  inline Int32 LocalAddress(SocketAddress<ProtocolT>& address);
  inline Int32 RemoteAddress(SocketAddress<ProtocolT>& address);
  */

public: // 数据传输
  inline ssize_t Recv(void *buffer, size_t buffer_size) const;
  inline ssize_t Send(const void *buffer, size_t buffer_size) const;

  /* TODO: 未实现
  inline ssize_t Recv(void* buffer, size_t buffer_size, Int32 flag);
  inline ssize_t Send(const void* buffer, size_t buffer_size, Int32 flag);

  inline ssize_t Recv();// readv实现
  inline ssize_t Send();// writev实现

  inline ssize_t Recv();// select实现recv_n()
  inline ssize_t Recv();// select实现send_n()

  inline ssize_t Recv();// UDP协议的recvfrom()
  inline ssize_t Recv();// UDP协议的sendto()
  */

private:
  static const Families kfamilies_ = ProtocolT::kfamilies_;
  static const SockType ktype_ = ProtocolT::ktype_;
  static const Protocol kprotocol_ = ProtocolT::kprotocol_;

private:
  Int32 socket_;
};

template <typename ProtocolT> 
Socket<ProtocolT>::Socket() {
}

template <typename ProtocolT> 
Socket<ProtocolT>::~Socket() {
  ::close(socket_); 
}

template <typename ProtocolT> 
Int32 Socket<ProtocolT>::Init() {
  socket_ = ::socket(kfamilies_, ktype_, kprotocol_);
  if (socket_ <= 0)
    return kNetErrorSocket;
  return 0;
}

template <typename ProtocolT> 
void Socket<ProtocolT>::set_socket(Int32 socket) {
  assert(socket >= 0);
  close(socket_);
  socket_ = socket;
}

template <typename ProtocolT> inline Int32 Socket<ProtocolT>::socket() const {
  return socket_;
}

template <typename ProtocolT>
inline Int32
Socket<ProtocolT>::Connect(const SocketAddress<ProtocolT> &address) const {
  return ::connect(socket_, address, address.AddressLength());
}

template <typename ProtocolT>
inline Int32 Socket<ProtocolT>::Connect(const string &ip, PortType port) const {
  SocketAddress<ProtocolT> address(ip, port);
  return Connect(address);
}

template <typename ProtocolT>
inline Int32
Socket<ProtocolT>::Bind(const SocketAddress<ProtocolT> &address) const {
  return ::bind(socket_, address, address.AddressLength());
}

template <typename ProtocolT>
inline Int32 Socket<ProtocolT>::Bind(const string &ip, PortType port) const {
  SocketAddress<ProtocolT> address;
  Int32 ret = Init(ip, port);
  if (ret != 0) {
    return ret;
  }
  return Bind(address);
}

template <typename ProtocolT>
inline Int32 Socket<ProtocolT>::Bind(PortType port) const {
  SocketAddress<ProtocolT> address;
  Int32 ret = Init(port);
  if (ret != 0) {
    return ret;
  }
  return Bind(address);
}

template <typename ProtocolT>
inline Int32 Socket<ProtocolT>::Listen(int backlog) const {
  return ::listen(socket_, backlog);
}

template <typename ProtocolT> inline Int32 Socket<ProtocolT>::Accept() const {
  return ::accept(socket_, nullptr, nullptr);
}

template <typename ProtocolT>
inline Int32 Socket<ProtocolT>::Accept(SocketAddress<ProtocolT> &address) const {
  typename SocketAddress<ProtocolT>::SocketAddressType socket_address;
  SockLengthType address_length;
  Int32 fd = ::accept(socket_, &socket_address, &address_length);
  if (fd != kInvalidFD)
    address.SetSocketAddress(socket_address);
  return fd;
}

template <typename ProtocolT>
inline Int32 Socket<ProtocolT>::Accept(string &ip, PortType &port) const {
  SocketAddress<ProtocolT> address;
  Int32 fd = Accept(address);
  if (fd != kInvalidFD) {
    ip = address.GetIp();
    port = address.GetPort();
  }
  return fd;
}

template <typename ProtocolT>
inline Int32 Socket<ProtocolT>::Accept(Socket &socket) const {
  Int32 fd = ::accept(socket_, NULL, NULL);
  if (fd != -1)
    socket.set_socket(fd);
  return fd;
}

template <typename ProtocolT>
inline Int32 Socket<ProtocolT>::Accept(SocketAddress<ProtocolT> &address,
                                       Socket &socket) const {
  typename SocketAddress<ProtocolT>::SocketAddressType socket_address;
  socklen_t address_length;
  Int32 fd = ::accept(socket_, &socket_address, &address_length);
  if (fd != -1) {
    address.SetSocketAddress(socket_address);
    socket.SetSocket(fd);
  }
  return fd;
}

template <typename ProtocolT>
inline Int32 Socket<ProtocolT>::Accept(string &ip, in_port_t &port,
                                       Socket &socket) const {
  SocketAddress<ProtocolT> address;
  Int32 fd = Accept(address);
  if (fd != -1) {
    socket.SetSocket(fd);
    ip = address.GetIp();
    port = address.GetPort();
  }
  return fd;
}

template <typename ProtocolT> inline void Socket<ProtocolT>::Close() const {
  ::close(socket_);
}

template <typename ProtocolT>
inline Int32 Socket<ProtocolT>::Shutdown(ShutdownType shutdown_type) const {
  return ::shutdown(socket_, shutdown_type);
}

template <typename ProtocolT>
inline Int32 Socket<ProtocolT>::ShutdownRead() const {
  return ::shutdown(socket_, kShutdownRead);
}

template <typename ProtocolT>
inline Int32 Socket<ProtocolT>::ShutdownWrite() const {
  return ::shutdown(socket_, kShutdownWrite);
}

template <typename ProtocolT>
inline Int32 Socket<ProtocolT>::ShutdownBoth() const {
  return ::shutdown(socket_, kShutdownBoth);
}

template <typename ProtocolT>
inline Int32 Socket<ProtocolT>::SetNoBlock() const {
  Int32 flags = ::fcntl(socket_, F_GETFL);
  if (flags < 0)
    return -1;
  if (::fcntl(socket_, F_SETFL, flags | O_NONBLOCK) < 0)
    return -1;
  return 0;
}

template <typename ProtocolT>
inline Int32 Socket<ProtocolT>::UnSetNoBlock() const {
  Int32 flags = ::fcntl(socket_, F_GETFL);
  if (flags < 0)
    return -1;
  if (::fcntl(socket_, F_SETFL, flags & (~O_NONBLOCK)) < 0)
    return -1;
  return 0;
}

template <typename ProtocolT>
inline Int32 Socket<ProtocolT>::SetReuseAddress() const {
  Int32 optins_value = 1;
  return SetSocketOptions(SOL_SOCKET, SO_REUSEADDR, &optins_value,
                          sizeof(optins_value));
}

template <typename ProtocolT>
inline Int32
Socket<ProtocolT>::GetSocketOptions(int level, int options_name,
                                    void *optins_value,
                                    socklen_t *optins_length) const {
  return ::getsockopt(socket_, level, options_name, optins_value, optins_length);
}

template <typename ProtocolT>
inline Int32
Socket<ProtocolT>::SetSocketOptions(int level, int options_name,
                                    const void *optins_value,
                                    socklen_t optins_length) const {
  return ::setsockopt(socket_, level, options_name, optins_value, optins_length);
}

template <typename ProtocolT>
inline ssize_t Socket<ProtocolT>::Recv(void *buffer, size_t buffer_size) const {
  return ::read(socket_, buffer, buffer_size);
}

template <typename ProtocolT>
inline ssize_t Socket<ProtocolT>::Send(const void *buffer,
                                       size_t buffer_size) const {
  return ::write(socket_, buffer, buffer_size);
}

} // namespace Water

#endif // NET_SOCKET_H_
