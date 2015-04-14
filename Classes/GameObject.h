//
//  GameObject.h
//  TanksBattle
//

#ifndef __TanksBattle__GameObject__
#define __TanksBattle__GameObject__

#include "cocos2d.h"
#include <stdio.h>

USING_NS_CC;

class GameObject
{
public:
    GameObject(uint typ, Vec2 pos);
    void SetObjectPos(Vec2 pos);
    Vec2 GetObjectPos();
    
    Sprite *_Spr;
    
protected:
    uint _Type;             // 1 = player, 2 = enemy, 3 = rock
    Vec2 _Pos;
};

#endif /* defined(__TanksBattle__GameObject__) */
