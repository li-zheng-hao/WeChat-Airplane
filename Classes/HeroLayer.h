#ifndef HERO_LAYER_H
#define HERO_LAYER_H
#include "cocos2d.h"
USING_NS_CC;
class HeroLayer:public Layer
{
public:
	static HeroLayer*create();
	virtual bool init();
	void moveTo();//�ƶ��ɻ�
	void blowUp();//��ըЧ��
	void removePlaneAndGameOver();//��Ϸ����������ת����������
	

public:
	bool isAlive;//�Ƿ���
	int score;//����

};

#endif // HERO_LAYER_H
