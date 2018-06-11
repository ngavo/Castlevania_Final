#pragma once
#include "Item.h"
#include "GCamera.h"
class MormingStar: public Item
{
public:
	MormingStar(float x, float y, int width, int height);

	DWORD last_time;
	float timerSprite;
	GTexture*texture;
	GSprite*sprite;
	GCamera*camera;
	void Render(float x, float y);
	void Update(float time);
	~MormingStar();
};

