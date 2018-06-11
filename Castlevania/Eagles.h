#pragma once
#include "Enemy.h"
class Eagles:public Enemy
{
public:
	DWORD last_time;
	void Init(float x, float y, int width, int height);
	void Render(float x, float y);
	void Update(int time);
	Eagles();
	~Eagles();
};

