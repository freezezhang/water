/*
 * socket_address.h
 *
 * Created on: 2011-5-17
 * Author: freezezhang
 */

#ifndef NET_SOCKET_ADDRESS_H_
#define NET_SOCKET_ADDRESS_H_

#include "net/net_types.h"
#include "net/protocol_types.h"

namespace Water {

template <typename ProtocolT>
class SocketAddress {
 public:
  typedef typename ProtocolT::SocketAddressType SocketAddressType;

 public:
  SocketAddress();
  SocketAddress(const SocketAddressType& socket_address);
  virtual ~SocketAddress();

 public:

  Int32 Init(PortType port);
  Int32 Init(const string& ip, PortType port);

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
  inline PortType GetPort() const;

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

template <typename ProtocolT>
SocketAddress<ProtocolT>::SocketAddress() {
}

template <typename ProtocolT>
SocketAddress<ProtocolT>::SocketAddress(
    const SocketAddressType& socket_address) {
  SetSocketAddress(socket_address);
}

template <typename ProtocolT>
Int32 SocketAddress<ProtocolT>::Init(PortType port) {
  SetPort(port);
  return 0;
}

template <typename ProtocolT>
Int32 SocketAddress<ProtocolT>::Init(const string& ip, PortType port) {
  SetPort(port);
  Int32 ret = SetIp(ip);
  if (ret != 0)
    return ret;
  return 0;
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

#endif // NET_SOCKET_ADDRESS_H_
