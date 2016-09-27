//
//  LoadingScene.h
//  ShootACandy
//
//  Created by Pham Thanh on 7/18/16.
//
//

#ifndef LoadingScene_hpp
#define LoadingScene_hpp

#include <cocos2d.h>
USING_NS_CC;
#include "Define.h"
class MenuScene;
class LoadingScene : public Scene {
public:
    CREATE_FUNC(LoadingScene);
    virtual ~LoadingScene();
    void sourceLoadCallback(Ref* data);
    
protected:
    virtual bool init() override;
    virtual void onEnter() override;
    virtual void onExit() override;
private:
    Sprite* _bg;
    MenuScene* _menuScene;
};

#endif /* LoadingScene_hpp */
