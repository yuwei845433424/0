#pragma once
#include <time.h>
#include"cocos2d.h"
class keyedit: public cocos2d::CCSprite
{
public:
	keyedit(void);
	~keyedit(void);
	keyedit(long time);
	bool isClick;
	long createTime;
	long endTime;
	int positionX;
	int positionY;
	void keyRunAnimation();
	void Change();
};


