#pragma once
#include "GCamera.h"
#include "Item.h"
class Food :public  Item
{
public:
	Food(float x, float y, int width, int height);
	DWORD last_time;
	GTexture*texture;
	GSprite*sprite;
	GCamera*camera;
	float timerSprite;
	float a;
	void Render(float x, float y);
	void Update(float time);
	boolean hienthi;
	~Food();
};
