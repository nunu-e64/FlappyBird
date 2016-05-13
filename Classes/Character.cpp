//
//  Character.cpp
//  FlappyBird
//
//  Created by Fumiya Amano on 2016/05/11.
//
//

#include "Character.h"
#include "Constants.h"
USING_NS_CC;

#pragma mark - Public methods

bool Character::init() {
    if (!Node::init()) {
        return false;
    }

    // load the character animation timeline
    this->timeline = cocos2d::CSLoader::createTimeline("Character.csb");
    // retain the character animation timeline so it doesn't get deallocated
    this->timeline->retain();

    this->scheduleUpdate();
    this->velocity = 0;
    this->accel = GRAVITY_ACCEL;
    this->hasStarted = false;

    return true;
}

#pragma mark - Private methods

#pragma mark View lifecycle

void Character::onEnter()
{
    Node::onEnter();
    
    Sprite* spriteBird = this->getChildByName<Sprite*>("bird");
    this->rect = spriteBird->getBoundingBox();
    
    Sprite* sprite = Sprite::create();
    sprite->setTextureRect(this->rect);
    sprite->setColor(Color3B::WHITE);
    sprite->setOpacity(100);
    this->addChild(sprite);
    
    birdSize = spriteBird->getContentSize() * 0.8f;
    
}

void Character::onExit()
{
    Node::onExit();
}

void Character::update(float dt)
{
    if (!this->hasStarted) return;
    
    if (this->isFlying)
    {
        this->velocity += this->accel * dt;
        this->setPosition(this->getPosition() + Vec2(0, this->velocity * dt));
    }
}

void Character::jump()
{
    this->hasStarted = true;
    this->velocity = JUMP_SPEED;
    this->timeline->play("Fly", false);
}

Rect Character::getRect()
{
    Rect rect = this->rect;
    rect.origin += this->getPosition();
    return rect;
}

void Character::startFly()
{
    this->isFlying = true;
}

void Character::stopFly()
{
    this->isFlying = false;
}