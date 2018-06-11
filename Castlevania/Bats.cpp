#include "Bats.h"

Bats::Bats()
{
	
	

}

void Bats::Update(float time)
{
	
	if (!die)
	{
		a += 20 * time;
		this->_x = this->_x + vx * time;
		this->_y = 5 * sin(a) + this->_y;
		this->_fire->_x = this->_x;
		this->_fire->_y = this->_y;
		timerSprite += time;
		if (timerSprite > 0.15)
		{
			sprite->Next();
			timerSprite -= 0.15;
		}
	}
	


	
		
		
}

void Bats::Init(int tyle ,float x, float y, int width, int height)
{
	_x = x;
	_y = y;
	_width = 36;
	_height = 36;
	a = 0;
	vx = -90;
	texture = new GTexture("Resources/enemy/creep_right.bmp", 6, 5, 29);
	sprite = new GSprite(texture, 7, 10, 2);
	camera = new GCamera();
	sprite->SelectIndex(7);
	this->_tyle = tyle;
	_fire = new fire(_x, _y, 32, 32);
}

void Bats::Render(float x, float y)
{
	if (this->hienthi && !this->die)
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

	if (die)
	{
		RenderFire(x, y);
	}
	

}


void Bats::UpdateFire(float time)
{
	_fire->Update(time);
}
void Bats::RenderFire(float x, float y)
{
	
	_fire->Render(x, y);
}


Bats::~Bats()
{
	if (texture != NULL)
		delete texture;
	if (sprite != NULL)
		delete sprite;
	if (camera != NULL)
		delete camera;
	if (_fire != NULL)
		delete _fire;
}
