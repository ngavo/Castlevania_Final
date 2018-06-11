#pragma once
#include "GCamera.h"
#include "GSprite.h"
#include "GTexture.h"
enum  eEnemy
{
	BoneDragon,
	TypeBat,
	TypeFishMan,
	TypeFrankenstein,
	TypeFleaman
};

class Enemy
{
public:
	GSprite*sprite;
	GTexture*texture;
	GCamera*camera;
	int _id;
	float _x;
	float _y;
	bool hienthi;
	bool die;
	int _width;
	int _height;
	int _tyle;
	bool move;
	float vx;
	float vy;
	float post_ground;
	int va_cham_voi_gach_so_may;
	virtual void Init( int tyle, float x, float y,int width,int height );
	virtual void  Update(int time);
	virtual void Render(float x, float y);
	
	Enemy();
	~Enemy();
};

