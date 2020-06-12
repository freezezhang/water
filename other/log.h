/*
 * log.h
 *
 *  Created on: 2012-11-8
 *      Author: zdj
 */

#ifndef LOG_H_
#define LOG_H_

#include "stream.h"
/*
class LogStream : public StringStream {
 public:
   LogStream& operator<<(Log::Time value);
};
*/
class Log {
 public:
   enum Level {
     kError,
   };

   enum ShowType {
     kStartType = 1,
     kTime = kStartType << 0,
     kServer = kStartType << 1, 
     kLevel = kStartType << 2,
     kLog = kStartType << 3,
   };

   class Time {};
  
 public:
   Log(Level level);
   ~Log();

  inline void set_level(Level level);
  inline StringStream& stream();

 private:
  Log(const Log&);
  Log& operator=(const Log&);

 private:
  Buffer stream_buffer_;
  StringStream stream_;
  Level level_;
  Uint8 show_set_;

public:
  static Buffer buffer_; 
};

inline StringStream& Log::stream() {
  return stream_;
}

inline void Log::set_level(Level level) {
  level_ = level;
}

#define LOG_ERROR Log(Log::kError).stream()

#endif // LOG_H_