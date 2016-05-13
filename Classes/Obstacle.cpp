//
//  Obstacle.cpp
//  FlappyBird
//
//  Created by Fumiya Amano on 2016/05/12.
//
//

#include "Obstacle.h"
USING_NS_CC;

#pragma mark - Public methods

bool Obstacle::init() {
    if (!Node::init()) {
        return false;
    }

    // load the character animation timeline
    this->timeline = CSLoader::createTimeline("Obstacle.csb");
    // retain the character animation timeline so it doesn't get deallocated
    this->timeline->retain();

    return true;
}

#pragma mark - Private methods

#pragma mark View lifecycle

void Obstacle::onEnter()
{
    Node::onEnter();

    Sprite* pipeT = this->getChildByName<Sprite*>("pipe_top");
    Rect rectT = pipeT->getBoundingBox();
    this->rects.push_back(rectT);

    Sprite* pipeB = this->getChildByName<Sprite*>("pipe_bottom");
    Rect rectB = pipeB->getBoundingBox();
    this->rects.push_back(rectB);
    
    bool isFirst = false;
    for (Rect pipeRect : this->rects) {
        Sprite* sprite = Sprite::create();
        sprite->setTextureRect(pipeRect);
        sprite->setColor((isFirst ? Color3B::RED : Color3B::BLUE));
        sprite->setOpacity(100);
        this->addChild(sprite);
        sprite->setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT);
        sprite->setPosition(pipeRect.origin.x, pipeRect.origin.y);
        isFirst = true;
    }
}

void Obstacle::onExit()
{
    Node::onExit();
}

void Obstacle::moveLeft(float distance)
{
    CCLOG("distance: %f", distance);
    this->setPosition(this->getPosition() + Vec2(-distance, 0));
}

std::vector<Rect> Obstacle::getRects()
{
    std::vector<Rect> rects;
    for (auto rectPipe : this->rects)
    {
        Rect rect = rectPipe;
        rect.origin += this->getPosition();
        rects.push_back(rect);
    }
    return rects;
}