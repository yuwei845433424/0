#pragma once
#include "keyedit.h"
#include "cocos2d.h"
#include "HelloWorldScene.h"
#include "line.h"
USING_NS_CC;

keyedit::keyedit(void)
{
}


keyedit::~keyedit(void)
{
}

keyedit::keyedit(long time,int positionX,int positionY,bool isSpecialKey)
{
	this->isSpecialKey = isSpecialKey;
	isClick = false;
	CCSize screenSize=CCDirector::sharedDirector()->getVisibleSize();
	createTime = time;
	this->PositionX = positionX;
	this->PositionY = positionY;
	this->setPosition(ccp(PositionX,PositionX));
	this->initWithFile("key.png");

	keyAmount++;
}

void keyedit::keyRunAnimation(CCPoint moveTo)
{
	CCActionInterval *rotation = CCRotateTo::create(1,180);
	if(this->isSpecialKey)
	{
		CCActionInterval *movoTo = CCMoveTo::create(1,moveTo);
		CCFiniteTimeAction *se=CCSpawn::create(rotation,movoTo,NULL);
		se->retain(); 
		this->runAction(se);
		this->specialAmount++;
	}
	else
	{
		this->runAction(rotation);
	}
}
//换图片
void keyedit::Change()
{	
	CCAnimation* animation = CCAnimation::create();
	animation->addSpriteFrameWithFileName("key2.png");
	animation->setDelayPerUnit(2.8f / 14.0f);//必须设置否则不会动态播放
	animation->setRestoreOriginalFrame(false);//是否回到第一帧
	animation->setLoops(1);//重复次数 （-1:无限循环）
	CCFiniteTimeAction * animate = CCAnimate::create(animation);
	this->runAction(animate);
}