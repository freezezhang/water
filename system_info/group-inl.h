#ifndef SYSTEM_INFO_GROUP_INL_H_
#define SYSTEM_INFO_GROUP_INL_H_

namespace Water {

inline string Group::GetGroupName() const {
	return group_->gr_name;
}

inline gid_t Group::GetGropuID() const {
	return group_->gr_gid;
}

inline string Group::GetPassword() const {
	return group_->gr_passwd;
}

} // namespace Water

#endif // SYSTEM_INFO_GROUP_INL_H_
