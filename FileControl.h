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

struct allMapCell
{
	int id;
	mapData data;
};

typedef  std::vector<allMapCell> allMap;

class FileControl
{
public:
	static mapData getMapData(int id);
	static void saveMapData(allMapCell);

	static allMap getAllMap();
};