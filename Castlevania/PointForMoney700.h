#pragma once
#include "GCamera.h"
class PointForMoney700
{
public:
	PointForMoney700(float x, float y);
	DWORD last_time;
	GTexture*texture;
	GSprite*sprite;
	GCamera*camera;
	float timerSprite;
	float _x;
	float _y;
	int _width;
	int _height;
	boolean hienthi = false;
	void Render(float x, float y);
	void Update(float time);
	~PointForMoney700();
};

