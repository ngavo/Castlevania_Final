#include "VatChuyebStage.h"



VatChuyebStage::VatChuyebStage(int id, int type, float x, float y, int width, int height)
{
	_Id = id;
	_Type = type;
	_x = x;
	_y = y;
	_width = width;
	_height = height;
	this->texture = new GTexture("Resources/enemy/creep_right.bmp", 1, 1, 1);
	sprite = new GSprite(this->texture, 0, 1, 2);
	this->camera = new  GCamera();
}

void VatChuyebStage::Render(float x, float y)
{
	/*if (this->hienthi)
	{
		D3DXVECTOR2 view;
		view.x = x;
		view.y = y;
		camera->setViewPort(view);
		D3DXVECTOR2 _pos = camera->Transform(this->_x, this->_y);
		G_SpriteHandler->Begin(D3DXSPRITE_SORT_DEPTH_FRONTTOBACK | D3DXSPRITE_ALPHABLEND);

		sprite->Draw(_pos.x, _pos.y);
		G_SpriteHandler->End();
	}*/

}

void VatChuyebStage::Update(float time)
{
}

VatChuyebStage::~VatChuyebStage()
{
}
