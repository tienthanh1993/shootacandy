//
//  SoundUtil.cpp
//  CloudWalker
//
//  Created by Pham Thanh on 7/8/16.
//
//

#include "SoundUtil.h"

#include "SoundUtil.h"
#include "SimpleAudioEngine.h"

SoundUtil *SoundUtil::_gInstance;
#define BACKGROUNDSOUND "abc.mp3"
void SoundUtil::playBackgroundSound(const std::string &rSBgSound)
{
    if (!_bIsBackGroundSound) return;
    
    if(rSBgSound == BACKGROUNDSOUND && _bIsSoundMainBackGroundMusic) return;
    else
    {
        CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic(rSBgSound.c_str(), true);
        if(rSBgSound == BACKGROUNDSOUND) _bIsSoundMainBackGroundMusic = true;
        else _bIsSoundMainBackGroundMusic = false;
    }
    
}

void SoundUtil::playEffect(const std::string &rSEffectSound)
{
    if(!_bIsEffectSound) return;
    
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(rSEffectSound.c_str());
}

void SoundUtil::preloadEffect(const std::string &rSEffectSound)
{
    if(!_bIsEffectSound) return;
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(rSEffectSound.c_str());
}

void SoundUtil::setIsBackGroundSound(const bool &rIsSound)
{
    _bIsBackGroundSound = rIsSound;
    _bIsSoundMainBackGroundMusic = !rIsSound;
    _bIsBackGroundSound ? playBackgroundSound(BACKGROUNDSOUND) : stopBackGroundSound();
}

void SoundUtil::stopBackGroundSound()
{
    CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
}



SoundUtil::SoundUtil():_bIsEffectSound(true)
{
    
}

SoundUtil::~SoundUtil()
{
    
}
