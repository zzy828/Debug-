#include "Fighter.h"

USING_NS_CC;

Fighter::Fighter()
{

}

Fighter::~Fighter()
{

}

bool Fighter::init()
{
	position.setPoint(10, 10);
	speed.setPoint(0, 0);
	radius = 0.0;
	HP = 100.0;
	this->scheduleUpdate();
	return true;
}
Fighter* Fighter::create(const char* fighterTypeName)
{

	Fighter* fighter = new Fighter();
	fighter->initWithFile(fighterTypeName);
	fighter->init();
	fighter->autorelease();
	return fighter;
}

void Fighter::fighterListener()
{
	EventListenerMouse* mouseListener = EventListenerMouse::create();
	EventListenerKeyboard* keyBoardListener = EventListenerKeyboard::create();
	mouseListener->onMouseMove = [=](Event * event)
	{
		EventMouse* e = (EventMouse*)event;
		float cursorX = e->getCursorX();
		float cursorY = e->getCursorY();
		Vec2 nowPos = getPosition();
		if ((cursorX - nowPos.x) * (cursorX - nowPos.x) + (cursorY - nowPos.y) * (cursorY - nowPos.y) > 1.0) {
			float nowAngel = acos((nowPos.y - cursorY) / sqrt((cursorX - nowPos.x) * (cursorX - nowPos.x) + (cursorY - nowPos.y) * (cursorY - nowPos.y))) / acos(-1) * 180;
			if (nowPos.x < cursorX) {
				nowAngel = -nowAngel;
			}
			auto rotateAngel = RotateTo::create(0, Vec3(0, 0, nowAngel));
			radius = nowAngel;
			runAction(rotateAngel);
		}
	};
	mouseListener->onMouseDown = [=](Event * event)
	{

	};
	keyBoardListener->onKeyPressed = [=](EventKeyboard::KeyCode keycode, Event * event)
	{
		keys[keycode] = true;
	};
	keyBoardListener->onKeyReleased = [=](EventKeyboard::KeyCode keycode, Event * event)
	{
		keys[keycode] = false;
	};
	auto _eventDispatcher = Director::getInstance()->getEventDispatcher();
	_eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyBoardListener, this);
	return;
}

void Fighter::update(float delta)
{
	Sprite::update(delta);
	auto leftArrow = EventKeyboard::KeyCode::KEY_A;
	auto rightArrow = EventKeyboard::KeyCode::KEY_D;
	auto upArrow = EventKeyboard::KeyCode::KEY_W;
	auto downArrow = EventKeyboard::KeyCode::KEY_S;

	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 nowPos = getPosition();
	if (keys[upArrow]) {
		nowPos.y += 5;
	}
	if (keys[downArrow]) {
		nowPos.y -= 5;
	}
	if (keys[leftArrow]) {
		nowPos.x -= 5;
	}
	if (keys[rightArrow]) {
		nowPos.x += 5;
	}
	if (nowPos.x < origin.x + getContentSize().width * 0.5 / 2) nowPos.x = origin.x + getContentSize().width * 0.5 / 2;
	if (nowPos.y < origin.y + getContentSize().height * 0.5 / 2) nowPos.y = origin.y + getContentSize().height * 0.5 / 2;
	if (nowPos.x > origin.x + visibleSize.width - getContentSize().width * 0.5 / 2) nowPos.x = origin.x + visibleSize.width - getContentSize().width * 0.5 / 2;
	if (nowPos.y > origin.y + visibleSize.height - getContentSize().height * 0.5 / 2) nowPos.y = origin.y + visibleSize.height - getContentSize().height * 0.5 / 2;
	auto moveTo = MoveTo::create(0.12f, nowPos);
	runAction(moveTo);
	return;
}
