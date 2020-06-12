#include "user.h"

namespace Water {

User::User() throw(BadUser) {
	passwd_ = getpwuid(getuid());
	if (passwd_ == NULL) {
		throw BadUser("User construct failure!");
	}
}

User::User(uid_t user_id) throw(BadUser) {
	passwd_ = getpwuid(user_id);
	if (passwd_ == NULL) {
		throw BadUser("User construct failure,"
				" User ID may not exist!");
	}
}

User::User(const string& user_name) throw(BadUser) {
	passwd_ = getpwnam(user_name.c_str());
	if (passwd_ == NULL) {
		throw BadUser("User construct failure,"
				" User name may not exist!");
	}
}

User::~User() {

}

} // namespace Water
