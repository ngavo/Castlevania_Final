#include "fire.h"



fire::fire(float x, float y, int width, int height)
{
	_x = x;
	_y = y;
	_width = width;
	_height = height;
	this->texture = new GTexture("Resources/item/effect.bmp", 6, 2, 7);
	sprite = new GSprite(this->texture, 0, 3, 2);
	this->camera = new  GCamera();
	vx = 3;
}

void fire::Update(float time)
{
//	DWORD now = GetTickCount();
	timerSprite += time;
	if (timerSprite > 0.2)
	{
		timerSprite -= 0.2;
		sprite->Next();
	}
}

void fire::Render(float x, float y)
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
		if (sprite->GetIndex() == 3)
		{
			this->hienthi = false;
		}
	}
		

}

fire::~fire()
{
	if (texture != NULL)
	{
		delete texture;
	}

	if (sprite != NULL)
	{
		delete sprite;
	}

	if (camera != NULL)
	{
		delete camera;
	}
}
