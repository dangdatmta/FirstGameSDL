#ifndef DOITUONGCOSO_H_
#define DOITUONGCOSO_H_
#include "XuLyChung.h"
class DoiTuongCoSo
{
protected:
	SDL_Rect rect_;
	SDL_Surface* p_object_;
public:
	DoiTuongCoSo();
	~DoiTuongCoSo();
	void Show(SDL_Surface* des);
	bool LoadImg(const char* file_name);

	void setRect(const int& x, const int& y) {rect_.x = x, rect_.y = y;}
	SDL_Rect GetRect() const {return rect_;}
	SDL_Surface* GetObject() {return p_object_;}
};
#endif // !DOITUONGCOSO_H_
