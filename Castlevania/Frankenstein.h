#pragma once
#include "Enemy.h"
#include "GameObject.h"
#include <vector>
#include "SweptAABB.h"
#include "Fleaman.h"
#include "LuaDanhQuai.h"
#include "LuaCuaFireBom.h"
#include "fire.h"
#include "Orb.h"
using namespace std;
class Frankenstein :public Enemy
{
public:
	Frankenstein();
	float timerSprite;
	float left =1510;
	float right = 1990;
	boolean _flat = false;
	boolean bidanh = false;//neu bi danh la true thi Frankenstein se lui lai
	float timerBiDanh;//set khoan thoi gian bi danh
	float timerLua;
	boolean hienthilua = false;
	boolean hienthiqua = false;
	int tangdiem = 0;
	int *hpBos;
	void Init(int tyle, float x, float y, int width, int height);
	void Render(float x, float y);
	void Update(float time, vector<GameObject*>_listObjectQuadtree, boolean simonflat, float posxSimon, float posySimon, Box boxSimon, int &simonwin);
	void UpdateLua(float time);
	void RenderLua(float x, float y);
	void UpdateQua(float time, vector<GameObject*>_listObjectQuadtree, Box boxSimon, int &simonwin);
	void RenderQua(float x, float y);
	Box boxFrankenstein();



	Fleaman*_fleamam;
	LuaDanhQuai* _luadanhquai;
	vector<LuaCuaFireBom*> _listLuaDie;
	fire*_fireFleamDie;
	Orb* _orb;

	~Frankenstein();
};

