#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "keyedit.h"
#include <vector>
#include <time.h>



USING_NS_CC;
using std::vector;
class HelloWorld : public cocos2d::CCLayer
{
public:
	void newUpdate(float dt);
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

	long GameBeginTime;
	int currentScore;
	CCLabelTTF *LabelScore;
	vector<keyedit*> m_pSpriteList; 
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    void menuCloseCallback(CCObject* pSender);
	static long getCurrentTime();    
	//采集数据
	long KeyTime[2000];
	int KeyPositionX[2000];
	int KeyPositionY[2000];
	bool isSpecialKey[2000];
	CCPoint specialKeyMoveTo[100];
    void GetData();
    // implement the "static node()" method manually
    CREATE_FUNC(HelloWorld);

	//创建可拖动的两点
	void createSpecialKey(int positionX,int positionY,CCPoint moveTo);
	void createmykey(int positionX,int positionY);
	void myDefine(CCNode* who);
	void ccTouchesEnded(CCSet *pTouches,CCEvent *pEvent);
	void timeset(float dt);




private:
	CCSprite* m_pSprite;

};

#endif // __HELLOWORLD_SCENE_H__
