#include "ControlLayer.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;
#define WINSIZE Director::getInstance()->getWinSize()

bool ControlLayer::init()
{
	//SpriteFrameCache::getInstance()->addSpriteFramesWithFile("ui/shoot.plist");

	//��Ӳ˵�
	auto button1 = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("game_pause_nor.png"));
	auto button2 = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("game_pause_pressed.png"));
	menuItem = MenuItemImage::create();
	menuItem->initWithNormalSprite(button1,button2, NULL, this, menu_selector(ControlLayer::menuCallBack));
	auto size = menuItem->getContentSize();

	menuItem->setPosition(ccp(WINSIZE.width-size.width/2, WINSIZE.height-size.height/2));
	auto menu = Menu::createWithItem(menuItem);
	menu->setPosition(Vec2(0,0));
	this->addChild(menu, 5,"menu");

	//��ʼ������
	scoreItem = LabelBMFont::create("0", "fonts/font.fnt");
	scoreItem->setColor(ccc3(143,146,147));
	scoreItem->setAnchorPoint(Vec2(1,1));
	scoreItem->setPosition(Vec2(WINSIZE.width,WINSIZE.height-60));
	this->addChild(scoreItem);
	return true;
}

void ControlLayer::menuCallBack(Ref* controlLayer)
{
	SimpleAudioEngine::getInstance()->playEffect("sound/newbutton.wav");
	ControlLayer* control=(ControlLayer*)controlLayer;
	if (!Director::getInstance()->isPaused())//����������Ϸ״̬
	{
		/*auto button1=Sprite::createWithSpriteFrameName(SpriteFrameCache::getInstance()->getSpriteFrameByName("game_resume_nor.png"))*/
		menuItem->setNormalSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("game_resume_nor.png"));
		menuItem->setSelectedSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("game_resume_pressed.png"));
		Director::getInstance()->pause();//��ͣ��Ϸ
		SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
		SimpleAudioEngine::getInstance()->pauseAllEffects();

	}
	else
	{
		menuItem->setNormalSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("game_pause_nor.png"));
		menuItem->setSelectedSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("game_pause_pressed.png"));

		Director::getInstance()->resume();//��Ϸ����
		SimpleAudioEngine::getInstance()->resumeBackgroundMusic();

		SimpleAudioEngine::getInstance()->resumeAllEffects();

	}
}

void ControlLayer::updateScore(int score)
{
	String* scoreStr = String::createWithFormat("%d", score);
	scoreItem->setString(scoreStr->getCString());//ת����char*����֮��ı�
}

