#include "group.h"

namespace Water {

Group::Group() throw(BadGroup) {
	group_ = getgrgid(getgid());
	if (group_ == NULL) {
		throw BadGroup("Group construct failure!");
	}
}

Group::Group(gid_t group_id) throw(BadGroup) {
	group_ = getgrgid(group_id);
	if (group_ == NULL) {
		throw BadGroup("Group construct failure,"
				" Group ID may not exist!");
	}
}

Group::Group(const string& group_name) throw(BadGroup) {
	group_ = getgrnam(group_name.c_str());
	if (group_ == NULL) {
		throw BadGroup("Group construct failure,"
				" Group name may not exist!");
	}
}


Group::~Group() {

}

const vector<string>& Group::GetMemberList() {
	member_list_.clear();
	char** member_list = group_->gr_mem;
	while (*member_list != NULL) {
		member_list_.push_back(*member_list);
		++(member_list);
	}
	return member_list_;
}

} // namespace Water
