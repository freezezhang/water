/*
 * group.h
 *
 * Created on: 2011-3-16
 * Author: freezezdj
 */

#ifndef SYSTEM_INFO_GROUP_H_
#define SYSTEM_INFO_GROUP_H_

#include <grp.h>
#include <unistd.h>

#include <string>
using std::string;

#include <vector>
using std::vector;

#include "system_info/system_info_exception.h"

namespace Water {

//TODO: Group 未测试

class Group {
public:
	Group() throw(BadGroup);
	explicit Group(gid_t group_id) throw(BadGroup);
	explicit Group(const string& group_name) throw(BadGroup);

	virtual ~Group();

public:
	inline string GetGroupName() const;
	inline gid_t GetGropuID() const;
	inline string GetPassword() const;
	const vector<string>& GetMemberList();

private:
	group* group_;
	vector<string> member_list_;
};

} // namespace Water

#include "group-inl.h"

#endif // SYSTEM_INFO_GROUP_H_
