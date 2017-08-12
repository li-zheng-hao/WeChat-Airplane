#include "GameOverLayer.h"
#include "WelcomeScene.h"
#define WINSIZE Director::getInstance()->getWinSize()




GameOverLayer* GameOverLayer::create(int score)
{
	auto ptr = new GameOverLayer;
	if (ptr&&ptr->init(score))
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

bool GameOverLayer::init(int score)
{
	Layer::init();
	this->currentScore = score;
	highHistoryScore=UserDefault::getInstance()->getIntegerForKey("highHistoryScore");
	auto background = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("gameover.png"));
	background->setContentSize(Size(480,852));
	background->setPosition(Vec2(WINSIZE.width/2,WINSIZE.height/2));
	this->addChild(background);

	String* scoreStr = String::createWithFormat("%d", currentScore);
	auto currentScoreItem = LabelBMFont::create(scoreStr->getCString(), "fonts/font.fnt");
	currentScoreItem->setPosition(Vec2(WINSIZE.width/2,WINSIZE.height/2));
	this->addChild(currentScoreItem);

	
	String* maxScore = String::createWithFormat("%d", highHistoryScore);
	auto maxScoreItem = LabelBMFont::create(maxScore->getCString(), "fonts/font.fnt");
	maxScoreItem->setPosition(Vec2(150+50,WINSIZE.height-50-5));
	this->addChild(maxScoreItem);
	

	auto button1 = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("btn_finish.png"));
	
	MenuItemImage* menuItem = MenuItemImage::create();
	menuItem->initWithNormalSprite(button1, NULL, NULL, this, menu_selector(GameOverLayer::menuCallBack));

	//auto spr1 = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("btn_finished.png"));
	//auto backButton = MenuItemImage::create();
	//backButton->initWithNormalImage(spr1,NULL, NULL, this, menu_selector(GameOverLayer::menuCallBack));
	menuItem->setPosition(Vec2(WINSIZE.width/2,WINSIZE.height/2-200));
	auto menu = Menu::createWithItem(menuItem);
	menu->setPosition(Vec2(0,0));
	this->addChild(menu);
	return true;
}

void GameOverLayer::setHighHistoryScore(int score)
{
	
	if (score>highHistoryScore)
	{
		UserDefault::getInstance()->setIntegerForKey("highHistoryScore", score);
		highHistoryScore = score;
	}
}

void GameOverLayer::menuCallBack(Ref*)
{
	
	auto scen = WelcomeScene::create();
	auto scene=TransitionFade::create(0.5, scen);
	Director::getInstance()->replaceScene(scene);
}

int GameOverLayer::highHistoryScore=0;
