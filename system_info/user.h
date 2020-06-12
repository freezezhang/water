/*
 * user.h
 *
 * Created on: 2011-3-15
 * Author: freezezdj
 */

#ifndef SYSTEM_INFO_USER_H_
#define SYSTEM_INFO_USER_H_

#include <pwd.h>
#include <unistd.h>

#include <string>
using std::string;

#include "system_info/system_info_exception.h"

namespace Water {

class User {
public:
	User() throw(BadUser);
	explicit User(uid_t user_id) throw(BadUser);
	explicit User(const string& user_name) throw(BadUser);
	virtual ~User();

public:
	inline string GetUserName() const;
	inline string GetPassword() const;
	inline uid_t GetUserID() const;
	inline gid_t GetGroupID() const;
	inline string GetRealName() const;
	inline string GetHomeDirectory() const;
	inline string GetShellProgram() const;

private:
	passwd* passwd_;
};

} // namespace Water

#include "user-inl.h"

#endif // SYSTEM_INFO_USER_H_
