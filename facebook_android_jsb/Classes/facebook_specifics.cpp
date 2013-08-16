#include "ScriptingCore.h"
#include "FacebookJni.h"

JSBool JSB_Facebook_login(JSContext *cx, uint32_t argc, jsval *vp){
	int cbIndex;
	JSString * str = NULL;
	
	if (argc == 1)
		JS_ConvertArguments(cx,1,JS_ARGV(cx,vp),"i",&cbIndex);
	else
		JS_ConvertArguments(cx,2,JS_ARGV(cx,vp),"iS",&cbIndex,&str);
	
	if (str)
	{
		JSStringWrapper wrapper(str);
		FacebookJni::login(cbIndex,wrapper);
	} 
	else
		FacebookJni::login(cbIndex,NULL);

	return JS_TRUE;
}

JSBool JSB_Facebook_logout(JSContext *cx, uint32_t argc, jsval *vp){
	int cbIndex;

	JS_ConvertArguments(cx,1,JS_ARGV(cx,vp),"i",&cbIndex);
	
	FacebookJni::logout(cbIndex);

	return JS_TRUE;
}

JSBool JSB_Facebook_getLoginStatus(JSContext *cx, uint32_t argc, jsval *vp){
	int cbIndex;
	bool force;

	JS_ConvertArguments(cx,2,JS_ARGV(cx,vp),"ib",&cbIndex,&force);

  CCLog("cpp-cbindex:%d",cbIndex); 
	FacebookJni::getLoginStatus(cbIndex,force);

	return JS_TRUE;
}

JSBool JSB_Facebook_api(JSContext *cx, uint32_t argc, jsval *vp){
	std::string graphPath ;
	std::string method ;
	std::string params ;
	std::string errorRet;
	int cbIndex;

	jsval *argv = JS_ARGV(cx, vp);	
	jsval_to_std_string(cx, argv[0], &graphPath);

	switch (argc)
	{
	case 2:
		{			
			cbIndex = JSVAL_TO_INT(argv[1]);
			errorRet = FacebookJni::api(graphPath.c_str(),NULL,NULL,cbIndex);
			break;
		}		
	case 3:
		{			
			jsval_to_std_string(cx, argv[1], &params);
			cbIndex = JSVAL_TO_INT(argv[2]);
			errorRet = FacebookJni::api(graphPath.c_str(),NULL,params.c_str(),cbIndex);
			break;
		}		
	case 4:
		{			
			jsval_to_std_string(cx, argv[1], &method);
			jsval_to_std_string(cx, argv[2], &params);
			cbIndex = JSVAL_TO_INT(argv[3]);			
			errorRet = FacebookJni::api(graphPath.c_str(),method.c_str(),params.c_str(),cbIndex);
			break;
		}		
	default:
		return JS_FALSE;
		break;
	}
	

	if (errorRet.length() > 0)
		JS_SET_RVAL(cx, vp, std_string_to_jsval(cx,errorRet));
	else
		JS_SET_RVAL(cx, vp, JSVAL_VOID);

	return JS_TRUE;
}

JSBool JSB_Facebook_ui(JSContext *cx, uint32_t argc, jsval *vp){
	std::string params ;
	int cbIndex;

	jsval *argv = JS_ARGV(cx, vp);
	jsval_to_std_string(cx, argv[0], &params);
	cbIndex = JSVAL_TO_INT(argv[1]);

	FacebookJni::ui(params.c_str(),cbIndex);

	return JS_TRUE;
}

void register_facebook_js(JSContext* cx, JSObject* global){
	jsval nsval;
	JSObject *facebookObject;

	JS_GetProperty(cx, global, "Facebook", &nsval);
	if (nsval == JSVAL_VOID) {
		facebookObject = JS_NewObject(cx, NULL, NULL, NULL);
		nsval = OBJECT_TO_JSVAL(facebookObject);
		JS_SetProperty(cx, global, "Facebook", &nsval);
	} else 
		JS_ValueToObject(cx, nsval, &facebookObject);

	JS_DefineFunction(cx, facebookObject, "login", JSB_Facebook_login, 2, JSPROP_READONLY | JSPROP_PERMANENT);
	JS_DefineFunction(cx, facebookObject, "logout", JSB_Facebook_logout, 1, JSPROP_READONLY | JSPROP_PERMANENT);
	JS_DefineFunction(cx, facebookObject, "getLoginStatus", JSB_Facebook_getLoginStatus, 2, JSPROP_READONLY | JSPROP_PERMANENT);
	JS_DefineFunction(cx, facebookObject, "api", JSB_Facebook_api, 4, JSPROP_READONLY | JSPROP_PERMANENT);
	JS_DefineFunction(cx, facebookObject, "ui", JSB_Facebook_ui, 2, JSPROP_READONLY | JSPROP_PERMANENT);
}