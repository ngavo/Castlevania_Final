#include "BreakWall.h"



BreakWall::BreakWall(int id, int type, float x, float y, int width, int height)
{
	_Id = id;
	_Type = type;
	_x = x-15;
	_y = y-3;
	_width = width;
	_height = height;
	this->texture = new GTexture("Resources/other/ground.png", 1, 1, 1);
	sprite = new GSprite(this->texture, 0, 0, 2);
	this->camera = new  GCamera();
}

void BreakWall::Render(float x, float y)
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

void BreakWall::Update(float time)
{
	/*DWORD now = GetTickCount();
	if ((now - last_time) > (1000 / 10))
	{
		sprite->Next();
		last_time = now;
	}*/
}

BreakWall::~BreakWall()
{
	if (texture != NULL)
		delete texture;
	if (sprite != NULL)
		delete sprite;

	if (camera != NULL)
		delete camera;
}
