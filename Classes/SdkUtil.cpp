//
//  SdkUtil.cpp
//  ShootACandy
//
//  Created by Pham Thanh on 7/21/16.
//
//

#include "SdkUtil.h"
#include "SdkPlayCallback.h"

SdkUtil* SdkUtil::_gInstance;

bool SdkUtil::init() {
#ifdef SDKBOX_ENABLED

    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
   sdkbox::init("4a48c9120255da95935655738ad5cb7d","eca407c501325ea0");
    sdkbox::PluginAdMob::init();
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    sdkbox::init("4faa01b09b3a6e1ac4158e3aad8a9878","1b07486dc92e60c0");
    sdkbox::PluginAdMob::init();
#endif
    sdkbox::PluginSdkboxPlay::init();
    sdkbox::PluginSdkboxPlay::setListener( new SdkPlayCallback() );
#endif
    return true;
}

void SdkUtil::preloadAdmob(std::string unit) {
#ifdef SDKBOX_ENABLED 
  sdkbox::PluginAdMob::cache(unit);
#endif
}
void SdkUtil::showAdmob(std::string unit) {
#ifdef SDKBOX_ENABLED
    if ( unit.compare("gameover") == 0 ) {
        _count++;
        if (_limitFullScreenAds && _count%_rate == 0) {
            sdkbox::PluginAdMob::show(unit);
        }
    }
    else {
       sdkbox::PluginAdMob::show(unit);
    }
#endif
}
void SdkUtil::hideAdmob(std::string unit) {
#ifdef SDKBOX_ENABLED
    sdkbox::PluginAdMob::hide(unit);
#endif
}
bool SdkUtil::isAdmobReady(std::string unit) {
#ifdef SDKBOX_ENABLED
    return sdkbox::PluginAdMob::isAvailable(unit);
#endif
    return false;
}

// play service & game center
void SdkUtil::signin() {
#ifdef SDKBOX_ENABLED
    sdkbox::PluginSdkboxPlay::signin();
#endif
}
void SdkUtil::submitScore(std::string leaderboard_name, int score) {
#ifdef SDKBOX_ENABLED
    sdkbox::PluginSdkboxPlay::submitScore(leaderboard_name,score );
#endif
}
void SdkUtil::showLeaderboard(std::string leaderboard_name) {
#ifdef SDKBOX_ENABLED
    sdkbox::PluginSdkboxPlay::showLeaderboard(leaderboard_name);
#endif
}
bool SdkUtil::isConnected() {
#ifdef SDKBOX_ENABLED
    return sdkbox::PluginSdkboxPlay::isConnected();
#endif
    return false;
}
