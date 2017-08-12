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
	//��ӷɻ�����
	auto cache = SpriteFrameCache::getInstance();
	cache->addSpriteFramesWithFile("ui/shoot.plist");
	//��ӷɻ�
	auto hero = Sprite::createWithSpriteFrameName("hero1.png");
	hero->setPosition(Vec2(WINSIZE.width/2,50));
	hero->setAnchorPoint(Vec2(0.5,0.5));
	this->addChild(hero, 0, "heroplane");
	this->isAlive = true;
	this->score = 0;
	//��˸����
	auto blink = Blink::create(0.5f, 5);
	//�ɻ�β������
	auto animation = Animation::create();
	animation->setDelayPerUnit(0.1f);
	animation->addSpriteFrame(cache->getSpriteFrameByName("hero1.png"));
	animation->addSpriteFrame(cache->getSpriteFrameByName("hero2.png"));
	auto animate = Animate::create(animation);
	
	hero->runAction(blink);//ִ����˸����
	hero->runAction(RepeatForever::create(animate));//ִ��֡����
	

	
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


