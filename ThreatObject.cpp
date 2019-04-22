#include "ThreatObject.h"

ThreatObject::ThreatObject()
{
	rect_.x = SCREEN_WIDTH*0.5;
	rect_.y = 0;
	rect_.w = WIDTH_THREAT;
	rect_.h = HEIGHT_THREAT;

	x_val_ = 0;
	y_val_ = 0;
}

ThreatObject::~ThreatObject()
{
	if(p_amo_list_.size() >0)
	{
		for(int i=0; i<p_amo_list_.size(); i++)
		{
			AmoObject* p_amo = p_amo_list_.at(i);
			if(p_amo != NULL)
			{
				delete p_amo;
				p_amo = NULL;
			}
		}
		p_amo_list_.clear();
	}
}

void ThreatObject::InitAmo(AmoObject* p_amo)
{
	if(p_amo)
	{
		bool ret= p_amo->LoadImg(g_name_amo_threats);
		if(ret)
		{
			p_amo->set_is_move(true);
			p_amo->SetWidthHeight(WIDTH_AMO_THREAT,HEIGHT_AMO_THREAT);
			p_amo->set_type(AmoObject::AMO_THREAT);
			p_amo->setRect(this->rect_.x +this->rect_.w*0.5 , this->rect_.y);
			p_amo->set_y_val_(SPEED_AMO_THREATS);//SET TOC DO DAN BAN CUA THREATS
			p_amo_list_.push_back(p_amo);
		}
	}
}

void ThreatObject::MakeAmo(SDL_Surface* des, const int& x_limit, const int& y_limit)
{
	for(int i=0; i < p_amo_list_.size(); i++)
	{
		AmoObject* p_amo = p_amo_list_.at(i);
		if(p_amo)
		{
			if(p_amo->get_is_move())
			{
				p_amo->Show(des);
				p_amo->HandleMoveUpToDown();
			}
			else
			{
				p_amo->set_is_move(true);
				p_amo->setRect(rect_.x +rect_.w*0.45, rect_.y + rect_.h);
			}
		}
	}
}
void ThreatObject::HandleMove(const int& x_border, const int& y_border)
{
	rect_.y += y_val_;
	if(rect_.y > SCREEN_HEIGHT )
	{
		rect_.y = 0;
		rect_.x = SDLxulychung::MakeRandValue();
	}
}
void ThreatObject::HandleInputAction(SDL_Event events)
{
	//to do
}
void ThreatObject::Reset(const int& yboder)
{
	rect_.x = SDLxulychung::MakeRandValue();
	rect_.y = yboder;

	/*for(int i=0; i<p_amo_list_.size(); i++)
	{
		AmoObject* p_amo = p_amo_list_.at(i);
		if(p_amo)
		{
			ResetAmo(p_amo);
		}
	}*/
}

void ThreatObject::ResetAmo(AmoObject* p_amo)
{
	p_amo->setRect(this->rect_.x +this->rect_.w*0.5 , this->rect_.y);
}