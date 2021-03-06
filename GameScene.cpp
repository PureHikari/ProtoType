#include "GameScene.h"
#include "ui/CocosGUI.h"

#include "FileControl.h"
#include "TitleScene.h"

#include "Logical.h"

USING_NS_CC;

Scene* GameScene::createScene(int id)
{
	auto scene = Scene::create();
	auto layer = GameScene::create(id);

	scene->addChild(layer);

	return scene;
}

GameScene* GameScene::create(int id)
{
	auto gs = new GameScene();
	if (gs && gs->init(id))
	{
		gs->autorelease();
		return gs;
	}

	CC_SAFE_DELETE(gs);
	return nullptr;
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
		case EventKeyboard::KeyCode::KEY_F10:
		{
			auto scene = TitleScene::createScene();
			Director::getInstance()->replaceScene(scene);
		}
			break;
		case EventKeyboard::KeyCode::KEY_Q:
		{
			cmd = COMMAND::Attack;
		}
			break;
		case EventKeyboard::KeyCode::KEY_E:
		{
			cmd = COMMAND::Skill1;
		}
			break;
		case EventKeyboard::KeyCode::KEY_R:
		{
			cmd = COMMAND::Skill2;
		}
			break;
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
	auto content = FileControl::getMapData(m_mapId);

	for (auto i = content.begin(); i != content.end(); i++)
	{
		if (i->isBreal)
		{
			m_map[i->x][i->y] = MapElement::BAREAL;
		}
	}

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

			/*
			//加载格子编号，调试用
			auto lab = Label::createWithSystemFont(StringUtils::format("%d",i), "", 16);
			lab->setPosition(Vec2(i*GRID_SIZE, VISIBLE_SIZE.height - j*GRID_SIZE) + Vec2(GRID_SIZE/2,-GRID_SIZE/2));
			lab->setColor(Color3B::BLACK);
			this->addChild(lab, 10);
			//*/
		}
	}
}

void GameScene::initHero()
{
	m_hero = Hero::create();
	m_hero->setPosition(m_heroPos + Vec2(GRID_SIZE/2,0));
	this->addChild(m_hero);
}

void GameScene::createEnemy()
{
	auto enmey = Monster::create();
	enmey->setPosition(Vec2(VISIBLE_SIZE.width / 2, VISIBLE_SIZE.height - GRID_SIZE * 2));
	this->addChild(enmey);

	m_monsters.pushBack(enmey);
}

bool GameScene::isNextLand(Vec2 pos,bool isDown)
{
	int x = pos.x  / GRID_SIZE;
	int y = (VISIBLE_SIZE.height - pos.y + GRID_SIZE / 2) / GRID_SIZE;

	//*
	//测试用，标明主角当前所在的x轴格子编号
	auto lab = (Label*)m_hero->getChildByTag(777);
	std::string str;
	str = m_hero->getDirection() == DIRECTION::LEFT ? "L" : "R";
	if (lab)
	{
		lab->setString(str);
	}
	else
	{
		lab = Label::createWithSystemFont(str, "", 24);
		lab->setPosition(m_hero->getContentSize() / 2);
		m_hero->addChild(lab, 99 , 777);
	}
	//*/

	if (!isDown)
	{
		y = (VISIBLE_SIZE.height - pos.y + GRID_SIZE) / GRID_SIZE;
	}

	bool flag = false;

	if (y < GRID_Y)
	{
		if (isDown)
		{
			if (m_map[x][y + 1] == MapElement::BAREAL )//|| m_map[x - 1][y + 1] == MapElement::BAREAL)
			{
				flag = true;
			}
		}
		else
		{
			if (m_map[x][y - 1] == MapElement::BAREAL )//|| m_map[x + 1][y - 1] == MapElement::BAREAL)
			{
				flag = true;
			}
		}
		
	}

	return flag;
}

void GameScene::fallDown(character* ch)
{
	//当英雄角色处于跳跃状态时不再判断
	if (ch)
	{
		if (!ch->getIsJumping())
		{
			//判断该位置下一格是否是障碍物，如果是则停止下落
			if (isNextLand(ch->getPosition(),true))
			{
				//停止下落
				ch->land();
			}
			else if (!ch->getIsFalling())
			{
				//开始下落
				ch->fallDown();
			}
		}
		else
		{
			/*
			//判断是否撞到头
			if (isNextLand(m_hero->getPosition(), false))
			{
				m_hero->jumpToHead();
			}
			//*/
		}
	}

}

void GameScene::leftNRight(character* ch)
{
	if (ch && !ch->getIsJumping())
	{
		int x = ch->getPositionX() / GRID_SIZE;
		int y = (VISIBLE_SIZE.height - ch->getPositionY() + GRID_SIZE / 2) / GRID_SIZE;

		bool left = false, right = false;
		
		if (m_map[x + 1][y] == MapElement::BAREAL || m_map[x + 1][y - 1] == MapElement::BAREAL)
		{
			ch->stop(DIRECTION::RIGHT);
			right = true;
		}
		if (m_map[x - 1][y] == MapElement::BAREAL || m_map[x - 1][y - 1] == MapElement::BAREAL)
		{
			ch->stop(DIRECTION::LEFT);
			left = true;
		}

		ch->stopped(left, right);
	}
}

void GameScene::update(float)
{
	fallDown(m_hero);
	leftNRight(m_hero);
	m_hero->coolDown();

	Logical::getInstance()->checkSkill(m_hero);

	Vector<Monster*> removeableEnemy;
	for (auto ms : m_monsters)
	{
		if (ms->getIsAlive())
		{
			fallDown(ms);
			leftNRight(ms);
			ms->coolDown();

			Logical::getInstance()->checkSkill(ms);
		}
		else
		{
			//如果该角色已经死亡
			removeableEnemy.pushBack(ms);
			ms->removeFromParent();
		}
	}

	for (auto ms : removeableEnemy)
	{
		m_monsters.eraseObject(ms);
	}

	removeableEnemy.clear();

	if (m_monsters.size() == 0)
	{
		createEnemy();
	}
}

bool GameScene::init(int id)
{
	if (!Layer::init())
	{
		return false;
	}

	m_mapId = id;

	initMap();
	paintMap();
	initHero();

	createEnemy();

	initListener();

	scheduleUpdate();

	Logical::getInstance()->init(this);

	//临时的，重新开始的按钮
	auto button = cocos2d::ui::Button::create("closeNormal.png");
	button->setPosition(VISIBLE_SIZE / 2);
	this->addChild(button, 11);

	button->addClickEventListener([=](Ref*) {
		auto scene = GameScene::createScene(id);
		Director::getInstance()->replaceScene(scene);
	});

	return true;
}