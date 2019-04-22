#ifndef THREAT_OBJECT_H_
#define THREAT_OBJECT_H_
#include "XuLyChung.h"
#include "DoiTuongCoSo.h"
#include "AmoObject.h"
#include <vector>

using namespace std;

#define WIDTH_THREAT 37
#define HEIGHT_THREAT 30

class ThreatObject: public DoiTuongCoSo
{
private:
	int x_val_;
	int y_val_;

	std::vector<AmoObject*> p_amo_list_;
public:
	ThreatObject();
	~ThreatObject();

	void HandleMove(const int& x_border, const int& y_border);
	void HandleInputAction(SDL_Event events);

	void set_x_val(const int& val) {x_val_ = val;}
	int get_x_val() const {return x_val_;}
	void set_y_val(const int& val) {y_val_ = val;}
	int get_y_val() const {return y_val_;}

	void SetAmoList(vector<AmoObject*> amo_list){p_amo_list_ = amo_list;}
	vector<AmoObject*> GetAmoList() const {return p_amo_list_;}

	void InitAmo(AmoObject* p_amo);
	void MakeAmo(SDL_Surface* des, const int& x_limit, const int& y_limit);
	void Reset(const int& yboder);
	void ResetAmo(AmoObject* p_amo);
};
#endif // !THREAT_OBJECT_H_
