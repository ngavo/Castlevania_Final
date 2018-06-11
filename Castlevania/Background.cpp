#include "Background.h"
#include <iostream>
#include <fstream>
#include <sstream>
//#define FILE "stage.PNG"
#define  FILE "background_state_12.PNG"

Background::Background(char* filepath, int col, int row, int count)
{
	/*texture = new GTexture(FILE, 11, 6, 66);
	sprite = new GSprite(texture, 0, 65, 2);*/
	/*texture = new GTexture(FILE, 6, 5, 30);
	sprite = new GSprite(texture, 0, 29, 2);*/
	texture = new GTexture(filepath, col, row, count);
	sprite = new GSprite(texture, 0, count - 1, 2);
	camera = new GCamera();
}
void Background::StringToArray(int **Array, int curentRow, string line, int lenght)
{
	if (line == "") { return; }

	Array[rowCount - 1 - curentRow] = new int[lenght];
	int index = 0;
	string word = "";
	int i = 0;

	while (i < line.length())
	{
		if (line[i] != '\t')
		{
			word += line[i];
		}
		else
		{
			Array[rowCount - 1 - curentRow][index] = atoi(word.c_str());
			word = "";
			index++;
		}
		i++;
	}
}
void Background::readfile(string filepath)
{
	//ifstream fi;
	//string line = "";
	///*list<string> a = {};*/
	//fi.open(filepath);

	//string linek;
	//getline(fi, linek);

	//int arrt[11][96];

	//    string arrtk[11];
	//	int j = 0;
	//	while (!fi.eof() && j<11)
	//	{
	//		string line;
	//		getline(fi, line);
	//		arrtk[j] = line;
	//		j++;
	//	}

	//	//chuyen chuoi thanh so
	//	//int mangso[11][64];
	//	for (int j = 0; j < 11; j++)
	//	{
	//		int indexso = 0;
	//		stringstream ssin(arrtk[j]);
	//		while (ssin.good() && indexso < 96)
	//		{
	//			ssin >> mang[10-j][indexso];
	//			++indexso;
	//		}
	//	}


	ifstream fi;
	string line = "";
 int curentRow = 0, value = 0;

	fi.open(filepath);

	fi >> rowCount;
	fi >> columnCount;
	Arr = new int*[rowCount];

	while (!fi.eof())
	{
		getline(fi, line);
		if (line != "")
		{
			StringToArray(Arr, curentRow, line, columnCount);
			curentRow++;
		}
	}

	//in mảng ra màn hình
	/*for (int i = 0; i < rowCount; i++) {
		for (int j = 0; j < columnCount; j++)
		{
			cout << Arr[i][j] << " ";
		}
		cout << endl;
	}*/

	fi.close();
	//cin.get();
	//delete[] Arr;
	//return 0;

		
	
	
}

void Background::DrawBackground(int viewpostx)
{
	int start_loadbackground = (int)(viewpostx / 32);
	int end_loadbackground = (int)((viewpostx + G_ScreenWidth) / 32);

	for (int i = 0; i < rowCount; i++)
	{
		for (int j = 0; j < columnCount; j++)
		{
			D3DXVECTOR2 view;
			view.x = (float) viewpostx;
			view.y = (float) G_ScreenHeight;
			camera->setViewPort(view);
			G_SpriteHandler->Begin(D3DXSPRITE_SORT_DEPTH_FRONTTOBACK | D3DXSPRITE_ALPHABLEND);
			sprite->_index = Arr[i][j];
			
			D3DXVECTOR2 pos = camera->Transform(j*32 -32/** 32 - 32 * start_loadbackground*/, i*32+82/** 32*/);
			sprite->Draw(pos.x, pos.y);
			//sprite->Draw(j * 32 - 32 * start_loadbackground, i * 32);
			G_SpriteHandler->End();
			
		}
	}
	
	
}

void Background::ChuyenChuoiThanhMang(int k,string chuoi)
{
	string arr[96];
		int i = 0;
		stringstream ssin(chuoi);
		while (ssin.good() && i < k) {
			ssin >> arr[i];
			++i;
		}
}
Background::~Background()
{
	delete[] Arr;
}
