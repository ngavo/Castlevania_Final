#pragma once
#include "GSprite.h"
#include "GTexture.h"
class GameObject
{
public:

	GameObject();

	GSprite*sprite;
	GTexture*texture;
	int _Id;
	int _Type;

	float _x;
	float _y;
	int _width;
	int _height;
	float _detalx;
	bool hienthi;


	int GetId() {
		return _Id;//ID
	}

	int GetType()
	{
		return _Type;
	}
	RECT getRect();
	// ====== các phương thức ảo =====
	virtual void Init(int _X, int _Y);		// reset object
	virtual void Update(float _DeltaTime);	// update per frame
	virtual void Render(float x,float y);							// render per frame
	virtual void Destroy();					// clear sub object, without delete this
	~GameObject();
};

