#include "BackgroundLayer.h"

BackgroundLayer::BackgroundLayer(void)
{
}

bool BackgroundLayer::init()
{
	if (!CCLayer::init())
	{
		return false;
	}
	CCSprite *bgSprite = CCSprite::create("bj01_01-ipadhd.png");
	//*�Ѿ���ӵ�����ӽڵ�*/
	this->addChild(bgSprite);
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	/*���ñ���ͼ��ʾλ�ã������λ���ڴ��ڵ����ģ�*/
	bgSprite->setPosition(CCPoint(winSize.width / 2, winSize.height / 2));
	return true;
}

BackgroundLayer::~BackgroundLayer(void)
{
}
