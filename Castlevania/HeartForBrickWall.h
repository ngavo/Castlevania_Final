#pragma once
#include "GCamera.h"
#include "Item.h"
class HeartForBrickWall:public Item
{
public:
	HeartForBrickWall(float x, float y, int width, int height);
	bool hienthi;
	DWORD last_time;
	GTexture*texture;
	GSprite*sprite;
	GCamera*camera;
	float timerSprite;
	void Render(float x, float y);
	void Update(float time);
	~HeartForBrickWall();
};

