#ifndef GAME_LAYER_H
#define GAME_LAYER_H
#include "cocos2d.h"
#include "HeroLayer.h"
#include "BulletLayer.h"
#include "EnemyLayer.h"
#include "Enemy.h"
#include "ControlLayer.h"
#include "GameOverLayer.h"
#include "WelcomeLayer.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;
USING_NS_CC;
class GameLayer:public cocos2d::Layer
{
public:
	static GameLayer* create();
	virtual bool init();
	void backgroundMove(float dt);
	void checkCrash(float dt);
	
private:
	Sprite* background1, *background2;
	Vector<Sprite*> *bulletVec;//对子弹层的数据引用
	Vector<Enemy*> *allEnemyOne;//对敌机层的数据引用
	Vector<Enemy*> *allEnemyTwo;
	Vector<Enemy*> *allEnemyThree;
	int score;//游戏分数
};
#endif

