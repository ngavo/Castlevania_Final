#include "Map.h"
#include "Ground.h"
#include "MormingStar.h"
#include "heart.h"
#include "Watch.h"
#include "MoneyBag700.h"
#include "MoneyBag400.h"
#include "FireBomb.h"
#include "heartSmall.h"
#include "VatChuyebStage.h"
#include "Danger.h"
#include "BreakWall.h"
#include "Frankenstein.h"
#include "Fleaman.h"
Map::Map()
{
	quadtree = new QuadTreeObject();
}

void Map::LoadObjectFromFile(string filepath)
{
	
}

void Map::LoadObject(int id, int flip, int type, float x, float y, int width, int height, int stage)
{
	this->_stage = stage;
	GameObject*object = NULL;
	NenNho*nenho = NULL;
	heart*_heart = NULL;
	MormingStar*morningStar = NULL;
	Watch*watch = NULL;
	MoneyBag700*moneyBag = NULL;
	MoneyBag400*moneyBag400 = NULL;
	FireBomb*fireBomb = NULL;
	Bats*bat = NULL;
	FishMan*fishMan = NULL;
	heartSmall*_heartSmall = NULL;
	Moving*_moving = NULL;
	Danger* _danger = NULL;
	BreakWall*_breakWall = NULL;
	Enemy*_enemy = NULL;

	switch (type)
	{
	case 12:
		object = new Ground(id, type, x, y, width, height);
		break;
	case 11:
		object = new NenNho(id, type, x, y, width, height);
		nenho = new NenNho(id, type, x, y, width, height);
		break;
	case 19:
		_moving = new Moving(id, type, x, y, width, height);
		break;
	case 0:
		
		_enemy = new Bats();
		_enemy->Init(eEnemy::TypeBat, x, y, width, height);
		break;
	case 3:
		
		_enemy = new FishMan();
		((FishMan*)_enemy)->Init(id, eEnemy::TypeFishMan, flip, x, y, width, height);
		break;
	case 13:
		object = new VatChuyebStage(id, type, x, y, width, height);
		break;
	case 14:
		object = new BreakWall(id, type, x, y, width, height);
		_breakWall = new BreakWall(id, type, x, y, width, height);
		break;
	case 30:
		_enemy = new BoneDragons();
		_enemy->Init(eEnemy::BoneDragon, x, y, width, height);
		break;
	case 31:
		_enemy = new Frankenstein();
		_enemy->Init(eEnemy::TypeFrankenstein, x, y, width, height);
		break;
	case 32:
		_enemy = new Fleaman();
		_enemy->Init(eEnemy::TypeFleaman, x, y, width, height);
		break;
	default:
		break;
	}
	if (object != NULL)
	{
		ListObjects.push_back(object);
	}
	if(_enemy !=NULL)
	{
		_listEnemy.push_back(_enemy);
	}

	

	if (_moving != NULL)
	{
		ListMoving.push_back(_moving);
	}

	if (_breakWall != NULL)
	{
		ListBreakWall.push_back(_breakWall);
	}


	//truong hop moi stage trong cac nen co cac item khac nhau

	switch (stage)
	{
	case 10:
		if (nenho != NULL)
		{
			ListNenNho.push_back(nenho);
			switch (ListNenNho.size())
			{
			case 1:
				morningStar = new MormingStar(nenho->_x, nenho->_y, 64, 64);
				morningStar->type = mormingStarType;
				ListItem.push_back(morningStar);
				break;
			case 2:
				_heart = new heart(nenho->_x, nenho->_y, 10, 24);
				_heart->type = bigHeartType;
				ListItem.push_back(_heart);
				break;
			/*case 3:
				watch = new Watch(nenho->_x, nenho->_y, 10, 36);
				ListItem.push_back(watch);
				break;*/
			case 7:
				morningStar = new MormingStar(nenho->_x, nenho->_y, 10, 36);
				morningStar->type = mormingStarType;
				ListItem.push_back(morningStar);
				break;
			case 9:
				moneyBag400 = new MoneyBag400(nenho->_x, nenho->_y, 10, 32);
				moneyBag400->type = pointMoney400Type;
				ListItem.push_back(moneyBag400);

				break;
			case 12:
				fireBomb = new FireBomb(nenho->_x, nenho->_y, 10, 34);
				fireBomb->type = FireBomType;
				ListItem.push_back(fireBomb);
				break;
			default:
				
				_heartSmall = new heartSmall(nenho->_x, nenho->_y, 10, 24);
				_heartSmall->type = smallHeartType;
				ListItem.push_back(_heartSmall);
				break;
			}
		}
		break;
	case 12:
		if (nenho != NULL)
		{
			ListNenNho.push_back(nenho);
			switch (ListNenNho.size())
			{
			case 1:
				_heartSmall = new heartSmall(nenho->_x, nenho->_y, 10, 24);
				_heartSmall->type = smallHeartType;
				ListItem.push_back(_heartSmall);
				break;
			case 2:
				_danger = new Danger(nenho->_x, nenho->_y, 10, 24);
				_danger->type = DangerType;
				ListItem.push_back(_danger);
				break;
			case 5:
				moneyBag = new MoneyBag700(nenho->_x, nenho->_y, 10, 36);
				moneyBag->type = pointMoney700Type;
				ListItem.push_back(moneyBag);
				break;
			case 7:
				_heart = new heart(nenho->_x, nenho->_y, 10, 24);
				_heart->type = bigHeartType;
				ListItem.push_back(_heart);
				break;
			case 11:
				moneyBag = new MoneyBag700(nenho->_x, nenho->_y, 10, 36);
				moneyBag->type = pointMoney700Type;
				ListItem.push_back(moneyBag);
				break;
			default:
				_heartSmall = new heartSmall(nenho->_x, nenho->_y, 10, 24);
				_heartSmall->type = smallHeartType;
				ListItem.push_back(_heartSmall);
				break;
			}
		}
		break;
	default:
		break;
	}

	//ket thuc truong hop moi stage trong cac nen co cac item khac nhau

	//mai lam tiep
	switch (ListBreakWall.size())
	{
	case 1:
		_food = new Food(ListBreakWall[0]->_x, ListBreakWall[0]->_y, 10, 24);
		_gachvun1 = new GachVun(ListBreakWall[0]->_x, ListBreakWall[0]->_y);
		break;
	case 2:
		_heartForBreakWall = new HeartForBrickWall(ListBreakWall[1]->_x, ListBreakWall[1]->_y, 10, 24);
		_gachvun2 = new GachVun(ListBreakWall[1]->_x, ListBreakWall[1]->_y);
		break;
	default:
		break;
	}
	//ket thuc mai lam tiep




	
	
	
}
void Map::LoadMap(string filepath, int stage)
{
	int  RowObject = 0;
	RowObject = CountRowObject(filepath);
	fstream file;
	file.open(filepath, ios::in);
	//dau danh sach object tu file vo ListObject
	for (int i = 0; i < RowObject; i++)
	{

		int IDObject; file >> IDObject;
		int Type; file >> Type;
		int flip; file >> flip;
		int x; file >> x;
		int y; file >> y;
		int width; file >> width;
		int height; file >> height;
		LoadObject(IDObject,flip, Type,  x, y, width, height,stage);
	}

	file.close();

	file.open(filepath, ios::in);


	int RowBetWeen = CountRowBetween(filepath, RowObject);

	quadtree->LoadNodeInFile(filepath, RowObject, RowBetWeen, ListObjects);
}

void Map::LoadListObjectInWorld(RECT rect)
{
	RECT rec;
	rec = rect;
	quadtree->GetListObjectInRect(rec);
	for (int i = 0; i < quadtree->ListObjectInRect.size() - 1; i++)
	{
		for (int j = i + 1; j<quadtree->ListObjectInRect.size(); j++)
			// Các object cùng địa chỉ
			if (quadtree->ListObjectInRect[i] == quadtree->ListObjectInRect[j])
			{
				quadtree->ListObjectInRect.erase(quadtree->ListObjectInRect.begin() + j);
				j--;
			}

	}

	for (int i = 0; i < _listEnemy.size(); i++)
	{
		switch (_listEnemy[i]->_tyle)
		{
		case eEnemy::TypeBat:
			if (_listEnemy[i]->_x < rec.right)
			{
				_listEnemy[i]->hienthi = true;
			}
			break;
		case eEnemy::TypeFishMan:
			if (!_listEnemy[i]->hienthi)
			{
				if (((FishMan*)_listEnemy[i])->Check(_posxSimon,((FishMan*) _listEnemy[i])->id))
				{
					_listEnemy[i]->hienthi = true;
				}
			}
			break;
		case eEnemy::TypeFrankenstein:
			if (_listEnemy[i]->_x < rec.right)
			{
				_listEnemy[i]->hienthi = true;
			}
		default:
			break;
		}
	}
	

}

void Map::Draw(float x, float y)
{
	if (quadtree->ListObjectInRect.size() != NULL)
	{
		for (int i = 0; i < quadtree->ListObjectInRect.size(); i++)
		{
			quadtree->ListObjectInRect[i]->Render(x,y);
		}
	}

	for (int i = 0; i < ListFires.size(); i++)
	{
		ListFires[i]->Render(x,y);
		if (ListFires[i]->sprite->GetIndex() == 3)
		{
			for (int j = 0; j < ListItem.size(); j++)
			{
				if(ListItem[j]->hienthi);
				ListItem[j]->Render(x, y);
			}
			
		}
	}


	for (int i = 0; i < ListMoving.size(); i++)
	{
		ListMoving[i]->Render(x, y);
	}

	if (point400 != NULL)
	{
		point400->Render(x, y);
	}

	if (point700 != NULL)
	{
		point700->Render(x, y);
	}

	if (_food != NULL)
	{
		_food->Render(x, y);
	}

	if (_heartForBreakWall != NULL)
	{
		_heartForBreakWall->Render(x, y);
	}
	
	if (_gachvun1 != NULL)
	{
		if (_gachvun1->hienthi)
			_gachvun1->Render(x, y);
	}

	if (_gachvun2 != NULL)
	{
		if (_gachvun2->hienthi)
			_gachvun2->Render(x, y);
	}

}


void Map::Update(float time, kitty*simon)
{
	simon->isTouchGround = false;
	this->_posxSimon = simon->_posx;

	UpdateCHungCho10And12(time, simon);

	
		UpdateStage10(time, simon);
	
		UpdateStage12(time, simon);
	
}



void Map::UpdateCHungCho10And12(float time, kitty* simon)
{
	if (quadtree->ListObjectInRect.size() != NULL)
	{

		for (int i = 0; i < quadtree->ListObjectInRect.size(); i++)
		{

			/*ket thuc enemy va cham voi cuc gach*/


			if (quadtree->ListObjectInRect[i]->GetType() == 12 || quadtree->ListObjectInRect[i]->GetType() == 19)// truong hop doi tuong trong quadtre la cuc gach hay la groundmove thi kiem tra xem simon co va cham voi no hay khong
			{
				/*Box simonBox(simon->_posx - 16, simon->_posy - 32, simon->_posx+16, simon->_posy+32, simon->_vx, simon->_vg);*/
				Box box(quadtree->ListObjectInRect[i]->_x - quadtree->ListObjectInRect[i]->_width / 2 - 16, quadtree->ListObjectInRect[i]->_y - quadtree->ListObjectInRect[i]->_height / 2, quadtree->ListObjectInRect[i]->_x + quadtree->ListObjectInRect[i]->_width / 2 -16, quadtree->ListObjectInRect[i]->_y + quadtree->ListObjectInRect[i]->_height / 2, 0, 0);
				Box broadphasebox = GetSweptBroadphaseBox(simon->bxSimon(), time);

				if (AABB(broadphasebox, box))
				{
					if (AABB(simon->bxSimon(), box))//long nhay ngay tu dau
					{
						if (simon->_posy - 10 > quadtree->ListObjectInRect[i]->_y)
							simon->_posy = quadtree->ListObjectInRect[i]->_y + quadtree->ListObjectInRect[i]->_height / 2 + simon->height / 2 + 0.8f;
						//	//simon->isTouchGround = true;
					}

					float normalx, normaly;
					float timeCollision = SweptAABB(simon->bxSimon(), box, normalx, normaly, time);
					if (timeCollision < 1.0f)
					{
						if (normaly == 1.0)
						{
							simon->_posy = quadtree->ListObjectInRect[i]->_y + quadtree->ListObjectInRect[i]->_height / 2 + 32 + 0.8f;
							simon->nhay = false;
							simon->isTouchGround = true;

							if (quadtree->ListObjectInRect[i]->GetType() == 19)
							{
								simon->dung_tren_moving = true;
								simon->detal_move = quadtree->ListObjectInRect[i]->_detalx;
							}
							else
								simon->dung_tren_moving = false;
						}
						if (normalx == -1.0)//tong ben phai simon
						{
							/*simon->_posx = box.l - 32;*/

							simon->isTouchLeftGround = true;

						}
						else
						{
							simon->isTouchLeftGround = false;
						}
						if (normalx == 1.0)//tong ben trai simon
						{
							/*simon->_posx = box.r + 32;*/
							simon->isTouchRightGround = true;
						}
						else
						{
							simon->isTouchRightGround = false;
						}


					}


				}

			}


			/*truong hop simon danh ngon nen hay cac vat trong quadtree*/
			if (quadtree->ListObjectInRect[i]->hienthi)
			{
				if (quadtree->ListObjectInRect[i]->GetType() == 11)
				{
					Box nenNhoBox(quadtree->ListObjectInRect[i]->_x - 8, quadtree->ListObjectInRect[i]->_y - 16, quadtree->ListObjectInRect[i]->_x + 8, quadtree->ListObjectInRect[i]->_y + 16, 0, 0);
					if (simon->IsActack && simon->isWhip)
					{
						if (simon->sprite->GetIndex() == 13)
						{
							if (simon->flat)//hinh trai
							{
								/*Box whipBox(simon->_posx - 32 - 70, simon->_posy - 20, simon->_posx - 32, simon->_posy - 10 + 20, simon->_vx, simon->_vg);*/
								Box whipBox = simon->_whip->boxWhip(simon->_posx, simon->_posy, simon->mucWhip, 13, simon->flat);
								if (AABB(whipBox, nenNhoBox))
								{
									quadtree->ListObjectInRect[i]->hienthi = false;
									fire* _fire = new fire(quadtree->ListObjectInRect[i]->_x, quadtree->ListObjectInRect[i]->_y, 64, 64);
									_fire->hienthi = true;
									ListFires.push_back(_fire);

									for (int index_hienthinen = 0; index_hienthinen < ListItem.size(); index_hienthinen++)
									{
										if (ListItem[index_hienthinen]->_x == quadtree->ListObjectInRect[i]->_x && ListItem[index_hienthinen]->_y == quadtree->ListObjectInRect[i]->_y)
										{
											ListItem[index_hienthinen]->hienthi = true;
										}
									}
								}
							}
							else
							{
								/*Box whipBox(simon->_posx + 32, simon->_posy - 20, simon->_posx + 32 + 70, simon->_posy - 10 + 20, simon->_vx, simon->_vg);*/
								Box whipBox = simon->_whip->boxWhip(simon->_posx, simon->_posy, simon->mucWhip, 13, simon->flat);
								if (AABB(whipBox, nenNhoBox))
								{
									quadtree->ListObjectInRect[i]->hienthi = false;
									fire* _fire = new fire(quadtree->ListObjectInRect[i]->_x, quadtree->ListObjectInRect[i]->_y, 64, 64);
									_fire->hienthi = true;
									ListFires.push_back(_fire);
									for (int index_hienthinen = 0; index_hienthinen < ListItem.size(); index_hienthinen++)
									{
										if (ListItem[index_hienthinen]->_x == quadtree->ListObjectInRect[i]->_x && ListItem[index_hienthinen]->_y == quadtree->ListObjectInRect[i]->_y)
										{
											ListItem[index_hienthinen]->hienthi = true;
										}
									}
								}
							}


						}


					}
				}
			}
			

			/*ket thuc simon danh cac vat trong quadtree*/

			if (quadtree->ListObjectInRect[i]->GetType() == 13)
			{
				Box box(quadtree->ListObjectInRect[i]->_x - quadtree->ListObjectInRect[i]->_width / 2, quadtree->ListObjectInRect[i]->_y - quadtree->ListObjectInRect[i]->_height / 2, quadtree->ListObjectInRect[i]->_x + quadtree->ListObjectInRect[i]->_width / 2, quadtree->ListObjectInRect[i]->_y + quadtree->ListObjectInRect[i]->_height / 2, 0, 0);
				if (AABB(simon->bxSimon(), box))
				{
					simon->stageMapChange = 1;
					simon->_posx = 210;
					simon->_posy = 450;
					simon->camera->viewport.x = 0;
					simon->camera->viewport.y = G_ScreenHeight;
				}
			}

			//bat dau truong hop simon danh break wall
			if (quadtree->ListObjectInRect[i]->GetType() == 14)
			{
				
				Box boxBreakWall(quadtree->ListObjectInRect[i]->_x - 16, quadtree->ListObjectInRect[i]->_y - 16, quadtree->ListObjectInRect[i]->_x + 16, quadtree->ListObjectInRect[i]->_y + 16, 0, 0);
				if (quadtree->ListObjectInRect[i]->hienthi)
				{
					if (simon->IsActack && simon->isWhip)
					{
						if (simon->sprite->GetIndex() == 13)
						{

							if (simon->flat)//hinh trai
							{
								/*Box whipBox(simon->_posx - 32 - 70, simon->_posy - 20, simon->_posx - 32, simon->_posy - 10 + 20, simon->_vx, simon->_vg);*/
								Box whipBox = simon->_whip->boxWhip(simon->_posx, simon->_posy, simon->mucWhip, 13, simon->flat);
								if (AABB(whipBox, boxBreakWall))
								{
									Sound::GetInstance()->Play(FALLING);
									quadtree->ListObjectInRect[i]->hienthi = false;
									if (quadtree->ListObjectInRect[i]->GetId() == 120)
									{
										_food->hienthi = true;
									}

									if (quadtree->ListObjectInRect[i]->GetId() == 152)
									{
										_heartForBreakWall->hienthi = true;
									}
								}
							}
							else
							{
								/*Box whipBox(simon->_posx + 32, simon->_posy - 20, simon->_posx + 32 + 70, simon->_posy - 10 + 20, simon->_vx, simon->_vg);*/
								Box whipBox = simon->_whip->boxWhip(simon->_posx, simon->_posy, simon->mucWhip, 13, simon->flat);
								if (AABB(whipBox, boxBreakWall))
								{
									Sound::GetInstance()->Play(FALLING);
									quadtree->ListObjectInRect[i]->hienthi = false;
									if (quadtree->ListObjectInRect[i]->GetId() == 120)
									{
										_food->hienthi = true;
										_gachvun1->hienthi = true;
									}

									if (quadtree->ListObjectInRect[i]->GetId() == 152)
									{
										_heartForBreakWall->hienthi = true;
										_gachvun2->hienthi = true;
									}
								}
							}


						}
					}
				}
				



				//simon va cham voi break wall
				if (quadtree->ListObjectInRect[i]->hienthi)
				{
					Box broadphasebox = GetSweptBroadphaseBox(simon->bxSimon(), time);

					if (AABB(broadphasebox, boxBreakWall))
					{
						if (AABB(simon->bxSimon(), boxBreakWall))//long nhay ngay tu dau
						{
							if (simon->_posy - 10 > quadtree->ListObjectInRect[i]->_y)
								simon->_posy = quadtree->ListObjectInRect[i]->_y + quadtree->ListObjectInRect[i]->_height / 2 + simon->height / 2 + 1.8f;
							//	//simon->isTouchGround = true;
						}

						float normalx, normaly;
						float timeCollision = SweptAABB(simon->bxSimon(), boxBreakWall, normalx, normaly, time);
						if (timeCollision < 1.0f)
						{
							if (normaly == 1.0)
							{
								simon->_posy = quadtree->ListObjectInRect[i]->_y + quadtree->ListObjectInRect[i]->_height / 2 + 32 + 1.8f;
								simon->nhay = false;
								simon->isTouchGround = true;

								if (quadtree->ListObjectInRect[i]->GetType() == 19)
								{
									simon->dung_tren_moving = true;
									simon->detal_move = quadtree->ListObjectInRect[i]->_detalx;
								}
								else
									simon->dung_tren_moving = false;
							}
							if (normalx == -1.0)//tong ben phai simon
							{
								/*simon->_posx = box.l - 32;*/

								simon->isTouchLeftGround = true;

							}
							else
							{
								simon->isTouchLeftGround = false;
							}
							if (normalx == 1.0)//tong ben trai simon
							{
								/*simon->_posx = box.r + 32;*/
								simon->isTouchRightGround = true;
							}
							else
							{
								simon->isTouchRightGround = false;
							}


						}


					}
				}
				

				// ket thuc simon va cham voi break wall


			}

			//ket thuc truong hop simon danh break wall



			quadtree->ListObjectInRect[i]->Update(time);


			for (int j = 0; j < ListItem.size(); j++)// kiem tra item roi cham dat
			{
				if (ListItem[j]->hienthi)
				{
					/*Box boxItem(ListItem[j]->_x-ListItem[j]->_width/2,ListItem[j]->_y- ListItem[j]->_height/2, ListItem[j]->_x + ListItem[j]->_width / 2, ListItem[j]->_y + ListItem[j]->_height / 2, 0,0);*/
					if (quadtree->ListObjectInRect[i]->GetType() == 12 || quadtree->ListObjectInRect[i]->GetType() == 19)
					{
						Box boxq(quadtree->ListObjectInRect[i]->_x - quadtree->ListObjectInRect[i]->_width / 2, quadtree->ListObjectInRect[i]->_y - quadtree->ListObjectInRect[i]->_height / 2, quadtree->ListObjectInRect[i]->_x + quadtree->ListObjectInRect[i]->_width / 2, quadtree->ListObjectInRect[i]->_y + quadtree->ListObjectInRect[i]->_height / 2, 0, 0);

						if (AABB(ListItem[j]->boxItem(), boxq))
						{
							ListItem[j]->_vy = 0;
							ListItem[j]->_y = boxq.b + 16;
							ListItem[j]->itemChamDat = true;// su dung cho truong hop heartSamll cham dat thi se khong bi dao dong qua lai quanh truc x
						}

					}
					ListItem[j]->Update(time);
				}

			}

		}

		for (int i = 0; i < ListFires.size(); i++)
		{
			if (ListFires[i]->sprite->GetIndex() != 3)
				ListFires[i]->Update(time);
		}

		for (int i = 0; i < ListItem.size(); i++)//kiem tra simon co cham item ko
		{
			if (ListItem[i]->hienthi)
			{


				if (AABB(simon->bxSimonCollisionItem(), ListItem[i]->boxItem()))
				{
					ListItem[i]->hienthi = false;
					Sound::GetInstance()->Play(COLLECT_ITEM);
					if (ListItem[i]->type == smallHeartType)
					{
						simon->heart += 1;
					}
					if (ListItem[i]->type == bigHeartType)
					{
						simon->heart += 5;
					}
					if (ListItem[i]->type == mormingStarType)
					{
						simon->mucWhip += 1;
						simon->anwhip = true;
					}
					if (ListItem[i]->type == pointMoney400Type)
					{
						point400 = new PointForMoney400(ListItem[i]->_x + 32, ListItem[i]->_y);
						point400->hienthi = true;
					}
					if (ListItem[i]->type == pointMoney700Type)
					{
						point700 = new PointForMoney700(ListItem[i]->_x + 32, ListItem[i]->_y);
						point700->hienthi = true;
					}

					if (ListItem[i]->type == FireBomType)
					{
						simon->LoaiVuKhi = FIREBOM;
					}

					if (ListItem[i]->type == DangerType)
					{
						simon->LoaiVuKhi = DANGER;
					}
				}


			}
		}

		


	}


	if (point400 != NULL)
	{
		if (point400->hienthi)
		{
			point400->Update(time);
		}
	}

	if (point700 != NULL)
	{
		if (point700->hienthi)
		{
			point700->Update(time);
		}
	}


}

void Map::UpdateStage10(float time, kitty* simon)
{

	//truong hop movung

	for (int i = 0; i < ListMoving.size(); i++)
	{

		Box simonBox(simon->_posx - 16, simon->_posy - 32, simon->_posx + 16, simon->_posy + 32, simon->_vx, simon->_vg);
		Box box(ListMoving[i]->_x - ListMoving[i]->_width / 2, ListMoving[i]->_y - ListMoving[i]->_height / 2, ListMoving[i]->_x + ListMoving[i]->_width / 2, ListMoving[i]->_y + ListMoving[i]->_height / 2, 0, 0);
		Box broadphasebox = GetSweptBroadphaseBox(simonBox, time);

		if (AABB(broadphasebox, box))
		{
			if (AABB(simonBox, box))//long nhay ngay tu dau
			{
				simon->_posy = ListMoving[i]->_y + ListMoving[i]->_height / 2 + 32 + 0.4f;
				//simon->isTouchGround = true;
			}

			float normalx, normaly;
			float timeCollision = SweptAABB(simonBox, box, normalx, normaly, time);
			if (timeCollision < 1.0f)
			{
				if (normaly == 1.0)
				{
					simon->_posy = ListMoving[i]->_y + ListMoving[i]->_height / 2 + 32 + 0.4f;
					simon->nhay = false;
					simon->isTouchGround = true;

					simon->dung_tren_moving = true;
					simon->detal_move = ListMoving[i]->_detalx;

				}

			}


		}

		ListMoving[i]->Update(time);

	}

	//ket thuc truong hop moving

}

void Map::UpdateStage12(float time, kitty* simon)
{

	//kiem tra simon cho cham an _food chua
	if (_food != NULL)
	{
		if (_food->hienthi)
		{
			if (AABB(_food->boxItem(), simon->bxSimonCollisionItem()))
			{
				_food->hienthi = false;
				Sound::GetInstance()->Play(COLLECT_ITEM);
				simon->hp += 6;
				if (simon->hp > 16)
				{
					simon->hp = 16;
				}
			}

		}
	}

	if (_heartForBreakWall != NULL)
	{
		if (_heartForBreakWall->hienthi)
		{
			if (AABB(_heartForBreakWall->boxItem(), simon->bxSimonCollisionItem()))
			{
				_heartForBreakWall->hienthi = false;
				Sound::GetInstance()->Play(COLLECT_ITEM);
			}
		}
	}

	if (_gachvun1 != NULL)
	{
		if (_gachvun1->hienthi)
			_gachvun1->Update(time);
	}

	if (_gachvun2 != NULL)
	{
		if (_gachvun2->hienthi)
			_gachvun2->Update(time);
	}
}



int Map::CountRowObject(string filepath)
{
	fstream file;
	file.open(filepath, ios::in);

	int dem = 0;
	while (!file.eof())
	{
		string line;
		getline(file, line);
		if (line != "END")
		{
			dem = dem + 1;;
			//cout << line << "\n";
		}
		else
		{
			file.close();
			return dem;
		}
	}
}
int Map::CountRowBetween(string filepath, int RowObject)
{
	string line;
	fstream file;
	file.open(filepath, ios::in);
	for (int i = 0; i < RowObject; i++)
	{
		getline(file, line);
	}
	int dem = 0;
	getline(file, line);//lay end
	while (!file.eof())
	{
		getline(file, line);
		if (line != "END")
		{
			dem++;
		}
		else
		{
			file.close();
			return dem;
		}
	}

}
Map::~Map()
{
	for (int i = 0; i<ListObjects.size(); i++)
		if (ListObjects[i]) {
			delete ListObjects[i];
			ListObjects[i] = NULL;
		}
	ListObjects.clear();
	

	


	for (int i = 0; i < ListFires.size(); i++)
	{
		if (ListFires[i])
		{
			delete ListFires[i];
			ListFires[i] = NULL;
		}
	}
	ListFires.clear();

	for (int i = 0; i < _listEnemy.size(); i++)
	{
		if (_listEnemy[i])
		{
			delete _listEnemy[i];
			_listEnemy[i] = NULL;
		}
	}

	_listEnemy.clear();

}
