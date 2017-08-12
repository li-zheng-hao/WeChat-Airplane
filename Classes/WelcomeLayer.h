#ifndef WELCOMELAYER_H
#define WELCOMELAYER_H
#include "cocos2d.h"
USING_NS_CC;
class WelcomeLayer:public Layer
{
public:
	CREATE_FUNC(WelcomeLayer);
	virtual bool init();
	bool isDataFile();
	void loadingFinished();

	int getHighHistoryScore();
};

#endif
