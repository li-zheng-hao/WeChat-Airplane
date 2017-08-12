#include "UFOLayer.h"
#define WINSIZE Director::getInstance()->getWinSize()



bool UFOLayer::init()
{
	Layer::init();
	Sprite* multiBullet = (Sprite*)SpriteFrameCache::getInstance()->spriteFrameByName("ufo1.png");
	auto size = multiBullet->getContentSize();
	float posX = random(WINSIZE.width-WINSIZE.width, WINSIZE.width);
	multiBullet->setPosition(Vec2(posX, WINSIZE.height+size.height/2));
	this->addChild(multiBullet, 0, "multiBullet");
	return true;
}
