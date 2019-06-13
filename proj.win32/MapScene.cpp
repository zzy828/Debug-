#include "MapScene.h"
#include "Fighter.h"
#include "TileMapPlus.h"
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

	/*���ñ���*/
	pSprite->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	auto pSize = pSprite->getContentSize();
	pSprite->setScaleX(visibleSize.width / pSize.width);
	pSprite->setScaleY(visibleSize.height / pSize.height);
	pSprite->setOpacity(100);
	this->addChild(pSprite, 0);

	TileMapPlus* tmxFile = TileMapPlus::createMapInfoWithFile("map/RoundBig1.tmx");

	//����ͼ�ŵ���Ļ�м�
	TMXTiledMap* tmxTileMap = tmxFile->getTileMap();
	this->addChild(tmxTileMap, 1);
	
	Fighter* fighter = Fighter::create("HelloWorld.png", tmxFile);
	fighter->fighterListener();
	fighter->hpConsole(tmxTileMap);

	
	
	return true;
}