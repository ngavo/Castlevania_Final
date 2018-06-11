#include "Water.h"



Water::Water(float x, float y)
{
	texture1 = new GTexture("Resources/item/effect.bmp",6,2,7);
	sprite1 = new GSprite(texture1,6,6,2);
	sprite1->SelectIndex(6);
	texture2 = new GTexture("Resources/item/effect.bmp", 6, 2, 7);
	sprite2 = new GSprite(texture2, 6, 6, 2);
	sprite2->SelectIndex(6);
	texture3 = new GTexture("Resources/item/effect.bmp", 6, 2, 7);
	sprite3 = new GSprite(texture3, 6, 6, 2);
	sprite3->SelectIndex(6);
	camera = new GCamera();
	this->_x1 = x;
	this->_y1 = y;
	this->_x2 = x;
	this->_y2 = y-20;
	this->_x3 = x;
	this->_y3 = y-20;
}

void Water::Render(float x, float y)
{
	D3DXVECTOR2 view;
	view.x = x;
	view.y = y;
	camera->setViewPort(view);
	D3DXVECTOR2 _pos1 = camera->Transform(this->_x1, this->_y1);
	D3DXVECTOR2 _pos2 = camera->Transform(this->_x2, this->_y2);
	D3DXVECTOR2 _pos3 = camera->Transform(this->_x3, this->_y3);
	G_SpriteHandler->Begin(D3DXSPRITE_SORT_DEPTH_FRONTTOBACK | D3DXSPRITE_ALPHABLEND);
	sprite1->Draw(_pos1.x, _pos1.y);
	sprite2->Draw(_pos2.x, _pos2.y);
	sprite3->Draw(_pos3.x, _pos3.y);
	G_SpriteHandler->End();
}
void Water::Update(float time)
{
	this->_y1 -= 100 * time;
	this->_x2 -= 50 * time;
	this->_y2 -= 100 * time;
	this->_x3 += 50 * time;
	this->_y3 -= 100 * time;
}

Water::~Water()
{
	if (texture1 != NULL)
		delete texture1;
	if (sprite1 != NULL)
		delete sprite1;

	


	if (texture2 != NULL)
		delete texture2;
	if (sprite2 != NULL)
		delete sprite2;

	

	if (texture3 != NULL)
		delete texture3;
	if (sprite3 != NULL)
		delete sprite3;

	if (camera != NULL)
		delete camera;
}
