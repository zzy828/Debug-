#include "MapScene.h"
#include "OverScene.h"
#include "Fighter.h"
#include "Weapon.h"
#include "enemyAi.h"
#include "EnemyNet.h"
#include "TileMapPlus.h"
#include "SimpleAudioEngine.h"


using namespace CocosDenshion;
USING_NS_CC;
extern ArrowClient client0;
extern ArrowMessage mess0[4];
Scene* MapScene::scene()
{
	Scene* scene = Scene::create();
	MapScene* layer = MapScene::create();

	scene->addChild(layer);

	return scene;
}

Scene* MapScene::scene(int round, int model, int kind)
{
	Scene* scene = Scene::create();
	MapScene* layer = MapScene::create(round, model, kind);

	scene->addChild(layer);

	return scene;
}

MapScene* MapScene::create(int round, int model, int kind)
{
	MapScene* pRet = new MapScene;
	if (pRet)
	{
		pRet->setRound(round);
		pRet->setModel(model);
		pRet->setSkind(kind);
		if (pRet->init())
		{
			pRet->autorelease();
			return pRet;
		}
	}


	return nullptr;
}

bool MapScene::init()
{
	if (!Layer::init()) {
		return false;
	}
	
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto pSprite = Sprite::create("BackGround.jpg");

	/*设置背景*/

	// 添加 声音  的开关按钮
	/*MenuItemImage *_turnOn, *_turnOff;
	_turnOn = MenuItemImage::create(
		"MidArrow1.png",
		"MidArrow1.png");
	_turnOff = MenuItemImage::create(
		"MidArrow.jpg",
		"MidArrow.jpg");
	MenuItemToggle *toggleItem = MenuItemToggle::createWithCallback(CC_CALLBACK_1(MapScene::menuMusicCallback, this), _turnOn, _turnOff, NULL);

	//toggleItem->setScale(0.3f);
	toggleItem->setPosition(Point(0, 0));
	*/

	pSprite->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	auto pSize = pSprite->getContentSize();
	pSprite->setScaleX(visibleSize.width / pSize.width);
	pSprite->setScaleY(visibleSize.height / pSize.height);
	pSprite->setOpacity(100);
	this->addChild(pSprite, 0);

	TileMapPlus* tmxFile = TileMapPlus::createMapInfoWithFile(("map/RoundBig" + std::to_string(getRound()) + ".tmx").c_str());

	//将地图放到屏幕中间
	TMXTiledMap* tmxTileMap = tmxFile->getTileMap();
	this->addChild(tmxTileMap, 1);
	
	fighter = Fighter::create(getSkind(), tmxFile);
	fighter->fighterListener();
	fighter->hpConsole();

	
	
	for (int i = 0; i < 30; ++i) {
		prop[i] = Prop::create(tmxFile, (rand() < 2 * RAND_MAX / 5) ? 1 : 2);
	}
	if (getModel() == 0) {
		enemyAi[0] = EnemyAi::create(rand() % 3 + 1, tmxFile);
		enemyAi[1] = EnemyAi::create(rand() % 3 + 1, tmxFile);
		enemyAi[2] = EnemyAi::create(rand() % 3 + 1, tmxFile);
		enemyAi[3] = EnemyAi::create(rand() % 3 + 1, tmxFile);
		enemyAi[4] = EnemyAi::create(rand() % 3 + 1, tmxFile);
	}
	else{
		client0.init();
		if (!client0.connectServer()) {
			setModel(0);
			enemyAi[0] = EnemyAi::create(rand() % 3 + 1, tmxFile);
			enemyAi[1] = EnemyAi::create(rand() % 3 + 1, tmxFile);
			enemyAi[2] = EnemyAi::create(rand() % 3 + 1, tmxFile);
			enemyAi[3] = EnemyAi::create(rand() % 3 + 1, tmxFile);
			enemyAi[4] = EnemyAi::create(rand() % 3 + 1, tmxFile);

		}
		else {
			for (int i = 0; i < 4; ++i) {
				mess0[i].fire = 0;
			}
			enemyAi[0] = EnemyAi::create(1, tmxFile);
			enemyAi[1] = EnemyAi::create(2, tmxFile);
			enemyAi[2] = EnemyAi::create(3, tmxFile);
			for(int i = 0; i < 5; ++i){
				for (int j = 0; j < 4; ++j) {
					enemyNet[i][j] = EnemyNet::create(1, tmxFile);
					client0.enemyNet[i][j] = enemyNet[i][j];
				}
			}
		}
	}

	scheduleUpdate();
	return true;
}

//int isPause = true;
/*void MapScene::menuMusicCallback(cocos2d::Ref* pSender)
{
	if (isPause == false)
	{
		SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
		isPause = true;
	}
	else
	{
		SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
		isPause = false;
	}
}*/

bool MapScene::IsRectIntersect(Rect rectA, Rect rectB)
{
	float left = std::max(rectA.getMinX(), rectB.getMinX());
	float right = std::min(rectA.getMaxX(), rectB.getMaxX());
	if (left > right)
		return false;

	float top = std::min(rectA.getMaxY(), rectB.getMaxY());
	float bottom = std::max(rectA.getMinY(), rectB.getMinY());
	if (top < bottom)
		return false;

	return true;

}

void MapScene::update(float delta)
{
	Layer::update(delta);
	
	if (fighter->HP <= 0)
	{
		mess0[0].HP = mess0[1].HP = mess0[2].HP = mess0[3].HP = 0;
		client0.sendSprite();
		unscheduleUpdate();
		Scene* nScene = OverScene::scene(0);
		Director::getInstance()->replaceScene(nScene);
		return;
	}
	int limit = getModel() ? 3 : 5;
	bool flagFail = true;
	for (int i = 0; i < limit; ++i) {
		if (enemyAi[i]->HP > 0) {
			flagFail = false;
		}
	}

	if (getModel()) {
		for (int i = 0; i < client0.number; ++i) {
			for (int j = 0; j < 4; ++j) {
				if (enemyNet[i][j]->HP > 0) {
					flagFail = false;
				}
			}
		}
	}
	if (flagFail) {
		client0.sendSprite();
		unscheduleUpdate();
		Scene* nScene = OverScene::scene(1);
		Director::getInstance()->replaceScene(nScene);
		return;
	}
	
	for (int i = 0; i < limit; ++i) {
		if (fighter->HP <= 0) {
			continue; 
		}
		if (fighter->getWeapRank() >= 1) {
			if (enemyAi[i]->HP > 0 && fighter->mWeapon[0]->isFlying && IsRectIntersect(fighter->mWeapon[0]->getBoundingBox(), enemyAi[i]->getBoundingBox())) {
				fighter->mWeapon[0]->stopFire();
				enemyAi[i]->hpUpdate(15);

			}
		}
		if (fighter->getWeapRank() >= 3) {
			if (enemyAi[i]->HP > 0 && fighter->mWeapon[1]->isFlying && IsRectIntersect(fighter->mWeapon[1]->getBoundingBox(), enemyAi[i]->getBoundingBox())) {
				fighter->mWeapon[1]->stopFire();
				enemyAi[i]->hpUpdate(15);

			}
			if (enemyAi[i]->HP > 0 && fighter->mWeapon[2]->isFlying && IsRectIntersect(fighter->mWeapon[2]->getBoundingBox(), enemyAi[i]->getBoundingBox())) {
				fighter->mWeapon[2]->stopFire();
				enemyAi[i]->hpUpdate(15);

			}

		}
		if (fighter->getWeapRank() >= 6){
			if (enemyAi[i]->HP > 0 && fighter->mWeapon[3]->isFlying && IsRectIntersect(fighter->mWeapon[3]->getBoundingBox(), enemyAi[i]->getBoundingBox())) {
				fighter->mWeapon[3]->stopFire();
				enemyAi[i]->hpUpdate(15);

			}
		}
		if(fighter->getWeapRank() >= 10) {
			if (enemyAi[i]->HP > 0 && fighter->mWeapon[4]->isFlying && IsRectIntersect(fighter->mWeapon[4]->getBoundingBox(), enemyAi[i]->getBoundingBox())) {
				fighter->mWeapon[4]->stopFire();
				enemyAi[i]->hpUpdate(15);

			}
			if (enemyAi[i]->HP > 0 && fighter->mWeapon[5]->isFlying && IsRectIntersect(fighter->mWeapon[5]->getBoundingBox(), enemyAi[i]->getBoundingBox())) {
				fighter->mWeapon[5]->stopFire();
				enemyAi[i]->hpUpdate(15);

			}
		}
	}
	
	//return;
	for (int i = 0; i < limit; ++i) {
		if (enemyAi[i]->HP > 0) {
			if (enemyAi[i]->weapRank >= 1) {
				if (fighter->HP > 0&& enemyAi[i]->mWeapon[0]->isFlying&& IsRectIntersect(fighter->getBoundingBox(), enemyAi[i]->mWeapon[0]->getBoundingBox())) {
					fighter->hpUpdate(15);
					enemyAi[i]->mWeapon[0]->stopFire();
				}
			}
			if (enemyAi[i]->weapRank >= 3){
				if (fighter->HP > 0 && enemyAi[i]->mWeapon[1]->isFlying && IsRectIntersect(fighter->getBoundingBox(), enemyAi[i]->mWeapon[1]->getBoundingBox())) {
					fighter->hpUpdate(15);
					enemyAi[i]->mWeapon[1]->stopFire();
				}
				if (fighter->HP > 0 && enemyAi[i]->mWeapon[2]->isFlying && IsRectIntersect(fighter->getBoundingBox(), enemyAi[i]->mWeapon[2]->getBoundingBox())) {
					fighter->hpUpdate(15);
					enemyAi[i]->mWeapon[2]->stopFire();
				}

			}
			if (enemyAi[i]->weapRank >= 6) {
				if (fighter->HP > 0 && enemyAi[i]->mWeapon[3]->isFlying && IsRectIntersect(fighter->getBoundingBox(), enemyAi[i]->mWeapon[3]->getBoundingBox())) {
					fighter->hpUpdate(15);
					enemyAi[i]->mWeapon[3]->stopFire();
				}
			}
			if (enemyAi[i]->weapKind >= 10) {
				if (fighter->HP > 0 && enemyAi[i]->mWeapon[4]->isFlying && IsRectIntersect(fighter->getBoundingBox(), enemyAi[i]->mWeapon[4]->getBoundingBox())) {
					fighter->hpUpdate(15);
					enemyAi[i]->mWeapon[4]->stopFire();
				}
				if (fighter->HP > 0 && enemyAi[i]->mWeapon[5]->isFlying && IsRectIntersect(fighter->getBoundingBox(), enemyAi[i]->mWeapon[5]->getBoundingBox())) {
					fighter->hpUpdate(15);
					enemyAi[i]->mWeapon[5]->stopFire();
				}
			}
		}
	}
	if (fighter->HP > 0) {
		for (int i = 0; i < 30; ++i) {
			if (prop[i]->isExist) {
				if (IsRectIntersect(fighter->getBoundingBox(), prop[i]->getBoundingBox())) {
					if (prop[i]->kind == 1) {
						fighter->weapRank = std::min(fighter->weapRank+ 1, 10);
						prop[i]->disappear();
					}
					else if(prop[i]->kind == 2){
						fighter->hpUpdate(-20);
						prop[i]->disappear();
					}
				}
			}
		}
	}
	if (getModel()) {
		if (fighter->HP > 0) {
			for (int i = 0; i < 5; ++i) {
				for (int j = 0; j < 4; ++j) {
					if (enemyNet[i][j]->HP > 0) {
						if (!enemyNet[i][j]->Ai) {
							if (enemyNet[i][j]->weapRank >= 1) {
								if (fighter->HP > 0 && enemyNet[i][j]->mWeapon[0]->isFlying && IsRectIntersect(fighter->getBoundingBox(), enemyNet[i][j]->mWeapon[0]->getBoundingBox())) {
									fighter->hpUpdate(15);
									enemyNet[i][j]->mWeapon[0]->stopFire();
								}
							}
							if (enemyNet[i][j]->weapRank >= 3) {
								if (fighter->HP > 0 && enemyNet[i][j]->mWeapon[1]->isFlying && IsRectIntersect(fighter->getBoundingBox(), enemyNet[i][j]->mWeapon[1]->getBoundingBox())) {
									fighter->hpUpdate(15);
									enemyNet[i][j]->mWeapon[1]->stopFire();
								}
								if (fighter->HP > 0 && enemyNet[i][j]->mWeapon[2]->isFlying && IsRectIntersect(fighter->getBoundingBox(), enemyNet[i][j]->mWeapon[2]->getBoundingBox())) {
									fighter->hpUpdate(15);
									enemyNet[i][j]->mWeapon[2]->stopFire();
								}

							}
							if (enemyNet[i][j]->weapRank >= 6) {
								if (fighter->HP > 0 && enemyNet[i][j]->mWeapon[3]->isFlying && IsRectIntersect(fighter->getBoundingBox(), enemyNet[i][j]->mWeapon[3]->getBoundingBox())) {
									fighter->hpUpdate(15);
									enemyNet[i][j]->mWeapon[3]->stopFire();
								}
							}
							if (enemyNet[i][j]->weapRank >= 10) {
								if (fighter->HP > 0 && enemyNet[i][j]->mWeapon[4]->isFlying && IsRectIntersect(fighter->getBoundingBox(), enemyNet[i][j]->mWeapon[4]->getBoundingBox())) {
									fighter->hpUpdate(15);
									enemyNet[i][j]->mWeapon[4]->stopFire();
								}
								if (fighter->HP > 0 && enemyNet[i][j]->mWeapon[5]->isFlying && IsRectIntersect(fighter->getBoundingBox(), enemyNet[i][j]->mWeapon[5]->getBoundingBox())) {
									fighter->hpUpdate(15);
									enemyNet[i][j]->mWeapon[5]->stopFire();
								}
							}
						}

					}
				}
			}
			
			for (int i = 0; i < 3; ++i) {
				if (enemyAi[i]->HP <= 0) {
					continue;
				}
				
				for (int j = 0; j < 4; ++j) {
					for (int k = 0; k < client0.number; ++k) {
						if (enemyNet[k][j]->HP <= 0) {
							continue;
						}
						if (enemyNet[k][j]->weapRank >= 1) {
							if (enemyAi[i]->HP > 0 && enemyNet[k][j]->mWeapon[0]->isFlying && IsRectIntersect(enemyNet[k][j]->mWeapon[0]->getBoundingBox(), enemyAi[i]->getBoundingBox())) {
								enemyNet[k][j]->mWeapon[0]->stopFire();
								enemyAi[i]->hpUpdate(15);

							}
						}
						
						if (enemyNet[k][j]->weapRank >= 3) {
							if (enemyAi[i]->HP > 0 && enemyNet[k][j]->mWeapon[1]->isFlying && IsRectIntersect(enemyNet[k][j]->mWeapon[1]->getBoundingBox(), enemyAi[i]->getBoundingBox())) {
								enemyNet[k][j]->mWeapon[1]->stopFire();
								enemyAi[i]->hpUpdate(15);

							}
							if (enemyAi[i]->HP > 0 && enemyNet[k][j]->mWeapon[2]->isFlying && IsRectIntersect(enemyNet[k][j]->mWeapon[2]->getBoundingBox(), enemyAi[i]->getBoundingBox())) {
								enemyNet[k][j]->mWeapon[2]->stopFire();
								enemyAi[i]->hpUpdate(15);

							}

						}
						if (enemyNet[k][j]->weapRank >= 6) {
							if (enemyAi[i]->HP > 0 && enemyNet[k][j]->mWeapon[3]->isFlying && IsRectIntersect(enemyNet[k][j]->mWeapon[3]->getBoundingBox(), enemyAi[i]->getBoundingBox())) {
								enemyNet[k][j]->mWeapon[3]->stopFire();
								enemyAi[i]->hpUpdate(15);

							}
						}
						if (enemyNet[k][j]->weapRank >= 10) {
							if (enemyAi[i]->HP > 0 && enemyNet[k][j]->mWeapon[4]->isFlying && IsRectIntersect(enemyNet[k][j]->mWeapon[4]->getBoundingBox(), enemyAi[i]->getBoundingBox())) {
								enemyNet[k][j]->mWeapon[4]->stopFire();
								enemyAi[i]->hpUpdate(15);

							}
							if (enemyAi[i]->HP > 0 && enemyNet[k][j]->mWeapon[5]->isFlying && IsRectIntersect(enemyNet[k][j]->mWeapon[5]->getBoundingBox(), enemyAi[i]->getBoundingBox())) {
								enemyNet[k][j]->mWeapon[5]->stopFire();
								enemyAi[i]->hpUpdate(15);

							}
						}
					}
				}
			}
		}
		if (fighter->HP > 0) {
			for (int i = 0; i < client0.number; ++i) {
				for (int j = 0; j < 4; ++j) {
					if (fighter->getWeapRank() >= 1) {
						if (enemyNet[i][j]->visb && fighter->mWeapon[0]->isFlying && IsRectIntersect(fighter->mWeapon[0]->getBoundingBox(), enemyNet[i][j]->getBoundingBox())) {
							fighter->mWeapon[0]->stopFire();
						}
					}
					if (fighter->getWeapRank() >= 3) {
						if (enemyNet[i][j]->visb && fighter->mWeapon[1]->isFlying && IsRectIntersect(fighter->mWeapon[1]->getBoundingBox(), enemyNet[i][j]->getBoundingBox())) {
							fighter->mWeapon[1]->stopFire();
						}
						if (enemyNet[i][j]->visb && fighter->mWeapon[2]->isFlying && IsRectIntersect(fighter->mWeapon[2]->getBoundingBox(), enemyNet[i][j]->getBoundingBox())) {
							fighter->mWeapon[2]->stopFire();
						}

					}
					if (fighter->getWeapRank() >= 6) {
						if (enemyNet[i][j]->visb && fighter->mWeapon[3]->isFlying && IsRectIntersect(fighter->mWeapon[3]->getBoundingBox(), enemyNet[i][j]->getBoundingBox())) {
							fighter->mWeapon[3]->stopFire();
						}
					}
					if (fighter->getWeapRank() >= 10) {
						if (enemyNet[i][j]->visb && fighter->mWeapon[4]->isFlying && IsRectIntersect(fighter->mWeapon[0]->getBoundingBox(), enemyNet[i][j]->getBoundingBox())) {
							fighter->mWeapon[0]->stopFire();
						}
						if (enemyNet[i][j]->visb && fighter->mWeapon[5]->isFlying && IsRectIntersect(fighter->mWeapon[0]->getBoundingBox(), enemyNet[i][j]->getBoundingBox())) {
							fighter->mWeapon[0]->stopFire();
						}
					}
				}
			}
		}
		pSec++;
		client0.sendSprite();
		if ((pSec % 4) == 0) {
			
			client0.recvSprite();
		}
		for (int i = 0; i < 4; ++i) {
			mess0[i].fire = 0;
		}
	}
	return;
}