#pragma once
#include"Enemy.h"
#include "GameObject.h"
#include <vector>
#include "LuaBanRaTuQuai.h"

using namespace std;
class Fleaman:public Enemy
{
public:
	Fleaman();
	float a;
	DWORD last_time;
	boolean flat = false;
	boolean IsTouchGround = false;
	float left = 1510;
	float right = 1990;
	float timeTrenFrankenstein;
	float timerSprite;
	float timerBan;
	float timerBiDanh;
	int trungEmeny = 0;
	boolean bidanh = false;
	vector<LuaBanRaTuQuai*>listLuaBanRaTuQuai;
	void Init(float x, float y, int width, int height);
	void Render(float x, float y);
	void Update(float timeu, float postxFrankenstein, float postyFrankenstein, vector<GameObject*> _listObjectQuadtree, float posxSimon,float posySimon);
	void UpdateVaChamGach(float timevc,vector<GameObject*> _listObjectQuadtree);
	Box boxFleaman();
	~Fleaman();
};

