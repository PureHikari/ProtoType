#include "FileControl.h"
#include <fstream>
#include "cocos2d.h"

USING_NS_CC;
using namespace std;

mapData FileControl::getMapData()
{
	auto path = FileUtils::getInstance()->getWritablePath() + "mapData";
	ifstream file;

	file.open(path.c_str());

	mapData result;
	
	if (file)
	{
		int size = 0;
		file >> size;

		for (int i = 0; i < size; i++)
		{
			mapCell temp;
			file >> temp.x;
			file >> temp.y;
			file >> temp.isBreal;

			result.push_back(temp);
		}
	}

	file.close();
	return result;
}

void FileControl::saveMapData(mapData content)
{
	auto path = FileUtils::getInstance()->getWritablePath() + "mapData";
	ofstream file;

	file.open(path.c_str());

	if (file)
	{
		file << content.size() << endl;

		for (auto i = content.begin(); i != content.end(); i++)
		{
			file << i->x << endl;
			file << i->y << endl;
			file << i->isBreal << endl;
		}
	}

	file.close();
}