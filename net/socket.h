/*
 * socket.h
 *
 * Created on: 2011-5-18
 * Author: freezezdj
 */

#ifndef NET_SOCKET_H_
#define NET_SOCKET_H_

#include <fcntl.h>
#include <assert.h>
#include <unistd.h>

#include "net/net_types.h"
#include "net/net_exception.h"
#include "net/socket_address.h"

namespace Water {

template <typename ProtocolT>
class Socket {
 public:
	Socket() throw (BadSocket);
	explicit Socket(int socket) throw (BadSocket);
	Socket(const Socket& other);
	virtual ~Socket();

 public:
	inline Socket& operator=(const Socket& other);

 public:
	inline int GetSocket() const;
	inline void SetSocket(int socket);

 public: // socket API
	inline int Connect(const SocketAddress<ProtocolT>& address) const;
	inline int Connect(const string& ip, in_port_t port) const;

	inline int Bind(const SocketAddress<ProtocolT>& address) const;
	inline int Bind(const string& ip, in_port_t port) const;
	inline int Bind(in_port_t port) const;

	inline int Listen(int backlog = kBackLog) const;

	inline int Accept() const;
	inline int Accept(SocketAddress<ProtocolT>& address) const;
	inline int Accept(string& ip, in_port_t& port) const;

	// socket 为引用类型，在函数体内被赋值为Accept返回的Socket对象
	inline int Accept(Socket& socket) const;
	inline int Accept(SocketAddress<ProtocolT>& address,
	                  Socket& socket) const;
	inline int Accept(string& ip,
	                  in_port_t& port,
	                  Socket& socket) const;

	inline void Close() const;

	inline int Shutdown(ShutdownType shutdown_type) const;
	inline int ShutdownRead() const;
	inline int ShutdownWrite() const;
	inline int ShutdownBoth() const;

	inline int SetNoBlock() const;
	inline int UnSetNoBlock() const;

	inline int SetReuseAddress() const;

	inline int GetSocketOptions(int level,
	                            int options_name,
	                            void* optins_value,
	                            socklen_t *optins_length) const;

	inline int SetSocketOptions(int level,
	                            int options_name,
	                            const void* optins_value,
	                            socklen_t optins_length) const;
/*	TODO: 未实现
	inline int LocalAddress(SocketAddress<ProtocolT>& address);
	inline int RemoteAddress(SocketAddress<ProtocolT>& address);

*/

public:	// 数据传输
	inline ssize_t Recv(void* buffer, size_t buffer_size) const;
	inline ssize_t Send(const void* buffer, size_t buffer_size) const;

/* TODO: 未实现
	inline ssize_t Recv(void* buffer, size_t buffer_size, int flag);
	inline ssize_t Send(const void* buffer, size_t buffer_size, int flag);

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
	int socket_;
};

} // namespace Water

#include "socket-inl.h"

#endif // NET_SOCKET_H_
