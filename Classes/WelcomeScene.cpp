#include "WelcomeScene.h"
#include "WelcomeLayer.h"

bool WelcomeScene::init()
{

	Scene::init();
	//欢迎界面用来提前加载纹理和音乐
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic("sound/newgamemusic.wav");
	SimpleAudioEngine::getInstance()->preloadEffect("sound/newbullet.wav");

	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("ui/shoot_background.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("ui/shoot.plist");

	auto welcomeLayer = WelcomeLayer::create();
	this->addChild(welcomeLayer);
	return true;
}


