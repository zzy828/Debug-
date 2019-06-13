
#ifndef _FIGHTER

#define _FIGHTER
#include "cocos2d.h"


class Fighter : public cocos2d::Sprite {

private:
	cocos2d::Vec2 position;// ����
	cocos2d::Vec2 speed;	//�ٶ�
	float radius;// �Ƕ�
	float HP;	//Ѫ��
	bool flagAi;//�Ƿ���AI

	std::map<cocos2d::EventKeyboard::KeyCode, bool> keys;
public:
	Fighter();
	~Fighter();

	bool init();

	//create������
	static Fighter* create(const char* figherType);


	/*�����̼���*/
	void fighterListener();

	/*
	//�����������ƹ��ܵĺ���
	void hpConsole(); //Ѫ����ʾ����
	void aiControl(); //ai���ƺ���
	
	*/

	void update(float delta);//ÿһ֡���º���

};
#endif

