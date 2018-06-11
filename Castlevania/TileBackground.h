#pragma once
#include "GCamera.h"
#include "GSprite.h"
#include "GTexture.h"
class TileBackground
{
public:
	int _x, _y;
	TileBackground(int x,int y,int row, int col);
	GCamera* camera;
	GTexture* texture;
	GSprite* sprite;
	void Render(int x, int y);
	~TileBackground();
};

