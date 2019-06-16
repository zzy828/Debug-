#include "Paddle.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;



void Paddle::setParentScene(ChoiceScene *_pscene)
{
	pScene = _pscene;
	return;
}

void Paddle::setParentScene(HeroChoice* _pscene)
{
	hScene = _pscene;
	return;
}

Paddle* Paddle::paddleWithTexture(Texture2D* pTexture, typeNum _type, int k)
{
	
	Paddle* pPaddle = new Paddle;
	pPaddle->initWithTexture(pTexture);
	pPaddle->typeNumber = _type;
	pPaddle->kind = k;
	return pPaddle;
}

void Paddle::mouseClickListener()
{
	auto _dispatcher = Director::getInstance()->getEventDispatcher();
	auto Lister = EventListenerMouse::create();
	Lister->onMouseDown = [=](Event * event)
	{
		
		EventMouse* e = (EventMouse*)event;
		Vec2 posXY = getPosition();
		Rect square = getBoundingBox();
		if (square.containsPoint(Vec2(e->getCursorX(), e->getCursorY()))) {
			if (kind == 0) pScene->clickDownAction(typeNumber);
			else hScene->clickDownAction(typeNumber);
		}
		
	};
	Lister->onMouseUp = [=](Event * event)
	{

	};
	Lister->onMouseMove = [=](Event * event)
	{

	};

	_dispatcher->addEventListenerWithSceneGraphPriority(Lister, this);
	return;
}

