#include "Fighter.h"
#include "Weapon.h"
#include "ArrowClient.h"
#include "NormalDefine.h"
USING_NS_CC;
extern ArrowMessage mess0[4];
extern ArrowClient client0;
Fighter::Fighter()
{
	weapRank = 1;
	weapKind = 2;
	mess0[0].weapKind = 2;
	mess0[0].weapRank = 1;

}

Fighter::~Fighter()
{

}

bool Fighter::init(TileMapPlus* tileMapInfo)
{
	int p = rand() % 3;
	setPosition(FighterPosition[p][0], FighterPosition[p][1]);
	mess0[0].x = FighterPosition[p][0];
	mess0[0].y = FighterPosition[p][1];
	mess0[0].HP = 100.0;
	mess0[0].Ai = false;
	HP = 100.0;
	mapDeltaX = mapDeltaY = 0.0;
	mTileMapPlus = tileMapInfo;
	setTag(FIGHTER_NODE);
	mTileMapPlus->getTileMap()->addChild(this);
	TMXTiledMap* tmxTileMap = mTileMapPlus->getTileMap();
	Size tileSize = tmxTileMap->getTileSize();
	Size tankSize = getContentSize();
	setScale(0.6f);
	this->scheduleUpdate();

	mWeapon[0] = Weapon::creatWeaponWithFighter(this, mTileMapPlus, weapKind);
	mWeapon[1] = Weapon::creatWeaponWithFighter(this, mTileMapPlus, weapKind);
	mWeapon[2] = Weapon::creatWeaponWithFighter(this, mTileMapPlus, weapKind);
	mWeapon[3] = Weapon::creatWeaponWithFighter(this, mTileMapPlus, weapKind);
	mWeapon[4] = Weapon::creatWeaponWithFighter(this, mTileMapPlus, weapKind);
	mWeapon[5] = Weapon::creatWeaponWithFighter(this, mTileMapPlus, weapKind);

	return true;
}
Fighter* Fighter::create(int k, TileMapPlus* tileMapInfo)
{

	Fighter* fighter = new Fighter();
	fighter->PicKind = k;
	mess0[0].picKind = fighter->PicKind;
	fighter->initWithFile("Sprite" + std::to_string(k) + ".png");
	
	fighter->init(tileMapInfo);
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
		
		float cursorX = e->getCursorX() + mapDeltaX;
		float cursorY = e->getCursorY() + mapDeltaY;
		
		Vec2 nowPos = getPosition();
		
		if ((cursorX - nowPos.x) * (cursorX - nowPos.x) + (cursorY - nowPos.y) * (cursorY - nowPos.y) > 1.0) {
			float nowAngel = acos((nowPos.y - cursorY) / sqrt((cursorX - nowPos.x) * (cursorX - nowPos.x) + (cursorY - nowPos.y) * (cursorY - nowPos.y))) / acos(-1) * 180;

			if (nowPos.x < cursorX) {
				nowAngel = -nowAngel;

			}
			
			float nowRotation = getRotation();
			setRotation(nowAngel);
			mess0[0].rotation = nowAngel;
			Rect nowBouding = getBoundingBox();
			if (mTileMapPlus->collisionTest(nowBouding)) {
				setRotation(nowRotation);
				mess0[0].rotation = nowRotation;
			}

			//auto rotateAngel = RotateTo::create(0, Vec3(0, 0, nowAngel));

			//runAction(rotateAngel);

		}
		
	};
	mouseListener->onMouseDown = [=](Event * event)
	{
		if (weapRank >= 1) {
			mWeapon[0]->fire(0);
		}
		if (weapRank >= 3) {
			mWeapon[1]->fire(20);
			mWeapon[2]->fire(-20);
		}
		if(weapRank >= 6){
			mWeapon[3]->fire(180);
		}
		if (weapRank >= 10) {
			mWeapon[4]->fire(-90);
			mWeapon[5]->fire(90);
		}
		mess0[0].fire = (unsigned char)(1);
	};
	keyBoardListener->onKeyPressed = [=](EventKeyboard::KeyCode keycode, Event * event)
	{
		keys[keycode] = true;
		if (keycode == EventKeyboard::KeyCode::KEY_1 || keycode == EventKeyboard::KeyCode::KEY_2 || keycode == EventKeyboard::KeyCode::KEY_3) {
			setWeapKind(int(keycode) - 76);
		}
		if (keycode == EventKeyboard::KeyCode::KEY_SPACE) {
			if (weapRank >= 1) {
				mWeapon[0]->fire(0);
			}
			if (weapRank >= 3) {
				mWeapon[1]->fire(20);
				mWeapon[2]->fire(-20);
			}
			if (weapRank >= 6) {
				mWeapon[3]->fire(180);
			}
			if (weapRank >= 10) {
				mWeapon[4]->fire(-90);
				mWeapon[5]->fire(90);
			}
			mess0[0].fire = (unsigned char)(1);
		}
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
	cocos2d::EventKeyboard::KeyCode leftArrow[2] = { EventKeyboard::KeyCode::KEY_A, EventKeyboard::KeyCode::KEY_LEFT_ARROW };
	cocos2d::EventKeyboard::KeyCode rightArrow[2] = { EventKeyboard::KeyCode::KEY_D, EventKeyboard::KeyCode::KEY_RIGHT_ARROW };
	cocos2d::EventKeyboard::KeyCode upArrow[2] = { EventKeyboard::KeyCode::KEY_W, EventKeyboard::KeyCode::KEY_UP_ARROW };
	cocos2d::EventKeyboard::KeyCode downArrow[2] = { EventKeyboard::KeyCode::KEY_S, EventKeyboard::KeyCode::KEY_DOWN_ARROW };

	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 dPosition = Vec2::ZERO;
	if (keys[upArrow[0]] || keys[upArrow[1]]) {
		dPosition.y += 6;
	}
	if (keys[downArrow[0]] || keys[downArrow[1]]) {
		dPosition.y -= 6;
	}
	if (keys[leftArrow[0]] || keys[leftArrow[1]]) {
		dPosition.x -= 6;
	}
	if (keys[rightArrow[0]] || keys[rightArrow[1]]) {
		dPosition.x += 6;
	}
	/*向量等长化*/
	if (dPosition.x * dPosition.x + dPosition.y * dPosition.y > 40) {
		dPosition.x /= 1.414f;
		dPosition.y /= 1.414f;
	}
	if (getPositionX() + dPosition.x >= 0 && getPositionX() + dPosition.x < mTileMapPlus->getTileMap()->getContentSize().width && getPositionY() + dPosition.y >= 0 && getPositionY() + dPosition.y < mTileMapPlus->getTileMap()->getContentSize().height) {
		Rect nowBounding = getBoundingBox();
		if (!mTileMapPlus->collisionTest(Rect(nowBounding.getMinX() + dPosition.x, nowBounding.getMinY() + dPosition.y, nowBounding.size.width, nowBounding.size.height))) {
			Vec2 nowPos = getPosition();
			setPosition(Vec2(nowPos.x + dPosition.x, nowPos.y + dPosition.y));
			mess0[0].x = nowPos.x + dPosition.x;
			mess0[0].y = nowPos.y + dPosition.y;
			if (HP >= 0) {
				
				auto sprite = (Sprite*)mTileMapPlus->getTileMap()->getChildByTag(BLOOD_BAD);
				auto progress = (ProgressTimer*)mTileMapPlus->getTileMap()->getChildByTag(BLOOD_BAR);
				sprite->setPosition(Vec2(getPositionX(), getPositionY() + 60));
				progress->setPosition(Vec2(getPositionX(), getPositionY() + 60));
				progress->setPercentage((((float)HP) / PLAYER_LIFE) * 100);  //这里是百分制显示
				
			}
			Vec2 nowTilePos = mTileMapPlus->getTileMap()->getPosition();
			MoveTo* act;
		

			if (nowPos.x <= visibleSize.width && nowPos.x + dPosition.x > visibleSize.width) {
				act = MoveTo::create(0.2f, Vec3(-SCREEN_SIZE.width + TILEWIDTH, nowTilePos.y, 0));
				mTileMapPlus->getTileMap()->runAction(act);
				//mTileMapPlus->getTileMap()->setPosition(-SCREEN_SIZE.width + TILEWIDTH, nowTilePos.y);
				mapDeltaX = SCREEN_SIZE.width - TILEWIDTH;
			}
			if (nowPos.x > visibleSize.width && nowPos.x + dPosition.x <= visibleSize.width) {
				act = MoveTo::create(0.2f, Vec3(0, nowTilePos.y, 0));
				mTileMapPlus->getTileMap()->runAction(act);
				//mTileMapPlus->getTileMap()->setPosition(0, nowTilePos.y);
				mapDeltaX = 0.0;
			}
			if (nowPos.y <= visibleSize.height && nowPos.y + dPosition.y > visibleSize.height) {
				act = MoveTo::create(0.2f, Vec3(nowTilePos.x,  - SCREEN_SIZE.height + TILEHEIGHT, 0));
				mTileMapPlus->getTileMap()->runAction(act);
				//mTileMapPlus->getTileMap()->setPosition(nowTilePos.x, -SCREEN_SIZE.height + TILEHEIGHT);
				mapDeltaY = SCREEN_SIZE.height - TILEHEIGHT;
			}
			if (nowPos.y > visibleSize.height && nowPos.y + dPosition.y <= visibleSize.height) {
				act = MoveTo::create(0.2f, Vec3(nowTilePos.x, 0, 0));
				mTileMapPlus->getTileMap()->runAction(act);
				//mTileMapPlus->getTileMap()->setPosition(nowTilePos.x, 0);
				mapDeltaY = 0.0;
			}
		}

	}
	return;
}

void Fighter::hpConsole()
{
	
	auto sprite = Sprite::create("Hp0.png");   //创建进度框
	sprite->setPosition(Vec2(getPosition().x,  getPosition().y + 100)); //设置框的位置
	sprite->setScale(0.2f);
	sprite->setTag(BLOOD_BAD);
	mTileMapPlus->getTileMap()->addChild(sprite, 1);    //加到默认图层里面去
	
	auto sprBlood = Sprite::create("Hp1.png");  //创建血条
	ProgressTimer * progress = ProgressTimer::create(sprBlood); //创建progress对象
	progress->setType(ProgressTimer::Type::BAR);        //类型：条状
	progress->setPosition(Vec2(getPosition().x, getPosition().y + 100));
	progress->setScale(0.2f);
	//从右到左减少血量
	progress->setMidpoint(Vec2(0, 0.5));     //如果是从左到右的话，改成(1,0.5)即可
	progress->setBarChangeRate(Point(1, 0));
	progress->setTag(BLOOD_BAR);       //做一个标记
	mTileMapPlus->getTileMap()->addChild(progress, 2);
	return;
}

void Fighter::hpUpdate(int delta)
{
	
	if (HP <= 0) return;
	HP -= delta;
	if (HP > 100) HP = 100;
	if (HP <= 0) {
		unscheduleUpdate();
		mTileMapPlus->getTileMap()->removeChildByTag(BLOOD_BAD);
		mTileMapPlus->getTileMap()->removeChildByTag(BLOOD_BAR);
		this->retain();
		mTileMapPlus->getTileMap()->removeChild(this);
	}
	mess0[0].HP = HP;
	return;
}

void Fighter::setWeapKind(int _kind)
{
	mess0[0].weapKind = _kind;
	weapKind = _kind;
	for (int i = 0; i < 6; ++i) {
		mWeapon[i]->switchKind(_kind);
	}
	return;
}