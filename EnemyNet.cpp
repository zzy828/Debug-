#include "EnemyNet.h"
#include "Weapon.h"
#include "NormalDefine.h"
USING_NS_CC;

EnemyNet::EnemyNet()
{
	weapRank = 1;
	weapKind = 2;
}

EnemyNet::~EnemyNet()
{

}

bool EnemyNet::init(TileMapPlus* tileMapInfo)
{

	setPosition(400.0f, 400.0f);
	HP = 100;
	Ai = false;
	mTileMapPlus = tileMapInfo;
	mTileMapPlus->getTileMap()->addChild(this);
	TMXTiledMap* tmxTileMap = mTileMapPlus->getTileMap();
	setScale(0.6f);
	setVisible(false);
	visb = false;
	mWeapon[0] = Weapon::creatWeaponWithFighter(this, mTileMapPlus, weapKind);
	mWeapon[1] = Weapon::creatWeaponWithFighter(this, mTileMapPlus, weapKind);
	mWeapon[2] = Weapon::creatWeaponWithFighter(this, mTileMapPlus, weapKind);
	mWeapon[3] = Weapon::creatWeaponWithFighter(this, mTileMapPlus, weapKind);
	mWeapon[4] = Weapon::creatWeaponWithFighter(this, mTileMapPlus, weapKind);
	mWeapon[5] = Weapon::creatWeaponWithFighter(this, mTileMapPlus, weapKind);

	return true;
}
EnemyNet* EnemyNet::create(int k, TileMapPlus* tileMapInfo)
{

	EnemyNet* fighter = new EnemyNet();
	fighter->PicKind = k;
	fighter->initWithFile("Sprite" + std::to_string(k) + ".png");

	fighter->init(tileMapInfo);
	fighter->autorelease();
	return fighter;
}

void EnemyNet::fireAll()
{

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


	return;

}


void EnemyNet::setWeapKind(int _kind)
{
	weapKind = _kind;
	for (int i = 0; i < 6; ++i) {
		mWeapon[i]->switchKind(_kind);
	}
	return;
}
void EnemyNet::switchKind(int _kind)
{
	PicKind = _kind;
	Texture2D* texture = Director::getInstance()->getTextureCache()->addImage("Sprite" + std::to_string(PicKind) + ".png");
	setTexture(texture);
	Rect tmp;
	tmp.size = texture->getContentSize();
	setTextureRect(tmp);
	setScale(0.6f);
	return;
}

void EnemyNet::goDie()
{
	visb = false;
	setVisible(false);
	return;
}
void EnemyNet::goAlive()
{
	visb = true;
	setVisible(true);
	return;
}