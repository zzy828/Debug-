#include "TileMapPlus.h"
#include "NormalDefine.h"
USING_NS_CC;

void TileMapPlus::initMapInfoWithFile(const char* tmxFile)
{
	mTMXTileMap = TMXTiledMap::create(tmxFile);
	mTMXLayers[0] = mTMXTileMap->getLayer("layer_0");
	mTMXLayers[1] = mTMXTileMap->getLayer("layer_1");

	Size winSize = Director::getInstance()->getWinSize();
	Size mapSize = mTMXTileMap->getContentSize();

	mTMXTileMap->setPosition(Vec2(10, 10));
	return;
}

TileMapPlus* TileMapPlus::createMapInfoWithFile(const char* tmxFile)
{
	TileMapPlus* tileMapPlus = new TileMapPlus();
	tileMapPlus->initMapInfoWithFile(tmxFile);

	return tileMapPlus;
}

bool TileMapPlus::collisionTest(Rect rect)
{
	int gid = 0;
	Size mapSize = mTMXTileMap->getContentSize();
	Size tileSize = mTMXTileMap->getTileSize();

	if (rect.getMinX() < 0 || rect.getMaxX() >= mapSize.width ||
		rect.getMinY() < 0 || rect.getMaxY() >= mapSize.height)
		return false;

	//将坦克Y坐标转换为地图上的Y坐标
	float MinY = mapSize.height - rect.getMinY();
	float MaxY = mapSize.height - rect.getMaxY();
	//对坦克四个顶点进行碰撞检测

	gid = mTMXLayers[1]->getTileGIDAt(Vec2((int)(rect.getMinX() / tileSize.width),
		(int)(MinY / tileSize.height)));
	//CCLog("gid: %d \n", gid);
	if (gid == 14 || gid == 15 || gid == 16 || gid == 20 || gid == 37 || gid == 43)
		return true;
	
	gid = mTMXLayers[1]->getTileGIDAt(Vec2((int)(rect.getMinX() / tileSize.width),
		(int)(MaxY / tileSize.height)));
	if (gid == 14 || gid == 15 || gid == 16 || gid == 20 || gid == 37 || gid == 43)
		return true;
	gid = mTMXLayers[1]->getTileGIDAt(Vec2((int)(rect.getMaxX() / tileSize.width),
		(int)(MaxY / tileSize.height)));
	if (gid == 14 || gid == 15 || gid == 16 || gid == 20 || gid == 37 || gid == 43)
		return true;
	gid = mTMXLayers[1]->getTileGIDAt(Vec2((int)(rect.getMaxX() / tileSize.width),
		(int)(MinY / tileSize.height)));
	if (gid == 14 || gid == 15 || gid == 16 || gid == 20 || gid == 37 || gid == 43)
		return true;

	return false;
}

