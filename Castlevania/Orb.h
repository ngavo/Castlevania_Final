#pragma once
#include"GameObject.h"
#include "GCamera.h"
#include <vector>
#include "SweptAABB.h"
using namespace std;
class Orb :public GameObject
{
public:
	Orb(float x, float y, int width, int height);
	DWORD last_time;
	GTexture*texture;
	GSprite*sprite;
	GCamera*camera;
	float timerSprite;
	boolean IsTouchGround = false;
	float vy;
	void Render(float x, float y);
	void Update(float time, vector<GameObject*>_listObjectQuadtree, Box boxSimon, int &simonwin);
	void UpdateVaChamGach(float time, vector<GameObject*>_listObjectQuadtree);
	Box BoxOrb();
	~Orb();
};

