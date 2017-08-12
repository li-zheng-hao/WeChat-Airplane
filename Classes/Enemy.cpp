#include "Enemy.h"


Enemy* Enemy::createWithType(int type)
{
	auto enemy = new Enemy;
	if (enemy&&enemy->init(type))
	{
		enemy->autorelease();
	}
	else
	{
		delete enemy;
		enemy = nullptr;
	}
	return enemy;
}

bool Enemy::init(int type)
{
	Sprite::init();
	initBlowAnimation();//加载爆炸动画到缓存
	switch (type)
	{
	case 1:
		addEnemyOne();
		break;
	case 2:
		addEnemyTwo();
		break;
	case 3:
		addEnemyThree();
		break;
	default:
		CCLOG("Wrong Enemy Type");
		return false;
	}
	return true;
}

int Enemy::getLife()
{
	return life;
}

void Enemy::setLife(int life)
{
	this->life = life;
}

void Enemy::reduceLife()
{
	life--;
}

void Enemy::addEnemyOne()
{
	this->initWithSpriteFrameName("enemy1.png");
	this->setLife(100);

}

void Enemy::addEnemyTwo()
{
	this->initWithSpriteFrameName("enemy2.png");
	this->setLife(200);
}

void Enemy::addEnemyThree()
{
	this->initWithSpriteFrameName("enemy3_n1.png");
	this->setLife(500);
	auto action1 = SpriteFrameCache::getInstance()->spriteFrameByName("enemy3_n1.png");
	auto action2 = SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy3_n2.png");
	auto animation = Animation::create();
	animation->addSpriteFrame(action1);
	animation->addSpriteFrame(action2);
	animation->setDelayPerUnit(0.2f);
	auto animate = Animate::create(animation);
	this->runAction(RepeatForever::create(animate));

}

void Enemy::removeEnemy()
{
	this->removeFromParentAndCleanup(true);
}

void Enemy::enemyBlowUp(int type)
{
	Animation* animation;
	switch (type)
	{
	case 1:
		animation=AnimationCache::getInstance()->animationByName("enemy1");//动画事先加入动画池  
		break;
	case 2:
		animation = AnimationCache::getInstance()->animationByName("enemy2");//动画事先加入动画池  
		break;
	case 3:
		animation = AnimationCache::getInstance()->animationByName("enemy3");//动画事先加入动画池  
		break;
	}
	auto animate = Animate::create(animation);
	auto ationFinished = CCCallFunc::create(this, CC_CALLFUNC_SELECTOR(Enemy::removeFromParent));
	auto actionDone = CCCallFunc::create(this, SEL_CallFunc(&Enemy::cleanup));
	Action* sequence = Sequence::create(animate, ationFinished, actionDone,NULL);
	this->runAction(sequence);
	

}

void Enemy::initBlowAnimation()
{
	//添加敌机1类的爆炸动画
	Animation* animation1 = Animation::create();
	SpriteFrame*  sprite1_1 = SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy1_down1.png");
	SpriteFrame*  sprite2_1 = SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy1_down2.png");
	SpriteFrame*  sprite3_1 = SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy1_down3.png");
	SpriteFrame*  sprite4_1 = SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy1_down4.png");
	animation1->addSpriteFrame(sprite1_1);
	animation1->addSpriteFrame(sprite2_1);
	animation1->addSpriteFrame(sprite3_1);
	animation1->addSpriteFrame(sprite4_1);
	animation1->setDelayPerUnit(0.05f);
	AnimationCache::getInstance()->addAnimation(animation1, "enemy1");
	//添加敌机2的爆炸动画
	Animation* animation2 = Animation::create();
	SpriteFrame* sprite1_2 = SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy2_down1.png");
	SpriteFrame*  sprite2_2 = SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy2_down2.png");
	SpriteFrame*  sprite3_2 = SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy2_down3.png");
	SpriteFrame*  sprite4_2 = SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy2_down4.png");
	animation2->addSpriteFrame(sprite1_2);
	animation2->addSpriteFrame(sprite2_2);
	animation2->addSpriteFrame(sprite3_2);
	animation2->addSpriteFrame(sprite4_2);
	animation2->setDelayPerUnit(0.05f);


	AnimationCache::getInstance()->addAnimation(animation2, "enemy2");
	//添加敌机3的爆炸动画
	Animation* animation3 = Animation::create();
	SpriteFrame*  sprite1_3 = SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy3_down1.png");
	SpriteFrame*  sprite2_3 = SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy3_down2.png");
	SpriteFrame*  sprite3_3 = SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy3_down3.png");
	SpriteFrame*  sprite4_3 = SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy3_down4.png");
	SpriteFrame*  sprite5_3 = SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy3_down5.png");
	SpriteFrame*  sprite6_3 = SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy3_down6.png");
	animation3->addSpriteFrame(sprite1_3);
	animation3->addSpriteFrame(sprite2_3);
	animation3->addSpriteFrame(sprite3_3);
	animation3->addSpriteFrame(sprite4_3);
	animation3->addSpriteFrame(sprite5_3);
	animation3->addSpriteFrame(sprite6_3);
	animation3->setDelayPerUnit(0.05f);

	AnimationCache::getInstance()->addAnimation(animation3, "enemy3");

	//添加击中动画
	Animation* animation4 = Animation::create();
	SpriteFrame*  sprite1_4 = SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy3_n1.png");
	SpriteFrame*  sprite2_4 = SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy3_hit.png");
	animation4->addSpriteFrame(sprite1_4);
	animation4->addSpriteFrame(sprite2_4);
	animation4->setDelayPerUnit(0.05f);
	AnimationCache::getInstance()->addAnimation(animation4, "enemy3hit");






}

void Enemy::enemyHit(int type)
{
	switch (type)
	{
	case 3:

		break;
	}
}


