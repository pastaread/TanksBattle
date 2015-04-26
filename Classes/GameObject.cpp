//
//  GameObject.cpp
//  TanksBattle
//

#include "GameObject.h"

GameObject::GameObject(uint typ, Vec2 pos)
{
    _Type = typ;
    _Pos = pos;
    if (_Type == 1)
    {
        _Spr = Sprite::create("Tank.png");
        _Spr->setScale(0.18f);
    }
    else if (_Type == 3)
    {
        _Spr = Sprite::create("Rock.png");
        _Spr->setScale(0.28f);
    }
    _Spr->setPosition(pos);
}

void GameObject::SetObjectPos(Vec2 pos)
{
    _Pos = pos;
    _Spr->setPosition(pos);
}

Vec2 GameObject::GetObjectPos()
{
    return _Pos;
}