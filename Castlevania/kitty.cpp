#include "kitty.h"
#define VX  100.0f
#define G -200.0f
#include "VuKhiFireBom.h"
#include "VuKhiDanger.h"
#include "BoneDragons.h"
#include "Bats.h"
#include "FishMan.h"
#include "Frankenstein.h"
#include "Fleaman.h"

kitty::kitty()
{
	texture = new GTexture("simon_right.bmp", 6, 5, 29);
	sprite = new GSprite(texture, 0, 28, 2);
	textureDie = new GTexture("simon_potion_right.bmp", 6, 5, 29);
	spriteDie = new GSprite(textureDie, 24, 26, 2);
	spriteDie->SelectIndex(24);
	this->_vx = VX;
	this->_vg = G;
	this->_vy = 0;
	this->_posx = 250;
	this->_posy = 450;
	camera = new GCamera();
	_whip = new whip();
	nhay = false;
	move = false;
	IsActack = false;
	IsDown = false;
	vachamgach = false;
	dung_tren_moving = false;
	width = 32;
	height = 64;
	heart = 62;
	this->mucWhip = 0;
	stageMapChange = 0;
	LoaiVuKhi = -1;
	VuKhiFireBom*_fireBom = new VuKhiFireBom(eVuKhi::FIREBOM, _posx, _posy, 16, 16, "Resources/item/HolyWater.png", 3, 1, 3, 0, 2, 0);
	VuKhiDanger*_vukhidanger = new VuKhiDanger(eVuKhi::DANGER, _posx, _posy, 32, 16, "Resources/item/bonus.bmp", 6, 4, 22, 0, 0, 0);
	_listVuKhi.push_back(_fireBom);
	_listVuKhi.push_back(_vukhidanger);
	hp = 16;
	
}

void kitty::Update(float time, vector<GameObject*>_listObjectQuadtree, vector<Enemy*>_listEnemy)
{
	if (hp <= 0)
	{
		this->isDie=true;
		/*this->mangSong -= 1;*/
		
	}

	if (this->_posy < 100 && this->stageMapChange == 0)
	{
		isDie = true;
		this->mangSong -= 1;
		
	}
	if (stageMapChange == 0)
	{
		CameraRight = 3040;
	}
	else
	{
		CameraRight = 2000;
	}
	if (this->_posx > G_ScreenWidth / 2 && this->_posx < (CameraRight-G_ScreenWidth/2))
	{
		this->camera->UpdateCamera(this->_posx);
	}


	if (simonBiThuongnho == 1)
	{
		this->sprite->SelectIndex(9);
		this->_vg -= 200 * time;
		this->_vx = 0;
		thoigiantrckhibattu += time;
		if (flat)
		{
			this->_posx += 50 * time;
		}
		else
		{
			this->_posx -= 50 * time;
		}
		
		if (thoigiantrckhibattu > 1.5)
		{
			thoigiantrckhibattu -= 1.5;
			simonBiThuongnho += 1;
			this->sprite->SelectIndex(0);
		}
		
	}
		
	
					
		/*khi khong bi thuong moi cho thuc hien*/

		if (this->nhay == true)
		{
			this->_vg -= 1000 * time;
		}

		
		if (this->IsActack)
		{
			if(isVuKhi)
			ThucHienActtackVuKhi(time);
			if (this->nhay)
			{
				
				ThucHienActack(11, 13);
			}
			else
			{
				if (this->IsDown)
				{
					
					ThucHienActack(14, 16);
				}
				else
				{
					
					ThucHienActack(11, 13);
				}

			}
		}
		else
		{
			if ((this->nhay && this->_vg < 0))//nhay den do cao cuc dai (max) thi simon o trang thai hinh thu 0 nhung khong danh
				this->sprite->SelectIndex(0);
			if (this->IsDown)
			{
				this->sprite->SelectIndex(4);
			}

			if (isTouchLeftGround || isTouchRightGround)
			{
				
			}
			else
			{
				if (this->move)
				{
					this->_posx += this->_vx*time;
					if (!this->nhay)
					{
						timerSprite += time;
						if (timerSprite > 0.15)
						{
							this->PosStart(0);
							this->PosEnd(3);
							this->Next();
							timerSprite -= 0.15;
						}
					}
				}
			}


		}

		if (this->dung_tren_moving)
		{
			this->_posx += this->detal_move;
		}

		if (!isTouchGround) {
			this->_posy = this->_posy + this->_vg*time;
			if (!nhay)
			{
				if (simonBiThuongnho == 1)
				{

				}
				else
				_vg = -200;
			}
				
		}
		else
		{
			this->_vg = 0;
		}

		/*ket thuc */

	
		for (int i = 0; i < _listVuKhi.size(); i++)
		{
			if (_listVuKhi[i]->_type == LoaiVuKhi)
			{
				switch (LoaiVuKhi)
				{
				case eVuKhi::DANGER:
					((VuKhiDanger*)_listVuKhi[i])->Update(time, _listObjectQuadtree, _listEnemy, this->camera->viewport.x, this->camera->viewport.x + G_ScreenWidth);
					break;
				case eVuKhi::FIREBOM:
					((VuKhiFireBom*)_listVuKhi[i])->Update(time, _listObjectQuadtree, _listEnemy,this->score);
					break;
				default:
					break;
				}
			}
			
			
		}
	



	if (simonBiThuongnho==2)
	{
		thoigianbattu += time;
		if (thoigianbattu > 4.0)
		{
			thoigianbattu -= 4.0;
			simonBiThuongnho = 0;
		}
	}


	SimonVaChamVoiEnemy(_listEnemy, time, _listObjectQuadtree);

}

void kitty::SimonVaChamVoiEnemy(vector<Enemy*> _listEnemy, float time, vector<GameObject*>_listObjectQuadtree)
{
	for (int i = 0; i < _listEnemy.size(); i++)
	{
		switch (_listEnemy[i]->_tyle)
		{
		
		case eEnemy::TypeBat:
			if (_listEnemy[i]->hienthi && !_listEnemy[i]->die)
			{
				Box boxBat(_listEnemy[i]->_x - 18, _listEnemy[i]->_y - 18, _listEnemy[i]->_x + 18, _listEnemy[i]->_y + 18, _listEnemy[i]->vx*time, 0);
				if (this->IsActack && this->isWhip)
				{
					if (this->sprite->GetIndex() == 13)
					{
						if (this->flat)//hinh trai
						{
							Box k = this->_whip->boxWhip(this->_posx, this->_posy, this->mucWhip, 13, 1);
							/*Box whipBox(simon->_posx - 32 - 70, simon->_posy - 20, simon->_posx - 32, simon->_posy - 10 + 20, simon->_vx, simon->_vg);*/
							if (AABB(k, boxBat))
							{
								_listEnemy[i]->hienthi = false;
								_listEnemy[i]->die = true;
								this->score += ((Bats*)_listEnemy[i])->scoreBat;
								((Bats*)_listEnemy[i])->_fire->hienthi = true;

							}
						}
						else
						{
							Box k = this->_whip->boxWhip(this->_posx, this->_posy, this->mucWhip, 13, 0);
							/*Box whipBox(simon->_posx + 32, simon->_posy - 20, simon->_posx + 32 + 70, simon->_posy - 10 + 20, simon->_vx, simon->_vg);*/
							if (AABB(k, boxBat))
							{
								_listEnemy[i]->hienthi = false;
								_listEnemy[i]->die = true;
								this->score += ((Bats*)_listEnemy[i])->scoreBat;
								((Bats*)_listEnemy[i])->_fire->hienthi = true;

							}
						}


					}

					if (this->sprite->GetIndex() == 16)
					{
						if (this->flat)//hinh trai
						{
							Box k = this->_whip->boxWhip(this->_posx, this->_posy, this->mucWhip, 16, 1);
							/*Box whipBox(simon->_posx - 32 - 70, simon->_posy - 20, simon->_posx - 32, simon->_posy - 10 + 20, simon->_vx, simon->_vg);*/
							if (AABB(k, boxBat))
							{
								_listEnemy[i]->hienthi = false;
								_listEnemy[i]->die = true;
								this->score += ((Bats*)_listEnemy[i])->scoreBat;
								((Bats*)_listEnemy[i])->_fire->hienthi = true;

							}
						}
						else
						{
							Box k = this->_whip->boxWhip(this->_posx, this->_posy, this->mucWhip, 16, 0);
							/*Box whipBox(simon->_posx + 32, simon->_posy - 20, simon->_posx + 32 + 70, simon->_posy - 10 + 20, simon->_vx, simon->_vg);*/
							if (AABB(k, boxBat))
							{
								_listEnemy[i]->hienthi = false;
								_listEnemy[i]->die = true;
								
								this->score += ((Bats*)_listEnemy[i])->scoreBat;
								((Bats*)_listEnemy[i])->_fire->hienthi = true;

							}
						}
					}
				}

				if (this->simonBiThuongnho == 0)//het thoi gian bat tu va truoc bat tu
				{
					if (!_listEnemy[i]->die)
					{
						if (AABB(this->bxSimon(), boxBat))
						{
							this->hp -= 3;
							Sound::GetInstance()->Play(eSoundID::SIMON_HURTED);
							if (this->_posx < _listEnemy[i]->_x)
							{
								this->sprite->SelectIndex(9);
								this->simonBiThuongnho = 1;
								this->isTouchGround = false;
								this->_vg = 140;
								this->flat = false;
							}
						}
					}
					
				}


				((Bats*)_listEnemy[i])->Update(time);

				/*ket thuc truong hop simon va bat cham nhau*/

				
			}
			if (((Bats*)_listEnemy[i])->die)
			{
				((Bats*)_listEnemy[i])->UpdateFire(time);
			}


			break;
		case eEnemy::BoneDragon:

			this->heart += ((BoneDragons*)_listEnemy[i])->Update(time, this->_posx, this->_posy, _listObjectQuadtree, this->bxSimon(), this->camera->viewport.x);
			if (((BoneDragons*)_listEnemy[i])->MangSong > 0)
			{
				if (this->IsActack)
				{
					if (this->CountSpriteActtack == 3)
					{
						if (this->isWhip)
							if (AABB(this->_whip->boxWhip(this->_posx, this->_posy, this->mucWhip, this->sprite->GetIndex(), this->flat), ((BoneDragons*)_listEnemy[i])->BoxBonDragons()))
							{
								((BoneDragons*)_listEnemy[i])->move = false;
								((BoneDragons*)_listEnemy[i])->MangSong -= 2;

							}
					}
				}
				for (int luaquai = 0; luaquai < ((BoneDragons*)_listEnemy[i])->_lisluabanratuquai.size(); luaquai++)
				{
					if (this->simonBiThuongnho == 0)
					{
						if (AABB(this->bxSimon(), ((BoneDragons*)_listEnemy[i])->_lisluabanratuquai[luaquai]->boxDan()))
						{
							this->hp -= 3;
							Sound::GetInstance()->Play(eSoundID::SIMON_HURTED);
							this->sprite->SelectIndex(9);
							this->simonBiThuongnho = 1;
							this->isTouchGround = false;
							this->_vg = 140;
							this->flat = false;
						}
					}

				}
			}



			if (simonBiThuongnho == 0)
			{
				if (((BoneDragons*)_listEnemy[i])->MangSong > 0)
				{
					if (AABB(this->bxSimon(), ((BoneDragons*)_listEnemy[i])->BoxBonDragons()))
					{
						this->hp -= 3;
						Sound::GetInstance()->Play(eSoundID::SIMON_HURTED);
						this->sprite->SelectIndex(9);
						this->simonBiThuongnho = 1;
						this->isTouchGround = false;
						this->_vg = 140;
						this->flat = false;
					}
				}
				
			}

			if (((BoneDragons*)_listEnemy[i])->MangSong <= 0 && ((BoneDragons*)_listEnemy[i])->die && ((BoneDragons*)_listEnemy[i])->chet ==1)
			{
				this->score += 1000;
				((BoneDragons*)_listEnemy[i])->chet += 1;
			}
			break;

		case eEnemy::TypeFishMan:
			if (_listEnemy[i]->hienthi && !_listEnemy[i]->die)
			{
				((FishMan*)_listEnemy[i])->IsTouchGround = false;

				((FishMan*)_listEnemy[i])->FishManVaChamGach(time, _listObjectQuadtree);

				Box fishmanBox(_listEnemy[i]->_x - 16, _listEnemy[i]->_y - 30, _listEnemy[i]->_x + 16, _listEnemy[i]->_y + 30, _listEnemy[i]->vx*time, 0);
				if (this->IsActack && this->isWhip)
				{
					if (this->sprite->GetIndex() == 13)
					{
						if (this->flat)//hinh trai
						{
							Box k = this->_whip->boxWhip(this->_posx, this->_posy, this->mucWhip, 13, 1);
							/*Box whipBox(simon->_posx - 32 - 70, simon->_posy - 20, simon->_posx - 32, simon->_posy - 10 + 20, simon->_vx, simon->_vg);*/
							if (AABB(k, fishmanBox))
							{
								_listEnemy[i]->hienthi = false;
								_listEnemy[i]->die = true;
								this->score += ((FishMan*)_listEnemy[i])->scoreFishman;

							}
						}
						else
						{
							Box k = this->_whip->boxWhip(this->_posx, this->_posy, this->mucWhip, 13, 0);
							/*Box whipBox(simon->_posx + 32, simon->_posy - 20, simon->_posx + 32 + 70, simon->_posy - 10 + 20, simon->_vx, simon->_vg);*/
							if (AABB(k, fishmanBox))
							{
								_listEnemy[i]->hienthi = false;
								_listEnemy[i]->die = true;
								this->score += ((FishMan*)_listEnemy[i])->scoreFishman;

							}
						}


					}

					if (this->sprite->GetIndex() == 16)
					{
						if (this->flat)//hinh trai
						{
							Box k = this->_whip->boxWhip(this->_posx, this->_posy, this->mucWhip, 16, 1);
							/*Box whipBox(simon->_posx - 32 - 70, simon->_posy - 20, simon->_posx - 32, simon->_posy - 10 + 20, simon->_vx, simon->_vg);*/
							if (AABB(k, fishmanBox))
							{
								_listEnemy[i]->hienthi = false;
								_listEnemy[i]->die = true;
								this->score += ((FishMan*)_listEnemy[i])->scoreFishman;

							}
						}
						else
						{
							Box k = this->_whip->boxWhip(this->_posx, this->_posy, this->mucWhip, 16, 0);
							/*Box whipBox(simon->_posx + 32, simon->_posy - 20, simon->_posx + 32 + 70, simon->_posy - 10 + 20, simon->_vx, simon->_vg);*/
							if (AABB(k, fishmanBox))
							{
								_listEnemy[i]->hienthi = false;
								_listEnemy[i]->die = true;
								this->score += ((FishMan*)_listEnemy[i])->scoreFishman;

							}
						}
					}
				}


				if (this->simonBiThuongnho == 0)//het thoi gian bat tu va truoc bat tu
				{

					if (AABB(this->bxSimon(), fishmanBox))
					{
						this->hp -= 3;
						Sound::GetInstance()->Play(eSoundID::SIMON_HURTED);
						this->sprite->SelectIndex(9);
						this->simonBiThuongnho = 1;
						this->isTouchGround = false;
						this->_vg = 140;
						if (this->_posx < _listEnemy[i]->_x)
						{

							this->flat = false;
						}
						else
						{
							this->flat = true;
						}
					}
				}


				//ket thuc simon va ca va cham




				((FishMan*)_listEnemy[i])->Update(time,_listObjectQuadtree);

			}
			if (((FishMan*)_listEnemy[i])->die)
			{
				((FishMan*)_listEnemy[i])->UpdateFire(time);
			}
			break;
		case eEnemy::TypeFrankenstein:
			((Frankenstein*)_listEnemy[i])->hpBos = &(this->hpBos);
			if (_listEnemy[i]->hienthi && !_listEnemy[i]->die)
			{
				((Frankenstein*)_listEnemy[i])->_fleamam->IsTouchGround = false;
				((Frankenstein*)_listEnemy[i])->Update(time, _listObjectQuadtree, this->flat, this->_posx,this->_posy, this->bxSimon(),this->win);

				//simon tan cong voi whip
				Box boxW = this->_whip->boxWhip(this->_posx, this->_posy, this->mucWhip, this->sprite->GetIndex(), this->flat);
				if (this->IsActack && this->isWhip)
				{
					//kiem tra simon danh trung Frankenstein
					if (trungEnemyWhip == 0)
					{
						
						if (AABB(boxW, ((Frankenstein*)_listEnemy[i])->boxFrankenstein()))
						{
							((Frankenstein*)_listEnemy[i])->bidanh = true;
							trungEnemyWhip++;
							hpBos -= 1;
							if (this->_posx < ((Frankenstein*)_listEnemy[i])->_x)
							{
								((Frankenstein*)_listEnemy[i])->vx = 50;
							}

							if (this->_posx >((Frankenstein*)_listEnemy[i])->_x)
							{
								((Frankenstein*)_listEnemy[i])->vx = -50;
							}

						}
					}

					//kiem tra danh trung Fleman
					if (((Frankenstein*)_listEnemy[i])->_fleamam->trungEmeny == 0)
					{
						if (AABB(boxW, ((Frankenstein*)_listEnemy[i])->_fleamam->boxFleaman()))
						{
							((Frankenstein*)_listEnemy[i])->_fleamam->bidanh = true;
						}
					}
					
				}



				if (this->simonBiThuongnho == 0)//het thoi gian bat tu va truoc bat tu
				{
					//simon va cham voi Frankenstein
					if (AABB(this->bxSimon(), ((Frankenstein*)_listEnemy[i])->boxFrankenstein()))
					{
						this->hp -= 3;
						Sound::GetInstance()->Play(eSoundID::SIMON_HURTED);
						this->sprite->SelectIndex(9);
						this->simonBiThuongnho = 1;
						this->isTouchGround = false;
						this->_vg = 140;
						if (this->_posx < _listEnemy[i]->_x)
						{

							this->flat = false;
						}
						else
						{
							this->flat = true;
						}
					}

					//simon va cham voi Fleman
					if (AABB(this->bxSimon(), ((Frankenstein*)_listEnemy[i])->_fleamam->boxFleaman()))
					{
						this->hp -= 3;
						Sound::GetInstance()->Play(eSoundID::SIMON_HURTED);
						this->sprite->SelectIndex(9);
						this->simonBiThuongnho = 1;
						this->isTouchGround = false;
						this->_vg = 140;
						if (this->_posx < ((Frankenstein*)_listEnemy[i])->_fleamam->_x)
						{

							this->flat = false;
						}
						else
						{
							this->flat = true;
						}
					}

					//simon va cham voi dan cua Fleman
					for (int luaquai = 0; luaquai < ((Frankenstein*)_listEnemy[i])->_fleamam->listLuaBanRaTuQuai.size(); luaquai++)
					{
						if (this->simonBiThuongnho == 0)
						{
							if (AABB(this->bxSimon(), ((Frankenstein*)_listEnemy[i])->_fleamam->listLuaBanRaTuQuai[luaquai]->boxDan()))
							{
								this->hp -= 3;
								Sound::GetInstance()->Play(eSoundID::SIMON_HURTED);
								this->sprite->SelectIndex(9);
								this->simonBiThuongnho = 1;
								this->isTouchGround = false;
								this->_vg = 140;
								if (this->_posx < ((Frankenstein*)_listEnemy[i])->_fleamam->listLuaBanRaTuQuai[luaquai]->toadobandau.x)
								{

									this->flat = false;
								}
								else
								{
									this->flat = true;
								}
							}
						}

					}

				}


			}

			if (hpBos <= 0)
			{
				_listEnemy[i]->die = true;
				if(!((Frankenstein*)_listEnemy[i])->hienthiqua)
				((Frankenstein*)_listEnemy[i])->hienthilua = true;
				((Frankenstein*)_listEnemy[i])->Update(time, _listObjectQuadtree, this->flat, this->_posx, this->_posy, this->bxSimon(),this->win);
				
			}
			if (_listEnemy[i]->die && ((Frankenstein*)_listEnemy[i])->tangdiem == 0 && ((Frankenstein*)_listEnemy[i])->hienthilua)
			{
				this->score += 5000;
				((Frankenstein*)_listEnemy[i])->tangdiem++;
			}
			break;
		default:
			break;
		}
	}
}

void kitty::MoveRight()
{

	this->move = true;
	this->_vx = 200;
	this->flat = false;
	this->IsDown = false;
}

void kitty::MoveLeft()
{
	this->move = true;
	this->flat = true;
	this->IsDown = false;
	this->_vx = -200;
}

void kitty::ThucHienActack(int start, int end)
{
	DWORD now = GetTickCount();
	sprite->GetStart(start);
	sprite->GetEnd(end);
	
		if (now - last_time > 1000 / 8)
		{
			
			last_time = now;
			
			if (this->IsDown == true)
			{

				if (CountSpriteActtack == 0)
				{
					sprite->SelectIndex(14);
					if(isWhip)
					_whip->SetIndex(14,mucWhip);
				}
				if (CountSpriteActtack == 1)
				{
					sprite->SelectIndex(15);
					if (isWhip)
					_whip->SetIndex(15,mucWhip);
				}

				if (CountSpriteActtack == 2)
				{
					sprite->SelectIndex(16);
					if (isWhip)
					_whip->SetIndex(16,mucWhip);
					trungEnemyWhip = 0;
				}

			}
			else
			{
				if (CountSpriteActtack == 0)
				{
					sprite->SelectIndex(11);
					if (isWhip)
					_whip->SetIndex(11,mucWhip);
				}
				if (CountSpriteActtack == 1)
				{
					sprite->SelectIndex(12);
					if (isWhip)
					_whip->SetIndex(12,mucWhip);
				}
				
				if (CountSpriteActtack == 2)
				{
					sprite->SelectIndex(13);
					if (isWhip)
					_whip->SetIndex(13,mucWhip);
					trungEnemyWhip = 0;
				}
				
			}

			CheckActack();
			
			
		}

	
	
}

void kitty::CheckActack()
{
	if (CountSpriteActtack == 3)
	{
		if(isWhip)
		Sound::GetInstance()->Play(eSoundID::USING_WHIP);
		IsActack = false;
		//this->_vy = VY;
		CountSpriteActtack = 0;
		if (this->IsDown == true)
		{
			this->PosIndex(4);
		}
		if (this->IsDown == false)
		{
			this->PosIndex(0);
		}
		this->_vx = VX;
	}
	else
	{
		CountSpriteActtack = CountSpriteActtack+1;
	}
}

void kitty::RenderVuKhi(float x, float y)
{
	for (int i = 0; i < _listVuKhi.size(); i++)
	{
		_listVuKhi[i]->Render(x, y);
	}
}

void kitty::RenderFrame(LPDIRECT3DDEVICE9 d3ddv, float t, vector<Enemy*>_listEnemy)
{

	
	//spriteDie->SelectIndex(sprite->GetIndex());
	D3DXVECTOR2 _pos = camera->Transform(_posx, _posy);
	G_SpriteHandler->Begin(D3DXSPRITE_SORT_DEPTH_FRONTTOBACK | D3DXSPRITE_ALPHABLEND);
	if (this->flat == false)
	{

			if (simonBiThuongnho == 2)
			{
				timerSpriteForBatTu += t;
				if (timerSpriteForBatTu > 0.1)
				{
					sprite->Draw(_pos.x, _pos.y);
					timerSpriteForBatTu -= 0.1;
				}

				
			}
			else
			{
				sprite->Draw(_pos.x, _pos.y);
			}
		
			if (IsActack == true)
			{
				if(isWhip)
				_whip->Draw(_pos.x, _pos.y, this->IsDown);
			
			}
			
	}
	else
	{
		if (simonBiThuongnho == 2)
		{
			timerSpriteForBatTu += t;
			if (timerSpriteForBatTu > 0.1)
			{
				sprite->DrawFlipX(_pos.x, _pos.y);
				timerSpriteForBatTu -= 0.1;
			}
				
			
		}
		else
		{
			sprite->DrawFlipX(_pos.x, _pos.y);
		}
		
		if (IsActack == true)
		{
			if(isWhip)
			_whip->DrawFlip(_pos.x, _pos.y, this->IsDown);
			
		}
		
	}
	
	if (anwhip)
	{
		if (this->flat == false)
		{
			spriteDie->Draw(_pos.x, _pos.y);
		}
		else
		{
			spriteDie->DrawFlipX(_pos.x, _pos.y);
		}
	}
	
	G_SpriteHandler->End();
	RenderVuKhi(camera->viewport.x, G_ScreenHeight);
	RenderEnemy(camera->viewport.x, G_ScreenHeight, _listEnemy);

	
	
}


void kitty::RenderEnemy(float x, float y, vector<Enemy*>_listEnemy)
{
	for (int i = 0; i < _listEnemy.size(); i++)
	{
		switch (_listEnemy[i]->_tyle)
		{
		case eEnemy::BoneDragon:
			((BoneDragons*)_listEnemy[i])->Render(x, y);
			break;
		case eEnemy::TypeBat:
			((Bats*)_listEnemy[i])->Render(x, y);
			break;
		case eEnemy::TypeFishMan:
				((FishMan*)_listEnemy[i])->Render(x, y);
			break;
		case eEnemy::TypeFrankenstein:
			((Frankenstein*)_listEnemy[i])->Render(x, y);
			break;
		default:
			break;
		}
	}
}

void kitty::Next()
{
	sprite->Next();
}

void kitty::PosIndex(int index)
{
	sprite->_index = index;
}

void kitty::PosEnd(int end)
{
	sprite->GetEnd(end);
}


void kitty::Jumb()
{
	if (!nhay)
	{
	this->nhay = true;
	this->_vg = 400;
	this->_posy += 10;
	this->sprite->SelectIndex(4);
	}
	
}

void kitty::ActackVuKhi()
{
	
	if (this->IsDown == true)
		this->PosIndex(14);
	if (this->IsDown == false)
		this->PosIndex(11);
	this->IsActack = true;
	this->isWhip = false;
	this->isVuKhi = true;
	this->heart -= 1;

	
	
}


void kitty::ThucHienActtackVuKhi(float time)
{
	for (int i = 0; i < _listVuKhi.size(); i++)
	{
		
		/*if (_listVuKhi[i]->_type == eVuKhi::FIREBOM)
		{
			
		}*/
		
		if (_listVuKhi[i]->_type == LoaiVuKhi)
		{
			switch (LoaiVuKhi)
			{
			case eVuKhi::FIREBOM:
				if (this->sprite->GetIndex() == 13 || this->sprite->GetIndex() == 16)
				{
					isVuKhi = true;
					isWhip = false;
					if (!_listVuKhi[i]->_hienthi)
					{
						_listVuKhi[i]->toado.x = this->_posx;
						_listVuKhi[i]->toado.y = this->_posy;
						if (!flat)
						{
							_listVuKhi[i]->lucnem.x = 50;
							_listVuKhi[i]->lucnem.y = 50;
						}
						else
						{
							_listVuKhi[i]->lucnem.x = -50;
							_listVuKhi[i]->lucnem.y = 50;
						}

					}
					_listVuKhi[i]->_hienthi = true;

				}
				break;
			case eVuKhi::DANGER:
				if (this->sprite->GetIndex() == 13 || this->sprite->GetIndex() == 16)
				{
					isVuKhi = true;
					isWhip = false;
					if (!_listVuKhi[i]->_hienthi)
					{
						_listVuKhi[i]->toado.x = this->_posx;
						_listVuKhi[i]->toado.y = this->_posy;
						if (!flat)
						{
							_listVuKhi[i]->lucnem.x = 350;
						}
						else
						{
							_listVuKhi[i]->lucnem.x = -350;
						}

					}
					_listVuKhi[i]->_hienthi = true;

				}
				break;
			default:
				break;
			}
		}

	}

	

}

void kitty::Actack()
{
	if (this->IsDown == true)
		this->PosIndex(14);
	if(this->IsDown==false)
		this->PosIndex(11);
	this->IsActack = true;
	this->isWhip = true;
	this->isVuKhi = false;
	/*Sound::GetInstance()->Play(eSoundID::USING_WHIP);*/
}

void kitty::PosStart(int start)
{
	sprite->GetStart(start);
}

Box kitty::bxSimon()
{
	/*Box k(this->_posx - width / 2, this->_posy - height / 2, this->_posx + width / 2, this->_posy + height / 2,this->_vx, this->_vg);*/
	if (this->IsDown || this->nhay)
	{
		return Box(this->_posx - width / 2, this->_posy - height / 2, this->_posx + width / 2 -20, this->_posy + height / 2-10, this->_vx, this->_vg);
	}
	else
	{
		return Box (this->_posx - width / 2, this->_posy - height / 2, this->_posx + width / 2, this->_posy + height / 2, this->_vx, this->_vg);
	}

}

Box kitty::bxSimonCollisionItem()
{
	Box k(this->_posx - 10, this->_posy - height / 2, this->_posx + 10, this->_posy + height / 4, this->_vx, this->_vg);

	return k;
}
kitty::~kitty()
{
}
