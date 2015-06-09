//
//  Bullet.h
//  TanksBattle
//

#ifndef __TanksBattle__Bullet__
#define __TanksBattle__Bullet__

#include "cocos2d.h"
#include <stdio.h>
#include "GameObject.h"

USING_NS_CC;

class Bullet : public GameObject
{
public:
    Bullet(uint typ, Vec2 pos, Vec2 dir);
    Vec2 GetObjectDir();
    void UpdatePosition();
    
private:
    Vec2 _DirectionVec;
};

#endif /* defined(__TanksBattle__Bullet__) */
