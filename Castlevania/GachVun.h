#pragma once
#include "GSprite.h"
#include "GCamera.h"
class GachVun
{
public:
	GachVun(float x, float y);

	GTexture*texture1;
	GSprite*sprite1;
	GTexture*texture2;
	GSprite*sprite2;
	GTexture*texture3;
	GSprite*sprite3;
	GTexture*texture4;
	GSprite*sprite4;


	GCamera*camera;


	float _x1;
	float _y1;
	float _x2;
	float _y2;
	float _x3;
	float _y3;
	float _x4;
	float _y4;
	boolean hienthi=false;
	float timerSprite;
	void Render(float x, float y);
	void Update(float time);

	~GachVun();
};

