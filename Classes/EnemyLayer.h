#ifndef ENEMY_LAYER_H
#define ENEMY_LAYER_H
#include "cocos2d.h"
#include "Enemy.h"
#include "BulletLayer.h"
USING_NS_CC;
class EnemyLayer:public Layer
{
public:
	CREATE_FUNC(EnemyLayer);
	virtual bool init();
	void moveEnemy(float dt);
	void addEnemy(float dt);

public:
	Vector<Enemy*> allEnemyOne;
	Vector<Enemy*> allEnemyTwo;
	Vector<Enemy*> allEnemyThree;
	int gameLevel;


	
};

#endif
