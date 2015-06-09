//
//  GameScene.cpp
//  Tanks
//

#include "GameScene.h"

Scene* GameScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = GameScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GameScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    _VisibleSize = Director::getInstance()->getVisibleSize();
    _Origin = Director::getInstance()->getVisibleOrigin();
    
    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.
    
    // add a "close" icon to exit the progress. it's an autorelease object
    auto pauseItem = MenuItemImage::create("buttonPause.png",
                                           "buttonPause.png",
                                           CC_CALLBACK_1(GameScene::PauseGame, this));
    
    pauseItem->setPosition(Vec2(_Origin.x + _VisibleSize.width - pauseItem->getContentSize().width/2 ,
                                _Origin.y + pauseItem->getContentSize().height/2));
    
    // create menu, it's an autorelease object
    auto menu = Menu::create(pauseItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
    
    InitDefaults();
    CreateObjects();
    setAccelerometerEnabled(true);
    
    // New begin
    setTouchEnabled(true);
    // New end
    
    schedule(schedule_selector(GameScene::update), 0.0167);
    
    return true;
}

void GameScene::InitDefaults()
{
    _GameIsPaused = false;
}

void GameScene::setTouchEnabled(bool enabled)
{
    if (enabled)
    {
        _touchListener = EventListenerTouchOneByOne::create();
        _touchListener->retain();
        _touchListener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
        _touchListener->onTouchEnded = CC_CALLBACK_2(GameScene::onTouchEnded, this);
        _eventDispatcher->addEventListenerWithSceneGraphPriority(_touchListener, this);
    }
    else if (!enabled)
    {
        _eventDispatcher->removeEventListener(_touchListener);
        _touchListener->release();
        _touchListener = nullptr;
    }
}

void GameScene::CreateObjects()
{
    // New begin
    auto backg = Sprite::create("Ground.png");
    backg->setPosition(_VisibleSize.width * 0.5f, _VisibleSize.height * 0.5f);
    backg->setScale(_VisibleSize.width / 1242.0f, _VisibleSize.height / 2208.0f);
    this->addChild(backg, Z_ORDER_GROUND);
    
    
    GameObject rock1(3, Vec2(_VisibleSize.width * 0.18f, _VisibleSize.height * 0.82f));
    this->addChild(rock1._Spr, Z_ORDER_ROCK);
    _Rocks.push_back(rock1);
    
    GameObject rock2(3, Vec2(_VisibleSize.width * 0.48f, _VisibleSize.height * 0.12f));
    this->addChild(rock2._Spr, Z_ORDER_ROCK);
    _Rocks.push_back(rock2);
    
    GameObject rock3(3, Vec2(_VisibleSize.width * 0.68f, _VisibleSize.height * 0.52f));
    this->addChild(rock3._Spr, Z_ORDER_ROCK);
    _Rocks.push_back(rock3);
    
    GameObject rock4(3, Vec2(_VisibleSize.width * 0.38f, _VisibleSize.height * 0.42f));
    this->addChild(rock4._Spr, Z_ORDER_ROCK);
    _Rocks.push_back(rock4);
    // New end
    
    _MainPlayer = new Player(1, Vec2(_VisibleSize.width * 0.12f, _VisibleSize.height * 0.12f));
    this->addChild(_MainPlayer->_Spr, Z_ORDER_PLAYER);
}

void GameScene::onAcceleration(Acceleration *acc, Event *unused_event)      // Acceleration (Device rotation)
{
    if(_GameIsPaused == true ) return;
    
    float acceleration = 2.0f;                              // acceleration
    float maxVelocity = 2;                                  // Max speed
    
    _PlayerVelocity.x = acc->x * acceleration;
    _PlayerVelocity.y = acc->y * acceleration;
    
    if (_PlayerVelocity.x > maxVelocity)
    {
        _PlayerVelocity.x = maxVelocity;
    }
    else if (_PlayerVelocity.x < -maxVelocity)
    {
        _PlayerVelocity.x = -maxVelocity;
    }
    
    if (_PlayerVelocity.y > maxVelocity)
    {
        _PlayerVelocity.y = maxVelocity;
    }
    else if (_PlayerVelocity.y < -maxVelocity)
    {
        _PlayerVelocity.y = -maxVelocity;
    }
}

void GameScene::updatePosition()                            // Update player position
{
    
    Vec2 pos = _MainPlayer->GetObjectPos();
    pos.x += _PlayerVelocity.x;
    pos.y += _PlayerVelocity.y;
    
    float imageWidthHalved = 48.0f;
    float imageHeightHalved = 48.0f;
    
    float leftBorderLimit = imageWidthHalved;
    float rightBorderLimit = _VisibleSize.width - imageWidthHalved;
    
    float topBorderLimit = imageHeightHalved;
    float bottomBorderLimit = _VisibleSize.height - imageHeightHalved;
    
    // If out of border, stop player
    if (pos.x < leftBorderLimit)
    {
        pos.x = leftBorderLimit;
        _PlayerVelocity.x = 0;
    }
    else if (pos.x > rightBorderLimit)
    {
        pos.x = rightBorderLimit;
        _PlayerVelocity.x = 0;
    }
    
    if (pos.y < topBorderLimit)
    {
        pos.y = topBorderLimit;
        _PlayerVelocity.y = 0;
    }
    else if (pos.y > bottomBorderLimit)
    {
        pos.y = bottomBorderLimit;
        _PlayerVelocity.y = 0;
    }
    
    // Check rock collision
    std::vector <GameObject>::iterator itRock;
    for (itRock = _Rocks.begin(); itRock != _Rocks.end(); itRock++)
    {
        if (fabsf(pos.x - itRock->GetObjectPos().x) < 80.0f &&
            fabsf(pos.y - itRock->GetObjectPos().y) < 74.0f)
            _PlayerVelocity.x = 0;
        
        if (fabsf(pos.x - itRock->GetObjectPos().x) < 74.0f &&
            fabsf(pos.y - itRock->GetObjectPos().y) < 80.0f)
            _PlayerVelocity.y = 0;
    }
    
//    CCLOG("x = %f      y = %f", _PlayerVelocity.x, _PlayerVelocity.y);
    _MainPlayer->SetObjectDir(_PlayerVelocity);
    _MainPlayer->UpdatePosition();
    
    for (int i = 0; i < _BulletsPlayer.size(); i++)
    {
        _BulletsPlayer[i].UpdatePosition();
    }
}

// New begin
bool GameScene::onTouchBegan(Touch *pTouch, Event *pEvent)
{
    Bullet bullet(4,
                  Vec2(_MainPlayer->GetObjectPos().x, _MainPlayer->GetObjectPos().y),
                  _MainPlayer->GetBulletDir());
    this->addChild(bullet._Spr, Z_ORDER_BULLET);
    _BulletsPlayer.push_back(bullet);
    
    return true;
}

void GameScene::onTouchEnded(Touch *pTouch, Event *pEvent)
{
}
// New end

void GameScene::update(float deltaT)                    // Method called every 0.0167 second
{
    if (_GameIsPaused == false)
    {
        updatePosition();
    }
}

void GameScene::PauseGame(Ref* pSender)
{
    if (_GameIsPaused == true) return;
    
    _GameIsPaused = true;
    
    auto bResume = MenuItemImage::create("buttonResume.png", "buttonResume.png",
                                         CC_CALLBACK_1(GameScene::ResumeGame, this));
    bResume->setScale(0.32f);
    
    auto bMenu = MenuItemImage::create("buttonMainMenu.png", "buttonMainMenu.png",
                                       CC_CALLBACK_1(GameScene::MainMenu, this));
    bMenu->setScale(0.32f);
    
    auto bRestart = MenuItemImage::create("buttonRestart.png", "buttonRestart.png",
                                          CC_CALLBACK_1(GameScene::RestartGame, this));
    bRestart->setScale(0.32f);
    
    
    _PauseMenu = Menu::create(bResume, bMenu, bRestart, NULL);
    _PauseMenu->alignItemsHorizontallyWithPadding(_VisibleSize.width / 15.0f);
    _PauseMenu->setPosition(_VisibleSize.width * 0.5f, _VisibleSize.height * 0.5f);
    this->addChild(_PauseMenu, Z_ORDER_MENU);
}

void GameScene::ResumeGame(Ref* pSender)
{
    _GameIsPaused = false;
    _PauseMenu->removeFromParentAndCleanup(true);
}

void GameScene::RestartGame(Ref* pSender)
{
    this->removeAllChildrenWithCleanup(true);
    
    Director::getInstance()->popScene();
    auto scene = GameScene::createScene();
    Director::getInstance()->pushScene(scene);
}

void GameScene::MainMenu(Ref* pSender)
{
    Director::getInstance()->popScene();
}
