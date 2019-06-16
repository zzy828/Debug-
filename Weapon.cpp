#include "Weapon.h"
#include "Fighter.h"
#include "SimpleAudioEngine.h"
#include "NormalDefine.h"

USING_NS_CC;

Weapon::Weapon() :isFlying(false), kind(1)
{

}
Weapon::~Weapon()
{

}
void Weapon::initWeaponWithFighter(cocos2d::Sprite* fighter, TileMapPlus* tilemap, int weapKind)
{
	mfighter = fighter;
	tTileMapPlus = tilemap;
	TMXTiledMap* tmxTileMap = tTileMapPlus->getTileMap();
	kind = weapKind;
	initWithFile("Weapon" + std::to_string(kind) + ".png");
	tTileMapPlus->getTileMap()->addChild(this);
	setVisible(false);

}
Weapon* Weapon::creatWeaponWithFighter(cocos2d::Sprite* fighter, TileMapPlus* tilemap, int weapKind) {
	Weapon* weapon = new Weapon();
	weapon->initWeaponWithFighter(fighter, tilemap, weapKind);
	weapon->autorelease();
	return weapon;
}
bool Weapon::fire(int dAngle) {
	if (!isFlying) {
		isFlying = true;
		setVisible(true);
		setPosition(mfighter->getPosition());
		float Rotation = mfighter->getRotation() + dAngle;
		setRotation(Rotation);
		if (kind == 3) setScale(0.2f);
		else if (kind == 2)setScale(0.25f);
		else setScale(0.35f);
		Rotation = Rotation / 180.0 * acos(-1);
		stepX = -WeaponV[kind] * sin(Rotation);
		stepY = -WeaponV[kind] * cos(Rotation);
		scheduleUpdate();
	}
	return isFlying;
}
void Weapon::update(float delta)
{
	Sprite::update(delta);
	//设置移动后的位置
	setPosition(Vec2(getPositionX() + stepX, getPositionY() + stepY));

	//检测是否有碰撞
	Rect rect = getBoundingBox();
	if (tTileMapPlus->collisionTest(rect))
	{
		unscheduleUpdate();
		setVisible(false);
		isFlying = false;
		//引爆子弹
	}
}

void Weapon::stopFire()
{
	if (isFlying == true)
	{
		isFlying = false;
		setVisible(false);
		unscheduleUpdate();

		return;
	}
	return;
}

void Weapon::switchKind(int _kind)
{
	kind = _kind;
	Texture2D* texture = Director::getInstance()->getTextureCache()->addImage("Weapon" + std::to_string(kind) + ".png");
	setTexture(texture);
	Rect tmp;
	tmp.size = texture->getContentSize();
	setTextureRect(tmp);
	
	if (kind == 3) setScale(0.2f);
	else if (kind == 2)setScale(0.25f);
	else setScale(0.35f);
	return; 
}