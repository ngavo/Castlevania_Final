#pragma once
#include<vector>
#include "GameObject.h"
using namespace std;
class QuadTreeNode
{
public:
	int IDNode;

	vector<int> ListIdObject;
	RECT Rect;
	vector<GameObject*> ListObject;//danh sach cac object
	//map<int, int> tile;//lu thong tin cua background (2,0);
	void GetListObjectInNode(RECT rect, vector<GameObject*>& _ListObjects);
	bool Interset(RECT rect1, RECT rect2);
	//Child
	QuadTreeNode* ChildTopLeft;
	QuadTreeNode* ChildTopRight;
	QuadTreeNode* ChildBottomLeft;
	QuadTreeNode* ChildBottomRight;
	QuadTreeNode();
	~QuadTreeNode();
};

