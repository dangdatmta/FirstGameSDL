#include "Text.h"

Text::Text()
{
	rect_.x = 230;
	rect_.y = 7;
	text_color_.r = 255;
	text_color_.g = 0;
	text_color_.b = 0;
}
Text::~Text()
{

}

void Text::SetColor(const int& type)
{
	if(type == RED_TEXT)
	{
		SDL_Color color = {255, 0, 0};
		text_color_ = color;
	}
	else if (type == WHITE_TEXT)
	{
		SDL_Color color = {255, 255, 255};
		text_color_ = color;
	}
	else
	{
		SDL_Color color = {0, 0 ,0};
		text_color_ = color;
	}
}
void Text::CreatGameText(TTF_Font* font, SDL_Surface* des)
{
	p_object_ = TTF_RenderText_Solid(font, str_val_.c_str(), text_color_);
	Show(des);
}