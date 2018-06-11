#include "Frankenstein.h"

#define VX 50;


Frankenstein::Frankenstein()
{
	_fleamam = new Fleaman();
	_luadanhquai = new LuaDanhQuai(0,0,0,0);

	_fireFleamDie = new fire(0, 0, 0, 0);

	_orb = new Orb(1750, 550, 32, 32);

	LuaCuaFireBom*_lua1 = new LuaCuaFireBom(0, 0);
	LuaCuaFireBom*_lua2 = new LuaCuaFireBom(0, 0);
	LuaCuaFireBom*_lua3 = new LuaCuaFireBom(0, 0);
	LuaCuaFireBom*_lua4 = new LuaCuaFireBom(0, 0);
	LuaCuaFireBom*_lua5 = new LuaCuaFireBom(0, 0);
	LuaCuaFireBom*_lua6 = new LuaCuaFireBom(0, 0);
	_listLuaDie.push_back(_lua1);
	_listLuaDie.push_back(_lua2);
	_listLuaDie.push_back(_lua3);
	_listLuaDie.push_back(_lua4);
	_listLuaDie.push_back(_lua5);
	_listLuaDie.push_back(_lua6);

}

void Frankenstein::Init(int tyle, float x, float y, int width, int height)
{
	_x = x;
	_y = y;
	_width = 32;
	_height = 96;
	texture = new GTexture("Resources/enemy/Frankenstein.bmp", 3, 1, 3);
	sprite = new GSprite(texture, 0, 2, 2);
	camera = new GCamera();
	this->_tyle = tyle;
	vx = -VX;
	vy = -50;

	_fleamam->Init(x + 64, y + 46, 32, 32);
}

void Frankenstein::Render(float x, float y)
{
	if (this->hienthi && !this->die)
	{
		_fleamam->Render(x, y);
		D3DXVECTOR2 view;
		view.x = x;
		view.y = y;
		camera->setViewPort(view);
		D3DXVECTOR2 _pos = camera->Transform(this->_x, this->_y);
		G_SpriteHandler->Begin(D3DXSPRITE_SORT_DEPTH_FRONTTOBACK | D3DXSPRITE_ALPHABLEND);
		if(!_flat)
		sprite->Draw(_pos.x, _pos.y);
		else
			sprite->DrawFlipX(_pos.x, _pos.y);
		G_SpriteHandler->End();

		_luadanhquai->Render(x, y);
		
	}

	if (die)
	{
		if (hienthilua && !hienthiqua)
		{
			RenderLua(x, y);
		}

		if (!hienthilua && hienthiqua)
		{
			RenderQua(x, y);
		}
	}

	

}
void Frankenstein::Update(float time, vector<GameObject*>_listObjectQuadtree, boolean simonflat, float posxSimon, float posySimon, Box boxSimon, int &simonwin)
{
	if (!die)
	{
		if (this->_x > posxSimon && !this->bidanh)
		{
			this->vx = -VX;
			_flat = false;
		}

		if (this->_x < posxSimon && !this->bidanh)
		{
			this->vx = VX;
			_flat = true;
		}

		if (this->bidanh)
		{
			_luadanhquai->hienthi = true;
			_luadanhquai->_x = _x;
			_luadanhquai->_y = _y;
			_luadanhquai->Update(time);
			timerBiDanh += time;
			if (timerBiDanh > 0.7)
			{
				this->bidanh = false;
				timerBiDanh -= 0.7;
			}
		}


		this->_x += this->vx*time;

		timerSprite += time;
		if (timerSprite > 0.6)
		{
			sprite->Next();
			timerSprite -= 0.6;
		}
		if (this->_x <= left)
		{
			this->vx = VX;
		}
		if (this->_x >= right)
		{
			this->vx = -VX;
		}

		_fleamam->Update(time, _x, _y, _listObjectQuadtree, posxSimon, posySimon);
	}
	else
	{
		if (hienthilua && !hienthiqua)
		{
			UpdateLua(time);
		}
		if (!hienthilua && hienthiqua)
		{
			UpdateQua(time, _listObjectQuadtree, boxSimon,simonwin);
		}
	}
	
}

void Frankenstein::UpdateQua(float time, vector<GameObject*>_listObjectQuadtree, Box boxSimon, int &simonwin)
{
	_orb->Update(time, _listObjectQuadtree, boxSimon, simonwin);
}
void Frankenstein::RenderQua(float x, float y)
{
	_orb->Render(x, y);
}

void Frankenstein::UpdateLua(float time)
{
	timerLua += time;
	if (timerLua > 2)
	{
		hienthiqua = true;
		hienthilua = false;
	}
	else
	{
		_listLuaDie[0]->_x = _x;
		_listLuaDie[0]->_y = _y;

		_listLuaDie[1]->_x = _x+32;
		_listLuaDie[1]->_y = _y;

		_listLuaDie[2]->_x = _x+64;
		_listLuaDie[2]->_y = _y;


		_listLuaDie[3]->_x = _x;
		_listLuaDie[3]->_y = _y+32;

		_listLuaDie[4]->_x = _x+32;
		_listLuaDie[4]->_y = _y+32;

		_listLuaDie[5]->_x = _x+64;
		_listLuaDie[5]->_y = _y+32;
		 
		_fireFleamDie->_x = this->_fleamam->_x;
		_fireFleamDie->_y = this->_fleamam->_y;

		_fireFleamDie->Update(time);

		for (int i = 0; i < _listLuaDie.size(); i++)
		{
			_listLuaDie[i]->Update(time);
		}
	}

}
void Frankenstein::RenderLua(float x, float y)
{
	for (int i = 0; i < _listLuaDie.size(); i++)
	{
		_listLuaDie[i]->Render(x, y);
	}
	_fireFleamDie->Render(x,y);
}

 Box Frankenstein::boxFrankenstein()
{
	 return Box(this->_x - this->_width / 2, this->_y - this->_height / 2, this->_x + this->_width / 2, this->_y + this->_height / 2,0,0);
}



Frankenstein::~Frankenstein()
{
	if (_fleamam != NULL)
	{
		delete _fleamam;
	}

	if (_luadanhquai != NULL)
	{
		delete _luadanhquai;
	}

	for (int i = 0; i < _listLuaDie.size(); i++)
	{
		if (_listLuaDie[i] != NULL)
		{
			delete _listLuaDie[i];
			_listLuaDie[i] = NULL;
		}
			
	}

	_listLuaDie.clear();


	if (_fireFleamDie != NULL)
	{
		delete _fireFleamDie;
	}
}
