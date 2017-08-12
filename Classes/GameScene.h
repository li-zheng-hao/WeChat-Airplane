#ifndef GAME_SCENE_H
#define GAME_SCENE_H
#include "cocos2d.h"
#include "GameOverLayer.h"
USING_NS_CC;
class GameScene:public cocos2d::Scene
{
public:
	static GameScene* createScene();
	virtual bool init();
	
};

#endif