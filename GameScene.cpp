#include "GameScene.h"
#include "ui/CocosGUI.h"

#include "FileControl.h"

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

	//auto controllerLis=Eventlistener
	
}

void GameScene::initMap()
{
	auto content = FileControl::getMapData();

	for (auto i = content.begin(); i != content.end(); i++)
	{
		if (i->isBreal)
		{
			m_map[i->x][i->y] = MapElement::BAREAL;
		}
	}

	/*
	//添加地面
	for (int i = 0; i < GRID_X; i++)
	{
		m_map[i][GRID_Y-1] = MapElement::BAREAL;
	}

	m_map[1][3] = MapElement::BAREAL;
	m_map[2][3] = MapElement::BAREAL;
	m_map[3][3] = MapElement::BAREAL;
	m_map[4][3] = MapElement::BAREAL;

	m_map[1][7] = MapElement::BAREAL;
	m_map[2][7] = MapElement::BAREAL;
	m_map[3][7] = MapElement::BAREAL;
	m_map[4][7] = MapElement::BAREAL;

	m_map[5][5] = MapElement::BAREAL;
	m_map[6][5] = MapElement::BAREAL;
	m_map[7][5] = MapElement::BAREAL;
	m_map[8][5] = MapElement::BAREAL;
	//*/

	//添加临时的英雄出生位置
	m_map[4][0] = MapElement::HEROPOS;
}

void GameScene::paintMap()
{
	//加载一整块的背景
	auto bg = Sprite::create("bg.png");
	bg->setPosition(VISIBLE_SIZE / 2);
	this->addChild(bg, BG_ZORDER);

	//按脚本的不同在相应位置加载对应的地图元素
	for (int i = 0; i < GRID_X; i++)
	{
		for (int j = 0; j < GRID_Y; j++)
		{
			switch (m_map[i][j])
			{
				case MapElement::BAREAL:
				{
					auto sp = Sprite::create("breal.png");
					sp->setPosition(Vec2(i*GRID_SIZE,VISIBLE_SIZE.height-j*GRID_SIZE));
					sp->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
					this->addChild(sp, BR_ZORDER);
				}
					break;
				case MapElement::HEROPOS:
				{
					//获取英雄初始位置
					m_heroPos = Vec2(i*GRID_SIZE, VISIBLE_SIZE.height - j*GRID_SIZE) + Vec2(GRID_SIZE,-GRID_SIZE);
				}
					break;
				default:break;
			}

			/*//加载格子编号，调试用
			auto lab = Label::createWithSystemFont(StringUtils::format("%d:%d",i,j), "", 32);
			lab->setPosition(Vec2(i*GRID_SIZE, VISIBLE_SIZE.height - j*GRID_SIZE));
			this->addChild(lab, 10);
			//*/
		}
	}
}

void GameScene::initHero()
{
	m_hero = Hero::create();
	m_hero->setPosition(m_heroPos);
	this->addChild(m_hero);
}

bool GameScene::isNextLand(Vec2 pos,bool isDown)
{
	int x = pos.x / GRID_SIZE;
	int y = (VISIBLE_SIZE.height - pos.y + GRID_SIZE / 2) / GRID_SIZE;

	if (!isDown)
	{
		y = (VISIBLE_SIZE.height - pos.y + GRID_SIZE) / GRID_SIZE;
	}

	if (y < GRID_Y)
	{
		if (isDown)
		{
			if (m_map[x][y + 1] == MapElement::BAREAL || m_map[x + 1][y + 1] == MapElement::BAREAL)
			{
				return true;
			}
		}
		else
		{
			if (m_map[x][y - 1] == MapElement::BAREAL || m_map[x + 1][y - 1] == MapElement::BAREAL)
			{
				return true;
			}
		}
		
	}

	return false;
}

void GameScene::fallDown()
{
	//当英雄角色处于跳跃状态时不再判断
	if (m_hero)
	{
		if (!m_hero->getIsJumping())
		{
			//判断该位置下一格是否是障碍物，如果是则停止下落
			if (isNextLand(m_hero->getPosition(),true))
			{
				//停止下落
				m_hero->land();
			}
			else if (!m_hero->getIsFalling())
			{
				//开始下落
				m_hero->fallDown();
			}
		}
		else
		{
			//判断是否撞到头
			if (isNextLand(m_hero->getPosition(), false))
			{
				m_hero->jumpToHead();
			}
		}
	}

}

void GameScene::update(float)
{
	fallDown();
}

bool GameScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	initMap();
	paintMap();
	initHero();

	initListener();

	scheduleUpdate();

	//临时的，重新开始的按钮
	auto button = cocos2d::ui::Button::create("closeNormal.png");
	button->setPosition(VISIBLE_SIZE / 2);
	this->addChild(button, 11);

	button->addClickEventListener([=](Ref*) {
		auto scene = GameScene::createScene();
		Director::getInstance()->replaceScene(scene);
	});

	return true;
}