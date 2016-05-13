#include "MainScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "CharacterReader.h"
#include "Character.h"
#include "ObstacleReader.h"
#include "Obstacle.h"
#include "Constants.h"

USING_NS_CC;

using namespace cocostudio::timeline;

Scene* MainScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = MainScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool MainScene::init()
{
    /**  you can create scene with following comment code instead of using csb file.
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
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
    
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(label, 1);

    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("HelloWorld.png");

    // position the sprite on the center of the screen
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
    this->addChild(sprite, 0);
    **/
    
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    CSLoader* instance = CSLoader::getInstance();
    instance->registReaderObject("CharacterReader", (ObjectFactory::Instance) CharacterReader::getInstance);
    instance->registReaderObject("ObstacleReader", (ObjectFactory::Instance) ObstacleReader::getInstance);
    
    auto rootNode = CSLoader::createNode("MainScene.csb");
    Size size = Director::getInstance()->getVisibleSize();
    rootNode->setContentSize(size);
    ui::Helper::doLayout(rootNode);
    addChild(rootNode);
    
    this->backGround = rootNode->getChildByName("background");
    this->character = backGround->getChildByName<Character*>("character");
    this->groundA = this->backGround->getChildByName("groundA");
    this->groundB = this->backGround->getChildByName("groundB");
    this->scoreLabel = this->backGround->getChildByName<ui::TextBMFont*>("score_label");
    
    this->backGround->setLocalZOrder(-1);
    this->groundA->setLocalZOrder(1);
    this->groundB->setLocalZOrder(1);
    this->character->setLocalZOrder(1);
    this->scoreLabel->setLocalZOrder(2);
    
    return true;
}

void MainScene::onEnter()
{
    Layer::onEnter();
    
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->onTouchBegan = [&](Touch* touch, Event* event)
    {
        switch (this->state) {
        case State::Ready:
            this->triggerPlaying();
        case State::Playing:
            this->character->jump();
            break;
        case State::GameOver:
            Scene* nextGameScene = MainScene::createScene();
            TransitionFade* transition = TransitionFade::create(1.0f, nextGameScene);
            Director::getInstance()->replaceScene(transition);
            break;
        }
        return true;
    };
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);
    
    this->triggerReady();
}

void onTouchBegan(Touch* touch, Event* event)
{
    
}

void MainScene::update(float dt)
{
    switch (this->state) {
        case State::Ready:
            updateReady(dt);
            break;
        case State::Playing:
            updatePlaying(dt);
            break;
        case State::GameOver:
            updateGameOver(dt);
            break;
        default:
            break;
    }
}

void MainScene::updateReady(float dt)
{
    float distance = SCROLL_SPEED_X * dt;
    
    // Move Ground
    this->groundA->setPosition(this->groundA->getPosition() + Vec2(-distance, 0));
    this->groundB->setPosition(this->groundB->getPosition() + Vec2(-distance, 0));
    
    // Check Ground Position
    auto groundScrollCheck = [&](Node* ground, Node* baddyGround) {
        if (ground->getPositionX() + ground->getContentSize().width < 0)
        {
            ground->setPosition(baddyGround->getPosition() + Vec2(1, 0) * baddyGround->getContentSize().width);
        }
    };
    groundScrollCheck(this->groundA, this->groundB);
    groundScrollCheck(this->groundB, this->groundA);
}

void MainScene::updatePlaying(float dt)
{
    float distance = SCROLL_SPEED_X * dt;
    
    // Move Obstacle
    for (auto obstacle : this->obstacles) {
        obstacle->moveLeft(distance);
    }
    
    // Move Ground
    this->groundA->setPosition(this->groundA->getPosition() + Vec2(-distance, 0));
    this->groundB->setPosition(this->groundB->getPosition() + Vec2(-distance, 0));
    
    // Check Ground Position
    auto groundScrollCheck = [&](Node* ground, Node* baddyGround) {
        if (ground->getPositionX() + ground->getContentSize().width < 0)
        {
            ground->setPosition(baddyGround->getPosition() + Vec2(1, 0) * baddyGround->getContentSize().width);
        }
    };
    groundScrollCheck(this->groundA, this->groundB);
    groundScrollCheck(this->groundB, this->groundA);
    
    // Check Ground Collision
    if (this->character->getRect().getMinY() < this->groundA->getPositionY())
    {
        this->character->setPosition(this->character->getPositionX(), this->groundA->getPositionY() + this->character->getRect().size.height / 2);
        this->triggerGameOver();
    }
    
    // Check Obstacle Collision
    Rect characterRect = this->character->getRect();
    for (auto obstacle : this->obstacles) {
        auto obstacleRects = obstacle->getRects();
        
        for (Rect obstacleRect : obstacleRects) {
            bool hit = characterRect.intersectsRect(obstacleRect);
            if (hit)
            {
                this->triggerGameOver();
            }
        }
    }
    
    // Add Score
    float characterX = this->character->getPositionX();
    for (auto obstacle : this->obstacles) {
        float obstacleX = obstacle->getPositionX();
        if (characterX >= obstacleX && characterX - distance < obstacleX)
        {
            this->addScore();
        }
            
    }
}

void MainScene::updateGameOver(float dt)
{
    
}

void MainScene::createObstacle(float dt)
{
    // Create
    Obstacle* obstacle = dynamic_cast<Obstacle*>(CSLoader::createNode(("Obstacle.csb")));
    this->backGround->addChild(obstacle);
    assert(obstacle);

    // Set Random PositionY
    obstacle->setLocalZOrder(0);
    obstacle->setPosition(Vec2(OBSTACLE_INIT_X, Lerp(OBSTACLE_MIN_Y, OBSTACLE_MAX_Y, CCRANDOM_0_1())));
    this->obstacles.pushBack(obstacle);
    
    // Delete Obstacle
    if (this->obstacles.size() > OBSTACLE_LIMIT) {
        this->obstacles.front()->removeFromParent();
        this->obstacles.erase(this->obstacles.begin());
    }
}

void MainScene::triggerReady()
{
    this->score = 0;
    this->state = State::Ready;
    this->character->stopFly();
}

void MainScene::triggerPlaying(){
    this->state = State::Playing;
    this->character->startFly();
    this->scheduleUpdate();
    this->schedule(CC_SCHEDULE_SELECTOR(MainScene::createObstacle), OBSTACLE_TIME_SPAN);
}

void MainScene::triggerGameOver(){
    this->state = State::GameOver;
    this->unscheduleAllCallbacks();
}

void MainScene::addScore()
{
    this->scoreLabel->setString(std::to_string(++score));
}
