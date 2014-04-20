#pragma once
#include "keyedit.h"
#include "cocos2d.h"

USING_NS_CC;

keyedit::keyedit(void)
{
}


keyedit::~keyedit(void)
{
}

keyedit::keyedit(long time)
{
	isClick = false;
	CCSize screenSize=CCDirector::sharedDirector()->getVisibleSize();
	createTime = time;
	positionX = rand()%(int)(screenSize.width);
	positionY = rand()%(int)(screenSize.height);
	this->setPosition(ccp(positionX,positionY));
	this->initWithFile("key.png");
}

void keyedit::keyRunAnimation()
{
	CCActionInterval *rotation = CCRotateTo::create(1,180);
	this->runAction(rotation);

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