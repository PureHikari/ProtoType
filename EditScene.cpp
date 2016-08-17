#include "EditScene.h"
#include "TitleScene.h"
#include "FileControl.h"

USING_NS_CC;

//==============================================
//元素部分
MapGrid* MapGrid::create()
{
	auto mg = new MapGrid();
	if (mg && mg->init())
	{
		mg->autorelease();
		return mg;
	}
	CC_SAFE_DELETE(mg);
	return nullptr;
}


bool MapGrid::init()
{
	if (!Sprite::init())
	{
		return false;
	}

	initWithFile("blank.png");

	this->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);

	return true;
}

void MapGrid::change()
{
	auto str = m_isBreal ? "blank.png" : "breal.png";

	this->setTexture(str);

	m_isBreal = !m_isBreal;
}

//==============================================
//场景部分
Scene* EditScene::createScene(int id, bool isNew)
{
	auto scene = Scene::create();
	auto layer = EditScene::create(id,isNew);
	scene->addChild(layer);

	return scene;
}

EditScene* EditScene::create(int id, bool isNew)
{
	auto es = new EditScene();
	if (es && es->init(id,isNew))
	{
		es->autorelease();
		return es;
	}
	CC_SAFE_DELETE(es);
	return nullptr;
}

bool EditScene::onBegin(Touch* touch, Event* event)
{
	auto touchPos = touch->getLocation();

	for (int i = 0; i < GRID_X; i++)
	{
		for (int j = 0; j < GRID_Y; j++)
		{
			if (m_map[i][j] && m_map[i][j]->getBoundingBox().containsPoint(touchPos))
			{
				m_map[i][j]->change();
			}
		}
	}

	return false;
}

void EditScene::onPress(EventKeyboard::KeyCode keyCode, Event* event)
{
	if (keyCode == EventKeyboard::KeyCode::KEY_F10)
	{
		this->saveMap();
	}
}

void EditScene::saveMap()
{
	mapData content;
	allMapCell data;

	for (int i = 0; i < GRID_X; i++)
	{
		for (int j = 0; j < GRID_Y; j++)
		{
			mapCell temp;
			temp.x = i; temp.y = j;
			temp.isBreal = m_map[i][j]->getIsBreal();

			content.push_back(temp);
		}
	}

	int id = m_mapId;
	if (m_isNew)
	{
		id = -1;//表示为新建的地图
	}

	data.data = content;
	data.id = id;

	FileControl::saveMapData(data);

	auto scene = TitleScene::createScene();
	Director::getInstance()->replaceScene(scene);
}

void EditScene::drawGridLine()
{
	//从上往下画横线
	for (int i = 0; i < GRID_Y; i++)
	{
		auto first = Vec2::ZERO;
		auto second = Vec2::ZERO;

		first = Vec2(0, VISIBLE_SIZE.height - GRID_SIZE *i);
		second = Vec2(VISIBLE_SIZE.width, VISIBLE_SIZE.height - GRID_SIZE * i);

		auto line = DrawNode::create();
		line->drawLine(first, second, Color4F::RED);
		this->addChild(line,10);
	}

	//从左往右画竖线
	for (int i = 0; i < GRID_X; i++)
	{
		auto first = Vec2::ZERO;
		auto second = Vec2::ZERO;

		first = Vec2(GRID_SIZE * i, 0);
		second = Vec2(GRID_SIZE * i, VISIBLE_SIZE.height);

		auto line = DrawNode::create();
		line->drawLine(first, second, Color4F::RED);
		this->addChild(line,10);
	}

	//从左往右，从上往下加载点
	for (int i = 0; i < GRID_X; i++)
	{
		for (int j = 0; j < GRID_Y; j++)
		{
			auto mg = MapGrid::create();
			mg->setPosition(Vec2(GRID_SIZE * i, VISIBLE_SIZE.height - GRID_SIZE * j));
			this->addChild(mg, 1);

			m_map[i][j] = mg;
		}
	}

	//如果是已有的地图，则开始加载
	if (!m_isNew)
	{
		auto data = FileControl::getMapData(m_mapId);

		for (auto i = data.begin(); i != data.end(); i++)
		{
			if (i->isBreal)
			{
				m_map[i->x][i->y]->change();
			}
		}
	}
}

bool EditScene::init(int id, bool isNew)
{
	if (!Layer::init())
	{
		return false;
	}

	m_mapId = id;

	auto bg = Sprite::create("bg.png");
	bg->setPosition(VISIBLE_SIZE / 2);
	this->addChild(bg, BG_ZORDER);

	this->drawGridLine();

	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(EditScene::onBegin, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	auto keyListener = EventListenerKeyboard::create();
	keyListener->onKeyPressed = CC_CALLBACK_2(EditScene::onPress, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyListener, this);

	return true;
}