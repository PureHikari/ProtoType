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
		return;//���Ӣ��ָ��Ϊ����ִ�н������Ĵ���

	COMMAND cmd=COMMAND::NONE;

	switch (keyCode)
	{
		case EventKeyboard::KeyCode::KEY_A://�����ƶ�
		{
			cmd = COMMAND::LeftMove;
		}
			break;
		case EventKeyboard::KeyCode::KEY_D://�����ƶ�
		{
			cmd = COMMAND::RightMove;
		}
			break;
		case EventKeyboard::KeyCode::KEY_SPACE://��Ծ
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
		return;//���Ӣ��ָ��Ϊ����ִ�н������Ĵ���

	COMMAND cmd = COMMAND::NONE;

	switch (keyCode)
	{
		case EventKeyboard::KeyCode::KEY_A://�����ƶ�ֹͣ
		{
			cmd = COMMAND::LeftStop;
		}
			break;
		case EventKeyboard::KeyCode::KEY_D://�����ƶ�ֹͣ
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

	//�����ʱ��Ӣ�۳���λ��
	m_map[4][0] = MapElement::HEROPOS;
}

void GameScene::paintMap()
{
	//����һ����ı���
	auto bg = Sprite::create("bg.png");
	bg->setPosition(VISIBLE_SIZE / 2);
	this->addChild(bg, BG_ZORDER);

	//���ű��Ĳ�ͬ����Ӧλ�ü��ض�Ӧ�ĵ�ͼԪ��
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
					//��ȡӢ�۳�ʼλ��
					m_heroPos = Vec2(i*GRID_SIZE, VISIBLE_SIZE.height - j*GRID_SIZE) + Vec2(GRID_SIZE,-GRID_SIZE);
				}
					break;
				default:break;
			}

			///*
			//���ظ��ӱ�ţ�������
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
	m_hero->setPosition(m_heroPos);
	this->addChild(m_hero);
}

bool GameScene::isNextLand(Vec2 pos,bool isDown)
{
	int x = (pos.x + GRID_SIZE / 2) / GRID_SIZE;
	int y = (VISIBLE_SIZE.height - pos.y + GRID_SIZE / 2) / GRID_SIZE;

	///*
	//�����ã��������ǵ�ǰ���ڵ�x����ӱ��
	std::string str;
	if (m_hero->getDirection() == DIRECTION::LEFT)
	{
		str = "Left";
	}
	else
	{
		str = "Right";
	}
	auto lab = (Label*)m_hero->getChildByTag(777);
	if (lab)
	{
		lab->setString(StringUtils::format("%s",str.c_str()));
	}
	else
	{
		lab = Label::createWithSystemFont(StringUtils::format("%s",str.c_str()), "", 24);
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
			if (m_map[x][y + 1] == MapElement::BAREAL || m_map[x - 1][y + 1] == MapElement::BAREAL)
			{
				flag = true;
			}
		}
		else
		{
			if (m_map[x][y - 1] == MapElement::BAREAL || m_map[x + 1][y - 1] == MapElement::BAREAL)
			{
				flag = true;
			}
		}
		
	}

	return flag;
}

void GameScene::fallDown(character* ch)
{
	//��Ӣ�۽�ɫ������Ծ״̬ʱ�����ж�
	if (ch)
	{
		if (!ch->getIsJumping())
		{
			//�жϸ�λ����һ���Ƿ����ϰ���������ֹͣ����
			if (isNextLand(ch->getPosition(),true))
			{
				//ֹͣ����
				ch->land();
			}
			else if (!ch->getIsFalling())
			{
				//��ʼ����
				ch->fallDown();
			}
		}
		else
		{
			/*
			//�ж��Ƿ�ײ��ͷ
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
		int x = (ch->getPositionX() + GRID_SIZE / 2) / GRID_SIZE;
		int y = (VISIBLE_SIZE.height - ch->getPositionY() + GRID_SIZE / 2) / GRID_SIZE;

		bool left = false, right = false;
		
		if (m_map[x + 1][y] == MapElement::BAREAL || m_map[x + 1][y - 1] == MapElement::BAREAL)
		{
			ch->stop(DIRECTION::RIGHT);
			right = true;
		}
		if (m_map[x - 2][y] == MapElement::BAREAL || m_map[x - 2][y - 1] == MapElement::BAREAL)
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

	Logical::getInstance()->checkSkill(m_hero);
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

	initListener();

	scheduleUpdate();

	Logical::getInstance()->init(this);

	//��ʱ�ģ����¿�ʼ�İ�ť
	auto button = cocos2d::ui::Button::create("closeNormal.png");
	button->setPosition(VISIBLE_SIZE / 2);
	this->addChild(button, 11);

	button->addClickEventListener([=](Ref*) {
		auto scene = GameScene::createScene(id);
		Director::getInstance()->replaceScene(scene);
	});

	return true;
}