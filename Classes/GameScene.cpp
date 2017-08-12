#include "GameScene.h"
#include "GameLayer.h"
GameScene* GameScene::createScene()
{
	auto scene = new GameScene;
	if (scene&&scene->init())
	{
		scene->autorelease();		
	}
	else
	{
		delete scene;
		scene = nullptr;
	}
	return scene;
}

bool GameScene::init()
{
	Scene::init();
	auto mainLayer = GameLayer::create();
	this->addChild(mainLayer);
	return true;
}


