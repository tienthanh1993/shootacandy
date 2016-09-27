//
//  ShopLayer.cpp
//  ShootACandy
//
//  Created by Pham Thanh on 7/18/16.
//
//

#include "ShopLayer.h"
#include "GameManager.h"
#include "SoundUtil.h"

bool ShopLayer::init() {
    bool bRet = false;
    
    do
    {
        CC_BREAK_IF(!Layer::init());
        
        // no touch
        auto pListener = EventListenerTouchOneByOne::create();
        pListener->setSwallowTouches(true);
        pListener->onTouchBegan = [](Touch *pTouch, Event *pEvent){return true;};
        Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(pListener, this);
        
        _currentIndex = readInt("bullet",0);
        if (_currentIndex == 0) {
            saveInt("bullet",0);
            saveInt(__String::createWithFormat("item_%d",_currentIndex)->getCString(),true);
        }
        
        
        _shopBg = Sprite::createWithSpriteFrameName("shop_bg.png");
        _shopBg->setAnchorPoint(Vec2::ZERO);
        addChild(_shopBg);
        
        _closeBtn = Button::create("close_shop.png","","",TextureResType::PLIST);
        _closeBtn->setPosition(Vec2(571,768.50));
        _closeBtn->addTouchEventListener([&](Ref* pSender, Widget::TouchEventType tt) {
            if (tt != Widget::TouchEventType::ENDED) {
                return;
            }
            SoundUtil::getInstance()->playEffect("res/sound/button.mp3");
            this->removeFromParent();
        });
        addChild(_closeBtn);
        
        _nextBtn= Button::create("next_btn_w.png","","",TextureResType::PLIST);
        _nextBtn->setPosition(Vec2(590.5,479.50));
        _nextBtn->addTouchEventListener([&](Ref* pSender, Widget::TouchEventType tt) {
            if (tt != Widget::TouchEventType::ENDED) {
                return;
            }
            SoundUtil::getInstance()->playEffect("res/sound/button.mp3");
            // current move to left  remove
            // current = left , current move to left
                        log("curr %d",_currentIndex);
            _currentItem->runAction(EaseExponentialOut::create(MoveTo::create(1.0f, Vec2(- _currentItem->getContentSize().width/2,530.00))));
            if(_currentIndex >= 8) {
                _currentIndex = 0;
            } else {
                _currentIndex++;
            }
            _currentItem = Sprite::createWithSpriteFrameName(__String::createWithFormat("item_%d.png",_currentIndex)->getCString());
            _currentItem->setPosition(Vec2(640+ _currentItem->getContentSize().width/2,530.00));
            addChild(_currentItem);
            _currentItem->runAction(EaseExponentialOut::create((MoveTo::create(1.0f, Vec2(325.5,530.00)))));
            
            if (!readBool(__String::createWithFormat("item_%d",_currentIndex)->getCString(),false)) {
               
                
                _buyBtn->setTitleText(GameManager::getInstance()->getItems().at(_currentIndex).asValueMap().at("price").asString().c_str());
                _buyBtn->setVisible(true);
                _selectBtn->setVisible(false);
            } else {
                _buyBtn->setVisible(false);
                _selectBtn->setVisible(true);
                if (readInt("bullet",0) == _currentIndex) {
                    _selectBtn->setBright(true);
                } else {
                    _selectBtn->setBright(false);
                }
            }
 
            
        });
        addChild(_nextBtn);
        
        _prevBtn= Button::create("prev_btn_w.png","","",TextureResType::PLIST);
        _prevBtn->setPosition(Vec2(51.50,479.50));
        _prevBtn->addTouchEventListener([&](Ref* pSender, Widget::TouchEventType tt) {
            // current move to right  remove
            // current = right , current move to right
            if (tt != Widget::TouchEventType::ENDED) {
                return;
            }
            SoundUtil::getInstance()->playEffect("res/sound/button.mp3");
            // current move to left  remove
            // current = left , current move to left
            log("curr %d",_currentIndex);
            _currentItem->runAction(EaseExponentialOut::create((MoveTo::create(1.0f, Vec2(640 + _currentItem->getContentSize().width/2,530.00)))));
            if(_currentIndex <= 0) {
                _currentIndex = 8;
            } else {
                _currentIndex--;
            }
            _currentItem = Sprite::createWithSpriteFrameName(__String::createWithFormat("item_%d.png",_currentIndex)->getCString());
            _currentItem->setPosition(Vec2(- _currentItem->getContentSize().width/2,530.00));
            addChild(_currentItem);
            _currentItem->runAction(EaseExponentialOut::create((MoveTo::create(1.0f, Vec2(325.5,530.00)))));
            
            if (!readBool(__String::createWithFormat("item_%d",_currentIndex)->getCString(),false)) {
                _buyBtn->setTitleText(GameManager::getInstance()->getItems().at(_currentIndex).asValueMap().at("price").asString().c_str());
                _buyBtn->setVisible(true);
                _selectBtn->setVisible(false);
            } else {
                _buyBtn->setVisible(false);
                _selectBtn->setVisible(true);
                if (readInt("bullet",0) == _currentIndex) {
                    _selectBtn->setBright(true);
                } else {
                    _selectBtn->setBright(false);
                }
                
            }
 
            
        });
        addChild(_prevBtn);

        
        
        
        _buyBtn= Button::create("money_pad_o.png","","",TextureResType::PLIST);
        _buyBtn->setPosition(Vec2(319,244.50));
        _buyBtn->setTitleAlignment(cocos2d::TextHAlignment::RIGHT);
        _buyBtn->setTitleFontSize(36);
        _buyBtn->setTitleText("0");
        _buyBtn->addTouchEventListener([&](Ref* pSender, Widget::TouchEventType tt) {
            if (tt != Widget::TouchEventType::ENDED) {
                return;
            }
            
           int price = GameManager::getInstance()->getItems().at(_currentIndex).asValueMap().at("price").asInt();
            
            if (GameManager::getInstance()->getCoin() >= price) {
                GameManager::getInstance()->addCoin(-price);
                saveInt("bullet",_currentIndex);
                saveInt(__String::createWithFormat("item_%d",_currentIndex)->getCString(),true);
                _buyBtn->setVisible(false);
                _selectBtn->setVisible(true);
            } else {
                log("not enough money");
            }
            
            log("buyed me ");
            //buy
        });
        addChild(_buyBtn);
        
        _selectBtn = Button::create("selected_btn.png","notselected_btn.png","",TextureResType::PLIST);
        _selectBtn->setPosition(Vec2(319,244.50));
        _selectBtn->setVisible(false);
        _selectBtn->addTouchEventListener([&](Ref* pSender, Widget::TouchEventType tt) {
            if (tt != Widget::TouchEventType::ENDED) {
                return;
            }
             log("select me %d ?",_currentIndex);
            saveInt("bullet",_currentIndex);
            saveBool(__String::createWithFormat("item_%d",_currentIndex)->getCString(),true);
            _selectBtn->setBright(true);
        });
        addChild(_selectBtn);
        
        

        _currentItem = Sprite::createWithSpriteFrameName(__String::createWithFormat("item_%d.png",_currentIndex)->getCString());
        _currentItem->setPosition(Vec2(325.5,530.00));
        addChild(_currentItem);
        
        if (!readBool(__String::createWithFormat("item_%d",_currentIndex)->getCString(),false)) {
            _buyBtn->setTitleText(GameManager::getInstance()->getItems().at(_currentIndex).asValueMap().at("price").asString().c_str());
            _buyBtn->setVisible(true);
            _selectBtn->setVisible(false);
        } else {
            _buyBtn->setVisible(false);
            _selectBtn->setVisible(true);
            if (readInt("bullet",0) == _currentIndex) {
                _selectBtn->setBright(true);
            } else {
                _selectBtn->setBright(false);
            }
        }

        bRet = true;
    }
    while (0);
    
    return bRet;
}

void ShopLayer::onEnter() {
    Layer::onEnter();
}

void ShopLayer::onExit() {
    Layer::onExit();
}
