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
	void update(float dt);
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
	int currentScore;
	CCLabelTTF *LabelScore;

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    void menuCloseCallback(CCObject* pSender);
	static long getCurrentTime();    

    
    // implement the "static node()" method manually
    CREATE_FUNC(HelloWorld);

	void createmykey();
	void myDefine(CCNode* who);
	void ccTouchesEnded(CCSet *pTouches,CCEvent *pEvent);
	void timeset(float dt);




private:
	CCSprite* m_pSprite;
	vector<keyedit*> m_pSpriteList; 
};

#endif // __HELLOWORLD_SCENE_H__
