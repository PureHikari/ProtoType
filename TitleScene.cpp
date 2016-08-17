#include "TitleScene.h"
#include "ui/CocosGUI.h"

#include "commonData.h"
#include "GameScene.h"
#include "EditScene.h"
#include "FileControl.h"

USING_NS_CC;
using namespace cocos2d::ui;

Scene* TitleScene::createScene()
{
	auto scene = Scene::create();
	auto layer = TitleScene::create();
	scene->addChild(layer);

	return scene;
}

void TitleScene::showMapSelect(bool isEdit)
{
	auto layer = Layer::create();
	this->addChild(layer, 99);

	auto bg = Sprite::create("bg.png");
	bg->setPosition(VISIBLE_SIZE / 2);
	layer->addChild(bg);

	auto data = FileControl::getAllMap();
	
	for (auto i = 0; i < data.size(); i++)
	{
		auto btn = Button::create("maps.png");
		btn->setPosition(Vec2(VISIBLE_SIZE.width / 2,VISIBLE_SIZE.height - GRID_SIZE * i * 3 - GRID_SIZE * 2));
		layer->addChild(btn);

		btn->setTitleText(StringUtils::format("%d", i));

		btn->addClickEventListener([=](Ref*) {
			if (isEdit)
			{
				Director::getInstance()->replaceScene(EditScene::createScene(data.at(i).id,false));
			}
			else
			{
				Director::getInstance()->replaceScene(GameScene::createScene(data.at(i).id));
			}
		});
	}

	if (isEdit)
	{
		auto btn_new = Button::create("maps.png");
		btn_new->setPosition(Vec2(VISIBLE_SIZE.width - btn_new->getContentSize().width, btn_new->getContentSize().height));
		layer->addChild(btn_new);

		btn_new->setTitleText("New Map");

		btn_new->addClickEventListener([=](Ref*) {
			Director::getInstance()->replaceScene(EditScene::createScene(0 , true));
		});
	}
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
		showMapSelect(false);
	});

	auto btn_edit = Button::create("btn_edit.png");
	btn_edit->setPosition(Vec2(VISIBLE_SIZE.width / 2, VISIBLE_SIZE.height / 2 - GRID_SIZE * 4));
	this->addChild(btn_edit, 1);

	btn_edit->addClickEventListener([=](Ref*) {
		showMapSelect(true);
	});

	return true;
}