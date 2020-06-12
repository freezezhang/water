#ifndef NET_SOCKET_INL_H_
#define NET_SOCKET_INL_H_

namespace Water {

template<typename ProtocolT>
Socket<ProtocolT>::Socket() throw (BadSocket) {
	if ((socket_ = socket(kfamilies_, ktype_, kprotocol_)) == -1) {
		throw BadSocket(errno);
	}
}

template<typename ProtocolT>
Socket<ProtocolT>::Socket(int socket) throw (BadSocket) :
	socket_(socket) {
	assert(socket >= 0);
	if (socket_ < 0) {
		throw BadSocket("socket < 0");
	}
}

template<typename ProtocolT>
Socket<ProtocolT>::Socket(const Socket& other) {
	close(socket_);
	socket_ = other.GetSocket();
}

template<typename ProtocolT>
Socket<ProtocolT>::~Socket() {
	close(socket_);
}

template<typename ProtocolT>
inline Socket<ProtocolT>& Socket<ProtocolT>::operator=(
		const Socket& other) {
	close(socket_);
	socket_ = other.GetSocket();
	return *this;
}

template<typename ProtocolT>
inline int Socket<ProtocolT>::GetSocket() const {
	return socket_;
}

template<typename ProtocolT>
inline void Socket<ProtocolT>::SetSocket(int socket) {
	assert(socket >= 0);
	close(socket_);
	socket_ = socket;
}

template<typename ProtocolT>
inline int Socket<ProtocolT>::Connect(
		const SocketAddress<ProtocolT>& address) const {
	return connect(socket_, address, address.AddressLength());
}

template<typename ProtocolT>
inline int Socket<ProtocolT>::Connect(const string& ip,
		in_port_t port) const {
	try {
		SocketAddress<ProtocolT> address(ip, port);
		return connect(socket_, address, address.AddressLength());
	} catch (BadAddress&) {
		return -1;
	}
}

template<typename ProtocolT>
inline int Socket<ProtocolT>::Bind(
		const SocketAddress<ProtocolT>& address) const {
	return bind(socket_, address, address.AddressLength());
}

template<typename ProtocolT>
inline int Socket<ProtocolT>::Bind(const string& ip,
		in_port_t port) const {
	try {
		SocketAddress<ProtocolT> address(ip, port);
		return bind(socket_, address, address.AddressLength());
	} catch (BadAddress&) {
		return -1;
	}
}

template<typename ProtocolT>
inline int Socket<ProtocolT>::Bind(in_port_t port) const {
	SocketAddress<ProtocolT> address(port);
	return bind(socket_, address, address.AddressLength());
}

template<typename ProtocolT>
inline int Socket<ProtocolT>::Listen(int backlog) const {
	return listen(socket_, backlog);
}

template<typename ProtocolT>
inline int Socket<ProtocolT>::Accept() const {
	return accept(socket_, NULL, NULL);
}

template<typename ProtocolT>
inline int Socket<ProtocolT>::Accept(
		SocketAddress<ProtocolT>& address) const {
	typename SocketAddress<ProtocolT>::SocketAddressType socket_address;
	socklen_t address_length;
	int fd = accept(socket_, &socket_address, &address_length);
	if (fd != -1) address.SetSocketAddress(socket_address);
	return fd;
}

template<typename ProtocolT>
inline int Socket<ProtocolT>::Accept(string& ip,
		in_port_t& port) const {
	SocketAddress<ProtocolT> address;
	int fd = Accept(address);
	if (fd != -1) {
		ip = address.GetIp();
		port = address.GetPort();
	}
	return fd;
}

template<typename ProtocolT>
inline int Socket<ProtocolT>::Accept(Socket& socket) const {
	int fd = accept(socket_, NULL, NULL);
	if (fd != -1) socket.SetSocket(fd);
	return fd;
}

template<typename ProtocolT>
inline int Socket<ProtocolT>::Accept(
		SocketAddress<ProtocolT>& address,
		Socket& socket) const {
	typename SocketAddress<ProtocolT>::SocketAddressType socket_address;
	socklen_t address_length;
	int fd = accept(socket_, &socket_address, &address_length);
	if (fd != -1) {
		address.SetSocketAddress(socket_address);
		socket.SetSocket(fd);
	}
	return fd;
}

template<typename ProtocolT>
inline int Socket<ProtocolT>::Accept(string& ip,
		in_port_t& port,
		Socket& socket) const {
	SocketAddress<ProtocolT> address;
	int fd = Accept(address);
	if (fd != -1) {
		socket.SetSocket(fd);
		ip = address.GetIp();
		port = address.GetPort();
	}
	return fd;
}

template<typename ProtocolT>
inline void Socket<ProtocolT>::Close() const {
	close(socket_);
}

template<typename ProtocolT>
inline int Socket<ProtocolT>::Shutdown(
		ShutdownType shutdown_type) const {
	return shutdown(socket_, shutdown_type);
}

template<typename ProtocolT>
inline int Socket<ProtocolT>::ShutdownRead() const {
	return shutdown(socket_, kShutdownRead);
}

template<typename ProtocolT>
inline int Socket<ProtocolT>::ShutdownWrite() const {
	return shutdown(socket_, kShutdownWrite);
}

template<typename ProtocolT>
inline int Socket<ProtocolT>::ShutdownBoth() const {
	return shutdown(socket_, kShutdownBoth);
}

template<typename ProtocolT>
inline int Socket<ProtocolT>::SetNoBlock() const {
	int flags = fcntl(socket_, F_GETFL);
	if (flags < 0) return -1;
	if (fcntl(socket_, F_SETFL, flags | O_NONBLOCK) < 0) return -1;
	return 0;
}

template<typename ProtocolT>
inline int Socket<ProtocolT>::UnSetNoBlock() const {
	int flags = fcntl(socket_, F_GETFL);
	if (flags < 0) return -1;
	if (fcntl(socket_, F_SETFL, flags & (~O_NONBLOCK)) < 0) return -1;
	return 0;
}

template<typename ProtocolT>
inline int Socket<ProtocolT>::SetReuseAddress() const
{
    int optins_value = 1;
    return SetSocketOptions(SOL_SOCKET, SO_REUSEADDR, &optins_value, sizeof(optins_value));
}

template<typename ProtocolT>
inline int Socket<ProtocolT>::GetSocketOptions(int level,
		int options_name,
		void* optins_value,
		socklen_t *optins_length) const {
	return getsockopt(socket_, level, options_name, optins_value,
			optins_length);
}

template<typename ProtocolT>
inline int Socket<ProtocolT>::SetSocketOptions(int level,
		int options_name,
		const void* optins_value,
		socklen_t optins_length) const {
	return setsockopt(socket_, level, options_name, optins_value,
			optins_length);
}

template<typename ProtocolT>
inline ssize_t Socket<ProtocolT>::Recv(void* buffer,
		size_t buffer_size) const {
	return read(socket_, buffer, buffer_size);
}

template<typename ProtocolT>
inline ssize_t Socket<ProtocolT>::Send(const void* buffer,
		size_t buffer_size) const {
	return write(socket_, buffer, buffer_size);
}

} // namespace Water

#endif // NET_SOCKET_INL_H_
