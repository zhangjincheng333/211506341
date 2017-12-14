#pragma once
#include "cocos2d.h"
#include "BackgroundLayer.h"
#include "FishLayer.h"
#include "MenuLayer.h"
#include "CannonLayer.h"
#include "TouchLayer.h"
#include "Fish.h"
#include "PanelLayer.h"
#include "FishJoyData.h"

USING_NS_CC;
/*游戏场景类*/
class GameScene :
	public CCScene
{
public:
	GameScene(void);
	CREATE_FUNC(GameScene)
	/*初始化函数，完成各个层的创建和加载*/
	virtual bool init();
	virtual ~GameScene();
	void cannonAimAt(CCPoint target);
	void cannonShootTo(CCPoint target);
protected:
	/*数据成员*/
	BackgroundLayer* _backgroundLayer;/*背景层*/
	FishLayer* _fishLayer;/*鱼层*/
	MenuLayer* _menuLayer;/*菜单层*/
	CannonLayer* _cannonLayer;/*炮台层*/
	TouchLayer* _touchLayer;/*触摸层*/
	PanelLayer* _paneLayer;/*功能层*/
	void preloadResources(void);
	bool checkOutCollisionBetweenFishesAndBullet(Bullet* bullet);
	void checkOutCollision();
	virtual void update(float delta);
	void fishWillBeCaught(Fish* fish);
	void checkOutCollisionBetweenFishesAndFishingNet(Bullet* bulet);
};

