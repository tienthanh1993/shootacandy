//
//  MenuScene.h
//  ShootACandy
//
//  Created by Pham Thanh on 7/18/16.
//
//

#ifndef MenuScene_hpp
#define MenuScene_hpp

#include <cocos2d.h>
USING_NS_CC;
#include "Define.h"

class MenuScene : public Scene {
public:
    CREATE_FUNC(MenuScene);
    virtual ~MenuScene();
    void preloadResource();
    void addLayers();
    void moveIn();
    void moveOut();
protected:
    virtual bool init() override;
    virtual void onEnter() override;
    virtual void onExit() override;
    virtual void onKeyReleased(EventKeyboard::KeyCode code, Event *event);
private:
    std::vector<std::string> *_pResource;
    int _resourceCount;
    
    Button* _playBtn;
//    Button* _moreBtn;
    Button* _shopBtn;
    Button* _soundBtn;
//    Sprite* _coin;
    Sprite* _coinBg;
    Label* _coinTxt;
    Sprite* _title;
    
    Sprite* _bg;
    Sprite* _bgTop;
    Sprite* _bgBottom;
    
    // animation
    ActionInterval* _soundAni;
    ActionInterval* _playAni;
    ActionInterval* _moreAni;
    ActionInterval* _shopAni;
    ActionInterval* _bgTopAni;
    ActionInterval* _bgBotAni;
    
    bool _exit = false;
};

#endif /* MenuScene_hpp */
