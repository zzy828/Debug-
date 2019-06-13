
#ifndef _FIGHTER

#define _FIGHTER
#include "cocos2d.h"
#include "TileMapPlus.h"


class Fighter : public cocos2d::Sprite {

private:
	cocos2d::Vec2 speed;	//速度
	float radius;// 角度
	float HP;	//血量
	bool flagAi;//是否是AI
	float mapDeltaX, mapDeltaY;
	TileMapPlus* mTileMapPlus;

	std::map<cocos2d::EventKeyboard::KeyCode, bool> keys;
public:
	Fighter();
	~Fighter();

	bool init(TileMapPlus* tileMapInfo);

	//create对象函数
	static Fighter* create(const char* figherType, TileMapPlus* tileMapInfo);


	/*鼠标键盘监听*/
	void fighterListener();

	/*
	//加入以下类似功能的函数
	
	void aiControl(); //ai控制函数
	
	*/

	void hpConsole(cocos2d::Node *pnode); 

	void update(float delta);//每一帧更新函数

};
#endif

