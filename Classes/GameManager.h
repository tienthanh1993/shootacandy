//
//  GameManager.h
//  ShootACandy
//
//  Created by Pham Thanh on 7/18/16.
//
//

#ifndef GameManager_h
#define GameManager_h

#include <cocos2d.h>
USING_NS_CC;
#include "Define.h"

class GameManager : public Ref {
public:
    CREATE_INSTANCE_FUNC(GameManager);
    DESTROY_INSTANCE_FUNC();
    GameManager();
    ~GameManager();
    int getScore();
    int getHiScore();
    int getCoin();
    int getCurrentBullet();
    float getSpeed();
    void setScore(int var);
    void setHiScore(int var);
    void setCoin(int var);
    void setSpeed(float var);
    void setCurrentBullet(int id);
    int addScore(int var);
    int addCoin(int var);
    void moreGames();
    ValueVector& getItems();
protected:
    virtual bool init();
private:

    
    
    int _score;
    int _hiScore;
    int _coin;
    float _speed;
    int _currentBullet;
    ValueVector _items;
};
#endif /* GameManager_h */
