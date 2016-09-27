//
//  GameManager.cpp
//  ShootACandy
//
//  Created by Pham Thanh on 7/18/16.
//
//

#include "GameManager.h"
GameManager* GameManager::_gInstance;
GameManager::GameManager() {
    
}

GameManager::~GameManager() {
    
}

bool GameManager::init() {
    _score = 0;
    _hiScore = readInt("hiscore",0);
    _coin = readInt("coin",0);
    _speed = 10;
    _currentBullet = readInt("bullet",0);
    // buyed item
    return true;
}

int GameManager::getScore() {
    return _score;
}
void GameManager::setScore(int var) {
    _score = var;
}

int GameManager::getHiScore() {
    return _hiScore;
}
void GameManager::setHiScore(int var) {
    saveInt("hiscore",_hiScore);
    _hiScore = var;
}

int GameManager::getCoin() {
    return _coin;
}
void GameManager::setCoin(int var) {
    _coin = var;
}

float GameManager::getSpeed() {
    return _speed;
}
void GameManager::setSpeed(float var) {
    _speed = var;
}

int GameManager::addScore(int var) {
    _score+=var;

    return _score;
}
int GameManager::addCoin(int var) {
    _coin+=var;
    saveInt("coin",_coin);
    return _coin;
}


int GameManager::getCurrentBullet() {
    return readInt("bullet",0);
}

void GameManager::setCurrentBullet(int id) {
    _currentBullet = id;
    saveInt("bullet",_currentBullet);
}

void GameManager::moreGames() {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    Application::getInstance()->openURL("https://play.google.com/store/apps/developer?id=VuaMobi");
#else
    #if  (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        Application::getInstance()->openURL("https://itunes.apple.com/us/developer/pham-thanh/id1106485064");
    #else
        Application::getInstance()->openURL("http://vuamobi.com");
    #endif
#endif
}

ValueVector& GameManager::getItems() {
    if (_items.size() == 0) {
        _items = FileUtils::getInstance()->getValueVectorFromFile("res/shotacandy/items.plist");
    }
    return _items;
}