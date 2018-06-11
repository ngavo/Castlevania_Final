#pragma once
#include "SweptAABB.h"
enum TypeItem
{
	smallHeartType,
	bigHeartType,
	mormingStarType,
	pointMoney400Type,
	pointMoney700Type,
	FireBomType,
	DangerType
};
class Item
{
public:
	float _x;
	float _y;
	int _width;
	int _height;
	int type;
	bool hienthi = false;
	bool itemChamDat = false;
	float _vy = 100;
	Item(float x, float y);
	virtual void Update(float _DeltaTime);	// update per frame
	virtual void Render(float x, float y);
	Box boxItem();

	~Item();
};

