#pragma once
#include "Enemy.h"
#include "Water.h"
#include "Sound.h"
#include "GameObject.h"
#include <vector>
#include "fire.h"
using namespace std;
class FishMan: public Enemy
{
public:
	FishMan();
	DWORD last_time;
	float timerSprite;
	bool xuong;
	bool flat = false;
	int fishmanid97 = 0;
	int fishmanid96 = 0;
	bool IsColision = false;
	bool IsTouchGround = false;
	int scoreFishman = 300;
	bool len;
	int flip;
	int id;
	int amthanhlucnhaylen = 0;
	int amthanhlucnhayxuong = 0;
	fire*_fire;
	Water*_water1;
	Water*_water2;

	void UpdateFire(float time);
	void RenderFire(float x, float y);
	void Init(int id,int tyle, int flip, float x, float y, int width, int height);
	void Render(float x, float y);
	void Update(float time, vector<GameObject*>_listObjectQuadtree);
	void FishManVaChamGach(float time,vector<GameObject*>_listObjectQuadtree);
	bool Check(float _posxSimon, int _id);
	~FishMan();
};

