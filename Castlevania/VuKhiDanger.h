#pragma once
#include "ObjectVuKhi.h"
#include "SweptAABB.h"
class VuKhiDanger :public ObjectVuKhi
{
public:
	VuKhiDanger(int type, float x, float y, int wight, int height, char*path, int columm, int row, int count, int start, int end, int selectedIndex);
	float timerSprite;
	int trungEnemy = 0;
	boolean flat;
	void Update(float _DeltaTime, vector<GameObject*> _listObjectQuadtree, vector<Enemy*> _listEnemy, float cameraleft, float cameraright);	// update per frame
	void Render(float x, float y);							// render per frame
	void UpdateVaChamEnemy(float _DeltaTime, vector<Enemy*> _listEnemy);
	~VuKhiDanger();
};

