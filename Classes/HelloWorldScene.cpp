#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "keyedit.h"
USING_NS_CC;

CCScene* HelloWorld::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    HelloWorld *layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

long HelloWorld::getCurrentTime()    
{     
	struct cc_timeval tv;     
	CCTime::gettimeofdayCocos2d(&tv, NULL);  
	return tv.tv_sec * 1000 + tv.tv_usec / 1000;     
}  

   
 


// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
	//加一个label
	LabelScore = CCLabelTTF::create("score","arial",30);
	LabelScore->setColor(ccBLACK);
	LabelScore->retain();
	LabelScore->setPosition(ccp(340, 300) );
	this->addChild(LabelScore, 1);
	LabelScore = CCLabelTTF::create("0","arial",30);
	LabelScore->setColor(ccBLACK);
	LabelScore->retain();
	LabelScore->setPosition(ccp(400, 300) );
	this->addChild(LabelScore, 1);
	scheduleUpdate();
	currentScore = 0;
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
                                        "CloseNormal.png",
                                        "CloseSelected.png",
                                        this,
                                        menu_selector(HelloWorld::menuCloseCallback));
    
	pCloseItem->setPosition(ccp(origin.x + visibleSize.width - pCloseItem->getContentSize().width/2 ,
                                origin.y + pCloseItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
    pMenu->setPosition(CCPointZero);
    this->addChild(pMenu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
  /*  CCLabelTTF* pLabel = CCLabelTTF::create("Hello World", "Arial", 24);
    
    // position the label on the center of the screen
    pLabel->setPosition(ccp(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - pLabel->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(pLabel, 1);   */

    // add "HelloWorld" splash screen"
    CCSprite* pSprite = CCSprite::create("00.png");

    // position the sprite on the center of the screen
    pSprite->setPosition(ccp(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
    this->addChild(pSprite, 0);

	/*CCSprite* key1=CCSprite::create("1.png");
	key1->setPosition(ccp(100,160));
	key1->setAnchorPoint(ccp(0,0.5));
	this->addChild(key1);
	*/

	//设置随机跳出按键
	
	schedule(schedule_selector(HelloWorld::timeset),0.5f);
	srand(time(0));

	//delete
	//m_pSprite = CCSprite::create("Projectile.png");
    setTouchEnabled(true);
	//m_pSprite->setPosition(ccp(visibleSize.width/2+origin.x,visibleSize.height/2+origin.y));
	//this->addChild(m_pSprite,1);


	CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("weifengtangtang.mp3",true);
    
    return true;
}

void HelloWorld::timeset(float dt)
{
	this->createmykey();
}


void HelloWorld::createmykey()
{	

	//为按键精灵添加动作
	CCSize screenSize=CCDirector::sharedDirector()->getVisibleSize();
	long createTime = getCurrentTime();
	//将当前创建的时间记录到指针对象里
	keyedit *mykey = new keyedit(createTime);
	
	this->addChild(mykey);
	mykey->keyRunAnimation();
	this->m_pSpriteList.push_back(mykey);
	CCShow *show=CCShow::create();
	mykey->runAction(show);
}




/*void HelloWorld::DelSpriteFunc(CCNode* who)
{
	who->removeFromParentAndCleanup(true);
}*/

bool isTouchGetNode(CCSprite *sprite,CCTouch* touch)
{
	CCPoint touchPoint = touch->getLocationInView();     
	touchPoint = CCDirector::sharedDirector()->convertToGL(touchPoint );         
	CCRect rc1 = sprite->boundingBox(); 
	if(rc1.containsPoint(touchPoint)) return true;
	else return false;
}

void HelloWorld::ccTouchesEnded(CCSet *pTouches,CCEvent *pEvent)
{
	//获取鼠标位置
	CCTouch *touch = (CCTouch*)pTouches->anyObject();
	CCPoint locInView= touch->getLocationInView();
	//坐标系的转化
	CCPoint loc =CCDirector::sharedDirector()->convertToGL(locInView);

	//精灵的动作
	//CCCallFuncN* disapear= CCCallFuncN::create(this,callfuncN_selector(HelloWorld::myDefine));
	for(vector<keyedit*>::iterator it=this->m_pSpriteList.begin();it!=m_pSpriteList.end();it++){
		if(isTouchGetNode(*it,touch)){
			(*it)->endTime = getCurrentTime();
			(*it)->Change();
			(*it)->isClick = true;
			currentScore+=5;
			CCLOG("currentScore:%d",currentScore);
			break;
		}
	}
	//mykey->runAction(disapear);
}


void HelloWorld::myDefine(CCNode* who)
{
	who->removeFromParentAndCleanup(true);

}
void HelloWorld::update(float dt)
{	
	char str[100] = {'0'};
	sprintf(str, "%d",currentScore);
	LabelScore->setString(str);
	LabelScore->setVisible(true);
	long currentTime = getCurrentTime();
	for(vector<keyedit*>::iterator it=this->m_pSpriteList.begin();it!=m_pSpriteList.end();it++){
		if(currentTime - (*it)->createTime>1000)
		{
			if(!(*it)->isClick)
			{
				currentScore -= 10;
			}
			(*it)->endTime = getCurrentTime();
			(*it)->removeFromParentAndCleanup(true);
			delete *it;
			this->m_pSpriteList.erase(it);
				
			CCLOG("currentScore:%d",currentScore);
			break;
		}
	}

}
void HelloWorld::menuCloseCallback(CCObject* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
#else
    CCDirector::sharedDirector()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
#endif
}
