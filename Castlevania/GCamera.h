#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "Global.h"
#include "GSprite.h"

class GCamera
{
public:
	D3DXVECTOR2 viewport;		//Thiết lập tọa độ của camera	
	int _maxSize, _minSize;
	RECT* region;
	RECT GetRegion(float left,float top, float width,float height);
	GCamera();
	D3DXVECTOR3 CenterSprite(int x, int y);	//Tìm tọa độ center của sprite
	void UpdateCamera(float x);		
	void UpdateCamera(int &w, int &h);
	void SetSizeMap(int _max, int _min);
	D3DXVECTOR2 Transform(float x, float y);		//Hàm transform, chuyển tọa độ viewport về tọa độ world
	void setViewPort(D3DXVECTOR2 view);
};

#endif