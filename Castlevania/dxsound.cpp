#include "dxsound.h"

CSoundManager *dsound;

int InitDirectSound(HWND hwnd)
{
	HRESULT result;

	// create DirectSound manager object;
	dsound = new CSoundManager();

	//initialize DirectSound
	result = dsound->Initialize(hwnd, DSSCL_PRIORITY);
	if (result != DS_OK)
		return 0;

	//set the primary buffer format
	result = dsound->SetPrimaryBufferFormat(2, 22050, 16);
	if (result != DS_OK)
		return 0;

	//return success
	return 1;
}

CSound *LoadSound(char *fileName)
{
	HRESULT result;

	//Create local reference to wave data
	CSound *wave;

	//attempt to load wave file
	result = dsound->Create(&wave, fileName);
	if (result != DS_OK)
		return 0;

	//return the wave
	return wave;
}

void PlaySound(CSound *sound)
{
	sound->Play();
}

void LoopSound(CSound *sound)
{
	sound->Play(0, DSBPLAY_LOOPING);
}

void StopSound(CSound *sound)
{
	sound->Stop();
}