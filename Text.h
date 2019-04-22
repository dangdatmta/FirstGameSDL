#ifndef TEXT_H_
#define TEXT_H_
#include "DoiTuongCoSo.h"
#include <string>
#include <SDL_ttf.h>

using namespace std;
class Text: public DoiTuongCoSo
{
private:
	string str_val_;
	SDL_Color text_color_;

public:
	enum TextColor
	{
		RED_TEXT = 0,
		WHITE_TEXT = 1,
		BLACK_TEXT = 2,
	};
	Text();
	~Text();

	void SetText(const string& text) {str_val_= text;}
	void SetColor(const int& type);
	void CreatGameText(TTF_Font* font, SDL_Surface* des);
};

#endif // !TEXT_H_
