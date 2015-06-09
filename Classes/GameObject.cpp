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
        _Spr = Sprite::create("TankG.png");
    }
    else if (_Type == 3)
    {
        _Spr = Sprite::create("sandbagBeige.png");
    }
    else if (_Type == 4)
    {
        _Spr = Sprite::create("bulletGreen_outline.png");
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