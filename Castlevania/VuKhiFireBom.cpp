#include "VuKhiFireBom.h"
#include "BoneDragons.h"
#include "Frankenstein.h"
#include "Sound.h"


VuKhiFireBom::VuKhiFireBom(int type, float x, float y, int wight, int height, char*path, int columm, int row, int count, int start, int end, int selectedIndex): ObjectVuKhi(type, x,  y, wight, height, path, columm, row, count, start, end, selectedIndex)
{
	lucnem.x = 50;
	lucnem.y = 50;
	chamgach = false;
	_luaCuaFireBon = new LuaCuaFireBom(toado.x, toado.x);
}

void VuKhiFireBom::Update(float _DeltaTime, vector<GameObject*> _listObjectQuadtree, vector<Enemy*> _listEnemy, int &score)
{
	if (_hienthi)
	{
		toado.x += lucnem.x*_DeltaTime;
		lucnem.y -= 100 * _DeltaTime;
		toado.y += lucnem.y*_DeltaTime;
		for (int i = 0; i < _listObjectQuadtree.size(); i++)
		{
			if (_listObjectQuadtree[i]->GetType() == 12)
			{
				Box quadtreeBox(_listObjectQuadtree[i]->_x - _listObjectQuadtree[i]->_width / 2, _listObjectQuadtree[i]->_y - _listObjectQuadtree[i]->_height / 2, _listObjectQuadtree[i]->_x + _listObjectQuadtree[i]->_width / 2, _listObjectQuadtree[i]->_y + _listObjectQuadtree[i]->_height / 2, 0, 0);
				if (AABB(this->BoxObjectVuKhi(), quadtreeBox))
				{

					chamgach = true;
					_hienthi = false;
					lucnem.x = 0;
					lucnem.y = 0;
					_luaCuaFireBon->_x = toado.x;
					_luaCuaFireBon->_y = toado.y;
				}

			}
		}
	}

	if (toado.y < 50)
	{
		_hienthi = false;
	}

	if (chamgach)
	{
		
		timerSpriteForLua += _DeltaTime;
		if (timerSpriteForLua >= 1.5)
		{
				Sound::GetInstance()->Play(eSoundID::HOLY_WATER);
				chamgach = false;
				timerSpriteForLua -= 1.5;
				trungEnemy = 0;
		}
		else
		{
			_luaCuaFireBon->Update(_DeltaTime);
			LuaVaChamEmeny(_listEnemy, score);
		}
		
		
	}
}

void VuKhiFireBom::LuaVaChamEmeny(vector<Enemy*> _listEnemy, int &score)
{
	for (int i = 0; i < _listEnemy.size(); i++)
	{
		switch (_listEnemy[i]->_tyle)
		{
		case eEnemy::BoneDragon:
			if (AABB(_luaCuaFireBon->boxItem(), ((BoneDragons*)_listEnemy[i])->BoxBonDragons()))
			{
				if (trungEnemy == 0)
				{
					((BoneDragons*)_listEnemy[i])->MangSong -= 30;
					((BoneDragons*)_listEnemy[i])->move = false;
					trungEnemy++;
				}

			}
			break;
		case eEnemy::TypeFrankenstein:
			if (AABB(_luaCuaFireBon->boxItem(), ((Frankenstein*)_listEnemy[i])->boxFrankenstein()))
			{
				if (trungEnemy == 0)
				{
					*(((Frankenstein*)_listEnemy[i])->hpBos) -= 2;
					((Frankenstein*)_listEnemy[i])->bidanh = true;
					if (((Frankenstein*)_listEnemy[i])->_flat)
					{
						((Frankenstein*)_listEnemy[i])->vx = -50;
					}
					else
					{
						((Frankenstein*)_listEnemy[i])->vx = 50;
					}

					trungEnemy++;
				}
				

			}
			break;
		case eEnemy::TypeFishMan:
			if (1)
			{
				Box fishmanBox(_listEnemy[i]->_x - 16, _listEnemy[i]->_y - 30, _listEnemy[i]->_x + 16, _listEnemy[i]->_y + 30, 0, 0);
				if (AABB(fishmanBox, _luaCuaFireBon->boxItem()))
				{
					if (trungEnemy == 0)
					{
						_listEnemy[i]->hienthi = false;
						_listEnemy[i]->die = true;
						score += 300;
						trungEnemy++;
					}
				}
			}
			
			break;
		default:
			break;
		}
		
	}
}

void VuKhiFireBom::Render(float x, float y)
{
	if (_hienthi)
	{
		D3DXVECTOR2 view;
		view.x = x;
		view.y = y;
		_camera->setViewPort(view);
		D3DXVECTOR2 _pos = _camera->Transform(toado.x, toado.y);
		G_SpriteHandler->Begin(D3DXSPRITE_SORT_DEPTH_FRONTTOBACK | D3DXSPRITE_ALPHABLEND);

		_sprite->Draw(_pos.x, _pos.y);
		G_SpriteHandler->End();
	}

	if (chamgach)
	{
		_luaCuaFireBon->Render(x, y);
	}
	
}

VuKhiFireBom::~VuKhiFireBom()
{
}
