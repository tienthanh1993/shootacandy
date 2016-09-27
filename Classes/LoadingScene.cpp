//
//  LoadingScene.cpp
//  ShootACandy
//
//  Created by Pham Thanh on 7/18/16.
//
//

#include "LoadingScene.h"
#include "MenuScene.h"

LoadingScene::~LoadingScene() {
}


bool LoadingScene::init() {
    bool bRet = false;
    
    do
    {
        CC_BREAK_IF(!Scene::init());
        
        _bg = Sprite::create("loading.png");
        _bg->setAnchorPoint(Vec2(0.5,0.5));
        _bg->setPosition(Vec2(640/2,960/2));
  //      _bg->setAnchorPoint(Vec2::ZERO);
        addChild(_bg);
        bRet = true;
    }
    while (0);
    
    return bRet;
}

void LoadingScene::onEnter() {
    Scene::onEnter();
    NOTIFY->addObserver(this, callfuncO_selector(LoadingScene::sourceLoadCallback), "loadFinish", nullptr);
    _menuScene = MenuScene::create();
    _menuScene->retain();
}

void LoadingScene::onExit() {
    Scene::onExit();
    NOTIFY->removeAllObservers(this);
}


void LoadingScene::sourceLoadCallback(Ref * data) {
    auto pTransScene = TransitionFade::create(0.2f, dynamic_cast<Scene*>(data));
    Director::getInstance()->replaceScene(pTransScene);
}
