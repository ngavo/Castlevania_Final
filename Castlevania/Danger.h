#pragma once
#include "Item.h"
#include "GCamera.h"
class Danger:public Item
{
public:
	Danger(float x, float y, int width, int height);
	DWORD last_time;
	GTexture*texture;
	GSprite*sprite;
	GCamera*camera;
	float timerSprite;
	float a;
	void Render(float x, float y);
	void Update(float time);
	~Danger();
};

