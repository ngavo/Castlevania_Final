#include "BoneDragons.h"
#include "Sound.h"

BoneDragons::BoneDragons()
{
	_luadanhquai = new LuaDanhQuai(0, 0, 0, 0);
}
void BoneDragons::Init(int type,float x, float y, int width, int height)
{
	move = true;
	_x = x;
	_y = y;
	this->_xbandau = _x;
	this->_ybandau = _y-20;
	this->maxtop = 250;
	_v = -100;
	_width = 38;
	_height = 38;
	this->maxleft = this->_x - 120;
	texture = new GTexture("Resources/enemy/BoneDragons.bmp", 3, 1, 3);
	sprite = new GSprite(texture, 0, 1, 2);
	camera = new GCamera();
	dragon[0] = new Dragon();
	dragon[1] = new Dragon();
	dragon[2] = new Dragon();
	dragon[3] = new Dragon();
	dragon[4] = new Dragon();
	dragon[5] = new Dragon();
	dragon[0]->Init(_x, _y, 24, 38);
	dragon[1]->Init(_x, _y, 24, 38);
	dragon[2]->Init(_x, _y, 24, 38);
	dragon[3]->Init(_x, _y, 24, 38);
	dragon[4]->Init(_x, _y, 24, 38);
	dragon[5]->Init(_x, _y, 24, 38);
	dragon[0]->minydragon = _y - 25;
	dragon[1]->minydragon = _y - 35;
	dragon[2]->minydragon = _y - 40;
	dragon[3]->minydragon = _y - 25;
	dragon[4]->minydragon = _y - 15;
	tancong = false;
	MangSong = 100;
	hienthiqua = 0;

}

void BoneDragons::GetToaDoQua()
{
	for (int i = 0; i < 7; i++)
	{
		heartSmall*_heartSamll = NULL; 
		if (i == 0)
		{
			_heartSamll = new heartSmall(this->_x, this->_y,10,24);
			_heartSamll->hienthi = true;
			_heartSamll->_vy = 200;
			_listHeartSmall.push_back(_heartSamll);
		}
		else
		{
			_heartSamll = new heartSmall(this->dragon[i-1]->_x, this->dragon[i - 1]->_y, 10, 24);
			_heartSamll->_vy = 200;
			_heartSamll->hienthi = true;
			_listHeartSmall.push_back(_heartSamll);
		}
		
	}

	hienthiqua += 1;
}

int BoneDragons::UpdateQua(float time, vector <GameObject*> ListObjects, Box simonBox)
{
	//truong hop qua va cham voi gach
	for (int i = 0; i < _listHeartSmall.size(); i++)
	{
		_listHeartSmall[i]->Update(time);
		
			if (_listHeartSmall[i]->hienthi)
			{
				for (int j = 0; j < ListObjects.size(); j++)
				{
					if (ListObjects[j]->GetType() == 12 || ListObjects[j]->GetType() == 19)
					{
						Box boxq(ListObjects[j]->_x - ListObjects[j]->_width / 2, ListObjects[j]->_y - ListObjects[j]->_height / 2, ListObjects[j]->_x + ListObjects[j]->_width / 2, ListObjects[j]->_y + ListObjects[j]->_height / 2, 0, 0);

						if (AABB(_listHeartSmall[i]->boxItem(), boxq))
						{
							_listHeartSmall[i]->_vy = 0;
							_listHeartSmall[i]->_y = boxq.b + 16;
							_listHeartSmall[i]->itemChamDat = true;// su dung cho truong hop heartSamll cham dat thi se khong bi dao dong qua lai quanh truc x
						}

					}
				}
				
				
				_listHeartSmall[i]->Update(time);
			}

	}
	//ket thuc truong hop qua va cham voi gach

	//bat dau qua va cham voi simon

	for (int i = 0; i < _listHeartSmall.size(); i++)
	{
		if (_listHeartSmall[i]->hienthi)
		{
			if (AABB(_listHeartSmall[i]->boxItem(), simonBox))
			{
				Sound::GetInstance()->Play(COLLECT_ITEM);
				_listHeartSmall[i]->hienthi = false;
				return 1;
			}
		}

	}

	//ket thuc qua va cham voi simon

	return 0;

}
void BoneDragons::RenderQua(float x, float y)
{
	for (int i = 0; i < _listHeartSmall.size(); i++)
	{
		_listHeartSmall[i]->Render(x,y);
	}
}
void BoneDragons::Render(float x, float y)
{
	if (MangSong > 0)
	{
		D3DXVECTOR2 view;
		view.x = x;
		view.y = y;
		camera->setViewPort(view);
		D3DXVECTOR2 _pos = camera->Transform(this->_x, this->_y);
		G_SpriteHandler->Begin(D3DXSPRITE_SORT_DEPTH_FRONTTOBACK | D3DXSPRITE_ALPHABLEND);

		sprite->Draw(_pos.x, _pos.y);
		G_SpriteHandler->End();

		this->dragon[0]->Render(x, y);
		this->dragon[1]->Render(x, y);
		this->dragon[2]->Render(x, y);
		this->dragon[3]->Render(x, y);
		this->dragon[4]->Render(x, y);
		this->dragon[5]->Render(x, y);

		for (int i = 0; i < _lisluabanratuquai.size(); i++)
		{
			_lisluabanratuquai[i]->Render(x, y);
		}
	}
	

	if (MangSong <= 0 && hienthiqua == 1)
	{
		RenderQua(x, y);
	}

	_luadanhquai->Render(x, y);
	

}
int BoneDragons::Update(float time, float simon_x, float simon_y, vector <GameObject*> ListObjects, Box simonBox, float viewportx)
{
	if (viewportx + G_ScreenWidth  > _x)
	{
		if (!move)
		{
			timerSprite += time;
			if (timerSprite > 0.5)
			{
				move = true;
				timerSprite -= 0.5;
			}
			_luadanhquai->_x = this->_x - 10;
			_luadanhquai->_y = this->_y - 10;
			_luadanhquai->hienthi = true;
		}
		_luadanhquai->Update(time);

		timerBan += time;
		if (timerBan > 4)
		{
			LuaBanRaTuQuai*_luabanratuquai = new LuaBanRaTuQuai(this->_x, this->_y, simon_x, simon_y);
			_lisluabanratuquai.push_back(_luabanratuquai);
			timerBan -= 4;
		}

		for (int i = 0; i < _lisluabanratuquai.size(); i++)
		{
			_lisluabanratuquai[i]->Update(time);
		}


		if (move)
		{
			if (this->_x > maxleft)
			{
				this->_x -= 95 * time;
				this->dragon[0]->_x -= 80 * time;
				this->dragon[1]->_x -= 68 * time;
				this->dragon[2]->_x -= 52 * time;
				this->dragon[3]->_x -= 38 * time;
				this->dragon[4]->_x -= 25 * time;
				this->dragon[5]->_x -= 10 * time;
			}

			if (this->this_xuong == 0 && this->_x <= maxleft)
			{
				this->_y -= 100 * time;
				this->dragon[0]->_y -= 80 * time;
				this->dragon[1]->_y -= 60 * time;
				this->dragon[2]->_y -= 40 * time;
				this->dragon[3]->_y -= 20 * time;
				this->dragon[4]->_y -= 10 * time;
				if (this->_y < 120)
				{
					this_xuong = 1;
				}
			}

			if (this_xuong == 1)
			{
				this->_y += 100 * time;
				this->dragon[0]->_y += 80 * time;
				this->dragon[1]->_y += 60 * time;
				this->dragon[2]->_y += 40 * time;
				this->dragon[3]->_y += 20 * time;
				this->dragon[4]->_y += 10 * time;
				if (this->_y > maxtop)
				{
					this_xuong = 2;
					this->xuong = true;
					this->len = false;
					this->dragon[0]->giuydragon = this->dragon[0]->_y;
					this->dragon[1]->giuydragon = this->dragon[1]->_y;
					this->dragon[2]->giuydragon = this->dragon[2]->_y;
					this->dragon[3]->giuydragon = this->dragon[3]->_y;
					this->dragon[4]->giuydragon = this->dragon[4]->_y;
				}
			}


			if (this_xuong == 2)
			{

				if (this->xuong)
				{
					if (this->_y >= this->_ybandau)
						this->_y -= 100 * time;
				}

				if (this->xuong&& this->_y > this->_ybandau)
				{
					if (this->_y < this->maxtop - 35)
					{
						this->dragon[0]->_y -= 110 * time;
					}
					if (this->_y < this->maxtop - 60)
					{
						this->dragon[1]->_y -= 110 * time;
					}
				}

				if (this->xuong&& this->_y <= this->_ybandau)
				{
					if (this->dragon[0]->_y > this->dragon[0]->minydragon)
					{
						this->dragon[0]->_y -= 110 * time;
					}
					if (this->dragon[1]->_y > this->dragon[1]->minydragon)
					{
						this->dragon[1]->_y -= 110 * time;
					}
					if (this->dragon[2]->_y > this->dragon[2]->minydragon)
					{
						this->dragon[2]->_y -= 110 * time;
					}

					if (this->dragon[2]->_y < this->dragon[2]->giuydragon - 20)
					{
						if (this->dragon[3]->_y > this->dragon[3]->minydragon)
						{
							this->dragon[3]->_y -= 110 * time;
						}
						if (this->dragon[3]->_y <= this->dragon[3]->minydragon)
						{
							if (this->dragon[4]->_y > this->dragon[4]->minydragon)
							{
								this->dragon[4]->_y -= 110 * time;
							}
							else
							{
								this->len = true;
								this->xuong = false;
							}
						}
					}
				}

				if (this->len)
				{
					if (this->_y < this->maxtop)
					{
						this->_y += 110 * time;
					}

					if (this->_y > 120 + 20)
					{
						if (this->dragon[0]->_y < this->dragon[0]->giuydragon)
						{
							this->dragon[0]->_y += 110 * time;
						}
					}
					if (this->dragon[0]->_y > this->dragon[0]->minydragon + 20)
					{
						if (this->dragon[1]->_y < this->dragon[1]->giuydragon)
						{
							this->dragon[1]->_y += 110 * time;
						}
					}
					if (this->dragon[1]->_y > this->dragon[1]->minydragon + 20)
					{
						if (this->dragon[2]->_y < this->dragon[2]->giuydragon)
						{
							this->dragon[2]->_y += 110 * time;
						}
					}
					if (this->dragon[2]->_y >= this->dragon[2]->giuydragon - 20)
					{
						if (this->dragon[3]->_y < this->dragon[3]->giuydragon)
						{
							this->dragon[3]->_y += 110 * time;
						}
						if (this->dragon[3]->_y >= this->dragon[3]->giuydragon)
						{
							if (this->dragon[4]->_y < this->dragon[4]->giuydragon)
							{
								this->dragon[4]->_y += 110 * time;
							}
						}
					}

					if (this->dragon[0]->_y >= this->dragon[0]->giuydragon&&this->dragon[1]->_y >= this->dragon[1]->giuydragon && this->dragon[2]->_y >= this->dragon[2]->giuydragon && this->dragon[3]->_y >= this->dragon[3]->giuydragon && this->dragon[4]->_y >= this->dragon[4]->giuydragon)
					{
						this->xuong = true;
						this->len = false;
					}


				}
			}


		}


		if (MangSong <= 0 && hienthiqua == 0)
		{
			this->die = true;
			chet += 1;
			GetToaDoQua();
		}

		if (MangSong <= 0 && hienthiqua == 1)
		{
			return UpdateQua(time, ListObjects, simonBox);
		}
	}
	
	return 0;

}



Box BoneDragons::BoxBonDragons()
{
	return Box(this->_x - this->_width / 2, this->_y - this->_height / 2, this->_x + this->_width / 2, this->_y + this->_height / 2, 0, 0);
}

BoneDragons::~BoneDragons()
{
	delete[] dragon;

	for (int i = 0; i < _lisluabanratuquai.size(); i++)
	{
		if (_lisluabanratuquai[i])
		{
			delete _lisluabanratuquai[i];
			_lisluabanratuquai[i] = NULL;
		}
	}
	_lisluabanratuquai.clear();

	if (texture != NULL)
		delete texture;
	if (sprite != NULL)
		delete sprite;
	if (camera != NULL)
		delete camera;
	if (_luadanhquai != NULL)
		delete _luadanhquai;
}
