#pragma once
#include <string>
#include "GSprite.h"
#include "GTexture.h"
#include "GCamera.h"
using namespace std;
class Background
{

public:
	GSprite * sprite;
	GTexture * texture;
	GCamera *camera;
	int columnCount, rowCount;
	int **Arr;
	Background(char* filepath, int col, int row, int count);
	void readfile(string filepath);
	int mang[11][64];
	void ChuyenChuoiThanhMang(int, string);
	void StringToArray(int **Array, int curentRow, string line, int lenght);
	void DrawBackground(int);//ve
	~Background();
};

