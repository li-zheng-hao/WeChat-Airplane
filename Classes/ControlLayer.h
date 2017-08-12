#ifndef PUASELAYER_H
#define PUASELAYER_H
#include "cocos2d.h"
USING_NS_CC;
class ControlLayer:public Layer
{
public:
	CREATE_FUNC(ControlLayer);
	virtual bool init();
	void menuCallBack(Ref*);
	void updateScore(int score);
public:
	MenuItemImage* menuItem;
	LabelBMFont* scoreItem;

};


#endif
