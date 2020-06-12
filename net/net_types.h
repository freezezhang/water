/*
 * net_types.h
 *
 * Created on: 2011-5-17
 * Author: freezezdj
 */

#ifndef NET_NET_TYPES_H_
#define NET_NET_TYPES_H_

#include <sys/stat.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#include <cstring>

#include <string>
using std::string;

#include "water_types.h"
#include "time/time_value.h"

namespace Water {

const int kBackLog = 100;
const int kMaxIpString = 128;

const int kDefaultEventListSize = 128;

const TimeValue kEventMaxTimeout(30 * 60, 0);

typedef int64 TimerID;

enum ShutdownType {
	kShutdownRead = SHUT_RD,
	kShutdownWrite = SHUT_WR,
	kShutdownBoth = SHUT_RDWR
};

enum Families {
	kLocal = AF_LOCAL,
	kIPv4 = AF_INET,
	kIPv6 = AF_INET6,
	kRoute = AF_ROUTE,
	kKey = AF_KEY
};

enum SockType {
	kStream = SOCK_STREAM,
	kDgram = SOCK_DGRAM,
	kSequenced = SOCK_SEQPACKET,
	kRAW = SOCK_RAW
};

enum Protocol {
	kTCP = IPPROTO_TCP,
	kUDP = IPPROTO_UDP,
	kSCTP = IPPROTO_SCTP
};

enum ReactorEvent {
	kEventInput = 0x01,
	kEventOutput = 0x02,
	kEventTimeout = 0x04,
	kEventException = 0x08,
	//kEventSignal = 0x10
};

enum EventPriority {
	kLowPriority = 10,
	kNormalPriority = 20,
	kHighProiority = 30
};

}	//namespace Water

#endif // NET_NET_TYPES_H_
