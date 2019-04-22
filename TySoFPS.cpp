#include "TySoFPS.h"
#include "XuLyChung.h"

TySoFPS::TySoFPS()
{
	 start_tick_ = 0;
	 paused_tick_ = 0;

	 is_paused_ = false;
	 is_started_ = false;
}
TySoFPS::~TySoFPS()
{

}


void TySoFPS::start()
{
	is_started_ = true;
	is_paused_ = false;
	start_tick_ = SDL_GetTicks();
}
void TySoFPS::stop()
{
	is_paused_ = false;
	is_started_ = false;
}
void TySoFPS::paused()
{
	if(is_started_ == true && is_paused_ == false)
	{
		is_paused_ = true;
		paused_tick_ = SDL_GetTicks()- start_tick_;
	}
}
void TySoFPS::unpaused()
{
	if(is_paused_ == true)
	{
		is_paused_ = false;
		start_tick_ = SDL_GetTicks()- start_tick_;
		paused_tick_ = 0;
	}
}
int TySoFPS::get_ticks()
{
	if(is_started_ == true)
	{
		if(is_paused_ == true)
		{
			return paused_tick_;
		}
		else
		{
			return SDL_GetTicks()- start_tick_;
		}
	}
	return 0;
}
bool TySoFPS::is_started()
{
	return is_started_;
}
bool TySoFPS::is_paused()
{
	return is_paused_;
}