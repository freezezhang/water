/*
 * handler.h
 *
 * Created on: 2020-8-29
 * Author: freezezhang
 */

#ifndef NET_NET_ERROR_H_ 
#define NET_NET_ERROR_H_ 

namespace Water {

enum NetError {
  kNetErrorSocket,
  kNetErrorMakeHadler,
  kNetErrorEpollCreate,
};

} // namespace Water

#endif // NET_NET_ERROR_H_ 