#include "LuaBanRaTuQuai.h"


LuaBanRaTuQuai::LuaBanRaTuQuai(float x, float y, float simon_x, float simon_y):Item(x,y)
{
	this->texture = new GTexture("Resources/enemy/creep_right.bmp", 6, 5, 29);
	sprite = new GSprite(this->texture, 28, 28, 2);
	sprite->SelectIndex(28);
	this->camera = new  GCamera();
	daban = false;
	vdan = -150;
	
	toadoban.x = x;
	toadoban.y = y;
	toadosimon.x = simon_x;
	toadosimon.y = simon_y;
	toadobandau.x = x;
	toadobandau.y = y;
}

void LuaBanRaTuQuai::Update(float time)
{
	D3DXVECTOR2 vetor;
	vetor.x = toadobandau.x - toadosimon.x;
	vetor.y = toadobandau.y - toadosimon.y;

	
	toadoban.x += vdan*time;

	float a = vetor.y / vetor.x;

	toadoban.y = this->_y + a*(toadoban.x - this->_x);
}

void LuaBanRaTuQuai::Render(float x, float y)
{
	
		D3DXVECTOR2 view;
		view.x = x;
		view.y = y;
		camera->setViewPort(view);
		D3DXVECTOR2 _pos = camera->Transform(this->toadoban.x, this->toadoban.y);
		G_SpriteHandler->Begin(D3DXSPRITE_SORT_DEPTH_FRONTTOBACK | D3DXSPRITE_ALPHABLEND);

		sprite->Draw(_pos.x, _pos.y);
		G_SpriteHandler->End();
	

}

Box LuaBanRaTuQuai::boxDan()
{
	return Box(toadoban.x - 7, toadoban.y - 7, toadoban.x + 7, toadoban.y + 7, 0, 0);
}

LuaBanRaTuQuai::~LuaBanRaTuQuai()
{
	if (texture != NULL)
		delete texture;
	if (sprite != NULL)
		delete sprite;

	if (camera != NULL)
		delete camera;
}
