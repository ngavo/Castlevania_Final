#include "LuaCuaFireBom.h"



LuaCuaFireBom::LuaCuaFireBom(float x, float y):Item(x, y)
{
	this->texture = new GTexture("Resources/item/effect.bmp", 6, 2, 7);
	sprite = new GSprite(this->texture, 3, 4, 2);
	sprite->SelectIndex(3);
	this->camera = new  GCamera();
	this->_width = 64;
	this->_height = 64;
}
void LuaCuaFireBom::Render(float x, float y)
{
	D3DXVECTOR2 view;
	view.x = x;
	view.y = y;
	camera->setViewPort(view);
	D3DXVECTOR2 _pos = camera->Transform(_x, _y);
	G_SpriteHandler->Begin(D3DXSPRITE_SORT_DEPTH_FRONTTOBACK | D3DXSPRITE_ALPHABLEND);

	sprite->Draw(_pos.x, _pos.y);
	G_SpriteHandler->End();
}
void LuaCuaFireBom::Update(float time)
{
	timerSprite += time;
	if (timerSprite >= 0.15)
	{
		sprite->Next();
		timerSprite -= 0.15;
	}
}

LuaCuaFireBom::~LuaCuaFireBom()
{
}
