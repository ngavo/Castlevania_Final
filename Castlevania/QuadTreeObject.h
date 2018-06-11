#pragma once
#include "QuadTreeNode.h"
#include<map>
#include "GameObject.h"
#include <string>
#include <sstream>
using namespace std;
class QuadTreeObject
{
public:

	QuadTreeNode*nodeRoot;//luu tru node root
	vector<QuadTreeNode*>ListNodeInViewPort;//giu danh sach cac node trong viewport
	map<int, QuadTreeNode*>mapNode;
	vector<GameObject*>ListObjectInRect;


	void LoadNodeInFile(string filepath, int RowObject, int RowBetWeen, vector<GameObject*>listobjects);


	vector<int> ChuyenChuoiThanhSo(string data);
	void CreateTree(QuadTreeNode *nodeParent, map<int, QuadTreeNode*> map);
	void MapIdToObjectInTree(QuadTreeNode* nodeParent, vector<GameObject*> listobject);
	vector<QuadTreeNode*> GetListNodeIntersectRect(QuadTreeNode*nodeParent, RECT rect);
	bool IsCollision(RECT node, RECT rect);
	void GetListObjectInRect(RECT);
	QuadTreeObject();
	~QuadTreeObject();
};

