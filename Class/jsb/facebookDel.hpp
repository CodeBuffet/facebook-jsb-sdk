#ifndef __facebookDel_h__
#define __facebookDel_h__

#include "jsapi.h"
#include "jsfriendapi.h"


extern JSClass  *jsb_FacebookKit_class;
extern JSObject *jsb_FacebookKit_prototype;

JSBool js_facebookDel_FacebookKit_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_facebookDel_FacebookKit_finalize(JSContext *cx, JSObject *obj);
void js_register_facebookDel_FacebookKit(JSContext *cx, JSObject *global);
void register_all_facebookDel(JSContext* cx, JSObject* obj);
JSBool js_facebookDel_FacebookKit_ui(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_facebookDel_FacebookKit_login(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_facebookDel_FacebookKit_api(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_facebookDel_FacebookKit_logout(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_facebookDel_FacebookKit_getLoginStatus(JSContext *cx, uint32_t argc, jsval *vp);
#endif

