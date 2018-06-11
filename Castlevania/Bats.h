#pragma once
#include "Enemy.h"
#include "fire.h"
class Bats:public Enemy
{
public:
	DWORD last_time;
	float a;
	float timerSprite;
	int scoreBat = 200;
	fire*_fire;
	void Init(int tyle,float x, float y, int width, int height);
	void Render(float x, float y);

	void Update(float time);
	void UpdateFire(float time);
	void RenderFire(float x, float y);
	Bats();
	~Bats();
};

