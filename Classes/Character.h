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

protected:
    cocostudio::timeline::ActionTimeline* timeline;
    
    void onEnter() override;
    void onExit() override;
    void update();
};

#endif /* defined(__FlappyBird__Character__) */
