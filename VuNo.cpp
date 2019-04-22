#include "VuNo.h"

VuNo::VuNo()
{

}
VuNo::~VuNo()
{

}
void VuNo::set_clip()
{
	clip_[0].x = 0;
	clip_[0].y = 0;
	clip_[0].w = VUNO_WIDTH;
	clip_[0].h = VUNO_HEIGHT;

	clip_[1].x = VUNO_WIDTH;
	clip_[1].y = 0;
	clip_[1].w = VUNO_WIDTH;
	clip_[1].h = VUNO_HEIGHT;

	clip_[2].x = VUNO_WIDTH*2;
	clip_[2].y = 0;
	clip_[2].w = VUNO_WIDTH;
	clip_[2].h = VUNO_HEIGHT;

	clip_[3].x = VUNO_WIDTH*3;
	clip_[3].y = 0;
	clip_[3].w = VUNO_WIDTH;
	clip_[3].h = VUNO_HEIGHT;
}

void VuNo::showVuNo(SDL_Surface* des)
{
	if(frame_ >= 4)
	{
		frame_ = 0;
	}
	SDLxulychung::ApplySurfaceClip(this->p_object_, des, &clip_[frame_], rect_.x, rect_.y);
}