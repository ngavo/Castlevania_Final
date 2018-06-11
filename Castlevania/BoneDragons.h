#pragma once
#include "Enemy.h"
#include "Dragon.h"
#include "SweptAABB.h"
#include "LuaDanhQuai.h"
#include "LuaBanRaTuQuai.h"
#include "heartSmall.h"
#include "GameObject.h"
#include <vector>
using namespace std;
class BoneDragons: public Enemy
{
public:
	int hienthiqua;
	BoneDragons();
	bool len = false;
	bool xuong = false;
	int this_xuong = 0;
	int this_len = 0;
	int hienthisangtrai = 0;
	int maxleft = 0;
	float _xbandau = 0;
	float _ybandau = 0;
	int chet = 0;
	float maxtop = 0;
	int _v = 0;
	boolean move;
	Dragon* dragon[6];
	LuaDanhQuai*_luadanhquai;
	vector<LuaBanRaTuQuai*>_lisluabanratuquai;
	vector<heartSmall*>_listHeartSmall;

	DWORD last_time;
	float timerSprite;
	float timerBan;
	int MangSong;
	void Init(int type,float x, float y, int width, int height);
	void Render(float x, float y);
	int Update(float time, float simon_x, float simon_y, vector <GameObject*> ListObjects, Box simonBox, float viewportx);
	int UpdateQua(float time, vector <GameObject*> ListObjects, Box simonBox);
	void RenderQua(float x, float y);
	void GetToaDoQua();
	bool tancong;
	float thoigianrandtancong = 0;
	Box BoxBonDragons();

	~BoneDragons();
};

