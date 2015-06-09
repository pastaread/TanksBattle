//
//  Bullet.cpp
//  TanksBattle
//

#include "Bullet.h"

Bullet::Bullet(uint typ, Vec2 pos, Vec2 dir) : GameObject(typ, pos)
{
    _DirectionVec.x = dir.x * 4.0f;
    _DirectionVec.y = dir.y * 4.0f;
    
    if (_DirectionVec.x > 0)
        _Spr->setRotation(90.0f);
    else if (_DirectionVec.x < 0)
        _Spr->setRotation(-90.0f);
    else if (_DirectionVec.y < 0)
        _Spr->setRotation(180.0f);
}

Vec2 Bullet::GetObjectDir()
{
    return _DirectionVec;
}

void Bullet::UpdatePosition()
{
    _Pos.x += _DirectionVec.x;
    _Pos.y += _DirectionVec.y;
    
    _Spr->setPosition(_Pos);
}