#include "TileBackground.h"



TileBackground::TileBackground(int x,int y, int row, int col)
{

	_x = (x%col)*64;
	_y = (x/col)*64;
	texture = new GTexture("quadtree.PNG",11,4,44);
	sprite = new GSprite(texture, 0, 43, 2);
	sprite->SelectIndex(y);
	camera = new GCamera();
}

void TileBackground::Render(int x, int y)
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
TileBackground::~TileBackground()
{
	delete(camera);
	delete(sprite);
	delete(texture);
}
