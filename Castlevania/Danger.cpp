#include "Danger.h"



Danger::Danger(float x, float y, int width, int height) :Item(x, y)
{
	this->texture = new GTexture("Resources/item/bonus.bmp", 6, 4, 22);
	sprite = new GSprite(this->texture, 0, 0, 2);
	sprite->SelectIndex(0);
	this->camera = new  GCamera();
	this->_width = width;
	this->_height = height;
}

void Danger::Update(float time)
{
	timerSprite += time;
	if (timerSprite > 0.15)
	{
		this->_y = this->_y - this->_vy*time;
		timerSprite -= 0.15;
	}

}

void Danger::Render(float x, float y)
{
	if (hienthi == true)
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

Danger::~Danger()
{
	if (texture != NULL)
		delete texture;
	if (sprite != NULL)
		delete sprite;

	if (camera != NULL)
		delete camera;
}
