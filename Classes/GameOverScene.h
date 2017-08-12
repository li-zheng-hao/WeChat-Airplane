#ifndef GAMEOVERSCENE_H
#define GAMEOVERSCENE_H
#include "cocos2d.h"
USING_NS_CC;
class GameOverScene:public Scene
{
public:
	static GameOverScene* create(int score);
	bool init(int score);
};
#endif

