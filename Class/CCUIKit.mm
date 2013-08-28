//
//  CCUIKit.cpp
//  GreTest
//
//  Created by lyy on 13-7-23.
//
//

#include "CCUIKit.h"
#include "AppDelegate.h"
#include "CCUIFaceBook.h"
#include "FacebookInterface.h"

static CCUIKit * g_CCUIKit = NULL;
using namespace std;

CCUIKit::CCUIKit()
{
    ;
}
CCUIKit::~CCUIKit()
{
    ;
}
CCUIKit * CCUIKit::shareCCUIKit()
{
    if (!g_CCUIKit)
    {
        g_CCUIKit = new CCUIKit();
    }
    return g_CCUIKit;
}

void CCUIKit::setCCUIKit(CCUIKit * aCCUIKit)
{
    g_CCUIKit = aCCUIKit;
}

bool CCUIKit::initFacebook()
{
    return [[CCUIFaceBook shareCCUIFaceBook] initFacebook];
}

bool CCUIKit::logInFacebook(int tag,const char* scope)
{
    NSString * aScope = @"";
    return [[CCUIFaceBook shareCCUIFaceBook] logInFacebook:tag Scope:aScope];
}
bool CCUIKit::logInFacebookCallBack(int cbIndex,const char*  logInfo)
{
    FacebookInterface::callbackJs(cbIndex, logInfo);
    
    return true;
}
const char * CCUIKit::logOutFacebook(int tag)
{
    return [[[CCUIFaceBook shareCCUIFaceBook] logOutFacebook:tag] UTF8String];
}
const char * CCUIKit::getActiveSessionState(int cbIndex,bool force)
{
    return [[[CCUIFaceBook shareCCUIFaceBook] getActiveSessionState:cbIndex Force:force] UTF8String];
}
////////////////////////////////////////////////////

void CCUIKit::requestWithGraphPath(const char * graphPath, const char * method, const char * parameters,int cbIndex)
{
    NSString * iosGraphPath = [NSString stringWithUTF8String:graphPath];
    NSString * iosMethod = [NSString stringWithUTF8String:method];
    NSString * iosParameters = [NSString stringWithUTF8String:parameters];

    [[CCUIFaceBook shareCCUIFaceBook] requestWithGraphPath:iosGraphPath
                                                        HTTPMethod:iosMethod
                                                        Parameters:iosParameters
                                                     index:cbIndex];   
}
void CCUIKit::requestApiCallBack(int cbIndex,const char * JsonString)
{
    FacebookInterface::shareFacebookInterface()->apiCallBack(cbIndex,JsonString);
}
////////////////////////////////////////////////////
void CCUIKit::ui(const char* params,int cbIndex)
{
    NSString * iosParams = [NSString stringWithUTF8String:params];
    
    [[CCUIFaceBook shareCCUIFaceBook] UI:iosParams Index:cbIndex];
	
}
void CCUIKit::uiCallBack(int  cbIndex,const char * result)
{
    FacebookInterface::shareFacebookInterface()->uiCallBack(cbIndex,result);
}
void CCUIKit::WebDialogsCallBack(const char *  resultURL,int result)
{
    FacebookInterface::shareFacebookInterface()->WebDialogsCallBack(resultURL,result);
}
void CCUIKit::webDialogsWillPresentDialog(const char *dialog,const char *parameters,const char  *session)
{
    FacebookInterface::shareFacebookInterface()->webDialogsWillPresentDialog(dialog,parameters,session);
}
void CCUIKit::webDialogsWillDismissDialog(const char *dialog,const char *parameters,const char  *session,int result,const char  *url)
{
    FacebookInterface::shareFacebookInterface()->webDialogsWillDismissDialog(dialog,parameters,session,result,url);
}

