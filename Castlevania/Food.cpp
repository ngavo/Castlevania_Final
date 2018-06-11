#include "Food.h"



Food::Food(float x, float y, int width, int height):Item(x, y)
{
	this->texture = new GTexture("Resources/item/bonus.bmp", 6, 4, 22);
	sprite = new GSprite(this->texture, 10, 10, 2);
	sprite->SelectIndex(10);
	this->camera = new  GCamera();
	this->_width = width;
	this->_height = height;
	hienthi = false;
}

void Food::Update(float time)
{

}

void Food::Render(float x, float y)
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
Food::~Food()
{
	if (texture != NULL)
		delete texture;
	if (sprite != NULL)
		delete sprite;


	if (camera != NULL)
		delete camera;
}
