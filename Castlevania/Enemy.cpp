#include "Enemy.h"



Enemy::Enemy()
{
}

void Enemy::Init(int tyle ,float x, float y, int width, int height)
{
	_x = x;
	_y = y;
	_width = width;
	_height = height;
	hienthi = false;
	die = false;
	move = false;
	_tyle = tyle;
	post_ground = 0;
}

void Enemy::Update(int time)
{

}

void Enemy::Render(float x, float y)
{

}

Enemy::~Enemy()
{
}
