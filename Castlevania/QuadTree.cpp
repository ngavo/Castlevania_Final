#include "QuadTree.h"
#include "Ground.h"


QuadTree::QuadTree()
{
	this->node = NULL;

}

void QuadTree::LoadFileObject(string filepath)
{
	string id,type, x,  y, width, height;
	ifstream fi;
	fi.open(filepath);

	while (!fi.eof())
	{
		fi >> id >> type >> x >> y >> width >> height;
		LoadObject(atoi(id.c_str()),atoi(type.c_str()),strtof(x.c_str(),0),strtof(y.c_str(),0),atoi(width.c_str()),atoi(height.c_str()));
	}

	fi.close();
}

void QuadTree::LoadFileQuadTree(string filepath)
{
	string trace;
	ifstream fi;
	fi.open(filepath);

	vector<string> data;

	while (!fi.eof())
	{
		string line;
		getline(fi, line);
		data.push_back(line);
	}

	vector<GameObject*>* list = new vector<GameObject*>();

	for (int i = 0; i < data.size(); i++)
	{
		vector<int> so = ChuyenChuoiThanhSo(data[i]);

		if (so.size() >= 6)
		{
			for (int j = 5; j < so.size(); j++)
			{
				list->push_back(mapObject[so[j]]);
			}
		}
		trace.clear();

		while (true)
		{
			so[0]--;
			if (so[0] < 1)
				break;
			else
			{
				trace = std::to_string(so[0] % 8) + trace;
				so[0] = so[0] / 8;
			}
		}

		trace = trace + "e";
		LoadQuad(trace, 0, so[1], so[2], so[3], so[4], list);
	}
}


void QuadTree::LoadQuad(std::string trace, int pos, float left, float top, float width, float height, std::vector<GameObject*> *list)
{
	if (trace[pos] == 'e')
	{
		SetRect(this->region, left, top, left + width, top + height);
		if (list->size()!=0)
		{
			this->listObject = list;
		}
		
	}
	else
	{
		if (!this->node)
		{
			node = new QuadTree*[4];
			node[0] = new QuadTree();
			node[1] = new QuadTree();
			node[2] = new QuadTree();
			node[3] = new QuadTree();
		}

		if (trace[pos] == '0')
			node[0]->LoadQuad(trace, pos + 1, left, top, width, height, list);
		else if (trace[pos] == '1')
			node[1]->LoadQuad(trace, pos + 1, left, top, width, height, list);
		else if (trace[pos] == '2')
			node[2]->LoadQuad(trace, pos + 1, left, top, width, height, list);
		else if (trace[pos] == '3')
			node[3]->LoadQuad(trace, pos + 1, left, top, width, height, list);
	}
}

vector<int> QuadTree::ChuyenChuoiThanhSo(string k)
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

void QuadTree::LoadObject(int id, int type, float x, float y, int width, int height)
{
	if (type == 617)
	{
		GameObject*object;
		object = new Ground(id,type,x,y,width,height);
		mapObject[id] = object;
	}
}

bool QuadTree::IsContain(RECT *region)
{
	if (this->region->right < region->left || this->region->left > region->right ||
		this->region->bottom > region->top || this->region->top < region->bottom)
		return false;
	return true;
}
void QuadTree::GetObjectList(std::vector<GameObject*> *returnList, RECT *region)
{
	if (this->node)
	{
		if (this->node[0]->IsContain(region))
			this->node[0]->GetObjectList(returnList, region);

		if (this->node[1]->IsContain(region))
			this->node[1]->GetObjectList(returnList, region);

		if (this->node[2]->IsContain(region))
			this->node[2]->GetObjectList(returnList, region);

		if (this->node[3]->IsContain(region))
			this->node[3]->GetObjectList(returnList, region);
	}
	else if (this->IsContain(region))
	{
		for (std::vector<GameObject*>::iterator i = this->listObject->begin(); i != this->listObject->end(); i++)
			/*if ((*i)->isAdded == false) {*/
			returnList->push_back(*i);
		/*(*i)->isAdded = true;
		}*/
	}
}

QuadTree::~QuadTree()
{
	for (std::vector<GameObject*>::iterator i = listObject->begin(); i != listObject->end(); i++)
	{
		delete[](*i);
	}

	delete[] listObject;
}
