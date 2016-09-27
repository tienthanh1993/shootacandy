//
//  MenuScene.cpp
//  ShootACandy
//
//  Created by Pham Thanh on 7/18/16.
//
//

#include "MenuScene.h"
#include "GameManager.h"
#include "GameScene.h"
#include "ShopLayer.h"
#include "SoundUtil.h"

MenuScene::~MenuScene() {
}


bool MenuScene::init() {
    bool bRet = false;
    
    do
    {
        CC_BREAK_IF(!Scene::init());
        
        preloadResource();
        
        
        bRet = true;
    }
    while (0);
    
    return bRet;
}

void MenuScene::onEnter() {
    Scene::onEnter();
//    NOTIFY->addObserver(, , , );
}

void MenuScene::onExit() {
    Scene::onExit();
}

void MenuScene::preloadResource() {
    _pResource = new std::vector<std::string>();
    _resourceCount = 0;
    _pResource->push_back("res/shotacandy/all");
    _pResource->push_back("res/shotacandy/bg");
    _pResource->push_back("res/shotacandy/bg2");
    _pResource->push_back("res/shotacandy/menu");
    _pResource->push_back("res/shotacandy/shop");
    
    for(auto &iterSourceName : *_pResource)
        Director::getInstance()->getTextureCache()->addImageAsync(iterSourceName + ".png", [&](Texture2D *pTexture)
                                                                  {
                                                                      
                                                                      SoundUtil::getInstance()->preloadEffect("res/sound/play.mp3");
                                                                      SoundUtil::getInstance()->preloadEffect("res/sound/button.mp3");
                                                                      SoundUtil::getInstance()->preloadEffect("res/sound/crash.mp3");
                                                                      SoundUtil::getInstance()->preloadEffect("res/sound/hit.mp3");
                                                                      SoundUtil::getInstance()->preloadEffect("res/sound/eatcoin.mp3");
                                                                      SoundUtil::getInstance()->preloadEffect("res/sound/shoot.mp3");
                                                                      ++this->_resourceCount;
                                                                      SpriteFrameCache::getInstance()->addSpriteFramesWithFile(iterSourceName + ".plist" , pTexture);
                                                                      
                                                                      if(this->_resourceCount == _pResource->size())
                                                                      {                                                                          this->addLayers();
                                                                          __NotificationCenter::getInstance()->postNotification("loadFinish", static_cast<Ref*>(this));
                                                                      }
                                                                  });

}

void MenuScene::addLayers() {
    Size winSize = Director::getInstance()->getWinSize();
    _bg = Sprite::createWithSpriteFrameName("bg.png");
    _bg->setAnchorPoint(Vec2::ZERO);
    _bg->setPosition(Vec2::ZERO);
    addChild(_bg);
    
    _bgTop= Sprite::createWithSpriteFrameName("bg.png");
    _bgTop->setPosition(Vec2(320,winSize.height + _bgTop->getContentSize().height/2 /*662.00*/));
    _bgTop->setVisible(false);
    addChild(_bgTop);
    _bgBottom= Sprite::createWithSpriteFrameName("bg.png");
    _bgBottom->setPosition(Vec2(320, - _bgBottom->getContentSize().height/2));
    _bgBottom->setVisible(false);
    addChild(_bgBottom);
    
    _playBtn = Button::create("play_btn_big.png","","",TextureResType::PLIST); // top down
    _playBtn->setPosition(Vec2(320,winSize.height +_playBtn->getContentSize().height/2/*+ 284.5*/));
    _playBtn->addTouchEventListener([&](Ref* pSender,Widget::TouchEventType tt) {
        if (tt != Widget::TouchEventType::ENDED) {
            return ;
        }
        SoundUtil::getInstance()->playEffect("res/sound/play.mp3");
        auto pTransScene = TransitionFade::create(0.2f, GameScene::create());
        Director::getInstance()->replaceScene(pTransScene);
    });
    addChild(_playBtn);
//    _moreBtn = Button::create("more_btn_g.png","","",TextureResType::PLIST); // left right
//    _moreBtn->setPosition(Vec2(-_moreBtn->getContentSize().width/2 /*69.50*/,63));
//    _moreBtn->addTouchEventListener([&](Ref* pSender,Widget::TouchEventType tt) {
//        if (tt != Widget::TouchEventType::ENDED) {
//            return ;
//        }
//        GameManager::getInstance()->moreGames();
//    });
//    addChild(_moreBtn);
    _shopBtn = Button::create("shop_btn_g.png","","",TextureResType::PLIST);
    _shopBtn->setPosition(Vec2(winSize.width + _shopBtn->getContentSize().width/2 /*575.5*/,63));
    _shopBtn->addTouchEventListener([&](Ref* pSender,Widget::TouchEventType tt) {
        if (tt != Widget::TouchEventType::ENDED) {
            return ;
        }
        SoundUtil::getInstance()->playEffect("res/sound/button.mp3");
        auto shopLayer = ShopLayer::create();
        addChild(shopLayer);
    });
    addChild(_shopBtn);
    
    _soundBtn = Button::create("sound_d.png","sound_btn_e_g.png","",TextureResType::PLIST);
    _soundBtn->setPosition(Vec2(winSize.width + _soundBtn->getContentSize().width/2 /*575.5*/,885.50));
    _soundBtn->addTouchEventListener([&](Ref* pSender,Widget::TouchEventType tt) {
        if (tt != Widget::TouchEventType::ENDED) {
            return ;
        }
        SoundUtil::getInstance()->playEffect("res/sound/button.mp3");
        bool bSound = UserDefault::getInstance()->getBoolForKey("sound",true);
        UserDefault::getInstance()->setBoolForKey("sound",!bSound);
        bSound = !bSound;
        SoundUtil::getInstance()->setIsBackGroundSound(bSound);
        SoundUtil::getInstance()->setIsEffectSound(bSound);
        if(bSound)
            _soundBtn->setBrightStyle(cocos2d::ui::Widget::BrightStyle::NORMAL);
        else {
            _soundBtn->setBrightStyle(cocos2d::ui::Widget::BrightStyle::HIGHLIGHT);
        }
    });
    addChild(_soundBtn);
    // update sound btn
    bool bSound = readBool("sound",true);
    SoundUtil::getInstance()->setIsBackGroundSound(bSound);
    SoundUtil::getInstance()->setIsEffectSound(bSound);
    if(bSound)
        _soundBtn->setBrightStyle(cocos2d::ui::Widget::BrightStyle::NORMAL);
    else {
        _soundBtn->setBrightStyle(cocos2d::ui::Widget::BrightStyle::HIGHLIGHT);
    }
    // end update sound
    
    
    
    
    _coinBg = Sprite::createWithSpriteFrameName("coin_bg.png");
    _coinBg->setPosition(Vec2(112,883.00));
    addChild(_coinBg);
    
//    _coin = Sprite::createWithSpriteFrameName("coin-1.png");
//    _coin->setPosition(Vec2(63.5,880.50));
//    addChild(_coin);
    
    
    _coinTxt = Label::createWithTTF("Test", "fonts/arial.ttf", 58);
    _coinTxt->setAnchorPoint(Vec2(0,0.5f));
    _coinTxt->setPosition(Vec2(70.08,882.33));
    _coinTxt->setString(__String::createWithFormat("%d",GameManager::getInstance()->getCoin())->getCString());
    addChild(_coinTxt);
    _title = Sprite::createWithSpriteFrameName("title.png");
    _title->setPosition(Vec2(320,704.80));
    addChild(_title);
    

    
    // animation
    _soundAni = MoveBy::create(0.5f, Vec2(-_shopBtn->getContentSize().width/2 - (winSize.width - 595.5),0)); // right 2 left
    _soundAni->retain();
    _playAni = MoveBy::create(0.2f, Vec2(0,-_playBtn->getContentSize().height/2 -(winSize.height- 284.5)));
    _playAni->retain();
//    _moreAni = MoveBy::create(0.5f, Vec2(69.5+_moreBtn->getContentSize().width/2,0)); // left to right
//    _moreAni->retain();
    _shopAni = MoveBy::create(0.5f, Vec2(-_shopBtn->getContentSize().width/2 - (winSize.width - 575.5),0)); // right to left
    _shopAni->retain();
    _bgTopAni = MoveBy::create(0.5f, Vec2(0,-_bgTop->getContentSize().height/2 -(winSize.height- 655))); // top to center
    _bgTopAni->retain();
    _bgBotAni = MoveBy::create(0.5f, Vec2(0,+300 + _bgBottom->getContentSize().height/2)); // bot 2 center
    _bgBotAni->retain();
    
    
    moveIn();
    
    auto  m_keyBoardListener = EventListenerKeyboard::create();
    m_keyBoardListener->retain();
    m_keyBoardListener->onKeyReleased = CC_CALLBACK_2(MenuScene::onKeyReleased,this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(m_keyBoardListener,this);
}

void MenuScene::moveIn() {
    _playBtn->runAction(_playAni);
    _shopBtn->runAction(_shopAni);
//    _moreBtn->runAction(_moreAni);
    _soundBtn->runAction(_soundAni);
    _bgTop->runAction(_bgTopAni);
    _bgBottom->runAction(_bgBotAni);
}

void MenuScene::moveOut()   {
    _playBtn->runAction(_playAni->reverse());
    _shopBtn->runAction(_shopAni->reverse());
//    _moreBtn->runAction(_moreAni->reverse());
    _soundBtn->runAction(_soundAni->reverse());
}


void MenuScene::onKeyReleased(EventKeyboard::KeyCode code, Event *event)
{
    if (code == EventKeyboard::KeyCode::KEY_BACK)
    {
        if (_exit)
        {
            Director::getInstance()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
            exit(0);
#endif
        }
        else
        {
            _exit = true;
            
            auto winSize= Director::getInstance()->getWinSize();
            auto tips = Label::createWithTTF("Back to exit", "fonts/arial.ttf", 32);
            tips->setPosition(winSize.width/2,winSize.height*0.1f);
            this->addChild(tips,999);
            
            auto moveBy = MoveBy::create(0.5f,Vec2(0,100));
            
            auto ease = EaseBackOut::create(moveBy);
            auto fadeIn = FadeIn::create(0.5f);
            auto spawn = Spawn::createWithTwoActions(fadeIn,ease);
            
            auto callfunc = CallFunc::create([=](){
                auto fadeout = FadeOut::create(0.5f);
                tips->runAction(Sequence::create(fadeout,RemoveSelf::create(),NULL));
                _exit = false;
            });
            tips->runAction(Sequence::create(spawn,DelayTime::create(1.0f),callfunc,NULL));
            
        }
    }
}
