#pragma once
#include "Item.h"
#include "GCamera.h"
class Watch: public Item
{
public:
	Watch(float x, float y, int width, int height);
	DWORD last_time;
	GTexture*texture;
	GSprite*sprite;
	GCamera*camera;
	float timerSprite;
	float a;
	/*Ground(int id, int type, float x, float y, int width, int height);*/
	void Render(float x, float y);
	void Update(float time);
	~Watch();
};

