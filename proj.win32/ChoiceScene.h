

#ifndef _CHOICE_SCENE_H

#define _CHOICE_SCENE_H
#include "cocos2d.h"
#include "EnumClass.h"

class ChoiceScene : public cocos2d::Layer
{
public:
	virtual bool init();
	CREATE_FUNC(ChoiceScene);
	static cocos2d::Scene* scene(int _model);
	void clickDownAction(typeNum _type);
	void update();
private:
	int nowRound;
	CC_SYNTHESIZE(int, m_model, Model);
};

#endif