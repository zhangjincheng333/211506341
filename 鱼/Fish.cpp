#include "Fish.h"

enum{
	k_Action_Animate = 0,
	k_Action_MoveTo
};

Fish::Fish(void)
{
}

Fish::~Fish(void)
{
}

Fish* Fish::create(FishType type/* = k_Fish_Type_SmallFish */)
{
	Fish* fish = new Fish;
	if (fish && fish->init(type))
	{
		fish->autorelease();
		return fish;
	}
	else
	{
		CC_SAFE_DELETE(fish);
		return NULL;
	}
}

bool Fish::init(FishType type /* = k_Fish_Type_SmallFish */)
{
	do 
	{
		if (!CCNode::init())
		{
			return false;
		}
		/*运行就出错？？   
			判断鱼的种类是否越绝界，越界置为小丑鱼
		*/
		if (type < k_Fish_Type_SmallFish || type >= k_Fish_Type_MarlineFish)
		{
			type = k_Fish_Type_SmallFish;
		}
		setType(type);
		//_type = type
		CCString* animationName = CCString::createWithFormat("fish_animation_%02d", _type + 1);
		CCAnimation* animation = CCAnimationCache::sharedAnimationCache()->animationByName(animationName->getCString());
		CC_BREAK_IF(!animation);
		CCAnimate* animate = CCAnimate::create(animation);
		_fishSprite = CCSprite::create();
		addChild(_fishSprite);
		_fishSprite->runAction(CCRepeatForever::create(animate));
		return true;
	} while (0);
	return false;
}

int Fish::getScore(void)
{
	return 0;
}

int Fish::getSpeed(void)
{
	return 200;
}

CCRect Fish::getCollisionArea()
{
	CCSize size = _fishSprite->getContentSize();
	CCPoint pos = getParent()->convertToWorldSpace(getPosition());
	return CCRect(pos.x - size.width / 2, pos.y - size.height/2, size.width, size.height);
}

void Fish::beCaught(){
	stopActionByTag(k_Action_MoveTo);
	CCCallFunc* callFunc = CCCallFunc::create(this,callfunc_selector(Fish::beCaught_CallFunc));
	CCSequence* sequence = CCSequence::create(CCDelayTime::create(1.0f),callFunc,NULL);
	CCBlink* blink = CCBlink::create(1.0f, 8);
	CCSpawn* spawn = CCSpawn::create(sequence, blink, NULL);
	_fishSprite->runAction(spawn);
}

void Fish::beCaught_CallFunc()
{
	if(isRunning())
	{
		getParent()->removeChild(this,false);
	}
}

void Fish::moveTo(CCPoint destination)//直线移动，将鱼移动到指定的位置destination
{
	CCPoint point = getParent()->convertToWorldSpace(this->getPosition());//获取鱼的位置并将其转换为世界坐标系
	float duration = ccpDistance(destination, point) / getSpeed();//根据目标点和鱼现在的位置计算出距离，除以速度，得到移动的时间
	CCMoveTo *moveTo = CCMoveTo::create(duration, destination);//构建鱼移动的动作
	CCCallFunc *callFunc = CCCallFunc::create(this, callfunc_selector(Fish::moveEnd));//执行移动结束后的动作
	CCSequence *sequence = CCSequence::create(moveTo, callFunc, NULL);
	sequence->setTag(k_Action_MoveTo);
	this->runAction(sequence);
}

void Fish::moveEnd()//鱼移动结束后执行的操作
{
	if (isRunning())
	{
		this->stopActionByTag(k_Action_MoveTo);
		getParent()->removeChild(this, false);//将鱼从FishLayer鱼层中删除
	}
}

CCSize Fish::getSize()
{
	return _fishSprite -> displayFrame() -> getRect().size;
}
