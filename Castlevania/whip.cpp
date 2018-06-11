#include "whip.h"



whip::whip()
{
	this->texture = new GTexture("Resources/weapon/whip_right.bmp",3,6,18);
	this->sprite = new GSprite(texture, 0, 27, 2);
}

void whip:: SetIndex(int TrangThaiSinmon, int mucWhip)
{
	switch (TrangThaiSinmon)
	{
	case 14:
		switch (mucWhip)
		{
		case 0:
			this->sprite->SelectIndex(0);
			break;
		case 1:
			this->sprite->SelectIndex(3);
			break;
		case 2:
			this->sprite->SelectIndex(6);
			break;
		default:
			break;
		}
		break;
	case 15:
		switch (mucWhip)
		{
		case 0:
			this->sprite->SelectIndex(1);
			break;
		case 1:
			this->sprite->SelectIndex(4);
			break;
		case 2:
			this->sprite->SelectIndex(10);
			break;
		default:
			break;
		}
		break;
	case 16:
		switch (mucWhip)
		{
		case 0:
			this->sprite->SelectIndex(2);
			break;
		case 1:
			this->sprite->SelectIndex(5);
			break;
		case 2:
			this->sprite->SelectIndex(14);
			break;
		default:
			break;
		}
		break;
	case 11:
		switch (mucWhip)
		{
		case 0:
			this->sprite->SelectIndex(0);
			break;
		case 1:
			this->sprite->SelectIndex(3);
			break;
		case 2:
			this->sprite->SelectIndex(6);
			break;
		default:
			break;
		}
		break;
	case 12:
		switch (mucWhip)
		{
		case 0:
			this->sprite->SelectIndex(1);
			break;
		case 1:
			this->sprite->SelectIndex(4);
			break;
		case 2:
			this->sprite->SelectIndex(10);
			break;
		default:
			break;
		}
		break;
	case 13:
		switch (mucWhip)
		{
		case 0:
			this->sprite->SelectIndex(2);
			break;
		case 1:
			this->sprite->SelectIndex(5);
			break;
		case 2:
			this->sprite->SelectIndex(14);
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}
	
}
void whip::Draw(int x,int y, boolean isDown)
{
	if(isDown)
	this->sprite->Draw(x, y+20);
	else
	{
		this->sprite->Draw(x, y);
	}
}
void whip::DrawFlip(int x, int y, boolean isDown)
{
	if(isDown)
	this->sprite->DrawFlipX(x, y+20);
	else
	{
		this->sprite->DrawFlipX(x, y );
	}
}

int whip::GetIndex()
{
	return this->sprite->GetIndex();
}

Box whip::boxWhip(float postSimonx, float postSimony, int mucWhip, int TrangThaiSimon, boolean flatSimon)
{
	/*Box k(0,0,0,0,0,0);*/
	switch (TrangThaiSimon)
	{
	case 13:
		if (flatSimon)
		{
			switch (mucWhip)
			{
			case 0:
				return Box(postSimonx - 32 - 50, postSimony - 20, postSimonx - 32, postSimony + 20, 0.0, 0.0);
			case 1:
				return Box(postSimonx - 32 - 50, postSimony - 20, postSimonx - 32, postSimony + 20, 0.0, 0.0);
			case 2:
				return Box(postSimonx - 32 - 80, postSimony - 20, postSimonx - 32, postSimony + 20, 0.0, 0.0);
			default:
				break;
			}
		}
		else
		{
			switch (mucWhip)
			{
			case 0:
				return Box(postSimonx + 32 , postSimony - 20, postSimonx + 32 + 50, postSimony  + 20, 0.0, 0.0);
			case 1:
				return Box(postSimonx + 32 , postSimony - 20, postSimonx + 32 + 50, postSimony + 20, 0.0, 0.0);
			case 2:
				return Box(postSimonx + 32 , postSimony - 20, postSimonx + 32 + 80, postSimony + 20, 0.0, 0.0);
			default:
				break;
			}
		}
		break;
	case 16:
		if (flatSimon)
		{
			switch (mucWhip)
			{
			case 0:
				return Box(postSimonx - 32 - 50, postSimony - 20, postSimonx - 32, postSimony + 20, 0.0, 0.0);
			case 1:
				return Box(postSimonx - 32 - 50, postSimony - 20, postSimonx - 32, postSimony + 20, 0.0, 0.0);
			case 2:
				return Box(postSimonx - 32 - 80, postSimony - 20, postSimonx - 32, postSimony + 20, 0.0, 0.0);
			default:
				break;
			}
		}
		else
		{
			switch (mucWhip)
			{
			case 0:
				return Box(postSimonx + 32, postSimony - 20, postSimonx + 32 + 50, postSimony + 20, 0.0, 0.0);
			case 1:
				return Box(postSimonx + 32, postSimony - 20, postSimonx + 32 + 50, postSimony + 20, 0.0, 0.0);
			case 2:
				return Box(postSimonx + 32, postSimony - 20, postSimonx + 32 + 80, postSimony + 20, 0.0, 0.0);
			default:
				break;
			}
		}
		break;
	default:
		break;
	}

	return Box(0, 0, 0, 0, 0, 0);
}

whip::~whip()
{
}
