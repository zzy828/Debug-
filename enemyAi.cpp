#include "enemyAi.h"
#include "Weapon.h"
#include "NormalDefine.h"
#include "ArrowClient.h"
USING_NS_CC;
extern ArrowMessage mess0[4];
extern ArrowClient client0;
EnemyAi::EnemyAi()
{
	

}

EnemyAi::~EnemyAi()
{

}

bool EnemyAi::init(TileMapPlus* tileMapInfo)
{

	int p = rand() % 5;
	setPosition(AiPosition[p][0], AiPosition[p][1]);
	setRotation(rand() % 360 - 170);

	mTileMapPlus = tileMapInfo;

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
	return true;
}
EnemyAi* EnemyAi::create(int k, TileMapPlus* tileMapInfo)
{

	EnemyAi* fighter = new EnemyAi();
	fighter->initWithFile("Sprite" + std::to_string(k) + ".png");
	fighter->PicKind = k;
	fighter->weapRank = rand() % 6;
	fighter->weapKind = rand() % 3 + 1;
	fighter->HP = 100;
	mess0[k].picKind = (unsigned char)(k);
	mess0[k].weapKind = (unsigned char)(fighter->weapKind);
	mess0[k].weapRank = (unsigned char)(fighter->weapRank);
	mess0[k].Ai = true;
	mess0[k].HP = 100;
	fighter->init(tileMapInfo);
	fighter->autorelease();
	return fighter;
}


void EnemyAi::update(float delta)
{
	Sprite::update(delta);

	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 dPosition = Vec2::ZERO;
	float Rotation = getRotation();
	dPosition.x = -2 * sin(Rotation / 180.0 * acos(-1));
	dPosition.y = -2 * cos(Rotation / 180.0 * acos(-1));
	if (getPositionX() + dPosition.x >= 0 && getPositionX() + dPosition.x < mTileMapPlus->getTileMap()->getContentSize().width && getPositionY() + dPosition.y >= 0 && getPositionY() + dPosition.y < mTileMapPlus->getTileMap()->getContentSize().height) {
		Rect nowBounding = getBoundingBox();
		if (!mTileMapPlus->collisionTest(Rect(nowBounding.getMinX() + dPosition.x, nowBounding.getMinY() + dPosition.y, nowBounding.size.width, nowBounding.size.height))) {
			Vec2 nowPos = getPosition();
			setPosition(Vec2(nowPos.x + dPosition.x, nowPos.y + dPosition.y));
			mess0[PicKind].x = nowPos.x + dPosition.x;
			mess0[PicKind].y = nowPos.y + dPosition.y;
		}
		else {
			Rotation += rand()%5 + 1;
			if (Rotation > 180.0) {
				Rotation -= 360.0;
			}
			setRotation(Rotation);
			mess0[PicKind].rotation = Rotation;
		}
	}
	if (rand() < 500) {
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
		mess0[PicKind].fire = (unsigned char)(1);
	}
	return;
}

void EnemyAi::hpUpdate(int delta) 
{
	
	if (HP <= 0) return;
	HP -= delta; 
	if (HP <= 0) {
		unscheduleUpdate();
		retain();
		mTileMapPlus->getTileMap()->removeChild(this);
		mess0[PicKind].HP = HP;
	}
	mess0[PicKind].HP = HP;
	return;
}