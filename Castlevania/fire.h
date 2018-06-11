#pragma once
#include"GameObject.h"
#include "GCamera.h"
class fire:public GameObject
{
public:
	fire(float x, float y, int width, int height);
	DWORD last_time;
	GTexture*texture;
	GSprite*sprite;
	GCamera*camera;
	float vx;
	float timerSprite;
	/*Ground(int id, int type, float x, float y, int width, int height);*/
	void Render(float x, float y);
	void Update(float time);
	~fire();
};

