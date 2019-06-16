#ifndef _PADDLE_STRUCT
#define _PADDLE_STRUCT

#include "cocos2d.h"
#include "ChoiceScene.h"
#include "HeroChoice.h"
#include "EnumClass.h"

class Paddle :public cocos2d::Sprite
{
public:
	int kind;
	typeNum typeNumber;
	ChoiceScene* pScene;
	HeroChoice* hScene;


	static Paddle* paddleWithTexture(cocos2d::Texture2D* pTexture, typeNum _type, int k);
	void mouseClickListener();
	void setParentScene(ChoiceScene* _pscene);
	void setParentScene(HeroChoice* _pscene);
};
#endif