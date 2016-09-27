//
//  PauseLayer.h
//  ShootACandy
//
//  Created by Pham Thanh on 7/21/16.
//
//

#ifndef PauseLayer_hpp
#define PauseLayer_hpp

#include <cocos2d.h>
#include "Define.h"

USING_NS_CC;

class PauseLayer : public Layer {
public:
    CREATE_FUNC(PauseLayer);
protected:
    virtual bool init()override;
    
    virtual void onEnter()override;
    
    virtual void onExit()override;
private:
    Button* _homeBtn;
    Button* _resumeBtn;
//    Button* _shopBtn;
    Button* _soundBtn;
    
};

#endif /* PauseLayer_hpp */
