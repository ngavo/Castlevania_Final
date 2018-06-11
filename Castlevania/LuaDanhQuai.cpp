#include "LuaDanhQuai.h"



LuaDanhQuai::LuaDanhQuai(float x, float y, int width, int height):Item(x, y)
{
	this->texture = new GTexture("Resources/item/effect.bmp", 6, 2, 7);
	sprite = new GSprite(this->texture, 0, 0, 2);
	sprite->SelectIndex(0);
	this->camera = new  GCamera();
	this->_width = width;
	this->_height = height;

}

void LuaDanhQuai::Update(float time)
{
	
	if (hienthi)
	{
		timerSprite += time;
		if (timerSprite > 1)
		{
			hienthi = false;
			timerSprite -= 1;
		}
	}

}

void LuaDanhQuai::Render(float x, float y)
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

LuaDanhQuai::~LuaDanhQuai()
{
	if (texture != NULL)
		delete texture;
	if (sprite != NULL)
		delete sprite;

	if (camera != NULL)
		delete camera;
}
