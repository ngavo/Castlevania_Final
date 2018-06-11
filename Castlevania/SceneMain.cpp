#include "SceneMain.h"


SceneMain::SceneMain(int _nCmdShow): CGame(_nCmdShow)
{
	
}

void SceneMain::UpdateFrame(float Delta)
{
	
	
	if (!this->_kitty->anwhip)
	{
		if (this->_kitty->win == 0)
		{
			time += Delta;
		}
		else
		{
			if (time > 0)
			{
				this->_kitty->score += 10;
				time -= 1;
			}
			else
			{
				if (this->_kitty->heart > 0)
				{
					this->_kitty->score += 100;
					this->_kitty->heart -= 1;
				}
				
			}
		}
		
		if (this->_kitty->isDie && this->_kitty->stageMapChange==0)
		{
			this->_kitty->_posx = 250;
			this->_kitty->_posy = 400;
			this->_kitty->camera->viewport.x = 0;
			this->_kitty->camera->viewport.y = G_ScreenHeight;
			this->_kitty->mucWhip = 0;
			this->_kitty->hp = 16;
			this->_kitty->isDie = false;
			this->_kitty->LoaiVuKhi = -1;
			this->_kitty->score = 0;
			this->map10 = new Map();
			map10->LoadMap("Resources/quadtree/stage10.o", 10);
		}
		
		switch (this->_kitty->stageMapChange)
		{
		case 0:
			map10->Update(Delta, this->_kitty);
			map10->LoadListObjectInWorld(this->_kitty->camera->GetRegion(this->_kitty->camera->viewport.x, 0, G_ScreenWidth, G_ScreenHeight));
			this->_kitty->Update(Delta, map10->quadtree->ListObjectInRect, map10->_listEnemy);
			break;
		case 1:
			map12->Update(Delta, this->_kitty);
			map12->LoadListObjectInWorld(this->_kitty->camera->GetRegion(this->_kitty->camera->viewport.x, 0, G_ScreenWidth, G_ScreenHeight));
			this->_kitty->Update(Delta, map12->quadtree->ListObjectInRect, map12->_listEnemy);
			break;
		default:
			break;
		}



		ui->Update(this->_kitty, (int)time);
	}
	else
	{
		timeAnWhip += Delta;
		if (timeAnWhip > 1.5)
		{
			this->_kitty->anwhip = false;
			timeAnWhip -= 1.5;
		}
		else
		{
			this->_kitty->spriteDie->Next();
		}
	}
	
	
	
	
}
void SceneMain::RenderFrame(LPDIRECT3DDEVICE9 d3ddv, float t)
{
	
	switch (this->_kitty->stageMapChange)
	{
	case 0:
		this->background10->DrawBackground(this->_kitty->camera->viewport.x);
		map10->Draw(this->_kitty->camera->viewport.x, G_ScreenHeight);
		this->_kitty->RenderFrame(d3ddv, t, map10->_listEnemy);
		break;
	case 1:
		this->background12->DrawBackground(this->_kitty->camera->viewport.x);
		map12->Draw(this->_kitty->camera->viewport.x, G_ScreenHeight);
		this->_kitty->RenderFrame(d3ddv, t, map12->_listEnemy);
	default:
		break;
	}

	
	
	ui->Render(this->_kitty);
	
	
}

void SceneMain::ProcessInput(LPDIRECT3DDEVICE9 d3ddv, float Delta)
{
	
	if (this->_kitty->simonBiThuongnho != 1)
	{
		if (IsKeyDown(DIK_RIGHT))
		{


			this->_kitty->MoveRight();

		}
		if (IsKeyDown(DIK_LEFT))
		{


			this->_kitty->MoveLeft();

		}
		if (IsKeyDown(DIK_DOWN))
		{
			this->_kitty->IsDown = true;
			this->_kitty->_vx = 0;
		}
	}
	

	
}

void SceneMain::LoadResources(LPDIRECT3DDEVICE9 d3ddv)
{
	this->background12 = new Background("Resources/background/background12.PNG", 8, 5, 40);
	this->background12->readfile("Resources/background/background12-MAP.txt");

	this->background10 = new Background("stage.PNG", 11, 6, 66);
	this->background10->readfile("stage.txt");

	this->_kitty = new kitty();
	this->map12 = new Map();
	map12->LoadMap("Resources/quadtree/quadtree12.o",12);

	this->map10 = new Map();
	map10->LoadMap("Resources/quadtree/stage10.o",10);
	_listMap.push_back(map10);
	ui = new UI();
	Sound::GetInstance()->loadSound(G_hWnd);
	ui->Initialize(G_Device);
	Sound::GetInstance()->PlayLoop(eSoundID::STAGE_01_VAMPIRE_KILLER);
}

void SceneMain::OnKeyDown(int KeyCode)
{
	if (this->_kitty->simonBiThuongnho != 1)
	{
		if (KeyCode == DIK_SPACE)
		{

			this->_kitty->Jumb();
		}
		if (KeyCode == DIK_F)
		{
			if (this->_kitty->IsActack == false)
				this->_kitty->Actack();
		}
		if (KeyCode == DIK_A)
		{
			if (this->_kitty->IsActack == false)
				this->_kitty->ActackVuKhi();
		}
	}
	
}
void SceneMain::OnKeyUp(int KeyCode)
{
	if (this->_kitty->simonBiThuongnho != 1)
	{
		if (KeyCode == DIK_RIGHT)
		{
			this->_kitty->PosIndex(0);
			this->_kitty->move = false;

		}
		if (KeyCode == DIK_LEFT)
		{
			this->_kitty->PosIndex(0);
			this->_kitty->move = false;
		}
		if (KeyCode == DIK_DOWN)
		{
			this->_kitty->IsDown = false;
			this->_kitty->PosIndex(0);
		}

	}
	
		
	
}
SceneMain::~SceneMain(void)
{
	if (ui != NULL) delete ui;
}
