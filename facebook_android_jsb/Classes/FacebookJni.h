#ifndef  _JNI_FACEBOOK_H_
#define  _JNI_FACEBOOK_H_

#include "string"

class FacebookJni
{
public:
	static void login(int cbIndex,const char* scope);
	static void logout(int cbIndex);
	static void getLoginStatus(int cbIndex,bool force);
	static std::string api(const char* graphPath,const char* method,const char* params,int cbIndex);
	static void ui(const char* params,int cbIndex);

private:
	FacebookJni();
};

#endif  //_JNI_FACEBOOK_H_