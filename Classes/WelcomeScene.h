#ifndef WELCOMESCENE_H
#define WELCOMESCENE_H
#include "cocos2d.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;
USING_NS_CC;
class WelcomeScene:public Scene
{
public:
	CREATE_FUNC(WelcomeScene);
	virtual bool init();
};

#endif //WELCOMELAYER_H