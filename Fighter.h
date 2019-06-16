
#ifndef _FIGHTER

#define _FIGHTER
#include "cocos2d.h"
#include "TileMapPlus.h"
#include "EnumClass.h"


const int FighterPosition[3][2] = {
	{400, 400 },
	{300, 300 },
	{600, 600 }
};


class Weapon;
class Fighter : public cocos2d::Sprite {

public:
	
	int weapRank;
	int weapKind;
	int PicKind;
	int HP;	//血量
	int Rank;

	float mapDeltaX, mapDeltaY;
	TileMapPlus* mTileMapPlus;
	Weapon* mWeapon[6];
	std::map<cocos2d::EventKeyboard::KeyCode, bool> keys;

	Fighter();
	~Fighter();
	int getWeapRank() { return weapRank; }

	void hpUpdate(int delta);
	void setWeapKind(int _kind);
	bool init(TileMapPlus* tileMapInfo);

	//create对象函数
	static Fighter* create(int k, TileMapPlus* tileMapInfo);


	/*鼠标键盘监听*/
	void fighterListener();

	/*
	//加入以下类似功能的函数
	
	void aiControl(); //ai控制函数
	
	*/

	void hpConsole(); 

	void update(float delta);//每一帧更新函数

};
#endif

