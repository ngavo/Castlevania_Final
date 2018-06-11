#include "Eagles.h"



Eagles::Eagles()
{
}

void Eagles::Init(float x, float y, int width, int height)
{
	_x = x;
	_y = y;
	_width = width;
	_height = height;
	texture = new GTexture("Resources/enemy/eagles.bmp", 2, 1, 2);
	sprite = new GSprite(texture, 0, 1, 2);
	camera = new GCamera();
	sprite->SelectIndex(0);
}
void Eagles::Render(float x, float y)
{
	D3DXVECTOR2 view;
	view.x = x;
	view.y = y;
	camera->setViewPort(view);
	D3DXVECTOR2 _pos = camera->Transform(this->_x, this->_y);
	G_SpriteHandler->Begin(D3DXSPRITE_SORT_DEPTH_FRONTTOBACK | D3DXSPRITE_ALPHABLEND);

	sprite->DrawFlipX(_pos.x, _pos.y);
	G_SpriteHandler->End();
}
void Eagles::Update(int time)
{
	DWORD now = GetTickCount();
	if ((now - last_time) > (1000 / 10))
	{
		this->_x = this->_x - 0.9*time;
		sprite->Next();
		last_time = now;
	}
}
Eagles::~Eagles()
{
}
