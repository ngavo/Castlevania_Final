#include "GCamera.h"

GCamera::GCamera()
{
	viewport.x = 0;
	viewport.y = G_ScreenHeight;
}

void GCamera::SetSizeMap(int _max, int _min)
{
	_maxSize = _max;
	_minSize = _min;
}
D3DXVECTOR2 GCamera::Transform(float x, float y)
{
	D3DXMATRIX matrix;
	D3DXMatrixIdentity (&matrix);
	matrix._22 = -1;
	matrix._41 = -viewport.x;
	matrix._42 = viewport.y;

	D3DXVECTOR3 pos3(x ,y ,0);	
	D3DXVECTOR4 MatrixResult;
	D3DXVec3Transform (&MatrixResult,&pos3,&matrix);

	D3DXVECTOR2 result = D3DXVECTOR2 (MatrixResult.x,MatrixResult.y);
	return result;
}

D3DXVECTOR3 GCamera::CenterSprite(int x, int y)
{
	D3DXVECTOR3 pCenter = D3DXVECTOR3(x/2, y/2, 0);
	return pCenter;
}

void GCamera::UpdateCamera(float x)
{
	//Tự viết dự vào hướng dẫn của GV LT
	viewport.x =  x - G_ScreenWidth / 2;
}

void GCamera::UpdateCamera(int &w, int &h)
{
	//Tự viết dự vào hướng dẫn của GV LT
}

void GCamera::setViewPort(D3DXVECTOR2 view)
{
	viewport.x = view.x;
	viewport.y = view.y;
}
RECT GCamera::GetRegion(float left, float top, float width, float height)
{
	
	RECT rect;
	rect.left = left;
	rect.top = top;
	rect.right = left + width;
	rect.bottom = top + height;
	return rect;

}