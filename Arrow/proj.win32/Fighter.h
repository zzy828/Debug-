
#ifndef _FIGHTER

#define _FIGHTER
#include "cocos2d.h"
#include "TileMapPlus.h"


class Fighter : public cocos2d::Sprite {

private:
	cocos2d::Vec2 speed;	//�ٶ�
	float radius;// �Ƕ�
	float HP;	//Ѫ��
	bool flagAi;//�Ƿ���AI
	float mapDeltaX, mapDeltaY;
	TileMapPlus* mTileMapPlus;

	std::map<cocos2d::EventKeyboard::KeyCode, bool> keys;
public:
	Fighter();
	~Fighter();

	bool init(TileMapPlus* tileMapInfo);

	//create������
	static Fighter* create(const char* figherType, TileMapPlus* tileMapInfo);


	/*�����̼���*/
	void fighterListener();

	/*
	//�����������ƹ��ܵĺ���
	
	void aiControl(); //ai���ƺ���
	
	*/

	void hpConsole(cocos2d::Node *pnode); 

	void update(float delta);//ÿһ֡���º���

};
#endif

