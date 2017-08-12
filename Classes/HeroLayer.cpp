#include "HeroLayer.h"
#define WINSIZE Director::getInstance()->getWinSize()




HeroLayer* HeroLayer::create()
{
	auto ptr = new HeroLayer();
	if (ptr&&ptr->init())
	{
		ptr->autorelease();
	}
	else
	{
		delete ptr;
		ptr = nullptr;
	}
	return ptr;
	
}

bool HeroLayer::init()
{
	Layer::init();
	//添加飞机纹理
	auto cache = SpriteFrameCache::getInstance();
	cache->addSpriteFramesWithFile("ui/shoot.plist");
	//添加飞机
	auto hero = Sprite::createWithSpriteFrameName("hero1.png");
	hero->setPosition(Vec2(WINSIZE.width/2,50));
	hero->setAnchorPoint(Vec2(0.5,0.5));
	this->addChild(hero, 0, "heroplane");
	this->isAlive = true;
	this->score = 0;
	//闪烁动画
	auto blink = Blink::create(0.5f, 5);
	//飞机尾气动画
	auto animation = Animation::create();
	animation->setDelayPerUnit(0.1f);
	animation->addSpriteFrame(cache->getSpriteFrameByName("hero1.png"));
	animation->addSpriteFrame(cache->getSpriteFrameByName("hero2.png"));
	auto animate = Animate::create(animation);
	
	hero->runAction(blink);//执行闪烁动画
	hero->runAction(RepeatForever::create(animate));//执行帧动画
	

	
	return true;
}

void HeroLayer::moveTo()
{
}

void HeroLayer::blowUp()
{
}

void HeroLayer::removePlaneAndGameOver()
{
}


