#include "WelcomeLayer.h"
#include "GameScene.h"
#define WINSIZE Director::getInstance()->getWinSize()


bool WelcomeLayer::init()
{
	Layer::init();
	//游戏背景
	auto background1 = Sprite::createWithSpriteFrameName("background.png");
	background1->setPosition(Vec2(WINSIZE.width/2,WINSIZE.height/2));
	background1->setContentSize(Size(480, 852));
	this->addChild(background1);
	//游戏标题
	auto gameName = Sprite::create("ui/shoot_background/shoot_copyright.png");
	gameName->setPosition(Vec2(WINSIZE.width / 2, WINSIZE.height / 2+100));
	this->addChild(gameName);
	//游戏加载界面
	auto loading = Sprite::create("ui/shoot_background/game_loading1.png");
	loading->setPosition(Vec2(WINSIZE.width/2,WINSIZE.height/2-150));
	this->addChild(loading);
	auto animation = Animation::create();
	animation->addSpriteFrameWithFileName("ui/shoot_background/game_loading1.png");
	animation->addSpriteFrameWithFileName("ui/shoot_background/game_loading2.png");
	animation->addSpriteFrameWithFileName("ui/shoot_background/game_loading3.png");
	animation->addSpriteFrameWithFileName("ui/shoot_background/game_loading4.png");
	animation->setDelayPerUnit(0.2f);
	auto animate = Animate::create(animation);
	auto repeat = Repeat::create(animate, 3);
	auto call = CallFunc::create(this,callfunc_selector(WelcomeLayer::loadingFinished));
	auto sequence = Sequence::create(repeat, call,NULL);

	loading->runAction(sequence);
	return true;
}

bool WelcomeLayer::isDataFile()
{
	if (!UserDefault::getInstance()->getBoolForKey("isDataFile"))
	{
		UserDefault::getInstance()->setBoolForKey("isDataFile", true);
		UserDefault::getInstance()->setIntegerForKey("highHistoryScore", 0);
		UserDefault::getInstance()->flush();
		return false;
	}
	else
	{
		return true;
	}
}

void WelcomeLayer::loadingFinished()
{
	auto gameScene = GameScene::createScene();
	auto scene=TransitionFade::create(0.5f, gameScene);
	Director::getInstance()->replaceScene(scene);
}

int WelcomeLayer::getHighHistoryScore()
{
	return UserDefault::getInstance()->getIntegerForKey("highHistoryScore");
}
