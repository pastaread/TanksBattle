//
//  Player.h
//  TanksBattle
//

#ifndef __TanksBattle__Player__
#define __TanksBattle__Player__

#include "cocos2d.h"
#include <stdio.h>
#include "GameObject.h"

USING_NS_CC;

class Player : public GameObject
{
public:
    Player(uint typ, Vec2 pos);
    void SetObjectDir(Vec2 dir);
    Vec2 GetObjectDir();
    void UpdatePosition();
    
private:
    Vec2 _DirectionVec;
};

#endif /* defined(__TanksBattle__Player__) */
