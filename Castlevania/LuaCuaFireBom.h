#pragma once
#include "Item.h"
#include "GCamera.h"
class LuaCuaFireBom : public Item
{
public:
	LuaCuaFireBom(float x, float y);
	GTexture*texture;
	GSprite*sprite;
	GCamera*camera;
	float timerSprite;
	void Render(float x, float y);
	void Update(float time);
	boolean hienthi;

	~LuaCuaFireBom();
};

