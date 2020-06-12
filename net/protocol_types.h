/*
 * protocol_types.h
 *
 * Created on: 2011-6-10
 * Author: freezezdj
 */

#ifndef NET_PROTOCOL_TYPES_H_
#define NET_PROTOCOL_TYPES_H_

#include "net/net_types.h"

namespace Water {

class ProtocolType {
 public:
	typedef sockaddr SocketAddressType;

	virtual void SetSocketAddress(
			const SocketAddressType& socket_address) = 0;

	virtual int SetIp(const string& ip) = 0;
	virtual void SetPort(in_port_t port) = 0;
	virtual sockaddr* GetSocketAddress() const = 0;
	virtual size_t AddressLength() const = 0;
	virtual string GetIp() const = 0;
	virtual in_port_t GetPort() const = 0;
};

class IPV4_TCP : public ProtocolType {
 public:
	IPV4_TCP() {
		bzero(&address_, sizeof(address_));
		address_.sin_family = kfamilies_;
		address_.sin_addr.s_addr = htonl(INADDR_ANY);
		address_.sin_port = htons(0);
	}

 public:
	virtual void SetSocketAddress(
			const SocketAddressType& socket_address) {
		memcpy(&address_, &socket_address, sizeof(socket_address));
	}

	virtual int SetIp(const string& ip = "") {
		if (ip.empty()) {
			address_.sin_addr.s_addr = htonl(INADDR_ANY);
			return 0;
		} else {
			if (inet_pton(kfamilies_, ip.c_str(), &address_.sin_addr) == 1)
				return 0;
		}
		return -1;
	}

	virtual void SetPort(in_port_t port) {
		address_.sin_port = htons(port);
	}

	virtual sockaddr* GetSocketAddress() const {
		return (sockaddr*)(&address_);
	}

	virtual size_t AddressLength() const {
		return sizeof(address_);
	}

	virtual string GetIp() const {
		char ip[kMaxIpString];
		if (inet_ntop(kfamilies_, &address_.sin_addr, ip,
				kMaxIpString) != 0) {
			return ip;
		} else {
			return "";
		}
	}

	virtual in_port_t GetPort() const {
		return address_.sin_port;
	}

 public:
	typedef sockaddr_in SocketAddressType;

 public:
	static const Families kfamilies_ = kIPv4;
	static const SockType ktype_ = kStream;
	static const Protocol kprotocol_ = kTCP;

 private:
	SocketAddressType address_;
};

class IPV6_TCP : public ProtocolType {
public:
	IPV6_TCP() {
		bzero(&address_, sizeof(address_));
		address_.sin6_family = kfamilies_;
		address_.sin6_addr = in6addr_any;
		address_.sin6_port = htons(0);
	}

public:
	virtual void SetSocketAddress(
			const SocketAddressType& socket_address) {
		memcpy(&address_, &socket_address, sizeof(socket_address));
	}

	virtual int SetIp(const string& ip = "") {
		if (ip.empty()) {
			address_.sin6_addr = in6addr_any;
		} else {
			return inet_pton(kfamilies_, ip.c_str(), &address_.sin6_addr);
		}
		return 0;
	}

	virtual void SetPort(in_port_t port) {
		address_.sin6_port = htons(port);
	}

	virtual sockaddr* GetSocketAddress() const {
		return (sockaddr*)(&address_);
	}

	virtual size_t AddressLength() const {
			return sizeof(address_);
	}

	virtual string GetIp() const {
		char ip[kMaxIpString];
		if (inet_ntop(kfamilies_, &address_.sin6_addr, ip,
				kMaxIpString) != 0) {
			return ip;
		} else {
			return "";
		}
	}

	virtual in_port_t GetPort() const {
		return address_.sin6_port;
	}

 public:
	typedef sockaddr_in6 SocketAddressType;

	static const Families kfamilies_ = kIPv6;
	static const SockType ktype_ = kStream;
	static const Protocol kprotocol_ = kTCP;

 private:
	SocketAddressType address_;
};

} // namespace Water
#endif // NET_PROTOCOL_TYPES_H_
