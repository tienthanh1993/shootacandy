//
//  GameScene.h
//  ShootACandy
//
//  Created by Pham Thanh on 7/18/16.
//
//

#ifndef GameScene_hpp
#define GameScene_hpp

#include <cocos2d.h>
USING_NS_CC;
#include "Define.h"
#include "GameOverLayer.h"
#include "GameManager.h"
#include "PauseLayer.h"

class GameScene : public Scene {
public:
    enum GameState {
        en_idle,
        en_playing,
        en_gameover
    };
    CREATE_FUNC(GameScene);
    virtual ~GameScene();
    Layer* _pGameSceneLayer;
protected:
    virtual bool init() override;
    virtual void onEnter() override;
    virtual void onExit() override;
    virtual bool onTouchBegan(Touch *touch, Event *unused_event);
    virtual void onTouchMoved(Touch *touch, Event *unused_event);
    virtual void onTouchEnded(Touch *touch, Event *unused_event);
    virtual void onKeyReleased(EventKeyboard::KeyCode code, Event *event);
private:
    Button* _pauseBtn;
    GameOverLayer* _gameOver;
    // background 1
    // background 2
    // score label
    // money label
    // bullet
    // target
    // check collision
    // genTarget
    // game state
    //  touch listener
    
    
    Sprite* _bg1;
    Sprite* _bg2;
    Sprite* _barierTop;
    Sprite* _barierBot;
    Label* _score;
    Sprite* _moneypad;
    Label* _money;
    
    
    Sprite* _bullet;
    Sprite* _target;
    
    void checkCollision(float dt);
    void genTarget();
    void genBullet();
    void startGame();
    void restartGame(Ref* pData);
    float calSpeed(float distance);
    void createEffect(Vec2 pos);
    int _gameState;
    int _shotCount = 0;
    bool _exit = false;
    
};

#endif /* GameScene_hpp */
