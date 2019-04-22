#ifndef AMO_OBJECT_H_
#define AMO_OBJECT_H_
#include "DoiTuongCoSo.h"

#define WIDTH_AMO 6
#define HEIGHT_AMO 15

#define WIDTH_AMO_THREAT 5
#define HEIGHT_AMO_THREAT 5

class AmoObject : public DoiTuongCoSo
{
public:
	enum AmoType
	{
		NONE = 0,
		AMO = 1,
		AMO_THREAT = 2
	};

	AmoObject();
	~AmoObject();

	void HandleInputAction(SDL_Event events);
	void HandleMove(const int& x_border, const int& y_border);
	void HandleMoveUpToDown();

	int get_type() const {return amo_type_;}
	void set_type(const int& type ) {amo_type_ = type;}

	bool get_is_move() const {return is_move_;}
	void set_is_move(bool is_move) {is_move_=is_move;}
	void SetWidthHeight(const int& width, const int& height) {rect_.w= width; rect_.h =height;};

	void set_x_val_(const int& val) {x_val_ = val;}
	void set_y_val_(const int& val) {y_val_ = val;}

	int get_x_val_() const {return x_val_;}
	int get_y_val_() const {return y_val_;}

private:
	int x_val_;
	int y_val_;
	unsigned int amo_type_;
	bool is_move_;
};
#endif // !AMO_OBJECT_H_
