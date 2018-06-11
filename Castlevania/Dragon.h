#pragma once
#include "Enemy.h"
class Dragon:public Enemy
{
public:
	Dragon();
	DWORD last_time;
	void Init(float x, float y, int width, int height);
	void Render(float x, float y);
	void Update(int time);
	int _v = 0;
	float timerSprite;
	float giuydragon;
	float minydragon;
	boolean len;
	boolean xuong;
	~Dragon();
};

