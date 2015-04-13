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
    
    return true;
}

void GameScene::InitDefaults()
{
    _GameIsPaused = false;
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
