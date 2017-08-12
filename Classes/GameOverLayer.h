#ifndef GAMEOVERLAYER_H
#define GAMEOVERLAYER_H
#include "cocos2d.h"
USING_NS_CC;
class GameOverLayer:public Layer
{
public:
	static GameOverLayer* create(int score);
	virtual bool init(int score);
	void setHighHistoryScore(int score);
	void menuCallBack(Ref*);
public:
	static int highHistoryScore;//历史最高分
	int currentScore;
};

#endif

