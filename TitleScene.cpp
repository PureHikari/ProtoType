#include "TitleScene.h"
#include "ui/CocosGUI.h"

#include "commonData.h"
#include "GameScene.h"
#include "EditScene.h"

USING_NS_CC;
using namespace cocos2d::ui;

Scene* TitleScene::createScene()
{
	auto scene = Scene::create();
	auto layer = TitleScene::create();
	scene->addChild(layer);

	return scene;
}

void TitleScene::newGame()
{
	auto scene = GameScene::createScene();
	Director::getInstance()->replaceScene(scene);
}

void TitleScene::editMode()
{
	auto scene = EditScene::createScene();
	Director::getInstance()->replaceScene(scene);
}

bool TitleScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	auto bg = Sprite::create("bg.png");
	bg->setPosition(VISIBLE_SIZE / 2);
	this->addChild(bg, BG_ZORDER);

	auto btn_start = Button::create("btn_start.png");
	btn_start->setPosition(Vec2(VISIBLE_SIZE.width / 2, VISIBLE_SIZE.height / 2 + GRID_SIZE * 4));
	this->addChild(btn_start, 1);

	btn_start->addClickEventListener([=](Ref*) {
		this->newGame();
	});

	auto btn_edit = Button::create("btn_edit.png");
	btn_edit->setPosition(Vec2(VISIBLE_SIZE.width / 2, VISIBLE_SIZE.height / 2 - GRID_SIZE * 4));
	this->addChild(btn_edit, 1);

	btn_edit->addClickEventListener([=](Ref*) {
		this->editMode();
	});

	return true;
}