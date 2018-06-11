#include "Item.h"



Item::Item(float x, float y)
{
	this->_x = x;
	this->_y = y;
	this->type = 0;
	
}

Box Item::boxItem()
{
	Box k(this->_x - this->_width / 2, this->_y - this->_height / 2, this->_x + this->_width / 2, this->_y + this->_height / 2,0,0);
	return k;
}

void Item::Update(float _DeltaTime)// update per frame
{

}

void Item::Render(float x, float y)
{

}
Item::~Item()
{
}
