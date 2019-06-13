
#ifndef _FIGHTER

#define _FIGHTER
#include "cocos2d.h"


class Fighter : public cocos2d::Sprite {

private:
	cocos2d::Vec2 position;// 坐标
	cocos2d::Vec2 speed;	//速度
	float radius;// 角度
	float HP;	//血量
	bool flagAi;//是否是AI

	std::map<cocos2d::EventKeyboard::KeyCode, bool> keys;
public:
	Fighter();
	~Fighter();

	bool init();

	//create对象函数
	static Fighter* create(const char* figherType);


	/*鼠标键盘监听*/
	void fighterListener();

	/*
	//加入以下类似功能的函数
	void hpConsole(); //血量显示函数
	void aiControl(); //ai控制函数
	
	*/

	void update(float delta);//每一帧更新函数

};
#endif

