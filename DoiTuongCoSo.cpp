#include "DoiTuongCoSo.h"

DoiTuongCoSo::DoiTuongCoSo()
{
	rect_.x=0;
	rect_.y=0;
	p_object_=NULL;
}
DoiTuongCoSo::~DoiTuongCoSo()
{
	if(p_object_!=NULL)
	{
		SDL_FreeSurface(p_object_);
	}
}

bool DoiTuongCoSo::LoadImg(const char* file_name)
{
	p_object_=SDLxulychung::LoadImage(file_name);
	if (p_object_ == NULL)
		return false;
	return true;
}

void DoiTuongCoSo::Show(SDL_Surface* des)
{
	if (p_object_ != NULL)
	{
		 rect_ = SDLxulychung::ApplySurface(p_object_, des, rect_.x, rect_.y);
	}
}