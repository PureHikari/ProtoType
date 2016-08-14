#include "GameScene.h"
#include "commonData.h"

USING_NS_CC;

Scene* GameScene::createScene()
{
	auto scene = Scene::create();
	auto layer = GameScene::create();

	scene->addChild(layer);

	return scene;
}

void GameScene::onKeyPress(EventKeyboard::KeyCode keyCode, Event* event)
{
	if (!m_hero)
		return;//如果英雄指针为空则不执行接下来的代码

	COMMAND cmd=COMMAND::NONE;

	switch (keyCode)
	{
		case EventKeyboard::KeyCode::KEY_A://向左移动
		{
			cmd = COMMAND::LeftMove;
		}
			break;
		case EventKeyboard::KeyCode::KEY_D://向右移动
		{
			cmd = COMMAND::RightMove;
		}
			break;
		case EventKeyboard::KeyCode::KEY_SPACE://跳跃
		{
			cmd = COMMAND::Jump;
		}
			break;
		default:break;
	}

	m_hero->getCommand(cmd);
}

void GameScene::onKeyRelease(EventKeyboard::KeyCode keyCode,Event* event)
{
	if (!m_hero)
		return;//如果英雄指针为空则不执行接下来的代码

	COMMAND cmd = COMMAND::NONE;

	switch (keyCode)
	{
		case EventKeyboard::KeyCode::KEY_A://向左移动停止
		{
			cmd = COMMAND::LeftStop;
		}
			break;
		case EventKeyboard::KeyCode::KEY_D://向右移动停止
		{
			cmd = COMMAND::RightStop;
		}
			break;
	}

	m_hero->getCommand(cmd);
}

void GameScene::initListener()
{
	auto lis = EventListenerKeyboard::create();
	lis->onKeyPressed = CC_CALLBACK_2(GameScene::onKeyPress, this);
	lis->onKeyReleased = CC_CALLBACK_2(GameScene::onKeyRelease, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(lis, this);
}

bool GameScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	m_hero = Hero::create();
	m_hero->setPosition(VISIBLE_SIZE / 2);
	this->addChild(m_hero);

	initListener();

	return true;
}