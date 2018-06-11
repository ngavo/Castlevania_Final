#pragma once
#include "Item.h"
#include "GCamera.h"
class MoneyBag400: public Item
{
public:
	MoneyBag400(float x, float y, int width, int height);
	DWORD last_time;
	GTexture*texture;
	GSprite*sprite;
	GCamera*camera;
	float timerSprite;
	float a;
	/*Ground(int id, int type, float x, float y, int width, int height);*/
	void Render(float x, float y);
	void Update(float time);
	~MoneyBag400();
};

