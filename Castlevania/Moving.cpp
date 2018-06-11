#include "Moving.h"



Moving::Moving(int id, int type, float x, float y, int width, int height)
{
	_Id = id;
	_Type = type;
	_x = x;
	_y = y;
	_width = width;
	_height = height;
	this->texture = new GTexture("Resources/other/9.png", 1, 1, 1);
	sprite = new GSprite(this->texture, 0, 1, 2);
	this->camera = new  GCamera();
	switch (_Id)
	{
	case 77:
		this->left = 470;
		this->right = 648;
		break;
	case 78:
		this->left = 1585;
		this->right = 1840;
		break;
	case 79:
		this->left = 2020;
		this->right = 2206;
		break;
	case 80:
		this->left = 2294;
		this->right = 2480;
		break;

	default:
		break;
	}
	/*this->left = x - 128;
	this->right = x + 80;*/
	if (_Id != 80)
	{
		this->_vx = -90;
	}
	else
		this->_vx = 90;
	
}

void Moving::Render(float x, float y)
{
	//if (this->hienthi)
	//{
		D3DXVECTOR2 view;
		view.x = x;
		view.y = y;
		camera->setViewPort(view);
		D3DXVECTOR2 _pos = camera->Transform(this->_x, this->_y);
		G_SpriteHandler->Begin(D3DXSPRITE_SORT_DEPTH_FRONTTOBACK | D3DXSPRITE_ALPHABLEND);

		sprite->Draw(_pos.x, _pos.y);
		G_SpriteHandler->End();
	//}

}


void Moving::Update(float time)
{
	if (_Id != 80)
	{
		float k = this->_x;
		if (this->_x < this->left)
		{
			this->_vx = 90.0f;
		}
		if (this->_x > this->right)
		{
			this->_vx = -90.0f;
		}
		this->_x = this->_x + this->_vx*time;
		this->_detalx = this->_x - k;
	}

	else
	{
		float k = this->_x;
		if (this->_x < this->left)
		{
			this->_vx = 90.0f;
		}
		if (this->_x > this->right)
		{
			this->_vx = -90.0f;
		}
		this->_x = this->_x + this->_vx*time;
		this->_detalx = this->_x - k;
	}
		

}
Moving::~Moving()
{
}
