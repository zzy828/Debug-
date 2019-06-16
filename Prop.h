
#ifndef _PROP

#define _PROP

#include "cocos2d.h"
#include "TileMapPlus.h"



//class Fighter;
class Prop : public cocos2d::Sprite {
public:
	int kind;
	bool isExist;
	TileMapPlus* tTileMapPlus;

	Prop();
	~Prop();

	static Prop* create(TileMapPlus* tilemap, int k);
	void init(TileMapPlus* tilemap, int k);
	void appear(float delta);
	void disappear();

};

#endif