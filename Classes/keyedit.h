#pragma once
#include <time.h>
#include"cocos2d.h"

USING_NS_CC;
 class keyedit: public cocos2d::CCSprite
{
public:
	keyedit(void);
	~keyedit(void);
	keyedit(long time,int positionX,int positionY,bool isSpecialKey=false);
	//Ϊ����㽨����һϵ������
	bool isSpecialKey;
	static int keyAmount;
	static int specialAmount;
	int specialTag;


	bool isClick;
	long createTime;
	long endTime;
	int PositionX;
	int PositionY;
	void keyRunAnimation(CCPoint moveTo = ccp(0,0));
	void Change();
};


