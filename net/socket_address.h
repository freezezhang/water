/*
 * socket_address.h
 *
 * Created on: 2011-5-17
 * Author: freezezdj
 */

#ifndef NET_SOCKET_ADDRESS_H_
#define NET_SOCKET_ADDRESS_H_

#include "net/net_types.h"
#include "net/protocol_types.h"
#include "net/net_exception.h"

namespace Water {

template <typename ProtocolT>
class SocketAddress {
 public:
	typedef typename ProtocolT::SocketAddressType SocketAddressType;

 public:
	SocketAddress();
	explicit SocketAddress(in_port_t port);
	SocketAddress(const string& ip, in_port_t port) throw (BadAddress);
	SocketAddress(const SocketAddressType& socket_address);
	virtual ~SocketAddress();

 public:
	inline operator sockaddr*() const;

	inline SocketAddress& operator=(
			const SocketAddressType& socket_address);

	inline bool operator==(const SocketAddressType& other) const;
	inline bool operator!=(const SocketAddressType& other) const;
	inline bool operator==(const SocketAddress& other) const;
	inline bool operator!=(const SocketAddress& other) const;

	inline void SetSocketAddress(
			const SocketAddressType& socket_address);

	inline sockaddr* GetSocketAddress() const;

	inline size_t AddressLength() const;

	inline int SetIp(const string& ip);
	inline void SetPort(in_port_t port);
	inline string GetIp() const;
	inline in_port_t GetPort() const;

 private:
 	ProtocolT protocol_;
};

template <typename ProtocolT>
inline bool operator==(
		const typename ProtocolT::SocketAddressType& socket_address1,
		const SocketAddress<ProtocolT>& socket_address2);

template <typename ProtocolT>
inline bool operator!=(
		const typename ProtocolT::SocketAddressType& socket_address1,
		const SocketAddress<ProtocolT>& socket_address2);


} // namespace Water

#include "socket_address-inl.h"

#endif // NET_SOCKET_ADDRESS_H_
