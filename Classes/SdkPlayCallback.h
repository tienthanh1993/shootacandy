//
//  SdkPlayCallback.h
//  ShootACandy
//
//  Created by Pham Thanh on 7/21/16.
//
//

#ifndef SdkPlayCallback_h
#define SdkPlayCallback_h
#ifdef SDKBOX_ENABLED
#include "Sdkbox/Sdkbox.h"
#include "PluginSdkboxPlay/PluginSdkboxPlay.h"
#endif


class SdkPlayCallback

#ifdef SDKBOX_ENABLED
: public sdkbox::SdkboxPlayListener
#endif
{
protected:
    void onConnectionStatusChanged( int status );
    
    void onScoreSubmitted( const std::string& leaderboard_name, int score, bool maxScoreAllTime, bool maxScoreWeek, bool maxScoreToday );
    
    void onIncrementalAchievementUnlocked( const std::string& achievement_name );
    
    void onIncrementalAchievementStep( const std::string& achievement_name, int step );
    
    void onAchievementUnlocked( const std::string& achievement_name, bool newlyUnlocked );
};

#endif /* SdkPlayCallback_h */
