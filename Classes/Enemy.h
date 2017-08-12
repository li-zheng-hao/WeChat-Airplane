#ifndef ENEMY_H
#define ENEMY_H
#include "cocos2d.h"
USING_NS_CC;
class Enemy:public Sprite
{
public:
	static Enemy* createWithType(int type);
	virtual bool init(int type);
	void addEnemyOne();//增加敌机类型1
	void addEnemyTwo();
	void addEnemyThree();
	void enemyBlowUp(int type);//飞机爆炸
	void initBlowAnimation();//加载爆炸动画到缓存


	
public:
	int life;//生命值
};

#endif
