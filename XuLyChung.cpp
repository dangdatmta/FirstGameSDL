#include "XuLyChung.h"
#include "Text.h"

using namespace std;

bool SDLxulychung::CheckFocusMenu(const int& x, const int& y, const SDL_Rect& rect)
{
	if(x>=rect.x && x<=rect.x + rect.w &&
    	y>=rect.y && y<=rect.y + rect.h)
	{
		return true;
	}
	return false;
}
int SDLxulychung::ShowMenuIntro(SDL_Surface*des, TTF_Font* font)
{
	g_menu_intro = LoadImage("Menu.png");
	if(g_menu_intro == NULL)
	{
		return 1;
	}
	
	const int Number_item_menu = 2;
	SDL_Rect pos_arr[Number_item_menu];
	pos_arr[0].x = 350;
	pos_arr[0].y = 400;

	pos_arr[1].x = 350;
	pos_arr[1].y = 470;

	Text text_Menu[Number_item_menu];

	text_Menu[0].SetText("PLAY");
	text_Menu[0].SetColor(Text::BLACK_TEXT);
	text_Menu[0].setRect(pos_arr[0].x, pos_arr[0].y);

	text_Menu[1].SetText("QUIT");
	text_Menu[1].SetColor(Text::BLACK_TEXT);
	text_Menu[1].setRect(pos_arr[1].x, pos_arr[1].y);

	bool selected[Number_item_menu] = {0,0};
	int xm=0;
	int ym=0;

	SDL_Event m_event;
	while (true)
	{
		SDLxulychung::ApplySurface(g_menu_intro, des, 0, 0);
		for(int i=0; i<Number_item_menu; i++)
		{
			text_Menu[i].CreatGameText(font, des);
		}
		while (SDL_PollEvent(&m_event))
		{
			switch (m_event.type)
			{
			case SDL_QUIT:
					return 1;
			case SDL_MOUSEMOTION:
					{
						xm = m_event.motion.x;
						ym = m_event.motion.y;
						for (int i=0; i<Number_item_menu; i++)
						{
							if(CheckFocusMenu(xm, ym, text_Menu[i].GetRect()))
							{
								if(selected[i] == false)
								{
									selected[i] = 1;
									text_Menu[i].SetColor(Text::RED_TEXT);
								}
							}
							else
							{
								if(selected[i] == true)
								{
									selected[i] = 0;
									text_Menu[i].SetColor(Text::BLACK_TEXT);
								}
							}
						}
					}
					break;
			case SDL_MOUSEBUTTONDOWN:
				{
					xm = m_event.button.x;
					ym = m_event.button.y;
					for (int i=0; i<Number_item_menu; i++)
					{
						if(CheckFocusMenu(xm, ym, text_Menu[i].GetRect()))
						{
							return i;
						}
					}
				}
				break;
			case SDL_KEYDOWN:
				if(m_event.key.keysym.sym == SDLK_ESCAPE)
					return 1;
			default:
				break;
			}
		}
		SDL_Flip(des);
	}
	return 1;
}

int SDLxulychung::ShowMenuOver(SDL_Surface*des, TTF_Font* font)
{
	g_menu_over = LoadImage("overGame.png");
	if(g_menu_over == NULL)
	{
		return 1;
	}

	const int Number_item_menu2 = 2;
	SDL_Rect pos_arr[Number_item_menu2];
	pos_arr[0].x = 100;
	pos_arr[0].y = 450;

	pos_arr[1].x = 100;
	pos_arr[1].y = 520;

	Text text_Menu2[Number_item_menu2];

	text_Menu2[0].SetText("PLAY AGAIN");
	text_Menu2[0].SetColor(Text::BLACK_TEXT);
	text_Menu2[0].setRect(pos_arr[0].x, pos_arr[0].y);

	text_Menu2[1].SetText("QUIT");
	text_Menu2[1].SetColor(Text::BLACK_TEXT);
	text_Menu2[1].setRect(pos_arr[1].x, pos_arr[1].y);

	bool selected[Number_item_menu2] = {0,0};
	int xm2=0;
	int ym2=0;

	SDL_Event m_event;
	while (true)
	{
		SDLxulychung::ApplySurface(g_menu_over, des, 0, 0);
		for(int i=0; i<Number_item_menu2; i++)
		{
			text_Menu2[i].CreatGameText(font, des);
		}
		while (SDL_PollEvent(&m_event))
		{
			switch (m_event.type)
			{
			case SDL_QUIT:
				return 1;
			case SDL_MOUSEMOTION:
				{
					xm2 = m_event.motion.x;
					ym2 = m_event.motion.y;
					for (int i=0; i<Number_item_menu2; i++)
					{
						if(CheckFocusMenu(xm2, ym2, text_Menu2[i].GetRect()))
						{
							if(selected[i] == false)
							{
								selected[i] = 1;
								text_Menu2[i].SetColor(Text::RED_TEXT);
							}
						}
						else
						{
							/*Mix_HaltChannel(-1);
							Mix_PlayChannel(0, g_sound_bgr, -1);*/
							if(selected[i] == true)
							{
								selected[i] = 0;
								text_Menu2[i].SetColor(Text::BLACK_TEXT);
							}
						}
					}
				}
				break;
			case SDL_MOUSEBUTTONDOWN:
				{
					xm2 = m_event.button.x;
					ym2 = m_event.button.y;
					for (int i=0; i<Number_item_menu2; i++)
					{
						if(CheckFocusMenu(xm2, ym2, text_Menu2[i].GetRect()))
						{
							return i;
							SDL_FreeSurface(g_screen);
						}
					}
				}
				break;
			case SDL_KEYDOWN:
				if(m_event.key.keysym.sym == SDLK_ESCAPE)
					return 1;
			default:
				break;
			}
		}
		SDL_Flip(des);
	}
	return 1;
}

SDL_Surface* SDLxulychung::LoadImage(string file_path)
{
	SDL_Surface * load_image = NULL;
	SDL_Surface* optimize_image = NULL;
	load_image = IMG_Load(file_path.c_str());
	if (load_image != NULL)
	{
		optimize_image= SDL_DisplayFormat(load_image);
		SDL_FreeSurface(load_image);
		if (optimize_image != NULL) 
		{
			UINT32 color_key = SDL_MapRGB(optimize_image->format, 128, 128, 0);
			SDL_SetColorKey(optimize_image, SDL_SRCCOLORKEY, color_key);
		}
	}
	return optimize_image;
}
SDL_Rect SDLxulychung::ApplySurface(SDL_Surface* src, SDL_Surface* des, int x, int y)
{
	SDL_Rect offset;
	offset.x = x;
	offset.y = y;
	SDL_BlitSurface(src, NULL, des, &offset);

	if (offset.y == 0)
	{
		offset.y = y;
	}
	if (offset.x == 0)
	{
		offset.x  = x;
	}
	return offset;
}

void SDLxulychung::ApplySurfaceClip(SDL_Surface* src, SDL_Surface* des,SDL_Rect* clip, int x, int y)
{
	SDL_Rect offset;
	offset.x = x;
	offset.y = y;
	SDL_BlitSurface(src, clip, des, &offset);
}
bool SDLxulychung::CheckVaCham(const SDL_Rect& object1, const SDL_Rect& object2)
{
	int left_a = object1.x;
	int right_a = object1.x + object1.w;
	int top_a = object1.y;
	int bottom_a = object1.y + object1.h;

	int left_b = object2.x;
	int right_b = object2.x + object2.w;
	int top_b = object2.y;
	int bottom_b = object2.y + object2.h;

	// Case 1: size object 1 < size object 2
	if (left_a > left_b && left_a < right_b)
	{
		if (top_a > top_b && top_a < bottom_b)
		{
			return true;
		}
	}

	if (left_a > left_b && left_a < right_b)
	{
		if (bottom_a > top_b && bottom_a < bottom_b)
		{
			return true;
		}
	}

	if (right_a > left_b && right_a < right_b)
	{
		if (top_a > top_b && top_a < bottom_b)
		{
			return true;
		}
	}

	if (right_a > left_b && right_a < right_b)
	{
		if (bottom_a > top_b && bottom_a < bottom_b)
		{
			return true;
		}
	}

	// Case 2: size object 1 < size object 2
	if (left_b > left_a && left_b < right_a)
	{
		if (top_b > top_a && top_b < bottom_a)
		{
			return true;
		}
	}

	if (left_b > left_a && left_b < right_a)
	{
		if (bottom_b > top_a && bottom_b < bottom_a)
		{
			return true;
		}
	}

	if (right_b > left_a && right_b < right_a)
	{
		if (top_b > top_a && top_b < bottom_a)
		{
			return true;
		}
	}

	if (right_b > left_a && right_b < right_a)
	{
		if (bottom_b > top_a && bottom_b < bottom_a)
		{
			return true;
		}
	}

	// Case 3: size object 1 = size object 2
	if (top_a == top_b && right_a == right_b && bottom_a == bottom_b)
	{
		return true;
	}

	return false;
}
int SDLxulychung::MakeRandValue(const int& div_val /*400*/)
{
	int rand_x = rand()%div_val;
	if (rand_x > SCREEN_WIDTH )
	{
		rand_x = SCREEN_WIDTH*0.3;
	}
	return rand_x;
}
void SDLxulychung::CleanUp()
{
	SDL_FreeSurface(g_screen);
	SDL_FreeSurface(g_bkground);
}