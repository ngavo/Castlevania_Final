#include "sound.h"

Sound::Sound() {}
Sound::~Sound() {}

Sound* Sound::instance;

Sound* Sound::GetInstance()
{
	if (instance == nullptr)
		instance = new Sound();
	return instance;
}

void Sound::loadSound(HWND hwnd)
{
	InitDirectSound(hwnd);

	CSound* sound = NULL;

	sound = LoadSound("Resources/sound/usingwhip.wav");
	listSound[eSoundID::USING_WHIP] = sound;

	sound = LoadSound("Resources/sound/splashwater.wav");
	listSound[eSoundID::SLASH_WATER] = sound;

	sound = LoadSound("Resources/sound/select.wav");
	listSound[eSoundID::SELECT] = sound;

	sound = LoadSound("Resources/sound/pause.wav");
	listSound[eSoundID::PAUSE] = sound;

	sound = LoadSound("Resources/sound/opendoor.wav");
	listSound[eSoundID::OPEN_DOOR] = sound;

	sound = LoadSound("Resources/sound/holywater.wav");
	listSound[eSoundID::HOLY_WATER] = sound;

	sound = LoadSound("Resources/sound/holycross.wav");
	listSound[eSoundID::HOLY_CROSS] = sound;

	sound = LoadSound("Resources/sound/hitcannon.wav");
	listSound[eSoundID::HIT_CANNON] = sound;

	sound = LoadSound("Resources/sound/hit.wav");
	listSound[eSoundID::HIT_SOUND] = sound;

	sound = LoadSound("Resources/sound/fallingdownwatersurface.wav");
	listSound[eSoundID::FALLING_DOWN_WATER_SUFACE] = sound;

	sound = LoadSound("Resources/sound/falling.wav");
	listSound[eSoundID::FALLING] = sound;

	sound = LoadSound("Resources/sound/decreaseweaponusepoint.wav");
	listSound[eSoundID::DECREASE_WEAPON_USE_POINT] = sound;

	sound = LoadSound("Resources/sound/collectweapon.wav");
	listSound[eSoundID::COLLECT_WEAPON] = sound;

	sound = LoadSound("Resources/sound/collectitem.wav");
	listSound[eSoundID::COLLECT_ITEM] = sound;

	sound = LoadSound("Resources/sound/gointocastle.wav");
	listSound[eSoundID::GO_INTO_CASTLE] = sound;

	sound = LoadSound("Resources/sound/hurted.wav");
	listSound[eSoundID::SIMON_HURTED] = sound;

	sound = LoadSound("Resources/music/Boss_Battle_Poison_Mind.wav");
	listSound[eSoundID::BOSS_BATTLE_POISON_MIND] = sound;

	sound = LoadSound("Resources/music/Game_Over.wav");
	listSound[eSoundID::GAME_OVER] = sound;

	sound = LoadSound("Resources/music/Game_Start_Prologue.wav");
	listSound[eSoundID::GAME_START_PROLOGUE] = sound;

	sound = LoadSound("Resources/music/Life_Lost.wav");
	listSound[eSoundID::LIFE_LOST] = sound;

	sound = LoadSound("Resources/music/Stage_01_Vampire_Killer.wav");
	listSound[eSoundID::STAGE_01_VAMPIRE_KILLER] = sound;

	sound = LoadSound("Resources/music/Stage_04_Stalker.wav");
	listSound[eSoundID::STAGE_04_STALKER] = sound;

	sound = LoadSound("Resources/music/Stage_Clear.wav");
	listSound[eSoundID::STAGE_CLEAR] = sound;

	sound = LoadSound("Resources/music/Title_Theme_Prelude.wav");
	listSound[eSoundID::TITLE_THEME_PRELUDE] = sound;

	sound = LoadSound("Resources/sound/eat_change_state_ball.wav");
	listSound[eSoundID::EAT_CHANGE_STATE_BALL] = sound;

	sound = LoadSound("Resources/sound/collectmoney.wav");
	listSound[eSoundID::MONEY] = sound;
	sound = LoadSound("Resources/sound/Knife.wav");
	listSound[eSoundID::KNIFE] = sound;
}

void Sound::Play(eSoundID id)
{
	auto sound = listSound[id];
	if (sound != NULL)
		PlaySound(sound);
}

void Sound::PlayLoop(eSoundID id)
{
	auto sound = listSound[id];
	if (sound != NULL)
		LoopSound(sound);
}

void Sound::Stop(eSoundID id)
{
	auto sound = listSound[id];
	if (sound != NULL)
		StopSound(sound);
}

bool Sound::IsPLaying(eSoundID id)
{
	auto sound = listSound[id];
	if (sound != NULL)
		return sound->IsSoundPlaying();
	return false;
}