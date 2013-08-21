facebook-jsb-sdk
----------------
The facebook-jsb-sdk for Cocos2d-x allows you to use the same JavaScript code in your Cocos2d-x application as you use facebook javascript sdk in your web application.

Requirements and Set-Up
-----------------------
  - To use this plugin you will need to make sure you've [registered] your Facebook app with Facebook and have an APP_ID.
  - Create your cocos2d-x application base with cocos2d-x 2.1.4.You can use the cocos2d-x/tools/project-creator.py to create a multi-platform project.
  - If you plan on rolling this out on Android, please note that you will need to generate a hash of your Android key(s) and submit those to the Developers page on Facebook to get it working.
  - *If you plan on rolling this out on iOS, please note that you will need to ensure that you have properly set up your Native iOS App settings on the Facebook App Dashboard. Please see the Getting Started with the Facebook SDK*

Project Structure
-----------------

 - *FB-Android-JSB* and  *FB-IOS-JSB* contain the native code for the plugin for both Android and iOS platforms. They also include versions of the Android and iOS Facebook SDKs.

 - *Resources* contain the JavaScript code for the plugin, this defines the JS API.
 - *Class* contain the C++ code for the plugin, this connect up JavaScript code and C++ by ScriptingCore.

Getting Started with the Facebook JSB SDK
-----------------------------------------
 1. Copy *Resources* and *Class* folder to your cocos2d-x application.
 2. Add the facebook RegisterCallback into Class/AppDelegate.cpp:

    extern void register_facebook_js(JSContext* cx, JSObject* global);
 
    bool AppDelegate::applicationDidFinishLaunching(){
        
        ScriptingCore* sc = ScriptingCore::getInstance();  
        sc->addRegisterCallback(register_facebook_js);
        sc->start();
    }
 3. [Set up the Facebook JSB SDK for Android]:
  - Import the facebook-android-sdk into Eclipse.
  - Link to the facebook-android-sdk project and configure the Facebook app ID.
  - Use the FacebookConnecActivity replaces the Cocos2dActivity.
  - Add the source file into pro.android/jni/Android.mk: 
     - FacebookAndroidInterface.cpp  
     - js_bindings_facebook.cpp 

 4. [Set up the Facebook JSB SDK for IOS]:

  [registered]:https://developers.facebook.com/apps
  [Set up the Facebook JSB SDK for Android]:https://developers.facebook.com/docs/android/getting-started/facebook-sdk-for-android/
  
