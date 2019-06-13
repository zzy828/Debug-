#include "MapScene.h"
#include "Fighter.h"
USING_NS_CC;

Scene* MapScene::scene()
{
	Scene* scene = Scene::create();
	MapScene* layer = MapScene::create();

	scene->addChild(layer);

	return scene;
}

Scene* MapScene::scene(int round, int model)
{
	Scene* scene = Scene::create();
	MapScene* layer = MapScene::create(round, model);

	scene->addChild(layer);

	return scene;
}

MapScene* MapScene::create(int round, int model)
{
	MapScene* pRet = new MapScene;
	if (pRet)
	{
		pRet->setRound(round);
		pRet->setModel(model);
		if (pRet->init())
		{
			pRet->autorelease();
			return pRet;
		}
	}

	return nullptr;
}

bool MapScene::init()
{
	if (!Layer::init()) {
		return false;
	}
	
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto pSprite = Sprite::create("BackGround.jpg");

	/*设置背景*/
	pSprite->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	auto pSize = pSprite->getContentSize();
	pSprite->setScaleX(visibleSize.width / pSize.width);
	pSprite->setScaleY(visibleSize.height / pSize.height);
	pSprite->setOpacity(100);
	this->addChild(pSprite, 0);

	TMXTiledMap* tmxFile = TMXTiledMap::create("map/Round.tmx");

	//将地图放到屏幕中间
	
	Size winSize = Director::getInstance()->getWinSize();
	Size size = tmxFile->getContentSize();
	tmxFile->setPosition(Vec2((winSize.width - size.width) / 2, (winSize.height - size.height) / 2));

	this->addChild(tmxFile, 1);

	Fighter* fighter = Fighter::create("HelloWorld.png");
	fighter->setPosition(30, 30);
	fighter->setScale(0.3f);
	fighter->fighterListener();
	this->addChild(fighter, 2);
	
	return true;
}