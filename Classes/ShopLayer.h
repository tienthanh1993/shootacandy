//
//  ShopLayer.h
//  ShootACandy
//
//  Created by Pham Thanh on 7/18/16.
//
//

#ifndef ShopLayer_hpp
#define ShopLayer_hpp

#include <cocos2d.h>
USING_NS_CC;
#include "Define.h"

class ShopLayer : public Layer {
public:
    CREATE_FUNC(ShopLayer);
protected:
    virtual bool init()override;
    
    virtual void onEnter()override;
    
    virtual void onExit()override;
private:
    Sprite* _shopBg;
    Button* _closeBtn;
    Button* _nextBtn;
    Button* _prevBtn;
    Button* _buyBtn;
    Button* _selectBtn;
    int _currentIndex;
    Sprite* _currentItem;
    Sprite* _reveseItem;
    
};

#endif /* ShopLayer_hpp */
