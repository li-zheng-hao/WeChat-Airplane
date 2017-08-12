#include "GameLayer.h"
#include "GameOverScene.h"
#define WINSIZE Director::getInstance()->getWinSize()


GameLayer* GameLayer::create()
{
	auto ptr = new GameLayer;
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

bool GameLayer::init()
{
	Layer::init();
	//先播放背景音乐
	SimpleAudioEngine::getInstance()->playBackgroundMusic("sound/newgamemusic.wav",true);
	
	
	//初始化游戏分数
	score = 0;

	//缓存所有背景图片
	auto frameCache = SpriteFrameCache::getInstance();
	

	//以下创建两个背景循环滚动
	//background1 = Sprite::createWithSpriteFrameName("background.png");
	background1 = Sprite::create("ui/shoot_background/background.png");
	background1->setAnchorPoint(Vec2(0.5, 0.5));
	background1->setPosition(Vec2(WINSIZE.width / 2, WINSIZE.height / 2-2));
	background1->setContentSize(Size(480,852));
	this->addChild(background1);
	CCLOG("%f,%f", background1->getContentSize().width, background1->getContentSize().height);

	CCLOG("%f,%f", background1->getContentSize().width, background1->getContentSize().height);
	background2 = Sprite::create("ui/shoot_background/background.png");

	background2->setAnchorPoint(Vec2(0.5, 0.5));
	background2->setContentSize(Size(480, 852));
	background2->setPosition(Vec2(WINSIZE.width/ 2, WINSIZE.height*3 / 2-2));
	this->addChild(background2);
	this->schedule(schedule_selector(GameLayer::backgroundMove),0.05f);

	//添加主角战机
	auto heroLayer = HeroLayer::create();
	this->addChild(heroLayer,10,"herolayer");
	//Sprite * heroPlane =(Sprite*) heroLayer->getChildByName("heroplane");
	//添加子弹层
	auto bulletLayer = BulletLayer::create();
	this->addChild(bulletLayer, 0, "bulletlayer");
	bulletVec = &(bulletLayer->bulletVec);
	bulletLayer->startShoot(1);

	//添加敌机层
	auto enemyLayer = EnemyLayer::create();
	this->addChild(enemyLayer);
	allEnemyOne = &(enemyLayer->allEnemyOne);
	allEnemyTwo = &(enemyLayer->allEnemyTwo);
	allEnemyThree = &(enemyLayer->allEnemyThree);

	//创建结束层
	//添加控制层控制暂停和分数的显示
	auto controlLayer = ControlLayer::create();
	this->addChild(controlLayer, 5, "controllayer");

	//检测子弹和敌机的碰撞
	this->schedule(schedule_selector(GameLayer::checkCrash));

	//设置触摸属性
	auto touchlistener = EventListenerTouchOneByOne::create();

	touchlistener->onTouchBegan = [&](Touch*t, Event*e) {
		return true;
	};
	touchlistener->onTouchMoved = [&](Touch*t, Event*e) {
		auto heroLayer = (HeroLayer*)this->getChildByName("herolayer");
		Sprite*heroPlane = (Sprite*)heroLayer->getChildByName("heroplane");
		if (heroLayer->isAlive && !Director::getInstance()->isPaused())
		{
			
			Size size = heroPlane->getContentSize();
			if (heroPlane->getBoundingBox().containsPoint(t->getLocation()))
			{
				/*if (heroPlane->getPositionX() > size.width / 2 && heroPlane->getPositionX() < WINSIZE.width - size.width / 2 &&
					heroPlane->getPositionY() > size.height / 2 && heroPlane->getPositionY() < WINSIZE.height - size.height / 2)*/
					heroPlane->setPosition(t->getLocation());
					if (heroPlane->getPositionX() < size.width/2)
						heroPlane->setPositionX(size.width/2);
					if (heroPlane->getPositionX() > WINSIZE.width - size.width / 2)
						heroPlane->setPositionX(WINSIZE.width-size.width/2);
					if (heroPlane->getPositionY() < size.height / 2-15)
						heroPlane->setPositionY(size.height/2-15);
					if (heroPlane->getPositionY() > WINSIZE.height - size.height / 2)
						heroPlane->setPositionY(WINSIZE.height - size.height / 2);
			}
		}
	};

	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchlistener, heroLayer);

	return true;
}

void GameLayer::backgroundMove(float dt)
{
	background1->setPositionY(background1->getPositionY() - 5);
	//auto downHeight1 = -(background1->getContentSize().height);
	if (background1->getPositionY() < -WINSIZE.height / 2)
	{
		background1->setPositionY(WINSIZE.height * 3 / 2-5);
	}

	background2->setPositionY(background2->getPositionY() - 5);
	//auto downHeight2 = -(background2->getContentSize().height);
	if (background2->getPositionY() < -WINSIZE.height/2)
	{
		background2->setPositionY( WINSIZE.height * 3 / 2-5);
	}
}

void GameLayer::checkCrash(float dt)
{

	ControlLayer* controllayer =(ControlLayer*) this->getChildByName("controllayer");
	for (auto i=0; i < bulletVec->size(); i++)
	{
		
		auto Bullet = bulletVec->at(i);
		for(int j=0;j<allEnemyOne->size();++j)
		{
			Enemy* enemyOne = allEnemyOne->at(j);
			if (enemyOne->getBoundingBox().containsPoint(Bullet->getPosition()))
			{

				enemyOne->enemyBlowUp(1);//爆炸之后自动从父类删除
				SimpleAudioEngine::getInstance()->playEffect("sound/newenemy1.wav");
				//实现分数的增加
				score += 100;
				controllayer->updateScore(score);
				
				allEnemyOne->eraseObject(enemyOne);
				bulletVec->eraseObject(Bullet);
				Bullet->removeFromParentAndCleanup(true);
				goto END;
			

			}
		}
		for (int k = 0; k < allEnemyTwo->size(); ++k)
		{
			Enemy* enemyTwo = allEnemyTwo->at(k);

			if (enemyTwo->getBoundingBox().containsPoint(Bullet->getPosition()))
			{
				enemyTwo->life -= 100;
				if (enemyTwo->life==0)
				{
					enemyTwo->enemyBlowUp(2);//爆炸之后自动从父类删除
					//实现分数的增加
					score += 200;
					controllayer->updateScore(score);

					SimpleAudioEngine::getInstance()->playEffect("sound/newenemy2.wav");
					allEnemyTwo->eraseObject(enemyTwo);
				}

				bulletVec->eraseObject(Bullet);
				Bullet->removeFromParentAndCleanup(true);

				goto END;
			}
		}
		for (int l = 0; l< allEnemyThree->size(); ++l)
		{
			Enemy* enemyThree = allEnemyThree->at(l);

			if (enemyThree->getBoundingBox().containsPoint(Bullet->getPosition()))
			{
				enemyThree->life -= 50;
				auto animation = AnimationCache::getInstance()->animationByName("enemy3hit");//动画事先加入动画池  

				auto action = Animate::create(animation);
				enemyThree->runAction(action);
				if (enemyThree->life == 0)
				{
					enemyThree->enemyBlowUp(3);//爆炸之后自动从父类删除
					//实现分数的增加
					score += 500;
					controllayer->updateScore(score);

					SimpleAudioEngine::getInstance()->playEffect("sound/newenemy3.wav");

					allEnemyThree->eraseObject(enemyThree);
				}

				bulletVec->eraseObject(Bullet);
				Bullet->removeFromParentAndCleanup(true);

				goto END;

			}

		}
	END:
		;

	//检测主角是否死亡
		auto heroLayer = this->getChildByName("herolayer");
		Sprite*heroPlane = (Sprite*)heroLayer->getChildByName("heroplane");
		auto maxX = heroPlane->getBoundingBox().getMaxX();
		auto minX = heroPlane->getBoundingBox().getMinX();

		auto maxY=heroPlane->getBoundingBox().getMaxY();
		auto minY = heroPlane->getBoundingBox().getMinY();


		auto posOne = Vec2((maxX - minX) / 2 + minX, maxY);
		auto posTwo = Vec2(minX+10,minY);
		auto posThree = Vec2(maxX-10,minY);
		for (int num1 = 0; num1 < allEnemyOne->size(); ++num1)
		{
			Enemy* enemyOne = allEnemyOne->at(num1);
			if (enemyOne->getBoundingBox().containsPoint(posOne)
				|| enemyOne->getBoundingBox().containsPoint(posTwo)
				|| enemyOne->getBoundingBox().containsPoint(posThree)
				)
			{
				auto game = GameOverScene::create(score);
				auto scene = TransitionFade::create(0.5f, game);
				Director::getInstance()->replaceScene(scene);
			}				
		}
		for (int num1 = 0; num1 < allEnemyTwo->size(); ++num1)
		{
			Enemy* enemyTwo = allEnemyTwo->at(num1);
			if (enemyTwo->getBoundingBox().containsPoint(posOne)
				|| enemyTwo->getBoundingBox().containsPoint(posTwo)
				|| enemyTwo->getBoundingBox().containsPoint(posThree)
				)
			{

				auto game = GameOverScene::create(score);
				auto scene = TransitionFade::create(0.5f, game);
				Director::getInstance()->replaceScene(scene);
			}
		}
		for (int num1 = 0; num1 < allEnemyThree->size(); ++num1)
		{
			Enemy* enemyThree= allEnemyThree->at(num1);
			if (enemyThree->getBoundingBox().containsPoint(posOne)
				|| enemyThree->getBoundingBox().containsPoint(posTwo)
				|| enemyThree->getBoundingBox().containsPoint(posThree)
				)
			{


				auto game = GameOverScene::create(score);
				auto scene = TransitionFade::create(0.5f, game);
				Director::getInstance()->replaceScene(scene);
			}


		}
	}
}

