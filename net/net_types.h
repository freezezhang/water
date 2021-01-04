/*
 * net_types.h
 *
 * Created on: 2011-5-17
 * Author: freezezhang
 */

#ifndef NET_NET_TYPES_H_
#define NET_NET_TYPES_H_

#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/stat.h>

#include <cstring>

#include <string>
using std::string;

#include "time/time_value.h"
#include "water_types.h"

namespace Water {

typedef in_port_t PortType;
typedef socklen_t SockLengthType;
typedef Uint64 TimerType;

const int kBackLog = 100;
const int kMaxIpString = 128;

const int kDefaultEventListSize = 128;

const int kInvalidFD = -1;

const TimeValue kEventMaxTimeout(30 * 60, 0);


enum ShutdownType {
  kShutdownRead = SHUT_RD,
  kShutdownWrite = SHUT_WR,
  kShutdownBoth = SHUT_RDWR,
};

enum Families {
  kLocal = AF_LOCAL,
  kIPv4 = AF_INET,
  kIPv6 = AF_INET6,
  kRoute = AF_ROUTE,
  kKey = AF_KEY,
};

enum SockType {
  kStream = SOCK_STREAM,
  kDgram = SOCK_DGRAM,
  kSequenced = SOCK_SEQPACKET,
  kRAW = SOCK_RAW,
};

enum Protocol { 
  kTCP = IPPROTO_TCP, 
  kUDP = IPPROTO_UDP, 
  kSCTP = IPPROTO_SCTP,
};

enum ReactorEvent {
  kEventInput = 0x01,
  kEventOutput = 0x02,
  kEventTimeout = 0x04,
  kEventException = 0x08,
  // kEventSignal = 0x10
};

enum EventPriority {
  kLowPriority = 10,
  kNormalPriority = 20,
  kHighProiority = 30,
};

} // namespace Water

#endif // NET_NET_TYPES_H_
