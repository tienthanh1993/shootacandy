//
//  GameScene.cpp
//  ShootACandy
//
//  Created by Pham Thanh on 7/18/16.
//
//

#include "GameScene.h"
#include "SoundUtil.h"
#include "SdkUtil.h"
#include "MenuScene.h"

#define GAMEOVER 2
#define BULLET 1
#define TARGET 1
GameScene::~GameScene() {
    
}


bool GameScene::init() {
    bool bRet = false;
    
    do
    {
        CC_BREAK_IF(!Scene::init());
        _gameState = en_idle;
        int currentBullet = GameManager::getInstance()->getCurrentBullet();
        _bg1 = Sprite::createWithSpriteFrameName(__String::createWithFormat("bg_%d.png",currentBullet)->getCString());
        _bg1->setAnchorPoint(Vec2::ZERO);
        addChild(_bg1);
        _bg2 = Sprite::createWithSpriteFrameName(__String::createWithFormat("bg_%d.png",currentBullet)->getCString());
        _bg2->setAnchorPoint(Vec2::ZERO);
        _bg2->setPosition(Vec2(0,-960));
        addChild(_bg2);
        
        
        _barierBot = Sprite::createWithSpriteFrameName("barier.png");
        _barierBot->setAnchorPoint(Vec2::ZERO);
        _barierBot->setPosition(Vec2(640,_barierBot->getContentSize().height));
        _barierBot->setRotation(180);
        addChild(_barierBot);
        
        _barierTop = Sprite::createWithSpriteFrameName("barier.png");
        _barierTop->setAnchorPoint(Vec2(0,1));
        _barierTop->setPosition(Vec2(0,960));
        addChild(_barierTop);
        
        _score = Label::createWithTTF("score", "fonts/arial.ttf", 72);
        _score->setString("0");
        _score->setPosition(Vec2(323.95,799.57));
        addChild(_score);
        _moneypad = Sprite::createWithSpriteFrameName("money_pad.png");
        _moneypad->setPosition(Vec2(112,883.00));
        addChild(_moneypad);
        _money = Label::createWithTTF("score", "fonts/arial.ttf", 52);
        _money->setAnchorPoint(Vec2(0,0.5f));
        _money->setPosition(Vec2(70.08,882.33 ));
        _money->setString(__String::createWithFormat("%d",GameManager::getInstance()->getCoin())->getCString());
        addChild(_money);
        
        _pauseBtn = Button::create("pause_btn.png","","",TextureResType::PLIST);
        _pauseBtn->setPosition(Vec2(593,883));
        _pauseBtn->addTouchEventListener([&](Ref* pSender, Widget::TouchEventType tt ) {
            if (tt != Widget::TouchEventType::ENDED) {
                return ;
            }
            auto _pauseLayer = PauseLayer::create();
            _pauseLayer->setPosition(Vec2(0,0));
            _pauseLayer->retain();
            addChild(_pauseLayer,GAMEOVER);

        });
        addChild(_pauseBtn);
        
        // bullet position
        // target position
        // game over layer
        _gameOver = GameOverLayer::create();
        _gameOver->retain();
        _gameOver->setPosition(Vec2(320,960+_gameOver->getContentSize().height));
        addChild(_gameOver,GAMEOVER);
        
        
        startGame();

        auto listener = EventListenerTouchOneByOne::create();
        listener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
        listener->onTouchMoved = CC_CALLBACK_2(GameScene::onTouchMoved, this);
        listener->onTouchEnded = CC_CALLBACK_2(GameScene::onTouchEnded, this);
        listener->retain();
        this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
        listener->setEnabled(true);
        auto  keyboardListener = EventListenerKeyboard::create();
        keyboardListener->onKeyReleased = CC_CALLBACK_2(GameScene::onKeyReleased,this);
        this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyboardListener,this);
        
        schedule(schedule_selector(GameScene::checkCollision), 0.01f);
        bRet = true;
    }
    while (0);
    
    return bRet;
}

void GameScene::onEnter() {
    Scene::onEnter();
    NOTIFY->addObserver(this, callfuncO_selector(GameScene::restartGame), "restartGame", nullptr);
}

void GameScene::onExit() {
    Scene::onExit();
    NOTIFY->removeAllObservers(this);
    
}

bool GameScene::onTouchBegan(Touch *touch, Event *unused_event) {
    if (_gameState == GameState::en_idle) {
        SoundUtil::getInstance()->playEffect("res/sound/shoot.mp3");
        _bullet->runAction(MoveBy::create(1.0f, Vec2(0,960)));
        _gameState = GameState::en_playing;
        // shoot effect
    }
    return true;
}
void GameScene::onTouchMoved(Touch *touch, Event *unused_event) {
    
}
void GameScene::onTouchEnded(Touch *touch, Event *unused_event) {
    
}
void GameScene::onKeyReleased(EventKeyboard::KeyCode code, Event *event) {
    if (code == EventKeyboard::KeyCode::KEY_BACK)
    {
        if (_exit)
        {
            auto pTransScene = TransitionFade::create(0.2f, MenuScene::create());
            Director::getInstance()->replaceScene(pTransScene);
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

void GameScene::checkCollision(float dt) {
    if (_gameState != GameState::en_gameover) {
        if (_bullet->getBoundingBox().intersectsRect(_barierTop->getBoundingBox()) || _bullet->getBoundingBox().intersectsRect(_barierBot->getBoundingBox())) {
            SdkUtil::getInstance()->showAdmob("gameover");
            if (GameManager::getInstance()->getScore() > GameManager::getInstance()->getHiScore()) {
                GameManager::getInstance()->setHiScore(GameManager::getInstance()->getScore());
                SdkUtil::getInstance()->submitScore("leaderboard",GameManager::getInstance()->getScore());
            }
            
            createEffect(_bullet->getPosition());
            SoundUtil::getInstance()->playEffect("res/sound/crash.mp3");
            _bullet->removeFromParent();
            _target->removeFromParent();
            _gameState = GameState::en_gameover;
             _gameOver->moveIn();
        } else {
            if (_bullet->getBoundingBox().intersectsRect(_target->getBoundingBox())) {
                _shotCount++;
                _gameState = GameState::en_idle;
                
                
                createEffect(_bullet->getPosition());
                
                SoundUtil::getInstance()->playEffect("res/sound/hit.mp3");
                _score->setString(__String::createWithFormat("%d",GameManager::getInstance()->addScore(1))->getCString());
                
                if (_shotCount%3 == 0) {
                    _money->setString(__String::createWithFormat("%d",GameManager::getInstance()->addCoin(1))->getCString());
                    SoundUtil::getInstance()->playEffect("res/sound/eatcoin.mp3");
                    auto gold = Label::createWithTTF("+1", "fonts/arial.ttf", 56);
                    gold->setPosition(_bullet->getPosition());
                    auto coin = Sprite::createWithSpriteFrameName("coin-1.png");
                    coin->setPosition(Vec2(gold->getContentSize().width+50,coin->getContentSize().height/4));
                    coin->setScale(0.5f);
                    gold->addChild(coin);
                    addChild(gold);
                    gold->runAction(Sequence::create(MoveBy::create(0.5f, Vec2(0,100)),FadeOut::create(0.5f),RemoveSelf::create(), NULL));
                    // add animation
                } else if (_shotCount%4 == 0) {
                    _money->setString(__String::createWithFormat("%d",GameManager::getInstance()->addCoin(3))->getCString());
                    SoundUtil::getInstance()->playEffect("res/sound/eatcoin.mp3");
                    auto gold = Label::createWithTTF("+3", "fonts/arial.ttf", 56);
                    gold->setPosition(_bullet->getPosition());
                    auto coin = Sprite::createWithSpriteFrameName("coin-1.png");
                    coin->setScale(0.5f);
                    coin->setPosition(Vec2(gold->getContentSize().width+50,coin->getContentSize().height/4));
                    gold->addChild(coin);
                    addChild(gold);
                    gold->runAction(Sequence::create(MoveBy::create(0.5f, Vec2(0,100)),FadeOut::create(0.5f),RemoveSelf::create(), NULL));
                }
                

                _bullet->removeFromParent();
                _target->removeFromParent();
                

                
                genBullet();
                genTarget();
            }
        }
    }
}

void GameScene::genTarget() {
    int currentBullet = GameManager::getInstance()->getCurrentBullet();
    _target = Sprite::createWithSpriteFrameName(__String::createWithFormat("target_%d.png",currentBullet)->getCString());
    _target->setPosition(Vec2(random(_target->getContentSize().width/2, 640 - _target->getContentSize().width/2),960 + _target->getContentSize().height/2));
    addChild(_target,TARGET);
    
    int newY =random(300, 860);
    auto init = MoveTo::create(0.4f,Vec2(_target->getPositionX(),newY));
    
    auto toright = MoveTo::create(calSpeed(std::abs(_target->getPositionX() -  (640 - _target->getContentSize().width))),Vec2(640 - _target->getContentSize().width/2,newY));
    

    
    auto callback = CallFuncN::create([&](Node* pSender){
        

        auto partrol = MoveBy::create(calSpeed(640 - _target->getContentSize().width), Vec2(-(640 - _target->getContentSize().width),0));
        auto repeat = RepeatForever::create(Sequence::createWithTwoActions(partrol,partrol->reverse()));
        _target->runAction(repeat);
    });
    

    
    
    _target->runAction(Sequence::create(init,toright,callback, NULL));
}
void GameScene::genBullet() {
    int currentBullet = GameManager::getInstance()->getCurrentBullet();
    _bullet = Sprite::createWithSpriteFrameName(__String::createWithFormat("bullet_%d.png",currentBullet)->getCString());
    _bullet->setPosition(Vec2(320,184));
    addChild(_bullet,BULLET);
    
    if (GameManager::getInstance()->getScore()>0) {
        auto fall = MoveBy::create(10.0f,Vec2(0,-200));
        _bullet->runAction(fall);
    } else if (GameManager::getInstance()->getScore()>5) {
        auto fall = MoveBy::create(9.0f,Vec2(0,-200));
        _bullet->runAction(fall);
    } else if (GameManager::getInstance()->getScore()>15) {
        auto fall = MoveBy::create(7.0f,Vec2(0,-200));
        _bullet->runAction(fall);
    } else  if (GameManager::getInstance()->getScore()>25) {
            auto fall = MoveBy::create(5.0f,Vec2(0,-200));
            _bullet->runAction(fall);
    } else  if (GameManager::getInstance()->getScore()>35) {
        auto fall = MoveBy::create(5.0f,Vec2(0,-200));
        _bullet->runAction(fall);
    } else if (GameManager::getInstance()->getScore()>50){
        auto fall = MoveBy::create(3.0f,Vec2(0,-200));
        _bullet->runAction(fall);
    }
}
void GameScene::startGame() {
        GameManager::getInstance()->setScore(0);
    genBullet();
    genTarget();
}

void GameScene::restartGame(Ref* pData) {
    
    _shotCount = 0;
    GameManager::getInstance()->setScore(0);
    _score->setString("0");
    _gameState = GameState::en_idle;
    startGame();
}

float GameScene::calSpeed(float distance) {
    float speed = 400.0f + 10 * GameManager::getInstance()->getScore();
    float far = distance;
    float time = far/speed;
    return time;
}

void GameScene::createEffect(Vec2 pos) {
    auto _emitter = ParticleFlower::create();
    _emitter->setPosition(pos);
    _emitter->setDuration(0.2f);
    this->addChild(_emitter, 10);
    _emitter->setTexture(Director::getInstance()->getTextureCache()->addImage("res/effect/texture.png") );

}
