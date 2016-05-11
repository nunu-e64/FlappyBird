//
//  CharacterReader.h
//  FlappyBird
//
//  Created by Fumiya Amano on 2016/05/11.
//
//

#ifndef __FlappyBird__CharacterReader__
#define __FlappyBird__CharacterReader__

#include "cocos2d.h"
#include "cocostudio/WidgetReader/NodeReader/NodeReader.h"

class CharacterReader : public cocostudio::NodeReader {
public:
    static CharacterReader* getInstance();
    static void purge();
    cocos2d::Node* createNodeWithFlatBuffers(const flatbuffers::Table* nodeOptions);
};

#endif /* defined(__FlappyBird__Character__) */
