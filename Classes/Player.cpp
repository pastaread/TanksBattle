//
//  Player.cpp
//  TanksBattle
//

#include "Player.h"

Player::Player(uint typ, Vec2 pos) : GameObject(typ, pos) {}

void Player::SetObjectDir(Vec2 dir)
{
    _DirectionVec = dir;
}

Vec2 Player::GetObjectDir()
{
    return _DirectionVec;
}

void Player::UpdatePosition()
{
    if (fabsf(_DirectionVec.x) >= fabsf(_DirectionVec.y) && _DirectionVec.x >= 0.0f)    // Right
    {
        _Pos.x += _DirectionVec.x;
        _Spr->setRotation(90.0f);
    //    CCLOG("Right");
    }
    else if (fabsf(_DirectionVec.x) >= fabsf(_DirectionVec.y) && _DirectionVec.x < 0.0f)    // Left
    {
        _Pos.x += _DirectionVec.x;
        _Spr->setRotation(-90.0f);
    //    CCLOG("Left");
    }
    else if (fabsf(_DirectionVec.y) > fabsf(_DirectionVec.x) && _DirectionVec.y >= 0.0f)    // Up
    {
        _Pos.y += _DirectionVec.y;
        _Spr->setRotation(0.0f);
    //    CCLOG("Up");
    }
    else                                                                                    // Down
    {
        _Pos.y += _DirectionVec.y;
        _Spr->setRotation(180.0f);
    //
        CCLOG("Down");
    }
    
    _Spr->setPosition(_Pos);
}