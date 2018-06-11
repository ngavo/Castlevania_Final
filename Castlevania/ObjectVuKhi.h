#pragma once
#include "GSprite.h"
#include "GCamera.h"
#include "GameObject.h"
#include <vector>
#include "SweptAABB.h"
#include "Enemy.h"

using namespace std;
enum eVuKhi {
	FIREBOM,
	DANGER
};


class ObjectVuKhi
{
public:
	int _type, _wight, _height;
	D3DXVECTOR2 lucnem;
	D3DXVECTOR2 toado;
	GTexture*_texture;
	GSprite*_sprite;
	GCamera*_camera;
	bool _hienthi;
	ObjectVuKhi(int type, float x, float y, int wight, int height, char*path, int columm,int row, int count, int start, int end, int selectedIndex);
	virtual void Update(float _DeltaTime, vector<GameObject*> _listObjectQuadtree, vector<Enemy*>_listEnemy);	// update per frame
	virtual void Render(float x, float y);							// render per frame
	Box BoxObjectVuKhi();
	~ObjectVuKhi();
};

