#ifndef __MAIN_SCENE_H__
#define __MAIN_SCENE_H__

#include "cocos2d.h"
#include "ui/cocosGUI.h"
#include "Obstacle.h"

class Character;

enum State
{
    Ready,
    Playing,
    GameOver,
};

class MainScene : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

    // implement the "static create()" method manually
    CREATE_FUNC(MainScene);
    
    void addScore();
    
private:
    void onEnter() override;
    void update(float dt) override;
    void updateReady(float dt);
    void updatePlaying(float dt);
    void updateGameOver(float dt);
    void createObstacle(float dt);
    void triggerReady();
    void triggerPlaying();
    void triggerGameOver();
    
    Character* character;
    cocos2d::Vector<Obstacle*> obstacles;
    cocos2d::Node* backGround;
    cocos2d::Node* groundA;
    cocos2d::Node* groundB;
    cocos2d::ui::TextBMFont* scoreLabel;
    
    State state;
    int score;
    
};

#endif // __MAIN_SCENE_H__
