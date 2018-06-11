#pragma once
#include "QuadTreeObject.h"
#include "GameObject.h"
#include<fstream>
#include "SweptAABB.h"
#include "kitty.h"
#include "Bats.h"
#include "FishMan.h"
#include "Eagles.h"
#include "Fleaman.h"
#include "BoneDragons.h"
#include "fire.h"
#include "NenNho.h"
#include "Item.h"
#include "Moving.h"
#include "PointForMoney400.h"
#include "PointForMoney700.h"
#include "BreakWall.h"
#include "Food.h"
#include "HeartForBrickWall.h"
#include "GachVun.h"
#include "BoneDragons.h"
using namespace std;
class Map
{
public:
	vector<Moving*> ListMoving;
	vector <GameObject*> ListObjects;//danh sach toan bo object trong Map 
	vector<fire*> ListFires;
	vector<NenNho*> ListNenNho;
	vector<BreakWall*>ListBreakWall;
	vector<Enemy*>_listEnemy;
	vector<Item*> ListItem;
	QuadTreeObject*quadtree;
	PointForMoney400*point400;
	PointForMoney700*point700;
	Food*_food;
	HeartForBrickWall*_heartForBreakWall;
	GachVun*_gachvun1;
	GachVun*_gachvun2;
	int _stage = 0;




	float vi_tri_nen_bi_danh = 0;
	//int getStageFromSimon = 0;
	float _posxSimon=0;
	void LoadObjectFromFile(string filepath);
	void LoadMap(string filepath, int stage);
	void LoadObject(int IDObject, int flip, int Type, float x, float y, int width, int height, int stage);
	void LoadListObjectInWorld(RECT rect);
	void Draw(float x,float y);
	void Update(float time, kitty* simon);
	void UpdateStage10(float time, kitty* simon);
	void UpdateStage12(float time, kitty* simon);
	void UpdateCHungCho10And12(float time, kitty* simon);
	int CountRowObject(string filepath);
	int CountRowBetween(string filepath, int RowObject);
	Map();
	~Map();
};

