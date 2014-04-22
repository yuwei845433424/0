
#include<cstring> 
#include<fstream> 
#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "keyedit.h"
USING_NS_CC;
int keyedit::specialAmount = 0;
int keyedit::keyAmount = 0;


std::vector<std::string>split(std::string str,std::string pattern)
{
	std::string::size_type pos;
	std::vector<std::string> result;
	str+=pattern;//扩展字符串以方便操作
	int size=str.size();
	for(int i=0; i<size; i++)
	{
		pos=str.find(pattern,i);
		if(pos<size)
		{
			std::string s=str.substr(i,pos-i);
			result.push_back(s);
			i=pos+pattern.size()-1;
		}
	}
	return result;
}
void HelloWorld::GetData()
{
	std::string lineValue;
	// declare file stream: 	
	std::ifstream file("test.csv");
	int keyRowNum = 0;
	int specialKeyRowNum = 0;
	while(file.good())
	{ 
		getline(file,lineValue); // read a string until next col:
//		if(!file.good()) break;
		std::string line = lineValue;
		vector<std::string> Value = split(line,",");
		KeyTime[keyRowNum] = atol(Value[0].c_str());
		KeyPositionX[keyRowNum]  = atoi(Value[1].c_str());
		KeyPositionY[keyRowNum] = atoi(Value[2].c_str());
		if(Value.size()>=4)
		{
			if(Value[3] =="true")
			{
				isSpecialKey[keyRowNum] = true;

			}

		}
		else
		{
			isSpecialKey[keyRowNum] = false;
		}
		keyRowNum++;
	}
	file.close();
	std::ifstream moveFile("moveTo.csv");
	while(file.good())
	{ 
		getline(file,lineValue); // read a string until next col:
//		if(!file.good()) break;
		std::string line = lineValue;
		vector<std::string> Value = split(line,",");
		specialKeyMoveTo[keyRowNum] =ccp(atof(Value[0].c_str()),atof(Value[1].c_str()));
		keyRowNum++;
	}
	file.close();

}
CCScene* HelloWorld::scene()
{
	// 'scene' is an autorelease object
	CCScene *scene = CCScene::create();
	
	// 'layer' is an autorelease objectv bn0 
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
		GetData();
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

	this->schedule(schedule_selector(HelloWorld::newUpdate),0.005); 
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


	CCSprite* pSprite = CCSprite::create("00.png");

	// position the sprite on the center of the screen
	pSprite->setPosition(ccp(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

	// add the sprite as a child to this layer
	this->addChild(pSprite, 0);


	//设置随机跳出按键
	
	//schedule(schedule_selector(HelloWorld::timeset),0.5f);
	srand(time(0));

	//delete
	//m_pSprite = CCSprite::create("Projectile.png");
	setTouchEnabled(true);
	//m_pSprite->setPosition(ccp(visibleSize.width/2+origin.x,visibleSize.height/2+origin.y));
	//this->addChild(m_pSprite,1);

	this->GameBeginTime = this->getCurrentTime();
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("weifengtangtang.mp3",true);
	
	return true;
}
//CreateTimeFrequency代表调用此函数的频率，是以秒为单位的，需要转换，
/*void HelloWorld::timeset(float CreateTimeFrequency)
{
	long currentTime = this->getCurrentTime();
	int frequency = CreateTimeFrequency*1000;
	//计算出离当前音乐的时间
	long musicCurrentTime  = currentTime-this->GameBeginTime;

	this->createmykey();

	long timeRange1  = musicCurrentTime - frequency;
	long timeRange2  = musicCurrentTime + frequency;
	long createTime = 2000;
	//创建特殊点
	
	if(createTime>timeRange1&&createTime<timeRange2)
	{
		this->createSpecialKeys();
	}
	
}*/
//读取文件后需加入（两个坐标）参数
void HelloWorld::createSpecialKey(int positionX,int positionY,CCPoint moveTo)
{
		//为按键精灵添加动作
	CCSize screenSize=CCDirector::sharedDirector()->getVisibleSize();
	long createTime = getCurrentTime();
	//将当前创建的时间记录到指针对象里
	keyedit *SpecialKey1 = new keyedit(createTime,positionX,positionY,true);
	
	this->addChild(SpecialKey1,1);
	SpecialKey1->keyRunAnimation(moveTo);
	this->m_pSpriteList.push_back(SpecialKey1);

}

//读取文件后需加入（一个坐标）参数
void HelloWorld::createmykey(int positionX,int positionY)
{	

	//为按键精灵添加动作
	CCSize screenSize=CCDirector::sharedDirector()->getVisibleSize();
	long createTime = getCurrentTime();
	//将当前创建的时间记录到指针对象里
	keyedit *mykey = new keyedit(createTime,positionX,positionY);
	
	this->addChild(mykey,1);
	mykey->keyRunAnimation();
	this->m_pSpriteList.push_back(mykey);
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
void HelloWorld::newUpdate(float dt)
{	
	
	long currentTime = this->getCurrentTime();
	CCLOG("test");
	int frequency = 10;
	//计算出离当前音乐的时间
	long musicCurrentTime  = currentTime-this->GameBeginTime;
	long KeyCreateTime = 10*KeyTime[keyedit::keyAmount];
	int diffTime = KeyCreateTime-musicCurrentTime;
	if(diffTime<frequency&&diffTime>-frequency)
	{
		if(isSpecialKey[keyedit::keyAmount]==false)
		{
			this->createmykey(KeyPositionX[keyedit::keyAmount],KeyPositionY[keyedit::keyAmount]);
		}
		else
		{
			this->createSpecialKey(KeyPositionX[keyedit::keyAmount],KeyPositionY[keyedit::keyAmount],specialKeyMoveTo[keyedit::specialAmount]);
		}
	}
	char str[100] = {'0'};
	sprintf(str, "%d",currentScore);
	LabelScore->setString(str);
	LabelScore->setVisible(true);
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