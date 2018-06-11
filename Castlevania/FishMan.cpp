#include "FishMan.h"
#include "SweptAABB.h"


FishMan::FishMan()
{
}
void FishMan::Init(int id,int tyle, int flip, float x, float y, int width, int height)
{
	_x = x;
	_y = y;
	_width = 34;
	_height = 62;
	this->flip = flip;
	texture = new GTexture("Resources/enemy/creep_right.bmp", 6, 5, 29);
	sprite = new GSprite(texture, 12, 13, 2);
	camera = new GCamera();
	sprite->SelectIndex(12);
	xuong = false;
	len = true;
	this->_tyle = tyle;
	this->id = id;
	vx = 27;
	vy = 830;
	_water1 = new Water(_x,250);
	_water2 = new Water(_x, 190);
	_fire = new fire(_x, _y, 32, 32);

}
void FishMan::Render(float x, float y)
{
	if (this->hienthi && !this->die)
	{
		if (this->_y > 100)
		{
			D3DXVECTOR2 view;
			view.x = x;
			view.y = y;
			camera->setViewPort(view);
			D3DXVECTOR2 _pos = camera->Transform(this->_x, this->_y);
			G_SpriteHandler->Begin(D3DXSPRITE_SORT_DEPTH_FRONTTOBACK | D3DXSPRITE_ALPHABLEND);
			if (this->flip == 1)
			{
				sprite->DrawFlipX(_pos.x, _pos.y);
			}
			else
			{
				sprite->Draw(_pos.x, _pos.y);
			}

			G_SpriteHandler->End();


		}

		if (this->_y > 100 && this->vy > 0)
		{
			_water1->Render(x, y);
		}

		if (this->_y < 100 && this->vy < 0)
		{
			if (_water2->_y1 > 100)
			{
				_water2->Render(x, y);
			}

		}
	}

	if (die)
	{
		RenderFire(x, y);
	}
	
	
}
void FishMan::Update(float time, vector<GameObject*>_listObjectQuadtree)
{
	if (!die)
	{
		if (id == 97)
		{
			if (this->_y > 300 && this->_y < 395)
			{
				this->IsTouchGround = true;
				if (this->_x < 2000)
				{

					this->vx = 27;
					this->flip = 0;
					this->fishmanid97 = 1;
				}
				if (this->fishmanid97)
				{
					if (this->_x > 2010)
					{
						this->IsTouchGround = false;
					}
				}
			}
		}
		if (id == 96)
		{
			if (this->_y > 300 && this->_y < 395)
			{
				this->IsTouchGround = true;
				if (this->_x > 1800)
				{

					this->vx = -27;
					this->flip = 1;
					this->fishmanid96 = 1;
				}
				if (this->fishmanid96)
				{
					if (this->_x < 1680)
					{
						this->IsTouchGround = false;
					}
				}
			}
		}
		if (IsTouchGround)
		{
			this->vy = 0;
		}
		else
		{

			this->vy -= 1000 * time;
			this->_y += this->vy*time;
		}

		if (this->flip == 1)
		{
			vx = -27;
		}
		if (IsTouchGround)
		{
			this->_x += vx * time;
			timerSprite += time;
			if (timerSprite > 0.15)
			{
				sprite->Next();
				timerSprite -= 0.15;
			}

		}

		if (this->_y > 100 && this->vy >0)
		{
			this->amthanhlucnhaylen += 1;
			if (this->amthanhlucnhaylen == 1)
			{
				Sound::GetInstance()->Play(FALLING_DOWN_WATER_SUFACE);
			}
			_water1->Update(time);

		}

		if (this->_y < 100 && this->vy < 0)
		{
			this->amthanhlucnhayxuong += 1;
			if (this->amthanhlucnhayxuong == 1)
			{
				Sound::GetInstance()->Play(FALLING_DOWN_WATER_SUFACE);
			}
			_water2->Update(time);
		}

		this->_fire->_x = this->_x;
		this->_fire->_y = this->_y;

	}
	


}

void FishMan::FishManVaChamGach(float time,vector<GameObject*>_listObjectQuadtree)
{
	for (int j = 0; j < _listObjectQuadtree.size(); j++)
	{
		Box boxFishMan(this->_x - this->_width / 2, this->_y - this->_height / 2, this->_x + this->_width / 2, this->_y + this->_height / 2, 0, this->vy);
		Box box(_listObjectQuadtree[j]->_x - _listObjectQuadtree[j]->_width / 2, _listObjectQuadtree[j]->_y - _listObjectQuadtree[j]->_height / 2, _listObjectQuadtree[j]->_x + _listObjectQuadtree[j]->_width / 2, _listObjectQuadtree[j]->_y + _listObjectQuadtree[j]->_height / 2, 0, 0);
		Box broadphasebox = GetSweptBroadphaseBox(boxFishMan, time);

		if (_listObjectQuadtree[j]->GetType() == 12)
		{
			if (this->vy < 0)
			{
				if (AABB(broadphasebox, box))
				{
					if (AABB(boxFishMan, box))//long nhay ngay tu dau
					{
						this->_y = _listObjectQuadtree[j]->_y + _listObjectQuadtree[j]->_height / 2 + this->_height / 2 + 0.4f;
						this->IsTouchGround = true;
					}

					float normalx, normaly;
					float timeCollision = SweptAABB(boxFishMan, box, normalx, normaly, time);
					if (timeCollision < 1.0f)
					{
						if (normaly == 1.0f)
						{
							this->_y = _listObjectQuadtree[j]->_y + _listObjectQuadtree[j]->_height / 2 + this->_height / 2 + 0.4f;
							this->IsTouchGround = true;
						}
					}


				}

			}


		}




	}
}

void FishMan::UpdateFire(float time)
{
	_fire->Update(time);
}
void FishMan::RenderFire(float x, float y)
{

	_fire->Render(x, y);
}
bool FishMan::Check(float _posxSimon, int _id)
{
	switch (_id)
	{
	case 86:
		if (_posxSimon > _x - 200)
			return true;
		else
			return false;
	case 92:
		if (_posxSimon > _x + 100)
			return true;
		else
			return false;
	case 87:
		if (_posxSimon > _x + 150)
			return true;
		else
			return false;
	case 93:
		if (_posxSimon > _x + 50)
			return true;
		else
		{
			return false;
		}
	case 88:
		if (_posxSimon > _x + 100)
			return true;
		else
			return false;
	case 94:
		if (_posxSimon > _x + 100)
			return true;
		else
		{
			return false;
		}
	case 95:
		if (_posxSimon > 1350)
			return true;
		else
			return false;
	case 89:
		if (_posxSimon > _x - 70)
		{
			return true;
		}
		else
		{
			return false;
		}
	case 96:
		if (_posxSimon > _x + 70)
		{
			return true;
		}
		else
		{
			return  false;
		}
	case 97:
		if (_posxSimon > _x + 70)
		{
			return true;
		}
		else
		{
			return false;
		}
	case 98:
		if (_posxSimon > _x + 100)
		{
			return true;
		}
		else
		{
			return false;
		}
	case 90:
		if (_posxSimon > _x + 100)
		{
			return true;
		}
		else
		{
			return false;
		}
	case 99:
		if (_posxSimon > _x + 100)
		{
			return true;
		}
		else
		{
			return false;
		}
	default:
		return false;
		break;
	}
}

FishMan::~FishMan()
{
	if (texture != NULL)
		delete texture;
	if (sprite != NULL)
		delete sprite;

	if (camera != NULL)
		delete camera;

	if (_water1 != NULL)
		delete _water1;
	if (_water2 != NULL)
		delete _water2;
}
