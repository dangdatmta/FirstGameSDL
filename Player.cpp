#include "Player.h"
#include "DoiTuongCoSo.h"

Player::Player()
{

}
Player::~Player()
{

}

void Player::AddPosTurn(const int& xpos)
{
	pos_list_.push_back(xpos);
}

//void Player::AddPosHp(const int& xpos, const int& ypos)
//{
//	pos_list_.push_back(xpos,ypos);
//}

//SHOW NHIEU HINH ANH 
void Player::Render(SDL_Surface* des)
{
	if(number_==pos_list_.size())
	{
		for(int i=0; i< pos_list_.size();i++)
		{
			rect_.x= pos_list_.at(i);			
			Show(des);
		}
	}
	else if (number_ > pos_list_.size())
	{
		rect_.x = pos_list_.size();
		Show(des);
	}
}

void Player::Init1()
{
	LoadImg("MainObj.png");
	number_= TURN_PLAYER;
	if(pos_list_.size() > 0)
	{
		pos_list_.clear();
	}
	AddPosTurn(FIRST_POS);
	AddPosTurn(SECOND_POS);
	AddPosTurn(THIRT_POS);
	
}
void Player::Init2()
{
	LoadImg("MainHp.png");
	number_= 5;
	if(pos_list_.size() > 0)
	{
		pos_list_.clear();
	}
	AddPosTurn(470);
	AddPosTurn(480);
	AddPosTurn(490);
	AddPosTurn(500);
	AddPosTurn(510);
}
void Player::Decrease()
{
	number_ --;
	pos_list_.pop_back();
}
//void Player::Increase()
//{
//	number_ += 5;
//  pos_list.push_back(470);
//}