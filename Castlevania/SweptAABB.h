#pragma once
#include <algorithm>
#include <limits>
#include <d3d9.h>

struct Box
{
	float l, t;
	float r, b;
	float vx, vy;

	Box(float _l, float _t, float _r, float _b, float _vx, float _vy)
	{
		l = _l;
		t = _t;
		r = _r;
		b = _b;
		vx = _vx;
		vy = _vy;
	}


};



static bool AABB(Box b1, Box b2)
{
	if (b1.l > b2.r)//canh trai box > canh phai vat qua cham
		return false;
	if (b1.r < b2.l)
		return false;
	if (b1.t > b2.b)
		return false;
	if (b1.b < b2.t)
		return false;
	return true;
}

// trả về box bao lấy phần giao thoa của box hiện tại và box đích
static Box GetSweptBroadphaseBox(Box b, float dt)
{
	Box broadphasebox(0.0f, 0.0f, 0.0f, 0.0f, 0.0f,0.0f);

	if (b.vx > 0)
	{
		broadphasebox.l = b.l;
		broadphasebox.r = b.r + b.vx*dt;
	}
	else
	{
		broadphasebox.l = b.l + b.vx*dt;
		broadphasebox.r = b.r;
	}

	if (b.vy > 0)
	{
		broadphasebox.t = b.t;
		broadphasebox.b = b.b + b.vy*dt;
	}
	else
	{
		broadphasebox.t = b.t + b.vy*dt;
		broadphasebox.b = b.b;
	}

	return broadphasebox;
}


static float SweptAABB(Box object, Box orther, float & normalx, float & normaly, float time)
{
	float dxEntry, dxExit;
	float dyEntry, dyExit;

	float deltaVX = (object.vx - orther.vx)*time;
	float deltaVY = (object.vy - orther.vy)*time;

	if (deltaVX > 0.0f)
	{
		dxEntry = orther.l - object.r;
		dxExit = orther.r - object.l;
	}
	else
	{
		dxEntry = orther.r - object.l;
		dxExit = orther.l - object.r;
	}

	if (deltaVY > 0.0f)
	{
		dyEntry = orther.t  - object.b;
		dyExit = orther.b - object.t;
	}
	else
	{
		dyEntry = orther.b - object.t;
		dyExit = orther.t - object.b;
	}

	float txEntry, txExit;
	float tyEntry, tyExit;

	if (deltaVX == 0.0f)
	{
		txEntry = -std::numeric_limits<float>::infinity();
		txExit = std::numeric_limits<float>::infinity();
	}
	else
	{
		txEntry = dxEntry / deltaVX;
		txExit = dxExit / deltaVX;
	}
	
	if (deltaVY == 0.0f)
	{
		tyEntry = -std::numeric_limits<float>::infinity();
		tyExit = std::numeric_limits<float>::infinity();
	}
	else
	{
		tyEntry = dyEntry / deltaVY;
		tyExit = dyExit / deltaVY;
	}

	//thoi gian va cham giua && ngung va cham giua hai chieu

	float timeCollision = max(txEntry, tyEntry);
	float timeNotCollision = min(txExit, tyExit);

	//neu khong co va cham
	if ((timeCollision > timeNotCollision) || ((txEntry < 0.0f) && (tyEntry < 0.0f)) || (txEntry > 1.0f) || (tyEntry > 1.0f))
	{
		normalx = 0.0f;
		normaly = 0.0f;
		return 1.0f;
	}

	//lay huong va cham

	if (txEntry > tyEntry)//va cham tren truc x
	{
		if (dxEntry > 0.0f)// va cham  ben right cua object
		{
			normalx = -1.0f;
			normaly = 0.0f;
		}
		else // va cham ben left cua object
		{
			normalx = 1.0f;
			normaly = 0.0f;
		}
	}

	else// va cham tren truc y
	{
		if (dyEntry > 0.0f)// va cham buttom cua object
		{
			normaly = -1.0f;
			normalx = 0.0f;
		}
		else //va cham top cua object
		{
			normaly = 1.0f; 
			normalx = 0.0f;
		}
	}

	return timeCollision;


}

//static float SweptAABB(Box b1, Box b2, float& normalx, float& normaly, int dt)
//{
//	float xInvEntry, yInvEntry;
//	float xInvExit, yInvExit;
//
//	// find the distance between the objects on the near and far sides for both x and y
//	if (b1.vx > 0.0f)
//	{
//		xInvEntry = b2.x - (b1.x + b1.w);
//		xInvExit = (b2.x + b2.w) - b1.x;
//	}
//	else
//	{
//		xInvEntry = (b2.x + b2.w) - b1.x;
//		xInvExit = b2.x - (b1.x + b1.w);
//	}
//
//	if (b1.vy < 0.0f)
//	{
//		yInvEntry = b2.y - (b1.y - b1.h);
//		yInvExit = (b2.y - b2.h) - b1.y;
//	}
//	else
//	{
//		yInvEntry = (b2.y - b2.h) - b1.y;
//		yInvExit = b2.y - (b1.y - b1.h);
//	}
//
//	// find time of collision and time of leaving for each axis (if statement is to prevent divide by zero)
//	float xEntry, yEntry;
//	float xExit, yExit;
//
//	if (b1.vx == 0.0f)
//	{
//		xEntry = -std::numeric_limits<float>::infinity();
//		xExit = std::numeric_limits<float>::infinity();
//	}
//	else
//	{
//		xEntry = xInvEntry / (b1.vx * dt);
//		xExit = xInvExit / (b1.vx * dt);
//	}
//
//	if (b1.vy == 0.0f)
//	{
//		yEntry = -std::numeric_limits<float>::infinity();
//		yExit = std::numeric_limits<float>::infinity();
//	}
//	else
//	{
//		yEntry = yInvEntry / (b1.vy * dt);
//		yExit = yInvExit / (b1.vy * dt);
//	}
//
//	// find the earliest/latest times of collision
//	float entryTime = max(xEntry, yEntry);
//	float exitTime = min(xExit, yExit);
//
//	// if there was no collision
//	if (entryTime > exitTime || xEntry < 0.0f && yEntry < 0.0f || xEntry > 1.0f || yEntry > 1.0f)
//	{
//		normalx = 0.0f;
//		normaly = 0.0f;
//		return 1.0f;
//	}
//	else // if there was a collision
//	{
//		// calculate normal of collided surface
//		if (xEntry > yEntry)
//		{
//			if (xInvEntry < 0.0f)
//			{
//				normalx = 1.0f;
//				normaly = 0.0f;
//			}
//			else
//			{
//				normalx = -1.0f;
//				normaly = 0.0f;
//			}
//		}
//		else
//		{
//			if (yInvEntry < 0.0f)
//			{
//				normalx = 0.0f;
//				normaly = 1.0f;
//			}
//			else
//			{
//				normalx = 0.0f;
//				normaly = -1.0f;
//			}
//		}
//
//		// return the time of collision
//		return entryTime;
//	}
//}
//
