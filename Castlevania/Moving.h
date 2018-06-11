#pragma once
#include"GameObject.h"
#include "GCamera.h"
class Moving : public GameObject
{
public:
	Moving(int id, int type, float x, float y, int width, int height);
	float left;
	float right;
	float _vx;
	DWORD last_time;
	GTexture*texture;
	GSprite*sprite;
	GCamera*camera;
	float timerSprite;
	/*Ground(int id, int type, float x, float y, int width, int height);*/
	void Render(float x, float y);
	void Update(float time);
	~Moving();
};

