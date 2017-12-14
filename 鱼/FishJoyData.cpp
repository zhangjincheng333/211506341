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

bool FishJoyData::init()//����CCUserDefault�������洢�ڴ����ļ��е�����
{
	_isBeginer = CCUserDefault::sharedUserDefault() -> getBoolForKey(IS_BEGINER, true);//���ж��Ƿ��ǵ�һ��ʹ��
	if (_isBeginer)//���_isBeginner��ֵΪtrue��������������ΪĬ��ֵ
	{
		reset();
		flush();
	}
	else//���_isBeginner��ֵΪtrue��������������ΪĬ��ֵ���ж�ȡ����������ֵ����ص����ݳ�Ա
	{
		CCUserDefault* userDefault = CCUserDefault::sharedUserDefault();
		this -> setGold(userDefault -> getDoubleForKey(GOLD));
		this -> setIsMusic(userDefault -> getBoolForKey(MUSIC));
		this -> setIsSound(userDefault -> getBoolForKey(SOUND));
	}
	return true;
}

void FishJoyData::reset()//����������Ϊ��ʼ��ʱ������
{
	this -> setIsMusic(true);
	this -> setIsSound(true);
	this -> setGold(200);
	this -> setIsBeginer(false);
}

void FishJoyData::flush()//����ǰ��̬���ݵ�ֵ���浽xml�ļ���
{
	CCUserDefault* userDefault = CCUserDefault::sharedUserDefault();//ͨ��CCUserDefault�Ķ��󱣴�������Զ�Ӧ��ֵ
	

	//ÿ�����ݳ�Աһ��Ψһ��key�ͳ�Ա��Ӧ��ֵ������һ�𲢱�������
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
