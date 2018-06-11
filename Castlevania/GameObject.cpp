#include "GameObject.h"



GameObject::GameObject()
{
	hienthi = true;
}

void GameObject::Init(int _X, int _Y)
{
}
void GameObject::Update(float _DeltaTime)
{
}
	 // update per frame
void GameObject::Render(float x, float y)
{

}

RECT GameObject::getRect()
{
	RECT rect;
	rect.left = _x - _width/2;
	rect.top = _y - _height/2;
	rect.right = rect.left + _width;
	rect.bottom = rect.top + _height;
	return rect;
}
void GameObject::Destroy()
{

}

GameObject::~GameObject()
{
}
