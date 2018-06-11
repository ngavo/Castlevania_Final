#pragma once
#include "ObjectVuKhi.h"
#include "LuaCuaFireBom.h"
class VuKhiFireBom:public ObjectVuKhi
{
public:
	VuKhiFireBom(int type, float x, float y, int wight, int height, char*path, int columm, int row, int count, int start, int end, int selectedIndex);
	~VuKhiFireBom();
	boolean chamgach;
	LuaCuaFireBom*_luaCuaFireBon;
	float timerSpriteForLua;
	float timerSprite;
	int trungEnemy=0;
	void Update(float _DeltaTime, vector<GameObject*> _listObjectQuadtree, vector<Enemy*> _listEnemy,int &score);	// update per frame
	void Render(float x, float y);							// render per frame
	void LuaVaChamEmeny(vector<Enemy*> _listEnemy, int &score);
};

