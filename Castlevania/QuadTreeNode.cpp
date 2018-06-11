#include "QuadTreeNode.h"



QuadTreeNode::QuadTreeNode()
{
}

void QuadTreeNode::GetListObjectInNode(RECT rect, vector<GameObject*>& _ListObjects)
{
	for (int i = 0; i < ListObject.size(); i++)
	{
		if (Interset(ListObject[i]->getRect(), rect))
		{
			_ListObjects.push_back(ListObject[i]);
		}
	}
}

bool QuadTreeNode::Interset(RECT rect1, RECT rect2)
{
	return !(rect1.right <= rect2.left || rect1.left >= rect2.right || rect1.bottom <= rect2.top || rect1.top > rect2.bottom);
}
QuadTreeNode::~QuadTreeNode()
{
}
