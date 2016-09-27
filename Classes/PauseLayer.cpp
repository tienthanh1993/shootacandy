//
//  PauseLayer.cpp
//  ShootACandy
//
//  Created by Pham Thanh on 7/21/16.
//
//

#include "PauseLayer.h"
#include "SoundUtil.h"
#include "ShopLayer.h"
#include "MenuScene.h"

bool PauseLayer::init() {
    bool bRet = false;
    
    do
    {
        CC_BREAK_IF(!Layer::init());
        
        // no touch
        auto pListener = EventListenerTouchOneByOne::create();
        pListener->setSwallowTouches(true);
        pListener->onTouchBegan = [](Touch *pTouch, Event *pEvent){return true;};
        Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(pListener, this);
        
        this->setPosition(Vec2(0,0));
        auto backLayer = LayerColor::create();
        backLayer->setContentSize(Size(640,960));
        backLayer->setColor(Color3B::BLACK);
        backLayer->setOpacity(70);
        backLayer->setAnchorPoint(Vec2::ZERO);
        addChild(backLayer);
        _homeBtn = Button::create("home_btn.png","","",TextureResType::PLIST);
        _homeBtn->setPosition(Vec2(204.50,479.00));
        _homeBtn->addTouchEventListener([&](Ref* pSender, Widget::TouchEventType tt) {
            if (tt != Widget::TouchEventType::ENDED) {
                return;
            }
            SoundUtil::getInstance()->playEffect("res/sound/button.mp3");
            Director::getInstance()->resume();
            auto pTransScene = TransitionFade::create(0.2f, MenuScene::create());
            Director::getInstance()->replaceScene(pTransScene);
        });
        addChild(_homeBtn);

        _resumeBtn = Button::create("play_btn.png","","",TextureResType::PLIST);
        _resumeBtn->setPosition(Vec2(320,479.00));
        _resumeBtn->addTouchEventListener([&](Ref* pSender, Widget::TouchEventType tt) {
            if (tt != Widget::TouchEventType::ENDED) {
                return;
            }
            SoundUtil::getInstance()->playEffect("res/sound/button.mp3");
            this->runAction(Sequence::createWithTwoActions(FadeOut::create(0.1f),RemoveSelf::create()));
            Director::getInstance()->resume();
        });
        addChild(_resumeBtn);
        
        
//        _shopBtn = Button::create("shop_btn.png","","",TextureResType::PLIST);
//        _shopBtn->setPosition(Vec2(373.50,479.00));
//        _shopBtn->addTouchEventListener([&](Ref* pSender, Widget::TouchEventType tt) {
//            if (tt != Widget::TouchEventType::ENDED) {
//                return;
//            }
//            auto shopLayer = ShopLayer::create();
//            addChild(shopLayer);
//        });
//        addChild(_shopBtn);
        
        _soundBtn = Button::create("sound_d.png","sound_e.png","",TextureResType::PLIST);
        _soundBtn->setPosition(Vec2(436.50,479.00));
        _soundBtn->addTouchEventListener([&](Ref* pSender, Widget::TouchEventType tt) {
            if (tt != Widget::TouchEventType::ENDED) {
                return;
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
        
        bool bSound = readBool("sound",true);
        SoundUtil::getInstance()->setIsBackGroundSound(bSound);
        SoundUtil::getInstance()->setIsEffectSound(bSound);
        if(bSound)
            _soundBtn->setBrightStyle(cocos2d::ui::Widget::BrightStyle::NORMAL);
        else {
            _soundBtn->setBrightStyle(cocos2d::ui::Widget::BrightStyle::HIGHLIGHT);
        }

        
        this->runAction(FadeIn::create(0.1f));
                    Director::getInstance()->pause();
        bRet = true;
    }
    while (0);
    
    return bRet;
}

void PauseLayer::onEnter() {
    Layer::onEnter();
}

void PauseLayer::onExit() {
    Layer::onExit();
}
