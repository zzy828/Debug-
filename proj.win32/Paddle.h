#ifndef _PADDLE_STRUCT
#define _PADDLE_STRUCT

#include "cocos2d.h"
#include "ChoiceScene.h"
#include "EnumClass.h"

class Paddle :public cocos2d::Sprite
{
private:
	typeNum typeNumber;
	ChoiceScene* pScene;
public:

	static Paddle* paddleWithTexture(cocos2d::Texture2D* pTexture, typeNum _type);
	void mouseClickListener();
	void setParentScene(ChoiceScene* _pscene);
	
};
#endif