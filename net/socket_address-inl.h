#ifndef NET_SOCKET_ADDRESS_INL_H_
#define NET_SOCKET_ADDRESS_INL_H_

namespace Water {

template <typename ProtocolT>
SocketAddress<ProtocolT>::SocketAddress() {

}

template <typename ProtocolT>
SocketAddress<ProtocolT>::SocketAddress(in_port_t port) {
	SetPort(port);
}

template <typename ProtocolT>
SocketAddress<ProtocolT>::SocketAddress(const string& ip,
		in_port_t port) throw (BadAddress) {
	SetPort(port);
	if (SetIp(ip) != 0) {
		throw BadAddress("SocketAddreess Construction Failure!");
	}
}

template <typename ProtocolT>
SocketAddress<ProtocolT>::SocketAddress(
		const SocketAddressType& socket_address) {
	SetSocketAddress(socket_address);
}

template <typename ProtocolT>
SocketAddress<ProtocolT>::~SocketAddress() {

}

template <typename ProtocolT>
inline SocketAddress<ProtocolT>& SocketAddress<ProtocolT>::operator=(
		const SocketAddressType& socket_address) {
	protocol_.SetSocketAddress(socket_address);
	return *this;
}

template <typename ProtocolT>
inline SocketAddress<ProtocolT>::operator sockaddr*() const {
	return GetSocketAddress();
}

template <typename ProtocolT>
inline bool SocketAddress<ProtocolT>::operator==(
		const SocketAddressType& other) const {
	if (memcmp(*this, &other, AddressLength()) == 0) return true;
	return false;
}

template <typename ProtocolT>
inline bool SocketAddress<ProtocolT>::operator!=(
		const SocketAddressType& other) const {
	return !(*this == SocketAddress(other));
}

template <typename ProtocolT>
inline bool SocketAddress<ProtocolT>::operator==(
		const SocketAddress& other) const {
	if (memcmp(*this, other, AddressLength()) == 0)
		return true;
	return false;
}

template <typename ProtocolT>
inline bool SocketAddress<ProtocolT>::operator!=(
		const SocketAddress& other) const {
	return !(*this == other);
}

template <typename ProtocolT>
inline void SocketAddress<ProtocolT>::SetSocketAddress(
			const SocketAddressType& socket_address) {
	protocol_.SetSocketAddress(socket_address);
}

template <typename ProtocolT>
inline sockaddr* SocketAddress<ProtocolT>::GetSocketAddress() const {
	return protocol_.GetSocketAddress();
}

template <typename ProtocolT>
inline size_t SocketAddress<ProtocolT>::AddressLength() const {
	return protocol_.AddressLength();
}

template <typename ProtocolT>
inline int SocketAddress<ProtocolT>::SetIp(const string& ip) {
	return protocol_.SetIp(ip);
}

template <typename ProtocolT>
inline void SocketAddress<ProtocolT>::SetPort(in_port_t port) {
	assert(port > 0);
	protocol_.SetPort(port);
}

template <typename ProtocolT>
inline string SocketAddress<ProtocolT>::GetIp() const {
	return protocol_.GetIp();
}

template <typename ProtocolT>
inline in_port_t SocketAddress<ProtocolT>::GetPort() const {
	return protocol_.GetPort();
}

template <typename ProtocolT>
inline bool operator==(
		const typename ProtocolT::SocketAddressType& address1,
		const SocketAddress<ProtocolT>& address2) {
	return address2 == address1;
}

template <typename ProtocolT>
inline bool operator!=(
		const typename ProtocolT::SocketAddressType& address1,
		const SocketAddress<ProtocolT>& address2) {
	return address2 != address1;
}

} // namespace Water

#endif // NET_SOCKET_ADDRESS_INL_H_
