#include "OverScene.h"
#include "ArrowClient.h"

USING_NS_CC;
extern ArrowClient client0;
Scene* OverScene::scene(int flagwin)
{
	Scene* scene = Scene::create();
	OverScene* layer = OverScene::create(flagwin);

	scene->addChild(layer);

	return scene;
}


OverScene* OverScene::create(int flagwin)
{
	OverScene* pRet = new OverScene;
	if (pRet)
	{
		if (pRet->init(flagwin))
		{
			pRet->flagWin = flagwin;
			pRet->autorelease();
			return pRet;
		}
	}
	return nullptr;
}

bool OverScene::init(int flag)
{
	if (!Layer::init()) {
		return false;
	}

	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto pSprite = Sprite::create("BackGround.jpg");


	/*设置背景*/
	pSprite->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	auto pSize = pSprite->getContentSize();
	pSprite->setScaleX(visibleSize.width / pSize.width);
	pSprite->setScaleY(visibleSize.height / pSize.height);
	pSprite->setOpacity(10);
	this->addChild(pSprite, 0);

	/*设置标题*/
	Label* label0;
	if(!flag) label0 = Label::createWithTTF("Game Over!: Your Fail", "fonts/Marker Felt.ttf", 60);
	else label0 = Label::createWithTTF("Congratulation!: Your Win", "fonts/Marker Felt.ttf", 60);
	label0->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + 2*visibleSize.height/3 - label0->getContentSize().height));
	label0->setColor(Color3B(200, 200, 20));
	this->addChild(label0, 1);

	/*关闭按钮*/
	auto closeItem = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(OverScene::closeCallback, this));

	float x = origin.x + visibleSize.width / 2.0f;
	float y = origin.y + visibleSize.height * 1.0f / 4.0f;
	closeItem->setPosition(Vec2(x, y));
	auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);
	client0.disconnectServer();

	return true;
}

void OverScene::closeCallback(Ref* pSender)
{
	Director::getInstance()->end();
	return;
}
