#ifndef MAINOBJECT_H_
#define MAINOBJECT_H_

#include "DoiTuongCoSo.h"
#include "XuLyChung.h"
#include "AmoObject.h"
#include <vector>

#define WIDTH_MAIN_OBJECT 37
#define HEIGHT_MAIN_OBJECT 30

class MainObject : public DoiTuongCoSo
{
private:
	int x_val_;
	int y_val_;

	std::vector<AmoObject*> p_amo_list_;

public:
	MainObject();
	~MainObject();

	void HandleInputAction(SDL_Event events, Mix_Chunk* amo_sound);
	void HandleMove();
	void SetAmoList(std::vector<AmoObject*> amo_list){p_amo_list_ = amo_list;}
	std::vector<AmoObject*> GetAmoList() const {return p_amo_list_;}
	void MakeAmo(SDL_Surface* des);
	void RemoveAmo(const int& dem);
};
#endif // !MAINOBJECT_H_
