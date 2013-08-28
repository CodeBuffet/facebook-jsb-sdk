#ifndef  __INTERFACE_FACEBOOK_H_
#define  __INTERFACE_FACEBOOK_H_

#include "string"

class FacebookInterface
{
public:
    FacebookInterface();
    
    ~FacebookInterface();
    
    static FacebookInterface * shareFacebookInterface();
	static void login(int cbIndex,const char* scope);
    static bool logInFacebookCallBack(int cbIndex,const char*  logInfo);
	static const char * logout(int cbIndex);
	static const char * getLoginStatus(int cbIndex,bool force);
	static void api(const char* graphPath,const char* method,const char* params,int cbIndex);
    static void apiCallBack(int cbIndex,const char* JsonString);
	static void ui(const char* params,int cbIndex);
    static void uiCallBack(int  cbIndex,const char * result);
    static void WebDialogsCallBack(const char *  resultURL,int result);
    static void webDialogsWillPresentDialog(const char *dialog,const char *parameters,const char  *session);
    static void webDialogsWillDismissDialog(const char *dialog,const char *parameters,const char  *session,int result,const char  *url);
    
    //for callback
    static void callbackJs(int cbIndex, const char* params);
};

#endif  //__INTERFACE_FACEBOOK_H_