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
		_fishes = CCArray::createWithCapacity(FISH_MAX_COUNT);//_fishesָ��ָ������Ϊ50���������
		CC_SAFE_RETAIN(_fishes);//���鴴����ɺ���Ҫͨ��CC_SAFE_RETAIN(_fishes)���䱣����������Ȼ�ᱻ���ճظ����յ�
		for(int i = 0; i < FISH_MAX_COUNT; i++){
			int type = CCRANDOM_0_1() * k_Fish_Type_MarlineFish - 1;//��������������0~16
			CCLOG("FishLayer type=%d", type);
			Fish* fish = Fish::create((FishType)type);////���ɶ�Ӧ�������
			_fishes->addObject(fish);
		}
		srand((unsigned)time(0));
		this->schedule(schedule_selector(FishLayer::addFish), 3.0f);////ÿ��3��ͻ����һ��addFish����
		return true;
	} while (0);
	return false;
}

void FishLayer::addFish(float delta)
	{
		int addToCount = CCRANDOM_0_1() * 5 + 1;//�������������ʾ�˴�Ҫ���ɵ��������
		int count = 0;
		CCObject* obj;
		CCSize winSize = CCDirector::sharedDirector()->getWinSize();
		/*CCARRAY_FOREACH������ı���*/
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

void FishLayer::resetFish(Fish* fish)//�����λ�ý����������ã��������ƶ���Ŀ��λ��
{
	int direction = CCRANDOM_0_1() * k_Direction_Count;
	float startX = 0, startY = 0, endX = 0, endY = 0;//��ʼ�����λ��Ϊ��Ļ�����࣬���ζ�������λ��
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	CCSize fishSize = fish -> getSize();
	if (direction == k_Direction_Left)//�ж��������Ļ������з�ת
	{
		startX = winSize.width + fishSize.width / 2;//��ʼ�����λ��
		fish -> setRotation(0);//������з�ת����ֹ���Σ�����಻���з�ת��
		endY = 0 -fishSize.width / 2;
	}
	else//��������Ҳ���з�ת180�ȷ�ֹ����
	{
		startX = -fishSize.width / 2;
		endX = winSize.width + fishSize.width / 2;
		fish -> setRotation(180);//��ת
	}

	endY = CCRANDOM_0_1() * (winSize.height - fishSize.height) + fishSize.height / 2;
	startY = CCRANDOM_0_1() * (winSize.height - fishSize.height) + fishSize.height / 2;
	addChild(fish);
	fish->setPosition(ccp(startX, startY));
	fish->moveTo(ccp(endX, endY));//����������MoveTo�����ƶ���Ŀ��λ��
}
