#ifndef SYSTEM_INFO_USER_INL_H_
#define SYSTEM_INFO_USER_INL_H_

namespace Water {

inline string User::GetUserName() const {
	return passwd_->pw_name;
}

inline string User::GetPassword() const {
	return passwd_->pw_passwd;
}

inline uid_t User::GetUserID() const {
	return passwd_->pw_uid;
}

inline gid_t User::GetGroupID() const {
	return passwd_->pw_gid;
}

inline string User::GetRealName() const {
	return passwd_->pw_gecos;
}

inline string User::GetHomeDirectory() const {
	return passwd_->pw_dir;
}

inline string User::GetShellProgram() const {
	return passwd_->pw_shell;
}

} // namespace Water

#endif // SYSTEM_INFO_USER_INL_H_
