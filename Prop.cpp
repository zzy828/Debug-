#include "Prop.h"
#include "Fighter.h"
#include "SimpleAudioEngine.h"
#include "NormalDefine.h"

USING_NS_CC;

Prop::Prop() :isExist(true)
{

}
Prop::~Prop()
{

}
void Prop::init(TileMapPlus* tilemap, int weapKind = 1)
{
	tTileMapPlus = tilemap;
	TMXTiledMap* tmxTileMap = tTileMapPlus->getTileMap();
	kind = weapKind;
	initWithFile("Prop" + std::to_string(kind) + ".png");
	Size mapSize = tmxTileMap->getContentSize();
	tTileMapPlus->getTileMap()->addChild(this);
	if (kind == 1) {
		setScale(0.2f);
	}
	else {
		setScale(0.1f);
	}
	int newx = rand() % int(mapSize.width- 200) + 100, newy = rand() % int(mapSize.height - 200) + 100;
	setPosition(newx, newy);
	
	setVisible(true);
	schedule(schedule_selector(Prop::appear), float(rand()%10 + 20));
	return;

}
Prop* Prop::create(TileMapPlus * tilemap, int weapKind) {
	Prop* prop = new Prop();
	prop->init(tilemap, weapKind);
	prop->autorelease();
	return prop;
}
void Prop::appear(float delta)
{
	if (!isExist) {
		isExist = true;
		setVisible(true);
		return;
	}
	return;
}
void Prop::disappear()
{
	if (isExist) {
		isExist = false;
		setVisible(false);
		return;
	}
	return;
}

