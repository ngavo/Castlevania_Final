#ifndef _SCENEMAIN_H_
#define _SCENEMAIN_H_

#include "Game.h"
#include "kitty.h"
#include "Map.h"
#include "BackgroundQuadtree.h"
#include "UI.h"
#include <vector>
using namespace std;
class SceneMain: public CGame
{
public: 	
	SceneMain(int _nCmdShow);
	~SceneMain();	
	kitty * _kitty;
	Background* background10;
	Map*map10;
	Background* background12;
	Map*map12;
	BackgroundQuadtree*bgq;
	vector<Map*>_listMap;
	float timerSprite;
	float thoigianhieuungnhapnhay;
	UI*ui;
	float time=0;
	float timeAnWhip;
protected:	
	
	virtual void RenderFrame(LPDIRECT3DDEVICE9 d3ddv, float t);
	virtual void ProcessInput(LPDIRECT3DDEVICE9 d3ddv, float Delta);
	virtual void LoadResources(LPDIRECT3DDEVICE9 d3ddv);
	virtual void UpdateFrame(float Delta);
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode);
};

#endif