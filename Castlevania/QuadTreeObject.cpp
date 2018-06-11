#include "QuadTreeObject.h"
#include <fstream>


QuadTreeObject::QuadTreeObject()
{
}

void QuadTreeObject::LoadNodeInFile(string filepath, int RowObject, int RowBetWeen, vector<GameObject*>listobjects)
{
	//ifstream fi;
	//fi.open(filepath);
	//vector<string> data;
	//while (!fi.eof())
	//{
	//	string line;
	//	getline(fi, line);
	//	data.push_back(line);
	//}


	//for (int i = 0; i < data.size(); i++)
	//{
	//	vector<int> so = ChuyenChuoiThanhSo(data[i]);
	//	QuadTreeNode*node = new QuadTreeNode();


	//	node->IDNode = so[0];
	//	node->Rect.left = so[1];
	//	node->Rect.top = so[2];
	//	node->Rect.right = so[1] + so[3];
	//	node->Rect.bottom = so[2] + so[4];

	//	if (so.size() >= 6)
	//	{
	//		for (int j = 5; j < so.size(); j++)
	//		{
	//			node->ListIdObject.push_back(so[j]);//danh sach idObject trong 1 node
	//		}
	//	}
	//	
	//	if (node->IDNode != 1)
	//	{
	//		mapNode[node->IDNode] = node;
	//	}
	//	else
	//	{
	//		nodeRoot = node;
	//	}

	//}

	fstream file;
	file.open(filepath, ios::in);
	string data;
	for (int i = 0; i < RowObject; i++)
	{
		getline(file, data);
	}
	getline(file, data);//lay END

	for (int i = 0; i < RowBetWeen; i++)
	{
		getline(file, data);
	}

	getline(file, data);//lay END

	while (!file.eof())
	{
		//	string line;

		getline(file, data);

		if (data != "END")
		{
			stringstream ss(data);
			vector<float> so;
			while (!ss.fail())
			{
				float f;
				ss >> f;
				if (!ss.fail())
				{
					so.push_back(f);
				}
			}

			QuadTreeNode * node = new QuadTreeNode();

			node->IDNode = so.at(0);
			node->Rect.left = so.at(1);
			node->Rect.top = so.at(2);
			node->Rect.right = so.at(3);
			node->Rect.bottom = so.at(4);

			if (so.size() > 5)
			{
				for (int i = 5; i < so.size(); i++)
				{
					node->ListIdObject.push_back(so.at(i));
				}
			}


			if (node->IDNode != 0)
			{
				mapNode[node->IDNode] = node;
			}
			else
			{

				nodeRoot = node;
			}
		}
	}

	CreateTree(nodeRoot, mapNode);
	MapIdToObjectInTree(nodeRoot, listobjects);
}



void QuadTreeObject::CreateTree(QuadTreeNode *nodeParent, map<int, QuadTreeNode*> map)
{
	if (map.find(nodeParent->IDNode * 4 + 1) != map.end())
	{
		nodeParent->ChildTopLeft = map.find(nodeParent->IDNode * 4 + 1)->second;
		CreateTree(nodeParent->ChildTopLeft, map);
	}
	if (map.find(nodeParent->IDNode * 4 + 2) != map.end())
	{
		nodeParent->ChildTopRight = map.find(nodeParent->IDNode * 4 + 2)->second;
		CreateTree(nodeParent->ChildTopRight, map);
	}
	if (map.find(nodeParent->IDNode * 4 + 3) != map.end())
	{
		nodeParent->ChildBottomLeft = map.find(nodeParent->IDNode * 4 + 3)->second;
		CreateTree(nodeParent->ChildBottomLeft, map);
	}
	if (map.find(nodeParent->IDNode * 4 + 4) != map.end())
	{
		nodeParent->ChildBottomRight = map.find(nodeParent->IDNode * 4 + 4)->second;
		CreateTree(nodeParent->ChildBottomRight, map);
	}
}

void QuadTreeObject::MapIdToObjectInTree(QuadTreeNode* nodeParent, vector<GameObject*> listobject)
{
	int m = 0;
	if (nodeParent->ListIdObject.size() != 0)
	{
		for (int i = 0; i < listobject.size(); i++)
		{
			for (int j = 0; j < nodeParent->ListIdObject.size(); j++)
			{
				m = listobject[i]->GetId();
				if (listobject[i]->GetId() == nodeParent->ListIdObject[j])
				{
					nodeParent->ListObject.push_back(listobject[i]);
				}
			}
		}
	}
	//
	if (nodeParent->ChildTopLeft != NULL)
	{
		MapIdToObjectInTree(nodeParent->ChildTopLeft, listobject);
	}
	if (nodeParent->ChildBottomLeft != NULL)
	{
		MapIdToObjectInTree(nodeParent->ChildBottomLeft, listobject);
	}
	if (nodeParent->ChildBottomRight != NULL)
	{
		MapIdToObjectInTree(nodeParent->ChildBottomRight, listobject);
	}
	if (nodeParent->ChildTopRight != NULL)
	{
		MapIdToObjectInTree(nodeParent->ChildTopRight, listobject);
	}
}

vector<int> QuadTreeObject::ChuyenChuoiThanhSo(string k)
{
	vector<int> so;
	int i = 0;
	string word = "";
	while (i<k.length())
	{

		if (k[i] != '\t')
		{
			word += k[i];

			if (i == k.length() - 1)
			{
				so.push_back(atoi(word.c_str()));
				word = "";
			}

		}
		else
		{
			so.push_back(atoi(word.c_str()));
			word = "";
		}

		i++;
	}

	return so;
}

void QuadTreeObject::GetListObjectInRect(RECT rect)
{
	ListNodeInViewPort.clear();
	ListObjectInRect.clear();
	GetListNodeIntersectRect(nodeRoot, rect);

	for (int i = 0; i < ListNodeInViewPort.size(); i++)
	{
		ListNodeInViewPort[i]->GetListObjectInNode(rect, ListObjectInRect);
	}
}

vector<QuadTreeNode*> QuadTreeObject::GetListNodeIntersectRect(QuadTreeNode* nodeParent, RECT rect)
{
	bool k = false;
	k = IsCollision(nodeParent->Rect, rect);

	if (IsCollision(nodeParent->Rect, rect) && nodeParent->ListObject.size() != 0)
	{
		ListNodeInViewPort.push_back(nodeParent);
	}
	if (nodeParent->ListObject.size() == 0 && IsCollision(nodeParent->Rect, rect))
	{
		if (nodeParent->ChildTopLeft != NULL)
		{
			GetListNodeIntersectRect(nodeParent->ChildTopLeft, rect);
		}
		if (nodeParent->ChildTopRight != NULL)
		{
			GetListNodeIntersectRect(nodeParent->ChildTopRight, rect);
		}
		if (nodeParent->ChildBottomLeft != NULL)
		{
			GetListNodeIntersectRect(nodeParent->ChildBottomLeft, rect);
		}
		if (nodeParent->ChildBottomRight != NULL)
		{
			GetListNodeIntersectRect(nodeParent->ChildBottomRight, rect);
		}
	}
	ListNodeInViewPort.size();
	return ListNodeInViewPort;
}

bool QuadTreeObject::IsCollision(RECT node, RECT rect)
{
	return !(node.right <= rect.left || node.left >= rect.right || node.bottom <= rect.top || node.top >= rect.bottom);
}
QuadTreeObject::~QuadTreeObject()
{
	for (map<int, QuadTreeNode *>::iterator it = mapNode.begin(); it != mapNode.end(); ++it)
	{
		delete it->second;
	}
	mapNode.clear();
	if (nodeRoot != NULL)
		delete nodeRoot;
}
