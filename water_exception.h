/*
 * water_exception.h
 *
 * Created on: 2011-2-28
 * Author: freezezdj
 */

#ifndef WATER_EXCEPTION_H_
#define WATER_EXCEPTION_H_

#include <exception>
#include <string>
using std::string;

namespace Water {

class WaterException : public std::exception {
 public:
	WaterException() throw() {}
	virtual ~WaterException() throw() {};

 public:
	virtual const char* what() const throw() {
		return "Water Exception!";
	}
};

} // namespace Water

#endif // WATER_EXCEPTION_H_
