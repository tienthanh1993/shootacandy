//
//  GameOverLayer.cpp
//  ShootACandy
//
//  Created by Pham Thanh on 7/18/16.
//
//

#include "GameOverLayer.h"
#include "MenuScene.h"
#include "SdkUtil.h"

bool GameOverLayer::init() {
    bool bRet = false;
    
    do
    {
        CC_BREAK_IF(!Layer::init());
        
 
        this->setPosition(Vec2(0,960 + this->getContentSize().height/2));
        auto backLayer = LayerColor::create();
        backLayer->setContentSize(Size(640,960));
        backLayer->setColor(Color3B::BLACK);
        backLayer->setOpacity(70);
        backLayer->setAnchorPoint(Vec2::ZERO);
        addChild(backLayer);
        _playBtn = Button::create("restart_btn.png","","",TextureResType::PLIST);
        _playBtn->setPosition(Vec2(319.50,503.5));
        _playBtn->addTouchEventListener([&](Ref* pSender, Widget::TouchEventType tt) {
            if (tt != Widget::TouchEventType::ENDED) {
                return;
            }
            this->moveOut();
            
            // post restart game to game scene
        });
        addChild(_playBtn);
        _homeBtn= Button::create("home_btn.png","","",TextureResType::PLIST);
        _homeBtn->setPosition(Vec2(204.50 ,329.0));
        _homeBtn->addTouchEventListener([&](Ref* pSender, Widget::TouchEventType tt) {
            if (tt != Widget::TouchEventType::ENDED) {
                return;
            }
            // go to menu scene
            auto pTransScene = TransitionFade::create(0.2f, MenuScene::create());
            Director::getInstance()->replaceScene(pTransScene);
        });
        addChild(_homeBtn);
        _rankBtn= Button::create("rank_btn.png","","",TextureResType::PLIST);
        _rankBtn->setPosition(Vec2(436.50 ,329.0)); // old position 320.50,329.0
        _rankBtn->addTouchEventListener([&](Ref* pSender, Widget::TouchEventType tt) {
            if (tt != Widget::TouchEventType::ENDED) {
                return;
            }
            // show rank
            SdkUtil::getInstance()->showLeaderboard("leaderboard");
        });
        addChild(_rankBtn);
//        _moreBtn= Button::create("more_btn.png","","",TextureResType::PLIST);
//        _moreBtn->setPosition(Vec2(436.50 ,329.0));
//        _moreBtn->addTouchEventListener([&](Ref* pSender, Widget::TouchEventType tt) {
//            if (tt != Widget::TouchEventType::ENDED) {
//                return;
//            }
//        });
//        addChild(_moreBtn);
        
        bRet = true;
    }
    while (0);
    
    return bRet;
}

void GameOverLayer::onEnter() {
    Layer::onEnter();
}

void GameOverLayer::onExit() {
    Layer::onExit();
}

void GameOverLayer::moveIn() {
    this->setPosition(Vec2(0,960 + getContentSize().height/2));
    this->runAction(MoveTo::create(0.5f, Vec2(0,0)));
}
void GameOverLayer::moveOut() {
    this->setPosition(Vec2(0,0));

    auto callback = CallFuncN::create([&](Node* pSender) {
            NOTIFY->postNotification("restartGame");
    });
    this->runAction(Sequence::createWithTwoActions(MoveTo::create(0.5f, Vec2(0,960 + this->getContentSize().height/2)), callback));
    // after move out post notify  restart game
}