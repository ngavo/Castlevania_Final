#include "MormingStar.h"



MormingStar::MormingStar(float x, float y, int width, int height):Item(x,y)
{
	this->texture = new GTexture("Resources/item/bonus.bmp", 6, 4, 22);
	sprite = new GSprite(this->texture, 7, 7, 2);
	sprite->SelectIndex(7);
	this->camera = new  GCamera();
	this->_width = width;
	this->_height = height;
}

void MormingStar::Update(float time)
{
		timerSprite += 0.15;
		if (timerSprite > 0.15)
		{
			this->_y = this->_y - this->_vy*time;
			timerSprite -= 0.15;
		}
		
}

void MormingStar::Render(float x, float y)
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

MormingStar::~MormingStar()
{
	if (texture != NULL)
		delete texture;
	if(sprite !=NULL)
	 delete sprite;

	if(camera!=NULL)
	delete camera;
}
