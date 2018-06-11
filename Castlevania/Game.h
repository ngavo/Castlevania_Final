#ifndef _GAME_H_
#define _GAME_H_
#include <windows.h>
#include <d3d9.h>
#include "Global.h"
#include <dinput.h>
#include "Background.h";
#include "Sound.h"


class CGame
{
public:
	CGame(int _nCmdShow);	
	CGame();
	void InitGame();

	void GameRun();

	void GameEnd();
	
	static int frameCounter;
	

protected:
	int nCmdShow;

	static LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	int InitWindow(int nCmdShow);

	int InitDirectX();

	void InitKeyboard();
	void InitBackbuffer();

	void ProcessKeyBoard();

	virtual void UpdateFrame(float Delta);
	virtual void RenderFrame(LPDIRECT3DDEVICE9 d3ddv, float Delta);
	virtual void LoadResources(LPDIRECT3DDEVICE9 d3ddv);
	virtual void ProcessInput(LPDIRECT3DDEVICE9 d3ddv, float Delta);
	
	virtual void OnKeyUp(int KeyCode);
	virtual void OnKeyDown(int KeyCode);

	int IsKeyDown(int KeyCode);

	void GameDraw(int deltaTime);

	void RenderFrame();

	DWORD _DeltaTime;

	BYTE  _KeyStates[256]; // DirectInput keyboard state buffer 

	DIDEVICEOBJECTDATA _KeyEvents[ GL_KEY_BUFFER_SIZE ]; // Buffered keyboard data
	
};

#endif