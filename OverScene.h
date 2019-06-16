#ifndef _OVERSCENE
#define _OVERSCENE
#include "cocos2d.h"
#include "Fighter.h"
#include "enemyAi.h"
#include "Prop.h"
class OverScene : public cocos2d::Layer
{

public:
	int flagWin;
	bool init(int flag);

	static cocos2d::Scene* scene(int flagwin);

	void closeCallback(cocos2d::Ref* pSender);
	static OverScene* create(int flagwin);
};
#endif