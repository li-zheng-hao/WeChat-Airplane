#include "BulletLayer.h"
#include "HeroLayer.h"
#include "SimpleAudioEngine.h"
#include "GameLayer.h"
using namespace CocosDenshion;
#define WINSIZE Director::getInstance()->getWinSize()




BulletLayer* BulletLayer::create()
{
	auto ptr = new BulletLayer;
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

bool BulletLayer::init()
{
	Layer::init();

	auto cache = SpriteFrameCache::getInstance();
	cache->addSpriteFramesWithFile("ui/shoot.plist");
	this->schedule(schedule_selector(BulletLayer::addBullet),0.2f);
	
	return true;
}

void BulletLayer::addBullet(float dt)
{

	//auto heroLayer = HeroLayer::create();
	auto gameLayer=(GameLayer*)this->getParent();
	auto heroLayer = (HeroLayer*)gameLayer->getChildByName("herolayer");
	auto heroPlane = heroLayer->getChildByName("heroplane");

	SimpleAudioEngine::getInstance()->playEffect("sound/newbullet.wav");
	//添加子弹
	auto bullet = Sprite::createWithSpriteFrameName("bullet1.png");
	bullet->setPosition(Vec2(heroPlane->getPositionX(),heroPlane->getPositionY()+50));
	bulletVec.pushBack(bullet);
	this->addChild(bullet);
	//子弹执行移动效果
	auto curPoint = bullet->getPosition();
	float speed = 3;
	auto size = bullet->getContentSize();


	auto moveAction = MoveTo::create(speed, Vec2(curPoint.x, size.height / 2 + WINSIZE.height));

	auto seq = Sequence::create(moveAction, CCCallFunc::create(this, SEL_CallFunc(&Sprite::removeFromParent)), NULL);

	//bullet->runAction(seq);
	this->schedule(schedule_selector(BulletLayer::moveBullet));//这一步采用定时器的方法，会随着帧率的变动而变动

}

void BulletLayer::moveFinished(Node* node)
{
	Sprite* spr = static_cast<Sprite*>(node);
	bulletVec.eraseObject(spr);
	spr->removeFromParentAndCleanup(true);
}

void BulletLayer::startShoot(float dt)
{
	this->schedule(schedule_selector(BulletLayer::addBullet),0.2f,-1,1.0f);
}

void BulletLayer::stopShoot()
{
	this->unschedule(schedule_selector(BulletLayer::addBullet));
}

void BulletLayer::removeBullet(Sprite*spr)
{
	bulletVec.eraseObject(spr);
	spr->cleanup();
}

void BulletLayer::moveBullet(float dt)
{
	for (int i=0;i<bulletVec.size();++i)
	{
		auto bullet = bulletVec.at(i);
		bullet->setPositionY(bullet->getPositionY() + 5);
		if (bullet->getPositionY()>WINSIZE.height+bullet->getContentSize().height/2)
		{
			bullet->removeFromParent();
			//bullet->removeFromParent();
			bulletVec.eraseObject(bullet);
		}
	}
}

