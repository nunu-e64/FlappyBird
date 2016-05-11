//
//  Character.cpp
//  FlappyBird
//
//  Created by Fumiya Amano on 2016/05/11.
//
//

#include "Character.h"

#pragma mark - Public methods

bool Character::init() {
    if (!Node::init()) {
        return false;
    }

    // load the character animation timeline
    this->timeline = cocos2d::CSLoader::createTimeline("Character.csb");
    // retain the character animation timeline so it doesn't get deallocated
    this->timeline->retain();

    return true;
}

#pragma mark - Private methods

#pragma mark View lifecycle

void Character::onEnter()
{
    Node::onEnter();
}

void Character::onExit()
{
    Node::onExit();
}

void Character::update()
{
    
}
