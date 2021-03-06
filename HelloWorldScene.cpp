/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));

    if (closeItem == nullptr ||
        closeItem->getContentSize().width <= 0 ||
        closeItem->getContentSize().height <= 0)
    {
        problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
    }
    else
    {
        float x = origin.x + visibleSize.width - closeItem->getContentSize().width/2;
        float y = origin.y + closeItem->getContentSize().height/2;
        closeItem->setPosition(Vec2(x,y));
    }

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label

    auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
    if (label == nullptr)
    {
        problemLoading("'fonts/Marker Felt.ttf'");
    }
    else
    {
        // position the label on the center of the screen
        label->setPosition(Vec2(origin.x + visibleSize.width/2,
                                origin.y + visibleSize.height - label->getContentSize().height));

        // add the label as a child to this layer
        this->addChild(label, 1);
    }

    // add "HelloWorld" splash screen"
	sprite = Sprite::create("HelloWorld.png");
    if (sprite == nullptr)
    {
        problemLoading("'HelloWorld.png'");
    }
    else
    {
        // position the sprite on the center of the screen
        sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
		sprite->setScale(0.5f);
        // add the sprite as a child to this layer
        this->addChild(sprite, 0);
    }
	
	auto _mouseListen = EventListenerMouse::create();
	// The mouse move function.
	_mouseListen->onMouseMove = [=](Event * event)
	{
		EventMouse* e = (EventMouse*)event;
		float cursorX = e->getCursorX();
		float cursorY = e->getCursorY();
		Vec2 nowPos = sprite->getPosition();
		if ((cursorX - nowPos.x) * (cursorX - nowPos.x) + (cursorY - nowPos.y) * (cursorY - nowPos.y) > 1.0) {
			float nowAngel = acos((nowPos.y - cursorY) / sqrt((cursorX - nowPos.x) * (cursorX - nowPos.x) + (cursorY - nowPos.y) * (cursorY - nowPos.y)))/acos(-1) * 180;
			if (nowPos.x < cursorX) {
				nowAngel = -nowAngel;
			}
			auto rotateAngel = RotateTo::create(0, Vec3(0, 0, nowAngel));
			sprite->runAction(rotateAngel);
		}
	};
	auto _keyboardListen = EventListenerKeyboard::create();
	_keyboardListen->onKeyPressed = [=](EventKeyboard::KeyCode keycode, Event * event)
	{
		keys[keycode] = true;
	};
	_keyboardListen->onKeyReleased = [=](EventKeyboard::KeyCode keycode, Event * event)
	{
		keys[keycode] = false;
	};
	auto _eventDispatcher = Director::getInstance()->getEventDispatcher();
	_eventDispatcher->addEventListenerWithSceneGraphPriority(_mouseListen, sprite);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(_keyboardListen, sprite);

	this->scheduleUpdate();
    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);


}

void HelloWorld::update(float delta)
{
	Node::update(delta);
	auto leftArrow = EventKeyboard::KeyCode::KEY_A;
	auto rightArrow = EventKeyboard::KeyCode::KEY_D;
	auto upArrow = EventKeyboard::KeyCode::KEY_W;
	auto downArrow = EventKeyboard::KeyCode::KEY_S;
	Vec2 nowPos = sprite->getPosition();
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
	if (nowPos.x < origin.x + sprite->getContentSize().width * 0.5/ 2) nowPos.x = origin.x + sprite->getContentSize().width * 0.5 / 2;
	if (nowPos.y < origin.y + sprite->getContentSize().height * 0.5 / 2) nowPos.y= origin.y + sprite->getContentSize().height * 0.5 / 2;
	if (nowPos.x > origin.x + visibleSize.width - sprite->getContentSize().width * 0.5 / 2) nowPos.x = origin.x + visibleSize.width - sprite->getContentSize().width * 0.5 / 2;
	if (nowPos.y > origin.y + visibleSize.height - sprite->getContentSize().height * 0.5 / 2) nowPos.y = origin.y + visibleSize.height - sprite->getContentSize().height * 0.5 / 2;
	auto moveTo = MoveTo::create(0.12f, nowPos);
	sprite->runAction(moveTo);
	return;

}