#include "EnemyLayer.h"
#define  WINSIZE Director::getInstance()->getWinSize()



void EnemyLayer::addEnemy(float dt)
{
	int type = random(1, 7);//随机获取类型
	Enemy* enemy;
	Sequence* sequence;
	Size size;
	float posX;
	MoveTo* actionMove;
	CCCallFuncN* actionFinished;
	switch (type)
	{
	case 1:case 2:case 3:case 4://加入类型1的敌机
		enemy=Enemy::createWithType(1);
		this->addChild(enemy);
		allEnemyOne.pushBack(enemy);//加入敌机
		size=enemy->getContentSize();
		posX = random(0, static_cast<int>(WINSIZE.width));
		enemy->setPosition(Vec2(posX,WINSIZE.height+size.height/2));//敌机生成位置
		
		break;
	case 5:case 6://加入类型2的敌机
		enemy=Enemy::createWithType(2);
		this->addChild(enemy);

		allEnemyTwo.pushBack(enemy);
		size = enemy->getContentSize();
		posX = random(0, static_cast<int>(WINSIZE.width));
		enemy->setPosition(Vec2(posX, WINSIZE.height + size.height / 2));
		
		break;
	case 7://加入类型3的敌机
		enemy=Enemy::createWithType(3);
		this->addChild(enemy);

		allEnemyThree.pushBack(enemy);
		size = enemy->getContentSize();
		posX = random(0, static_cast<int>(WINSIZE.width));
		enemy->setPosition(Vec2(posX, WINSIZE.height + size.height / 2));
		
		break;
	}
	this->schedule(schedule_selector(EnemyLayer::moveEnemy));//飞机移动

}



bool EnemyLayer::init()
{
	Layer::init();
	this->schedule(schedule_selector(EnemyLayer::addEnemy),0.5f);
	//this->scheduleUpdate();
	return true;
}

void EnemyLayer::moveEnemy(float dt)
{
	for (int i = 0; i < allEnemyOne.size(); ++i)
	{
		auto enemyOne = allEnemyOne.at(i);
		enemyOne->setPositionY(enemyOne->getPositionY() - 5);
		if (enemyOne->getPositionY()<-50)
		{

			allEnemyOne.eraseObject(enemyOne);

		}
	}
	for (int i = 0; i < allEnemyTwo.size(); ++i)
	{
		auto enemyTwo = allEnemyTwo.at(i);
		enemyTwo->setPositionY(enemyTwo->getPositionY() - 4);
		if (enemyTwo->getPositionY() < -50)
		{
			allEnemyTwo.eraseObject(enemyTwo);
		
		}
	}
	for (int i = 0; i < allEnemyThree.size(); ++i)
	{
		auto enemyThree = allEnemyThree.at(i);
		enemyThree->setPositionY(enemyThree->getPositionY() - 2);
		if (enemyThree->getPositionY() < -100)
		{
			enemyThree->removeFromParent();

			allEnemyThree.eraseObject(enemyThree);
			
		}
	}
}
