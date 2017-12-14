#include "FishLayer.h"
#include <ctime>

enum{
	k_Direction_Left = 0,
	k_Direction_Right,
	k_Direction_Count
};

FishLayer::FishLayer(void)
{
}

bool FishLayer::init()
{
	do 
	{
		if (!CCLayer::init())
		{
			return false;
		}
		_fishes = CCArray::createWithCapacity(FISH_MAX_COUNT);//_fishes指针指向容量为50的鱼的数组
		CC_SAFE_RETAIN(_fishes);//数组创建完成后，需要通过CC_SAFE_RETAIN(_fishes)将其保存下来，不然会被回收池给回收掉
		for(int i = 0; i < FISH_MAX_COUNT; i++){
			int type = CCRANDOM_0_1() * k_Fish_Type_MarlineFish - 1;//随机生成鱼的种类0~16
			CCLOG("FishLayer type=%d", type);
			Fish* fish = Fish::create((FishType)type);////生成对应种类的鱼
			_fishes->addObject(fish);
		}
		srand((unsigned)time(0));
		this->schedule(schedule_selector(FishLayer::addFish), 3.0f);////每隔3秒就会调用一次addFish函数
		return true;
	} while (0);
	return false;
}

void FishLayer::addFish(float delta)
	{
		int addToCount = CCRANDOM_0_1() * 5 + 1;//生成随机数，表示此次要生成的鱼的数量
		int count = 0;
		CCObject* obj;
		CCSize winSize = CCDirector::sharedDirector()->getWinSize();
		/*CCARRAY_FOREACH对数组的遍历*/
		CCARRAY_FOREACH(_fishes, obj)
		{
			Fish* fish = (Fish*)obj;
			if(fish->isRunning())
			{
				continue;
			}
//			this->addChild(fish);
//			fish->setPosition(ccp(CCRANDOM_0_1() * winSize.width, CCRANDOM_0_1() * winSize.height));
			resetFish(fish);
			count++;
			if(count == addToCount)
			{
				break;
			}
		}
}

FishLayer::~FishLayer(void)
{
}

CCArray* FishLayer::getFishArray()
{
	return _fishes;
}

void FishLayer::resetFish(Fish* fish)//对鱼的位置进行重新设置，并让其移动到目标位置
{
	int direction = CCRANDOM_0_1() * k_Direction_Count;
	float startX = 0, startY = 0, endX = 0, endY = 0;//初始化鱼的位置为屏幕的两侧，和游动结束的位置
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	CCSize fishSize = fish -> getSize();
	if (direction == k_Direction_Left)//判断鱼在左侧的话不进行翻转
	{
		startX = winSize.width + fishSize.width / 2;//初始化鱼的位置
		fish -> setRotation(0);//对鱼进行翻转，防止倒游（在左侧不进行翻转）
		endY = 0 -fishSize.width / 2;
	}
	else//如果鱼在右侧进行翻转180度防止倒游
	{
		startX = -fishSize.width / 2;
		endX = winSize.width + fishSize.width / 2;
		fish -> setRotation(180);//翻转
	}

	endY = CCRANDOM_0_1() * (winSize.height - fishSize.height) + fishSize.height / 2;
	startY = CCRANDOM_0_1() * (winSize.height - fishSize.height) + fishSize.height / 2;
	addChild(fish);
	fish->setPosition(ccp(startX, startY));
	fish->moveTo(ccp(endX, endY));//调用鱼对象的MoveTo函数移动到目标位置
}
