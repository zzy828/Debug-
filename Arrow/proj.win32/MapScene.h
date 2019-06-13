#ifndef _MAPSCENE
#define _MAPSCENE
#include "cocos2d.h"

class MapScene : public cocos2d::Layer
{

public:

	virtual bool init();

	static cocos2d::Scene* scene();
	static cocos2d::Scene* scene(int round, int model);
	CREATE_FUNC(MapScene);

	static MapScene* create(int round, int model);

	CC_SYNTHESIZE(int, m_nRound, Round);
	CC_SYNTHESIZE(int, m_model, Model);
};
#endif