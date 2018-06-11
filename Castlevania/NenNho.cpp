#include "NenNho.h"



NenNho::NenNho(int id, int type, float x, float y, int width, int height)
{
	_Id = id;
	_Type = type;
	_x = x;
	_y = y;
	_width = width;
	_height = height;
	this->texture = new GTexture("Resources/other/1.png", 2, 1, 4);
	sprite = new GSprite(this->texture, 0, 1, 2);
	this->camera = new  GCamera();
}

void NenNho::Render(float x, float y)
{
	if (this->hienthi)
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

void NenNho::Update(float time)
{
	DWORD now = GetTickCount();
	if ((now - last_time) > (1000 / 10))
	{
		sprite->Next();
		last_time = now;
	}
}
NenNho::~NenNho()
{
	if (texture != NULL)
		delete texture;
	if (sprite != NULL)
		delete sprite;

	if (camera != NULL)
		delete camera;
}
