//
//  GameOverLayer.h
//  ShootACandy
//
//  Created by Pham Thanh on 7/18/16.
//
//

#ifndef GameOverLayer_hpp
#define GameOverLayer_hpp

#include <cocos2d.h>
USING_NS_CC;
#include "Define.h"
class GameOverLayer : public Layer {
public:
    CREATE_FUNC(GameOverLayer);
    void moveIn();
    void moveOut();
protected:
    virtual bool init()override;
    
    virtual void onEnter()override;
    
    virtual void onExit()override;
private:
    Button* _playBtn;
    Button* _homeBtn;
    Button* _rankBtn;
//    Button* _moreBtn;
    
    ActionInterval* _falldown;
};

#endif /* GameOverLayer_hpp */
