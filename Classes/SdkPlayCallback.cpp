//
//  SdkPlayCallback.cpp
//  ShootACandy
//
//  Created by Pham Thanh on 7/21/16.
//
//

#include "SdkPlayCallback.h"
#include <cocos2d.h>
USING_NS_CC;
void SdkPlayCallback::onConnectionStatusChanged( int status ) {
    log("connection:%d",status);
}

void SdkPlayCallback::onScoreSubmitted( const std::string& leaderboard_name, int score, bool maxScoreAllTime, bool maxScoreWeek, bool maxScoreToday ) {
    log("submitted %s:%d",leaderboard_name.c_str(),score);
}

void SdkPlayCallback::onIncrementalAchievementUnlocked( const std::string& achievement_name ) {}

void SdkPlayCallback::onIncrementalAchievementStep( const std::string& achievement_name, int step ) {}

void SdkPlayCallback::onAchievementUnlocked( const std::string& achievement_name, bool newlyUnlocked ) {}
