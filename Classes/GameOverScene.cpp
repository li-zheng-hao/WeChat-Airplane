#include "GameOverScene.h"
#include "HeroLayer.h"
#include "GameOverLayer.h"

GameOverScene* GameOverScene::create(int score)
{
	auto ptr = new GameOverScene;
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

bool GameOverScene::init(int score)
{
	Scene::init();
	auto layer = GameOverLayer::create(score);
	layer->setHighHistoryScore(score);
	this->addChild(layer);
	
	return true;
}
