#include "PointForMoney400.h"



PointForMoney400::PointForMoney400(float x, float y)
{
	this->_x = x;
	this->_y = y;
	texture = new GTexture("Resources/item/400.png",1,1,1);
	sprite = new GSprite(texture, 0, 0, 2);
	camera = new GCamera();
	sprite->SelectIndex(0);
	_width = 10;
	_height = 10;
}

void PointForMoney400::Update(float time)
{
	timerSprite += time;
	if (timerSprite > 2)
	{
		hienthi = false;
	}
}

void PointForMoney400::Render(float x, float y)
{
	if (hienthi)
	{
		D3DXVECTOR2 view;
		view.x = x;
		view.y = y;
		camera->setViewPort(view);
		D3DXVECTOR2 _pos = camera->Transform(this->_x, this->_y);
		G_SpriteHandler->Begin(D3DXSPRITE_SORT_DEPTH_FRONTTOBACK | D3DXSPRITE_ALPHABLEND);

		sprite->Draw(_pos.x, _pos.y);
		G_SpriteHandler->End();
	}
	
}

PointForMoney400::~PointForMoney400()
{
	if (texture != NULL)
		delete texture;
	if (sprite != NULL)
		delete sprite;

	if (camera != NULL)
		delete camera;
}
