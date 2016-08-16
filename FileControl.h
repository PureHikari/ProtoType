#pragma once
#include <iostream>
#include <vector>

struct mapCell
{
	int x;
	int y;
	bool isBreal;
};

typedef std::vector<mapCell> mapData;

class FileControl
{
public:
	static mapData getMapData();
	static void saveMapData(mapData);
};