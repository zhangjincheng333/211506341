#include "FishJoyData.h"
#include "StaticData.h"

USING_NS_CC;

#define IS_BEGINER "isBeginer"
#define MUSIC "music"
#define SOUND "sound"
#define GOLD "gold"

static FishJoyData* _sharedFishJoyData = NULL;

FishJoyData::FishJoyData(void)
{
}


FishJoyData::~FishJoyData(void)
{
}

FishJoyData* FishJoyData::sharedFishJoyData()
{
	if(NULL == _sharedFishJoyData)
	{
		_sharedFishJoyData = new FishJoyData();
		_sharedFishJoyData -> init();
	}
	return _sharedFishJoyData;
}

void FishJoyData::destoryInstance()
{
	CC_SAFE_DELETE(_sharedFishJoyData);
}

bool FishJoyData::init()//利用CCUserDefault来操作存储在磁盘文件中的数据
{
	_isBeginer = CCUserDefault::sharedUserDefault() -> getBoolForKey(IS_BEGINER, true);//先判断是否是第一次使用
	if (_isBeginer)//如果_isBeginner的值为true，则将数据重新设为默认值
	{
		reset();
		flush();
	}
	else//如果_isBeginner的值为true，则将数据重新设为默认值件中读取出来，并赋值给相关的数据成员
	{
		CCUserDefault* userDefault = CCUserDefault::sharedUserDefault();
		this -> setGold(userDefault -> getDoubleForKey(GOLD));
		this -> setIsMusic(userDefault -> getBoolForKey(MUSIC));
		this -> setIsSound(userDefault -> getBoolForKey(SOUND));
	}
	return true;
}

void FishJoyData::reset()//将数据重设为初始化时的数据
{
	this -> setIsMusic(true);
	this -> setIsSound(true);
	this -> setGold(200);
	this -> setIsBeginer(false);
}

void FishJoyData::flush()//将当前动态数据的值保存到xml文件中
{
	CCUserDefault* userDefault = CCUserDefault::sharedUserDefault();//通过CCUserDefault的对象保存各个属性对应的值
	

	//每种数据成员一个唯一的key和成员对应的值关联在一起并保存起来
	userDefault -> setBoolForKey(IS_BEGINER, _isBeginer);
	userDefault -> setIntegerForKey(GOLD, _gold);
	userDefault -> setBoolForKey(MUSIC, _isMusic);
	userDefault -> setBoolForKey(SOUND, _isSound);

	userDefault -> flush();
}

void FishJoyData::alterGold(int golds)
{
	int num = getGold();
	num += golds;
	setGold(num);
	flush();
}
