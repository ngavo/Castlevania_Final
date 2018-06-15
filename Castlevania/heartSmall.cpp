#include "heartSmall.h"



heartSmall::heartSmall(float x, float y, int width, int height):Item(x,y)
{
	this->texture = new GTexture("Resources/item/bonus.bmp", 6, 4, 22);
	sprite = new GSprite(this->texture, 8, 8, 2);
	sprite->SelectIndex(8);
	this->camera = new  GCamera();
	this->_width = width;
	this->_height = height;
	vx = 0;
	this->_vy = 60;

}

void heartSmall::Update(float time)
{
	timerSprite += time;
	/*float vx = 0;*/
	if (timerSprite > 0.3)
	{
		if (!itemChamDat)
		{
			a += 15 * time;
			vx = 5;
		}
		else
		{
			vx = 0;
		}
		
		this->_y = this->_y - this->_vy*time ;
		this->_x = this->_x + vx*cos(a) ;
		timerSprite -= 0.3;
	}

}

void heartSmall::Render(float x, float y)
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

heartSmall::~heartSmall()
{
	if (texture != NULL)
		delete texture;
	if (sprite != NULL)
		delete sprite;

	if (camera != NULL)
		delete camera;
}
