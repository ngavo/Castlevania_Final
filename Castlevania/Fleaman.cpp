#include "Fleaman.h"
#include "SweptAABB.h"
#include <cstdlib>
#include <ctime>
#define VX  60;
Fleaman::Fleaman()
{
}

void Fleaman::Init(float x, float y, int width, int height)
{
	_x = x;
	_y = y;
	_width = width;
	_height = height;
	texture = new GTexture("Resources/enemy/Fleaman.bmp", 2, 1, 2);
	sprite = new GSprite(texture, 0, 1, 2);
	camera = new GCamera();
	sprite->SelectIndex(0);
	vx = -50;
}
void Fleaman::Render(float x, float y)
{
	D3DXVECTOR2 view;
	view.x = x;
	view.y = y;
	camera->setViewPort(view);
	D3DXVECTOR2 _pos = camera->Transform(this->_x, this->_y);
	G_SpriteHandler->Begin(D3DXSPRITE_SORT_DEPTH_FRONTTOBACK | D3DXSPRITE_ALPHABLEND);
	if (!flat)
		sprite->Draw(_pos.x, _pos.y);
	else
		sprite->DrawFlipX(_pos.x, _pos.y);
	G_SpriteHandler->End();


	for (int i = 0; i < listLuaBanRaTuQuai.size(); i++)
	{
		listLuaBanRaTuQuai[i]->Render(x,y);
	}

}
void Fleaman::Update(float timeu, float postxFrankenstein, float postyFrankenstein, vector<GameObject*> _listObjectQuadtree, float posxSimon, float posySimon)
{

	if (bidanh)
	{

		timerBiDanh += timeu;
		if (timerBiDanh > 2)
		{
			bidanh = false;
			timerBiDanh -= 2;
			trungEmeny = 0;
		}
		
	}

	if (!bidanh)
	{
		timeTrenFrankenstein += timeu;
		if (timeTrenFrankenstein > 3)
		{

			if (this->_x <= left)
			{
				this->vx = VX;
				srand(time(NULL));

				this->vy = 100;
			}
			if (this->_x >= right)
			{
				this->vx = -50;
				srand(time(NULL));

				this->vy = 100;
			}

			this->vy -= 200 * timeu;
			this->_x += this->vx*timeu;
			if (!IsTouchGround)
			{
				timerSprite += timeu;
				if (timerSprite > 0.15)
				{
					sprite->SelectIndex(0);
					timerSprite -= 0.15;
				}
			}

			timerBan += timeu;
			if (timerBan > 3)
			{
				LuaBanRaTuQuai* _luabanratuqua = new LuaBanRaTuQuai(this->_x, this->_y, posxSimon, posySimon);
				if (this->_x >= posxSimon)
				{
					_luabanratuqua->vdan = -150;
				}
				else
				{
					_luabanratuqua->vdan = 150;
				}
				listLuaBanRaTuQuai.push_back(_luabanratuqua);
				timerBan -= 3;
			}
		}
		else
		{
			this->_x = postxFrankenstein + 5;
			timerSprite += timeu;
			if (timerSprite > 0.15)
			{
				sprite->Next();
				timerSprite -= 0.15;
			}
		}

		if (vx < 0)
		{
			flat = false;
		}
		else
		{
			flat = true;
		}

		this->_y += this->vy*timeu;

		UpdateVaChamGach(timeu, _listObjectQuadtree);
	}
		





		for (int i = 0; i < listLuaBanRaTuQuai.size(); i++)
		{
			listLuaBanRaTuQuai[i]->Update(timeu);
		}

	
	

	
}

void Fleaman::UpdateVaChamGach( float timevc,vector<GameObject*> _listObjectQuadtree)
{
	for (int j = 0; j < _listObjectQuadtree.size(); j++)
	{
		Box boxFishMan(this->_x - this->_width / 2, this->_y - this->_height / 2, this->_x + this->_width / 2, this->_y + this->_height / 2, 0, this->vy);
		Box box(_listObjectQuadtree[j]->_x - _listObjectQuadtree[j]->_width / 2, _listObjectQuadtree[j]->_y - _listObjectQuadtree[j]->_height / 2, _listObjectQuadtree[j]->_x + _listObjectQuadtree[j]->_width / 2, _listObjectQuadtree[j]->_y + _listObjectQuadtree[j]->_height / 2, 0, 0);
		Box broadphasebox = GetSweptBroadphaseBox(boxFishMan, timevc);

		if (_listObjectQuadtree[j]->GetType() == 12)
		{
			
				if (AABB(broadphasebox, box))
				{
					if (AABB(boxFishMan, box))//long nhay ngay tu dau
					{
						this->_y = _listObjectQuadtree[j]->_y + _listObjectQuadtree[j]->_height / 2 + this->_height / 2 + 0.4f;
						this->IsTouchGround = true;
						this->sprite->SelectIndex(1);
						this->vy = 50;
					}

					float normalx, normaly;
					float timeCollision = SweptAABB(boxFishMan, box, normalx, normaly, timevc);
					if (timeCollision < 1.0f)
					{
						if (normaly == 1.0f)
						{
							this->_y = _listObjectQuadtree[j]->_y + _listObjectQuadtree[j]->_height / 2 + this->_height / 2 + 0.4f;
							this->IsTouchGround = true;

							srand(time(NULL));
							float a = rand() % (300 - 200 + 1) + 200;
							this->sprite->SelectIndex(1);
							this->vy = a;
						}
					}


				}

		}

	}
}

Box Fleaman::boxFleaman()
{
	return Box(this->_x - this->_width / 2, this->_y - this->_height / 2, this->_x + this->_width / 2, this->_y + this->_height / 2, 0, 0);
}

Fleaman::~Fleaman()
{
}
