//
//  FacebookIosInterface.cpp
//  tojs
//
//  Created by lyy on 13-8-20.
//
//

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)

#include "FacebookInterface.h"
#include "CCUIKit.h"
#include "ScriptingCore.h"
using namespace std;

static FacebookInterface * g_FacebookInterface = NULL;

extern jsval anonEvaluate(JSContext *cx, JSObject *thisObj, const char* string);
JSObject *fbObject = NULL;
void FacebookInterface::callbackJs(int cbIndex, const char* params)
{
	ScriptingCore* sc = ScriptingCore::getInstance();
	JSContext *cx = sc->getGlobalContext();
	
	if (fbObject == NULL)
		fbObject = JSVAL_TO_OBJECT(anonEvaluate(cx, sc->getGlobalObject(), "(function () { return FB; })()"));
	
	jsval res;
	
	if (params != NULL)
	{
		jsval argv[2];
		argv[0] = INT_TO_JSVAL(cbIndex);
		std::string tstr = params;
		argv[1] = std_string_to_jsval(cx,tstr);
        
		JS_CallFunctionName(cx, fbObject, "callback", 2, argv, &res);
	}
	else
	{
		jsval argv[1];
		argv[0] = INT_TO_JSVAL(cbIndex);
        
		JS_CallFunctionName(cx, fbObject, "callback", 1, argv, &res);
	}
}
FacebookInterface::FacebookInterface()
{
    ;
}
FacebookInterface::~FacebookInterface()
{
    ;
}
FacebookInterface * FacebookInterface::shareFacebookInterface()
{
    if (!g_FacebookInterface)
    {
        g_FacebookInterface = new FacebookInterface();
    }
    return g_FacebookInterface;
}

void FacebookInterface::login(int cbIndex,const char* scope)
{
	CCUIKit::shareCCUIKit()->logInFacebook(cbIndex,scope);
}
bool FacebookInterface::logInFacebookCallBack(int cbIndex,const char*  logInfo)
{
    callbackJs(cbIndex,logInfo);
    return true;
}
const char * FacebookInterface::logout(int cbIndex)
{
    callbackJs(cbIndex, CCUIKit::shareCCUIKit()->logOutFacebook(cbIndex));
	return CCUIKit::shareCCUIKit()->logOutFacebook(cbIndex);
}

const char * FacebookInterface::getLoginStatus(int cbIndex, bool force)
{
    callbackJs(cbIndex, CCUIKit::shareCCUIKit()->getActiveSessionState(cbIndex,force));
	return CCUIKit::shareCCUIKit()->getActiveSessionState(cbIndex,force);
}

void FacebookInterface::api(const char* graphPath,const char* method,const char* params,int cbIndex)
{
	 CCUIKit::shareCCUIKit()->requestWithGraphPath(graphPath, method, params,cbIndex);
}
void FacebookInterface::apiCallBack(int cbIndex,const char* JsonString)
{
    callbackJs(cbIndex, JsonString);
}
void FacebookInterface::ui(const char* params,int cbIndex)
{
    CCUIKit::shareCCUIKit()->ui(params, cbIndex);
}
void FacebookInterface::uiCallBack(int  cbIndex,const char * result)
{
    callbackJs(cbIndex,result);
}
void FacebookInterface::WebDialogsCallBack(const char *  resultURL,int result)
{
    ;
}
void FacebookInterface::webDialogsWillPresentDialog(const char *dialog,const char *parameters,const char  *session)
{
    ;
}
void FacebookInterface::webDialogsWillDismissDialog(const char *dialog,const char *parameters,const char  *session,int result,const char  *url)
{

}
#endif