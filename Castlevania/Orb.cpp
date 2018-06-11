#include "Orb.h"



Orb::Orb(float x, float y, int width, int height)
{
	_x = x;
	_y = y;
	_width = width;
	_height = height;
	this->texture = new GTexture("Resources/item/bonus.bmp", 6, 4, 22);
	sprite = new GSprite(this->texture, 16, 17, 2);
	sprite->SelectIndex(16);
	this->camera = new  GCamera();
	vy = -400;
}

void Orb::Update(float time, vector<GameObject*>_listObjectQuadtree, Box boxSimon, int &simonwin)
{
	if (simonwin == 0)
	{
		hienthi = true;
	}
	else
	{
		hienthi = false;
	}
	timerSprite += time;
	if (timerSprite > 0.2)
	{
		timerSprite -= 0.2;
		sprite->Next();
	}

	this->_y += this->vy*time;
	UpdateVaChamGach(time, _listObjectQuadtree);

	if (AABB(boxSimon, BoxOrb()))
	{
		if (simonwin == 0)
		{
			simonwin = 1;
		}
	}

}

void Orb::UpdateVaChamGach(float time, vector<GameObject*>_listObjectQuadtree)
{
	for (int j = 0; j < _listObjectQuadtree.size(); j++)
	{
		Box boxFishMan(this->_x - this->_width / 2, this->_y - this->_height / 2, this->_x + this->_width / 2, this->_y + this->_height / 2, 0, this->vy);
		Box box(_listObjectQuadtree[j]->_x - _listObjectQuadtree[j]->_width / 2, _listObjectQuadtree[j]->_y - _listObjectQuadtree[j]->_height / 2, _listObjectQuadtree[j]->_x + _listObjectQuadtree[j]->_width / 2, _listObjectQuadtree[j]->_y + _listObjectQuadtree[j]->_height / 2, 0, 0);
		Box broadphasebox = GetSweptBroadphaseBox(boxFishMan, time);

		if (_listObjectQuadtree[j]->GetType() == 12)
		{

			if (AABB(broadphasebox, box))
			{
				if (AABB(boxFishMan, box))//long nhay ngay tu dau
				{
					this->_y = _listObjectQuadtree[j]->_y + _listObjectQuadtree[j]->_height / 2 + this->_height / 2 + 0.4f;
					this->IsTouchGround = true;
					vy = 0;
				}

				float normalx, normaly;
				float timeCollision = SweptAABB(boxFishMan, box, normalx, normaly, time);
				if (timeCollision < 1.0f)
				{
					if (normaly == 1.0f)
					{
						this->_y = _listObjectQuadtree[j]->_y + _listObjectQuadtree[j]->_height / 2 + this->_height / 2 + 0.4f;
						this->IsTouchGround = true;
						vy = 0;
					}
				}


			}

		}

	}
}

void Orb::Render(float x, float y)
{
	if (hienthi)
	{
		D3DXVECTOR2 view;
		view.x = x;
		view.y = y;
		camera->setViewPort(view);
		D3DXVECTOR2 _pos = camera->Transform(this->_x, this->_y);
		G_SpriteHandler->Begin(D3DXSPRITE_SORT_DEPTH_FRONTTOBACK | D3DXSPRITE_ALPHABLEND);

		sprite->Draw(_pos.x, _pos.y);
		G_SpriteHandler->End();
	}
		
	


}

Box Orb::BoxOrb()
{
	return Box(_x - 10, _y - 10, _x + 10, _y + 10, 0, 0);
}

Orb::~Orb()
{
	if (texture != NULL)
	{
		delete texture;
	}

	if (sprite != NULL)
	{
		delete sprite;
	}

	if (camera != NULL)
	{
		delete camera;
	}
}
