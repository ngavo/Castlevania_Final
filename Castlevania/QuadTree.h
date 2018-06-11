#pragma once
#include<fstream>
#include <string>
#include <map>
#include "GameObject.h"
#include <vector>
using namespace std;
class QuadTree
{
public:

	QuadTree**node;
	map<int, GameObject*> mapObject;
	vector<GameObject*> *listObject;
	RECT* region;
	void LoadFileObject(string filepath);
	void LoadObject(int id, int type, float x, float y, int width, int height);
	void LoadFileQuadTree(string filepath);
	void LoadQuad(std::string trace, int pos, float left, float top, float width, float height, std::vector<GameObject*> *list);
	vector<int> ChuyenChuoiThanhSo(string data);
	void GetObjectList(std::vector<GameObject*> *returnList, RECT *region);
	bool IsContain(RECT *region);
	QuadTree();
	~QuadTree();

};

