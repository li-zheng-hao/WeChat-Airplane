#ifndef BULLET_LAYER_H 
#define BULLET_LAYER_H
#include "cocos2d.h"
USING_NS_CC;
class BulletLayer:public Layer
{
public:

	static BulletLayer*create();
	virtual bool init();
	void addBullet(float dt);
	void moveFinished(Node* node);
	void startShoot(float dt);
	void stopShoot();
	void removeBullet(Sprite*spr);
	void moveBullet(float dt);
public:
	Vector<Sprite*> bulletVec;
};

#endif // BULLET_LAYER_H
