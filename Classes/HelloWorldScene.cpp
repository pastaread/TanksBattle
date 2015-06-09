#include "HelloWorldScene.h"
#include "GameScene.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.
    
    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create("CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
    closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));
    
    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
    
    
    // Background
    auto backg = Sprite::create("Ground.png");
    backg->setPosition(visibleSize.width * 0.5f, visibleSize.height * 0.5f);
    backg->setScale(visibleSize.width / 1242.0f, visibleSize.height / 2208.0f);
    this->addChild(backg);
    
    
    
    // Button: start game
    auto startItem = MenuItemImage::create("buttonGamePlay.png",
                                           "buttonGamePlay.png",
                                           CC_CALLBACK_1(HelloWorld::startGame, this));
    
    startItem->setPosition(Vec2(visibleSize.width * 0.5f, visibleSize.height * 0.3f));
    
    // create menu, it's an autorelease object
    // Menu with start game button
    auto menuStart = Menu::create(startItem, NULL);
    menuStart->setPosition(Vec2::ZERO);
    this->addChild(menuStart, 1);
    
    return true;
}

void HelloWorld::startGame(cocos2d::Ref* pSender)
{
    auto scene = GameScene::createScene();
    
    Director::getInstance()->pushScene(scene);
}

void HelloWorld::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
    MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif
    
    Director::getInstance()->end();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
