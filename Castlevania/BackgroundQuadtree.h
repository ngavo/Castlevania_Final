#pragma once
#include <string>
#include<fstream>
#include <sstream>
#include <vector>
#include "QuadTreeObject.h"
#include "TileBackground.h"
using namespace std;
class BackgroundQuadtree
{
public:
	BackgroundQuadtree();

	QuadTreeObject* quadtree;
	//TileBackground* tilebg;
	vector<int> value;
	int _row;
	int _col;
	void ReadFileBackground(string filepath);
	int Row(string filepath);
	int Column(string filepath);
	void DrawBackground(RECT viewport);
	~BackgroundQuadtree();
};

