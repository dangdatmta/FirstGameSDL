#ifndef XULYCHUNG_H_
#define XULYCHUNG_H_

using namespace std;
#include<Windows.h>
#include<SDL.h>
#include<string>
#include<SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>


//SCREEN
const int SCREEN_WIDTH  = 525;
const int SCREEN_HEIGHT = 700;
const int SCREEN_BPP    = 32;
const int SPEED_SCREEN  = 1;
const int NUMBER_FRAME = 4;


//MAIN OBJECT
const int FRAME_PER_SECOND      = 30; //fps
const int POS_X_START_MAIN_OBJ  = 220;
const int POS_Y_START_MAIN_OBJ  = 600;
const int SPEED_MAIN_OBJECT     = 10;//3
const int SPEED_AMO_MAIN        = 15;//5

//Threats
const int SPEED_THREAT                  = 4;
const int NUM_THREATS                   = 3;
const int SPEED_AMO_THREATS             = 10;
const int VAL_OFFSET_START_POST_THREATS = 400;

static SDL_Surface* g_screen = NULL;
static SDL_Surface* g_bkground = NULL;
static SDL_Surface* g_menu_intro = NULL;
static SDL_Surface* g_menu_over = NULL;
static SDL_Event g_even;

//Audio
static Mix_Chunk* g_sound_amo = NULL;
static Mix_Chunk* g_sound_VuNo[2];
static Mix_Chunk* g_sound_bgr = NULL;
static Mix_Chunk* g_sound_over = NULL;
static Mix_Chunk* g_sound_intro = NULL;

static char g_name_bgr[] = {"bgrr.jpg"};
static char g_name_audio_intro[] = {"intro.wav"};

static char g_name_main_obj[]           = {"MainObj.png"};
static char g_name_vuno[]               = {"VuNo.png"};
static char g_name_amo_main[]           = {"amo.png"};
static char g_name_audio_amo_main[]     = {"fire.wav"};
static char g_name_audio_vuno_main[]    = {"explosionMain.wav"};

static char g_name_threats[]            = {"ThreatObj.png"};
static char g_name_amo_threats[]        = {"AmoThreat.png"};
static char g_nam_audio_vuno_threats[]  = {"explosionThreat.wav"};
static char g_name_audio_background[]   = {"sound_bgr.wav"};

static char g_name_audio_over[]         = {"GameOver.wav"};
//player
const int TURN_PLAYER = 3;
const int FIRST_POS   = 20;
const int SECOND_POS  = 60;
const int THIRT_POS   = 100;
const int DELAY_COMEBACK = 1000;

namespace SDLxulychung
{
	SDL_Surface* LoadImage(string file_path);
	SDL_Rect ApplySurface(SDL_Surface* src, SDL_Surface* des, int x, int y);
	void ApplySurfaceClip(SDL_Surface* src, SDL_Surface* des, SDL_Rect* clip, int x, int y);
	void CleanUp();
	bool CheckVaCham(const SDL_Rect& object1, const SDL_Rect& object2);
	int MakeRandValue(const int& div_val = 400 );
	int ShowMenuIntro(SDL_Surface*des, TTF_Font* font);
	int ShowMenuOver(SDL_Surface*des, TTF_Font* font);
	bool CheckFocusMenu(const int& x, const int& y, const SDL_Rect& rect);
}
#endif // !XULYCHUNG_H_
