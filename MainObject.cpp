#include "MainObject.h"

MainObject::MainObject()
{
	rect_.x=0;
	rect_.y=0;
	rect_.w = WIDTH_MAIN_OBJECT;
	rect_.h = HEIGHT_MAIN_OBJECT;
	x_val_=0;
	y_val_=0;
}
MainObject::~MainObject()
{
}
void MainObject::HandleInputAction(SDL_Event events, Mix_Chunk* amo_sound)
{
	if (events.type==SDL_KEYDOWN)
	{
		switch (events.key.keysym.sym)
		{
		case SDLK_w:
			y_val_ -= SPEED_MAIN_OBJECT;
			break;
		case SDLK_s:
			y_val_ += SPEED_MAIN_OBJECT;
			break;
		case SDLK_d:
			x_val_ += SPEED_MAIN_OBJECT;
			break;
		case SDLK_a:
			x_val_ -= SPEED_MAIN_OBJECT;
			break;
		case SDLK_SPACE:
			{
				AmoObject* p_amo = new AmoObject();
				p_amo->SetWidthHeight(WIDTH_AMO, HEIGHT_AMO);
				p_amo->LoadImg(g_name_amo_main);
				p_amo->set_is_move(true);
				p_amo->set_y_val_(SPEED_AMO_MAIN);//SET TOC DO DAN BAN CUA MAIN
				p_amo->set_type(AmoObject::AMO);
				Mix_PlayChannel(-1, amo_sound, 0);
				
				p_amo->setRect(this->rect_.x + this->rect_.w*0.45, this->rect_.y-10);
				p_amo_list_.push_back(p_amo);
			}
			
			break;
		default:
			break;
		}
	}
	else if(events.type==SDL_KEYUP)
	{
		switch (events.key.keysym.sym)
		{
		case SDLK_w:
			y_val_ += SPEED_MAIN_OBJECT;
			break;
		case SDLK_s:
			y_val_ -= SPEED_MAIN_OBJECT; 
			break;
		case SDLK_d:
			x_val_ -= SPEED_MAIN_OBJECT;
			break;
		case SDLK_a:
			x_val_ += SPEED_MAIN_OBJECT;
			break;
		default:
			break;
		}
	}
	else{}
}

void MainObject::MakeAmo(SDL_Surface* des)
{
	for(int i=0; i< p_amo_list_.size();i++)
	{
		AmoObject* p_amo = p_amo_list_.at(i);
		if(p_amo!=NULL)
		{
			if(p_amo->get_is_move())
			{
				p_amo->Show(des);
				p_amo->HandleMove(SCREEN_WIDTH, SCREEN_HEIGHT);
			}
			else
			{
				if(p_amo!=NULL)
				{
					p_amo_list_.erase(p_amo_list_.begin()+i);
					delete p_amo;
					p_amo= NULL;
				}
			}
		}
	}
}
void MainObject::HandleMove()
{
	rect_.x += x_val_;
	if (rect_.x < 0 || rect_.x + WIDTH_MAIN_OBJECT > SCREEN_WIDTH )
	{
		rect_.x -= x_val_;
	}

	rect_.y += y_val_;
	if(rect_.y < 0 || rect_.y + HEIGHT_MAIN_OBJECT > SCREEN_HEIGHT)
	{
		rect_.y -= y_val_;
	}
}

void MainObject::RemoveAmo(const int& dem)
{
	for(int i=0; i< p_amo_list_.size(); i++)
	{
		if(dem < p_amo_list_.size())
		{
			AmoObject* p_amo = p_amo_list_.at(dem);
			p_amo_list_.erase(p_amo_list_.begin() + dem);
			if(p_amo != NULL)
			{
				delete p_amo;
				p_amo = NULL;
				break;
			}
		}
	}
}