#include "cocos2d.h"
#include "CCEGLView.h"
#include "AppDelegate.h"
#include "SimpleAudioEngine.h"
#include "UI/MainMenu/MainMenu.h"
using namespace CocosDenshion;

USING_NS_CC;

AppDelegate::AppDelegate()
{
}

AppDelegate::~AppDelegate()
{
    SimpleAudioEngine::end();
}

bool AppDelegate::applicationDidFinishLaunching()
{
/*#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)

	// Initialize OpenGLView instance, that release by CCDirector when application terminate.
	// The HelloWorld is designed as HVGA.
	CCEGLView * pMainWnd = new CCEGLView();
	CC_BREAK_IF(! pMainWnd
		|| ! pMainWnd->Create(TEXT("cocos2d: Hello World"), 480, 320));

#endif  // CC_PLATFORM_WIN32

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	// OpenGLView is initialized in AppDelegate.mm on ios platform, nothing need to do here.
#endif  // CC_PLATFORM_IOS

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)        
	// OpenGLView is initialized in HelloWorld/android/jni/helloworld/main.cpp
	// the default setting is to create a fullscreen view
	// if you want to use auto-scale, please enable view->create(320,480) in main.cpp
#endif  // CC_PLATFORM_ANDROID

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WOPHONE)

	// Initialize OpenGLView instance, that release by CCDirector when application terminate.
	// The HelloWorld is designed as HVGA.
	CCEGLView* pMainWnd = new CCEGLView(this);
	CC_BREAK_IF(! pMainWnd || ! pMainWnd->Create(320,480, WM_WINDOW_ROTATE_MODE_CW));

#ifndef _TRANZDA_VM_  
	// on wophone emulator, we copy resources files to Work7/TG3/APP/ folder instead of zip file
	cocos2d::CCFileUtils::setResource("HelloWorld.zip");
#endif

#endif  // CC_PLATFORM_WOPHONE

#if (CC_TARGET_PLATFORM == CC_PLATFORM_AIRPLAY)
	// MaxAksenov said it's NOT a very elegant solution. I agree, haha
	CCDirector::sharedDirector()->setDeviceOrientation(kCCDeviceOrientationLandscapeLeft);
#endif*/









    // initialize director
    CCDirector *pDirector = CCDirector::sharedDirector();
    pDirector->setOpenGLView(CCEGLView::sharedOpenGLView());

    // enable High Resource Mode(2x, such as iphone4) and maintains low resource on other devices.
//     pDirector->enableRetinaDisplay(true);

    // turn on display FPS
    pDirector->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 60);
	// set FPS. the default value is 1.0/60 if you don't call this
	pDirector->setAnimationInterval(1.0 / 60);

	// create a scene. it's an autorelease object
	CCScene *pScene = SomeTD::UI::MainMenu::scene();

	// run
	pDirector->runWithScene(pScene);
	//GameManager* gameMangeger = GameManager::sharedGameManager();
	//gameMangeger->runSceneWithID(SCENE_ID_MAINMENU);
    // create a scene. it's an autorelease object
    //CCScene *pScene = HelloWorld::scene();

    // run
    //pDirector->runWithScene(pScene);
    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground()
{
    CCDirector::sharedDirector()->stopAnimation();

    SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{
    CCDirector::sharedDirector()->startAnimation();

    SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}
