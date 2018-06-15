#include "UI.h"



UI::UI()
{
}

bool UI::Initialize(LPDIRECT3DDEVICE9 gDevice)
{
	
	AddFontResourceEx("Resources/font/prstart.ttf", FR_PRIVATE, NULL);
	HRESULT result = D3DXCreateFont(
		gDevice, 20, 0, FW_NORMAL, 1, false,
		DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
		ANTIALIASED_QUALITY, FF_DONTCARE, "Press Start", &font);

	if (!SUCCEEDED(result))
		return false;

	for (int i = 0; i < 16; i++)
	{
		GTexture*textute = new GTexture("Resources/UI/HP.png",1,1,1);
		GSprite*sprite = new GSprite(textute,0,1,0);
		listHpSimon.push_back(sprite);
	}

	for (int i = 0; i < 16; i++)
	{
		GTexture*textute = new GTexture("Resources/UI/NoHP.png", 1, 1, 1);
		GSprite*sprite = new GSprite(textute, 0, 1, 0);
		listNoHp.push_back(sprite);
	}

	for (int i = 0; i < 16; i++)
	{
		GTexture*textute = new GTexture("Resources/UI/EnemyHP.png", 1, 1, 1);
		GSprite*sprite = new GSprite(textute, 0, 1, 0);
		listHpEnemy.push_back(sprite);
	}

	redEdgeTexture = new GTexture("Resources/UI/redEdge.bmp", 1, 1, 1);
	redEdgeSprite = new GSprite(redEdgeTexture, 0, 1, 0);

	HeartTexture = new GTexture("Resources/UI/Heart.png", 1, 1, 1);
	HeartSprite = new GSprite(HeartTexture, 0, 1, 0);

	TextureFireBom = new GTexture("Resources/item/bonus.bmp", 6, 4, 22);
	SpriteFireBom = new GSprite(TextureFireBom, 3, 3, 2);
	SpriteFireBom->SelectIndex(3);

	TextureDanger = new GTexture("Resources/item/bonus.bmp", 6, 4, 22);
	SpriteDanger = new GSprite(TextureFireBom, 0, 0, 2);
	SpriteDanger->SelectIndex(0);


	/*texture = new GTexture("Resources/UI/AXE.png", 1, 1, 1);
	sprite = new GSprite(texture,0,1,1);*/

	SetRect(&rect, 0, 20, G_ScreenWidth, G_ScreenHeight);
	information = "SCORE-000000 TIME 0000 STAGE 10\n";
	information += "PLAYER               =62\n";
	information += "ENEMY               P=3\n";
}

void UI::Render(kitty*simon)
{
		font->DrawTextA(NULL, information.c_str(), -1, &rect, DT_LEFT, D3DCOLOR_XRGB(255, 255, 255));
		
		/*sprite->Draw(20, 20);*/
		G_SpriteHandler->Begin(D3DXSPRITE_SORT_DEPTH_FRONTTOBACK | D3DXSPRITE_ALPHABLEND);
		for (int i = 0; i < 16; i++)
		{
			listNoHp[i]->Draw(130 + i * 7, 50);
		}
		for (int i = 0; i < hpSimon; i++)
		{
			listHpSimon[i]->Draw(130 + i * 7, 50);
		}

		
		for (int i = 0; i < 16; i++)
		{
			listNoHp[i]->Draw(130 + i * 7, 70);
		}
		for (int i = 0; i < hpEmeny; i++)
		{
			listHpEnemy[i]->Draw(130 + i * 7, 70);
		}

		HeartSprite->Draw(410, 50);


		switch (simon->LoaiVuKhi)
		{
		case eVuKhi::DANGER:
			SpriteDanger->Draw(290, 70);
			break;
		case eVuKhi::FIREBOM:
			SpriteFireBom->Draw(290, 70);
			break;
		default:
			break;
		}



		redEdgeSprite->Draw(290, 70);

		


		G_SpriteHandler->End();
		
		
}

void UI::Update(kitty*simon, int time)
{
	hpSimon = simon->hp;
	hpEmeny = simon->hpBos;
	std::string scoreString = std::to_string(simon->score);

	while (scoreString.length() < 6)
		scoreString = "0" + scoreString;

	std::string timeString = std::to_string(time);
		while (timeString.length()<5)
		{
			timeString = "0" + timeString;
		}
	
		std::string Stage = std::to_string(simon->MangTrenUI);
		std::string MangSong = std::to_string(simon->mangSong);
	 
	std::string heart = std::to_string(simon->heart);
	information = "SCORE-"+ scoreString + "TIME " + timeString + " STAGE"+ Stage+ "\n";
	information += "PLAYER               ="+ heart + "\n";
	information += "ENEMY               P="+MangSong+"\n";

}

UI::~UI()
{
	for (int i = 0; i < 16; i++)
	{
		delete listHpSimon[i];
		listHpSimon[i] = NULL;
	}

	for (int i = 0; i < 16; i++)
	{
		delete listHpEnemy[i];
		listHpEnemy[i] = NULL;
	}
}
