#pragma once
#include "GSprite.h"
#include "GTexture.h"
#include "GCamera.h"
#include "whip.h"
#include "Sound.h"
#include "SweptAABB.h"
#include <vector>
#include "ObjectVuKhi.h"
#include "GameObject.h"
#include "Enemy.h"
using namespace std;

class kitty
{
public:
	bool isWhip = false;
	bool isVuKhi = false;
	bool isTouchGround = false;
	bool isTouchLeftGround = false;
	bool isTouchRightGround = false;
	int simonBiThuongnho = 0;
	bool simonBiThuonglon = false;
	float thoigianbattu;
	float thoigiantrckhibattu;
	int score = 0;
	int heart;
	int life = 3;
	int hp = 16;
	int hpBos = 16 ;
	int mucWhip ;
	int stageMapChange;
	int trungEnemyWhip = 0;
	int LoaiVuKhi ;
	bool nhay;
	bool move;
	bool moveRight = false;
	bool moveLeft = false;
	bool IsActack;
	bool IsDown;
	bool vachamgach;
	bool dung_tren_moving;
	boolean anwhip = false;
	boolean isDie = false;
	int postground=100;
	float _vx;
	float _vy;
	float _vg;
	int width;
	int height;
	DWORD last_time;
	float _posx;
	float _posy;
	float detal_move;
	float timerSprite = 0;
	float timerSpriteForBatTu = 0;
	float timerAnWhip = 0;
	int win = 0;













	GSprite *sprite;
	GTexture *texture;
	GSprite*spriteDie;
	GTexture*textureDie;
	GCamera*camera;
	whip*_whip;
	vector<ObjectVuKhi*>_listVuKhi;
	bool flat = false;
	kitty();
	LPDIRECT3DSURFACE9 _Background;
	void RenderFrame(LPDIRECT3DDEVICE9 d3ddv, float t, vector<Enemy*>_listEnemy);
	void RenderVuKhi(float x, float y);
	void RenderEnemy(float x, float y, vector<Enemy*>_listEnemy);
	void Update(float time, vector<GameObject*>_listObjectQuadtree, vector<Enemy*>_listEnemy);
	void Next();
	void PosIndex(int index);
	void PosEnd(int end);
	void PosStart(int start);
	void Jumb();
	void Actack();
	void ActackVuKhi();
	int countMax;
	bool khongchonembonnua = false;
	void MoveRight();
	void MoveLeft();
	void ThucHienActack(int start, int end);
	void ThucHienActtackVuKhi(float time);
	
	void SimonVaChamVoiEnemy(vector<Enemy*>_listEnemy, float time, vector<GameObject*>_listObjectQuadtree);//cai nay set va cham voi rong va bot vi code truoc llo xu ly va cham o map 
	void CheckActack();
	Box bxSimon();
	Box bxSimonCollisionItem();

	int CountSpriteActtack = 0;
	~kitty();
};

