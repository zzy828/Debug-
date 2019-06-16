#include "ChoiceScene.h"
#include "Paddle.h"
#include "SimpleAudioEngine.h"
#include "NormalDefine.h"
#include "MapScene.h"
#include "ctime"
USING_NS_CC;

bool ChoiceScene::init()
{
	if (!Layer::init())
	{
		return false;
	}
	srand((unsigned)time(NULL));
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto pSprite = Sprite::create("BackGround.jpg");


	/*设置背景*/
	pSprite->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	auto pSize = pSprite->getContentSize();
	pSprite->setScaleX(visibleSize.width / pSize.width);
	pSprite->setScaleY(visibleSize.height / pSize.height);
	pSprite->setOpacity(150);
	this->addChild(pSprite, 0);

	/*设置标题*/
	auto label0 = Label::createWithTTF("Stage Select", "fonts/Marker Felt.ttf", 60);
	label0->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height - label0->getContentSize().height));
	label0->setColor(Color3B(50, 10, 20));
	this->addChild(label0, 1);

	/*设置管卡选择按钮*/
	const char* chooseImage[3] = { "LeftArrow.jpg", "RightArrow.jpg",
		"MidArrow.jpg"};
	float fSettings[4][4] = {
		{ 50.0f / 1280, 45.0f / 720, 480.0f / 1280, 220.0f / 720 },
		{ 50.0f / 1280, 45.0f / 720, 800.0f / 1280, 220.0f / 720 },
		{ 50.0f / 1280, 45.0f / 720, 640.0f / 1280, 220.0f / 720 },
		{ 70.0f / 1280, 60.0f / 720, 740.0f / 1280, 150.0f / 320 }
	};

	typeNum evts[4] = { typeNum::left, typeNum::right, typeNum::mid, typeNum::text };
	for (int i = 0; i < 3; ++i)
	{
		float* fSetting = fSettings[i];
		auto paddleTexture = Director::getInstance()->getTextureCache()->addImage(chooseImage[i]);
		auto pPaddle = Paddle::paddleWithTexture(paddleTexture, evts[i], 0);
		Size szBtn = pPaddle->getContentSize();
		pPaddle->setParentScene(this);
		pPaddle->setScaleX(visibleSize.width / szBtn.width * fSetting[0]);
		pPaddle->setScaleY(visibleSize.height / szBtn.height * fSetting[1]);
		pPaddle->setPosition(Vec2(origin.x + visibleSize.width * fSetting[2], origin.y + visibleSize.height * fSetting[3]));
		pPaddle->mouseClickListener();
		this->addChild(pPaddle, 1);
	

	}

	/*设置Round*/
	nowRound = 1;
	auto labelRound = Label::createWithTTF("Round:", "fonts/arial.ttf", 60);
	labelRound->setPosition(Vec2(origin.x + visibleSize.width / 2 - labelRound->getContentSize().width/2, origin.y + visibleSize.height/1.8 - labelRound->getContentSize().height));
	labelRound->setColor(Color3B(255, 255, 255));
	labelRound->enableShadow(Color4B::RED, Size(2, -2), 0.8);
	this->addChild(labelRound, 1);
	
	Label* label1 = Label::createWithTTF("1", "fonts/arial.ttf", 60);
	float* fSetting = fSettings[3];
	Size sz = label1->getContentSize();
	label1->setAnchorPoint(Vec2(0.5f, 0.5f));
	label1->setScaleX(visibleSize.width / sz.width * fSetting[0]);
	label1->setScaleY(visibleSize.height / sz.height * fSetting[1]);
	label1->setPosition(Vec2(visibleSize.width * fSetting[2], visibleSize.height * fSetting[3]));
	label1->setColor(Color3B(205, 205, 205));
	label1->enableShadow(Color4B::RED, Size(2, -2), 0.8);
	this->addChild(label1, 1, evts[3]);

	/*服务器*/

	return true;
}

Scene* ChoiceScene::scene(int _hero, int _model)
{
	auto scene = Scene::create();
	auto layer = ChoiceScene::create();
	
	if (scene && layer)
	{
		layer->setHero(_hero);
		layer->setModel(_model);
		scene->addChild(layer);
	}
	return scene;
}

void ChoiceScene::clickDownAction(typeNum _type)
{
	if (_type == typeNum::mid) {
		Scene* scene = MapScene::scene(nowRound, m_model, m_hero);
		Director::getInstance()->replaceScene(scene);
	}
	else if (_type == typeNum::left) {
		nowRound = (nowRound - 1 + ROUND - 1) % ROUND + 1;
		update();
	}
	else if (_type == typeNum::right) {
		nowRound = (nowRound + 1 + ROUND - 1) % ROUND + 1;
		update();
	}
	return;

}

void ChoiceScene::update()
{
	Label* label1 = (Label*)getChildByTag(text);
	label1->setString(std::to_string(nowRound));
	return;
}