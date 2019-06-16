#ifndef _MAPSCENE
#define _MAPSCENE
#include "cocos2d.h"
#include "Fighter.h"
#include "enemyAi.h"
#include "Prop.h"
#include "ArrowClient.h"



class MapScene : public cocos2d::Layer
{

private:
	Fighter* fighter;
	EnemyAi* enemyAi[5];
	EnemyNet* enemyNet[4][5];
	Prop* prop[30];
	unsigned int pSec;
public:

	virtual bool init();

	static cocos2d::Scene* scene();
	static cocos2d::Scene* scene(int round, int model, int kind);
	CREATE_FUNC(MapScene);

	static MapScene* create(int round, int model, int kind);
	void update(float delta);//每一帧更新函数
	bool IsRectIntersect(cocos2d::Rect rectA, cocos2d::Rect rectB);
	CC_SYNTHESIZE(int, m_nRound, Round);
	CC_SYNTHESIZE(int, m_model, Model);
	CC_SYNTHESIZE(int, m_skind, Skind);
	void menuMusicCallback(cocos2d::Ref* pSender);
};
#endif