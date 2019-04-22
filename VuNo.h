#ifndef VU_NO_H_
#define VU_NO_H_

#include "DoiTuongCoSo.h"
#include "XuLyChung.h"
const int VUNO_WIDTH = 60;
const int VUNO_HEIGHT = 240;
class VuNo : public DoiTuongCoSo
{
private:
	int frame_;
	SDL_Rect clip_[4];

public:
	VuNo();
	~VuNo();
	void set_clip();
	void set_frame(const int& fr) {frame_ =fr;}
	void showVuNo(SDL_Surface* des);

};
#endif // !VU_NO_H_
