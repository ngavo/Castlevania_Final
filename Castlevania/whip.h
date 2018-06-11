#pragma once
#include "GSprite.h"
#include "SweptAABB.h"
class whip
{
public:
	GSprite *sprite;
	GTexture *texture;
	whip();
	void SetIndex(int TrangThaiSinmon, int mucWhip);
	Box boxWhip(float postSimonx,float postSimony, int mucWhip, int TrangThaiSimon, boolean flatSimon);
	void Draw(int x,int y, boolean isDown);
	void DrawFlip(int x, int y,boolean isDown);
	int GetIndex();
	~whip();
};

