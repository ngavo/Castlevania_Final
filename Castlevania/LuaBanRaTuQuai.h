#pragma once
#include "Item.h"
#include "GCamera.h"
class LuaBanRaTuQuai : public Item
{
public:
	LuaBanRaTuQuai(float x, float y, float simon_x, float simon_y);
	GTexture*texture;
	GSprite*sprite;
	GCamera*camera;
	float timerSprite;
	float a;
	float vdan;
	boolean daban;
	D3DXVECTOR2 toadobandau;
	D3DXVECTOR2 toadoban;
	D3DXVECTOR2 toadosimon;
	void Render(float x, float y);
	void Update(float time);
	Box boxDan();
	boolean hienthi;
	~LuaBanRaTuQuai();
};

