#pragma once
#include "d3dx9.h"
#include <string>
#include "Global.h"
#include "GSprite.h"
#include <vector>
#include "kitty.h"
static int timeGameHienThiSo=0;
class UI
{
public:
	UI();
	ID3DXFont *font;
	std::vector<GSprite*> listHpSimon;
	std::vector<GSprite*>listHpEnemy;
	std::vector<GSprite*>listNoHp;
	int hpSimon;
	int hpEmeny;


	GTexture* redEdgeTexture;
	GSprite*redEdgeSprite;
	GTexture*HeartTexture;
	GSprite*HeartSprite;

	GTexture* TextureDanger;
	GSprite* SpriteDanger;

	GTexture* TextureFireBom;
	GSprite* SpriteFireBom;



	std::string information;
	RECT rect;
	bool Initialize(LPDIRECT3DDEVICE9 gDevice);
	void Update(kitty*simon, int time);
	
	void Render(kitty*simon);
	~UI();
};

