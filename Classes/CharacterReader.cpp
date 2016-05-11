//
//  CharacterReader.cpp
//  FlappyBird
//
//  Created by Fumiya Amano on 2016/05/11.
//
//

#include "CharacterReader.h"
#include "Character.h"

using namespace cocos2d;

static CharacterReader* _instanceCharacterReader = nullptr;

CharacterReader* CharacterReader::getInstance() {
    if (!_instanceCharacterReader) {
        _instanceCharacterReader = new CharacterReader();
    }
    return _instanceCharacterReader;
}

void CharacterReader::purge() {
    CC_SAFE_DELETE(_instanceCharacterReader);
}

Node* CharacterReader::createNodeWithFlatBuffers(const flatbuffers::Table *nodeOptions) {
    Character* node = Character::create();
    setPropsWithFlatBuffers(node, nodeOptions);
    return node;
}
