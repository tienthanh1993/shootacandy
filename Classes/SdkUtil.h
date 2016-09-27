//
//  SdkUtil.h
//  ShootACandy
//
//  Created by Pham Thanh on 7/21/16.
//
//

#ifndef SdkUtil_h
#define SdkUtil_h

#include <cocos2d.h>
#include "Define.h"

USING_NS_CC;

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) || (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#define SDKBOX_ENABLED 1
#else

#endif

#ifdef SDKBOX_ENABLED
#include "Sdkbox/Sdkbox.h"
#include "PluginAdMob/PluginAdMob.h"
#include "PluginSdkboxPlay/PluginSdkboxPlay.h"
#endif

class SdkUtil : public Ref
{
public:

    CREATE_INSTANCE_FUNC(SdkUtil);
    DESTROY_INSTANCE_FUNC();
    virtual bool init();
    // admob
    void preloadAdmob(std::string unit);
    void showAdmob(std::string unit);
    void hideAdmob(std::string unit);
    bool isAdmobReady(std::string unit);
    
    // play service & game center
    void signin();
    void submitScore(std::string leaderboard_name, int score);
    void showLeaderboard(std::string leaderboard_name);
    bool isConnected();
    inline void setLimit(bool var, int rate = 3) { _limitFullScreenAds = var; _rate = rate; _count = 0; }
protected:
    void onConnectionStatusChanged( int status );
    
    void onScoreSubmitted( const std::string& leaderboard_name, int score, bool maxScoreAllTime, bool maxScoreWeek, bool maxScoreToday );
    
    void onIncrementalAchievementUnlocked( const std::string& achievement_name );
    
    void onIncrementalAchievementStep( const std::string& achievement_name, int step );
    
    void onAchievementUnlocked( const std::string& achievement_name, bool newlyUnlocked );
private:
    bool _limitFullScreenAds = true;
    int _rate = 3;
    int _count = 0;
};
#endif /* SdkUtil_h */
