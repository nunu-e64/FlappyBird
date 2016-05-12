//
//  Character.h
//  FlappyBird
//
//  Created by Fumiya Amano on 2016/05/11.
//
//

#ifndef __FlappyBird__Character__
#define __FlappyBird__Character__

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"

class Character : public cocos2d::Node {
public:
    CREATE_FUNC(Character);
    bool init() override;
    void jump();
    cocos2d::Rect getRect();

protected:
    cocostudio::timeline::ActionTimeline* timeline;

    void onEnter() override;
    void onExit() override;
    void update(float dt) override;

    float velocity;
    float accel;
    bool hasStarted;
    cocos2d::Rect rect;
    cocos2d::Size birdSize;
};

#endif /* defined(__FlappyBird__Character__) */
