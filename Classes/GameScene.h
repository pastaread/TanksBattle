//
//  GameScene.h
//  Tanks
//

#ifndef __Tanks__GameScene__
#define __Tanks__GameScene__

#include "cocos2d.h"
#include <stdio.h>
#include "GameConstants.h"
#include "Player.h"
#include "Bullet.h"

USING_NS_CC;

class GameScene : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    void InitDefaults();
    
    // New begin
    void setTouchEnabled(bool enabled);
    // New end
    
    void PauseGame(Ref* pSender);
    void ResumeGame(Ref* pSender);
    void RestartGame(Ref* pSender);
    void MainMenu(Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(GameScene);
    
    void CreateObjects();
    virtual void onAcceleration(Acceleration *acc, Event *unused_event);
    void updatePosition();
    void update(float deltaT);
    
    // New begin
    bool onTouchBegan(Touch *pTouch, Event *pEvent);
    void onTouchEnded(Touch *pTouch, Event *pEvent);
    // New end
    
    
private:
    Size _VisibleSize;
    Vec2 _Origin;
    bool _GameIsPaused;
    Menu *_PauseMenu;
    
    // New begin
    EventListenerTouchOneByOne *_touchListener;
    // New end
    
    Player *_MainPlayer;
    Vec2 _PlayerVelocity;
    
    // New begin
    std::vector<GameObject> _Rocks;
    std::vector<Bullet> _BulletsPlayer;
    // New end
};

#endif /* defined(__Tanks__GameScene__) */
