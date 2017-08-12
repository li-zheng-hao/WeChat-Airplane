#ifndef ENEMY_H
#define ENEMY_H
#include "cocos2d.h"
USING_NS_CC;
class Enemy:public Sprite
{
public:
	static Enemy* createWithType(int type);
	virtual bool init(int type);
	void addEnemyOne();//���ӵл�����1
	void addEnemyTwo();
	void addEnemyThree();
	void enemyBlowUp(int type);//�ɻ���ը
	void initBlowAnimation();//���ر�ը����������


	
public:
	int life;//����ֵ
};

#endif
