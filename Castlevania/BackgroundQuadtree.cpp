#include "BackgroundQuadtree.h"



BackgroundQuadtree::BackgroundQuadtree()
{
	quadtree = new QuadTreeObject();
}

void BackgroundQuadtree::ReadFileBackground(string filepath)
{
	 _row = Row("quadtree.b");
	 _col = Column("quadtree.b");
	fstream f;
	f.open("quadtree.b", ios::in);
	
	for (int i = 0; i < _row; i++)
	{
		for (int j = 0; j < _col; j++)
		{
			int x;
			f >> x;
			value.push_back(x);
		}
	}

	string k;
	getline(f, k);//read end;

	string data;
	while (!f.eof())
	{
		getline(f, data);

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
					node->ListIdObject.push_back((int)so.at(i));
				//	node->tile[so.at(i)]= value[so.at(i) -2];
				
				}
			}


			if (node->IDNode != 0)
			{
			 quadtree->mapNode[node->IDNode] = node;
			}
			else
			{

				quadtree->nodeRoot = node;
			}
		}
	}

	f.close();

	quadtree->CreateTree(quadtree->nodeRoot, quadtree->mapNode);
}

void BackgroundQuadtree::DrawBackground(RECT viewport)
{

	quadtree->ListNodeInViewPort.clear();
	quadtree->GetListNodeIntersectRect(quadtree->nodeRoot, viewport);

	for (int i = 0; i < quadtree->ListNodeInViewPort.size(); i++)
	{
		/*for (map<int, int>::iterator it = quadtree->ListNodeInViewPort[i]->tile.begin(); it != quadtree->ListNodeInViewPort[i]->tile.end(); ++it)
		{
			TileBackground tilebg = new TileBackground()
		}*/

		for (int j = 0; j < quadtree->ListNodeInViewPort[i]->ListIdObject.size(); j++)
		{
			TileBackground* tile = new TileBackground(quadtree->ListNodeInViewPort[i]->ListIdObject[j], value[quadtree->ListNodeInViewPort[i]->ListIdObject[j] - 1],_row,_col);
			tile->Render(viewport.left, G_ScreenHeight);
		}
	}
}

int BackgroundQuadtree::Row(string filepath)
{
	fstream f;
	f.open(filepath, ios::in);

	string line;

	int count = 0;

	while (!f.eof())
	{
		getline(f, line);
		if (line == "END")
		{
			break;
		}

		count++;
	}
	f.close();
	return count;
}
int BackgroundQuadtree::Column(string filepath)
{
	fstream f;
	f.open(filepath, ios::in);
	string line;

	getline(f, line);

	f.close();
	int row = 0;
	stringstream ss(line);
	while (!ss.fail())
	{
		int x;
		ss >> x;
		if (!ss.fail())
		{
			row++;
		}
	}

	return row;
}
BackgroundQuadtree::~BackgroundQuadtree()
{
}
