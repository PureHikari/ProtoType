#include "FileControl.h"
#include <fstream>
#include "cocos2d.h"

USING_NS_CC;
using namespace std;

allMap FileControl::getAllMap()
{
	auto path = FileUtils::getInstance()->getWritablePath() + "AllMapData";
	ifstream file;

	file.open(path.c_str());

	allMap content;

	//如果存在存档，读取所有地图数据
	if (file)
	{
		int mapNum = 0;
		file >> mapNum;

		for (int i = 0; i < mapNum; i++)
		{
			allMapCell temp;
			file >> temp.id;

			int tempNum = 0;
			file >> tempNum;

			for (int j = 0; j < tempNum; j++)
			{
				mapCell tempc;

				file >> tempc.x;
				file >> tempc.y;
				file >> tempc.isBreal;

				temp.data.push_back(tempc);
			}

			content.push_back(temp);
		}
	}

	file.close();

	return content;
}

mapData FileControl::getMapData(int id)
{
	auto content = getAllMap();

	mapData result;

	//根据id找到对应的存档
	for (auto i = content.begin(); i != content.end(); i++)
	{
		if (i->id == id)
		{
			result = i->data;
			break;
		}
	}
	
	return result;
}

void FileControl::saveMapData(allMapCell content)
{
	auto allMap = getAllMap();

	//在已有的地图中寻找id，如果没有则添加新的地图，如果有则修改对应的数据
	bool flag = false;
	for (auto i = allMap.begin(); i != allMap.end(); i++)
	{
		if (i->id == content.id)
		{
			flag = true;
			
			i->data = content.data;

			break;
		}
	}

	if (!flag)
	{
		content.id = allMap.size();
		allMap.push_back(content);
	}
	
	auto path = FileUtils::getInstance()->getWritablePath() + "AllMapData";
	ofstream file;

	file.open(path.c_str());

	if (file)
	{
		file << allMap.size() << endl;

		for (auto i = allMap.begin(); i != allMap.end(); i++)
		{
			file << i->id << endl;
			file << i->data.size() << endl;

			for (auto j = i->data.begin(); j != i->data.end(); j++)
			{
				file << j->x << endl;
				file << j->y << endl;
				file << j->isBreal << endl;
			}
		}
	}

	file.close();
}

bool FileControl::saveAllMap(allMap content)
{
	auto path = FileUtils::getInstance()->getWritablePath() + "AllMapData";
	ofstream file;

	file.open(path.c_str());

	if (file)
	{
		file << content.size() << endl;

		for (auto i = content.begin(); i != content.end(); i++)
		{
			file << i->id << endl;
			file << i->data.size() << endl;

			for (auto j = i->data.begin(); j != i->data.end(); j++)
			{
				file << j->x << endl;
				file << j->y << endl;
				file << j->isBreal << endl;
			}
		}
	}

	file.close();

	return true;
}