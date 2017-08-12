#include "WelcomeScene.h"
#include "WelcomeLayer.h"

bool WelcomeScene::init()
{

	Scene::init();
	//��ӭ����������ǰ�������������
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic("sound/newgamemusic.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("sound/newbullet.wav");

	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("ui/shoot_background.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("ui/shoot.plist");

	auto welcomeLayer = WelcomeLayer::create();
	this->addChild(welcomeLayer);
	return true;
}


