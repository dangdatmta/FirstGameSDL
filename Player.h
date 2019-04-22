#ifndef PLAYER_H_
#define PLAYER_H_
#include "DoiTuongCoSo.h"
#include <vector>

using namespace std;

class Player : public DoiTuongCoSo
{
private:
	int number_;
	int numHp;
	vector <int> pos_list_;
	/*vector<Player*> p_bood_list;

	void SetPosList(vector<Player*> bood_list){p_bood_list = bood_list;}
	vector<Player*> GetPosList() const {return p_bood_list;}*/
public:
	Player();
	~Player();
	void SetNumber(const int& num) {number_= num;}
	void AddPosTurn(const int& xpos);
	void Render(SDL_Surface* des);
	void Init1();
	void Init2();
	void Decrease();

	//void SetHp(const int& num) {numHp = num;}
	//void Increase();
};
#endif // !PLAYER_H_
