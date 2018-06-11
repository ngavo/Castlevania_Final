#include "VuKhiDanger.h"
#include "Frankenstein.h"
#include "BoneDragons.h"
#include "FishMan.h"


VuKhiDanger::VuKhiDanger(int type, float x, float y, int wight, int height, char*path, int columm, int row, int count, int start, int end, int selectedIndex) : ObjectVuKhi(type, x, y, wight, height, path, columm, row, count, start, end, selectedIndex)
{
	lucnem.x = 100;
}

void VuKhiDanger::Update(float _DeltaTime, vector<GameObject*> _listObjectQuadtree, vector<Enemy*> _listEnemy,float cameraleft, float cameraright)
{
	if (lucnem.x < 0)
	{
		flat = true;
	}
	else
	{
		flat = false;
	}
	if (_hienthi)
	{
		toado.x += lucnem.x*_DeltaTime;
		UpdateVaChamEnemy(_DeltaTime, _listEnemy);
	}

	if (toado.x > cameraright)
	{
		_hienthi = false;
		trungEnemy = 0;
	}

	if (toado.x < cameraleft)
	{
		_hienthi = false;
		trungEnemy = 0;
	}
}


void VuKhiDanger::UpdateVaChamEnemy(float _DeltaTime, vector<Enemy*> _listEnemy)
{
	for (int i = 0; i < _listEnemy.size(); i++)
	{
		switch (_listEnemy[i]->_tyle)
		{
		case eEnemy::BoneDragon:
			if (AABB(BoxObjectVuKhi(), ((BoneDragons*)_listEnemy[i])->BoxBonDragons()))
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
			if (AABB(BoxObjectVuKhi(), ((Frankenstein*)_listEnemy[i])->boxFrankenstein()))
			{
				if (trungEnemy == 0)
				{
					Sound::GetInstance()->Play(eSoundID::KNIFE);
					*(((Frankenstein*)_listEnemy[i])->hpBos) -= 1;
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

				//kiem tra danh trung Fleman
				if (((Frankenstein*)_listEnemy[i])->_fleamam->trungEmeny == 0)
				{
					if (AABB(BoxObjectVuKhi(), ((Frankenstein*)_listEnemy[i])->_fleamam->boxFleaman()))
					{
						((Frankenstein*)_listEnemy[i])->_fleamam->bidanh = true;
						((Frankenstein*)_listEnemy[i])->_fleamam->trungEmeny++;
					}
				}


			}
			break;
		default:
			break;
		}

	}
}

void VuKhiDanger::Render(float x, float y)
{
	if (_hienthi)
	{
		D3DXVECTOR2 view;
		view.x = x;
		view.y = y;
		_camera->setViewPort(view);
		D3DXVECTOR2 _pos = _camera->Transform(toado.x, toado.y);
		G_SpriteHandler->Begin(D3DXSPRITE_SORT_DEPTH_FRONTTOBACK | D3DXSPRITE_ALPHABLEND);

		if (!flat)
			_sprite->Draw(_pos.x, _pos.y);
		else
			_sprite->DrawFlipX(_pos.x, _pos.y);
		G_SpriteHandler->End();
	}
}




VuKhiDanger::~VuKhiDanger()
{
}
