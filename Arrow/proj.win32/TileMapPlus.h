#ifndef _TILEMAPPLUS
#define _TILEMAPPLUS

#include "cocos2d.h"

class TileMapPlus
{
public:
	bool collisionTest(cocos2d::Rect rect);


	static TileMapPlus* createMapInfoWithFile(const char* tmxFile);
	void initMapInfoWithFile(const char* tmxFile);
	CC_SYNTHESIZE(cocos2d::TMXTiledMap*, mTMXTileMap, TileMap);



private:
	cocos2d::TMXLayer* mTMXLayers[2];
};

#endif