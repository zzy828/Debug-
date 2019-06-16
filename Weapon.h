
#ifndef _WEAPON

#define _WEAPON

#include "cocos2d.h"
#include "TileMapPlus.h"



//class Fighter;
class Weapon : public cocos2d::Sprite {
public:
	int kind;
	bool isFlying;
	cocos2d::Sprite* mfighter;
	TileMapPlus* tTileMapPlus;
	float stepX, stepY;

	Weapon();
	~Weapon();

	static Weapon* creatWeaponWithFighter(cocos2d::Sprite* fighter, TileMapPlus* tilemap, int weapKind);
	void initWeaponWithFighter(cocos2d::Sprite* fighter, TileMapPlus* tilemap, int weapKind);
	bool fire(int dAngle);
	void stopFire();
	void switchKind(int _kind);
	virtual void update(float delta);

};

#endif