#pragma once
#include "Item.h"
#include "GCamera.h"
class FireBomb:public Item
{
public:
	FireBomb(float x, float y, int width, int height);
	DWORD last_time;
	GTexture*texture;
	GSprite*sprite;
	GCamera*camera;
	float timerSprite;
	float a;
	void Render(float x, float y);
	void Update(float time);
	~FireBomb();
};

