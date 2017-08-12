#ifndef HERO_LAYER_H
#define HERO_LAYER_H
#include "cocos2d.h"
USING_NS_CC;
class HeroLayer:public Layer
{
public:
	static HeroLayer*create();
	virtual bool init();
	void moveTo();//移动飞机
	void blowUp();//爆炸效果
	void removePlaneAndGameOver();//游戏结束并且跳转到结束场景
	

public:
	bool isAlive;//是否存活
	int score;//分数

};

#endif // HERO_LAYER_H
