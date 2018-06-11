#pragma once
#include"GameObject.h"
#include "GCamera.h"
class BreakWall : public GameObject
{
public:
	BreakWall(int id, int type, float x, float y, int width, int height);
	DWORD last_time;
	GTexture*texture;
	GSprite*sprite;
	GCamera*camera;
	/*Ground(int id, int type, float x, float y, int width, int height);*/
	void Render(float x, float y);
	void Update(float time);
	~BreakWall();
};

