
#ifndef _ENEMYNET

#define _ENEMYNET
#include "cocos2d.h"
#include "TileMapPlus.h"


class Weapon;
class EnemyNet : public cocos2d::Sprite {

public:
	bool visb;
	int weapRank;
	int weapKind;
	int PicKind;
	int HP;	//血量
	int Ai;
	TileMapPlus* mTileMapPlus;
	Weapon* mWeapon[6];


	EnemyNet();
	~EnemyNet();

	bool init(TileMapPlus* tileMapInfo);
	void fireAll();
	//create对象函数
	static EnemyNet* create(int k, TileMapPlus* tileMapInfo);
	void switchKind(int _kind);
	void setWeapKind(int _kind);
	
	void goDie();
	void goAlive();
};
#endif

