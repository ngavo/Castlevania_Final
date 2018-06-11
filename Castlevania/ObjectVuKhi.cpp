#include "ObjectVuKhi.h"



ObjectVuKhi::ObjectVuKhi(int type, float x, float y, int wight, int height, char*path, int columm, int row, int count, int start, int end, int selectedIndex)
{
	_type = type;
	toado.x = x;
	toado.y = y;
	_wight = wight;
	_height = height;
	
	_texture = new GTexture(path, columm, row, count);
	_sprite = new GSprite(_texture, start, end, 2);
	_sprite->SelectIndex(selectedIndex);
	_camera = new GCamera();
	_hienthi = false;
}

void ObjectVuKhi::Update(float _DeltaTime, vector<GameObject*> _listObjectQuadtree, vector<Enemy*>_listEnemy){}

void ObjectVuKhi::Render(float x, float y){}
Box ObjectVuKhi::BoxObjectVuKhi()
{
	return Box(toado.x - _wight / 2, toado.y - _height / 2, toado.x + _wight / 2, toado.y + _height / 2, 0, 0);
}
ObjectVuKhi::~ObjectVuKhi()
{
	if (_texture != NULL)
		delete _texture;
	if (_sprite != NULL)
		delete _sprite;

	if (_camera != NULL)
		delete _camera;
}
