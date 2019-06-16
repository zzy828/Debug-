
#ifndef _EnemyAi

#define _EnemyAi
#include "cocos2d.h"
#include "TileMapPlus.h"
#include "EnumClass.h"


const int AiPosition[5][2] = {
	{300, 300 },
	{1000, 1000 },
	{1500, 1600 },
	{2000, 1600},
	{3000, 1300}
};
class Weapon;
class EnemyAi : public cocos2d::Sprite {

public:
	
	int weapRank;
	int weapKind;
	int PicKind;
	float HP;	//Ѫ��

	TileMapPlus* mTileMapPlus;
	Weapon* mWeapon[6];

	EnemyAi();
	~EnemyAi();

	bool init(TileMapPlus* tileMapInfo);
	void hpUpdate(int delta);
	//create������
	static EnemyAi* create(int k, TileMapPlus* tileMapInfo);

	void update(float delta);//ÿһ֡���º���

};
#endif

