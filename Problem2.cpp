#include <iostream>

template<class T_CLASS>
class Vector2D
{
public:
	T_CLASS x_, y_;
	void sum()
	{
		std::cout << x_+y_ << std::endl;
	}
};

int main()
{
	Vector2D <int> my_int;
	my_int.x_ = 1;
	my_int.y_ = 2;
	my_int.sum();

	Vector2D <float> my_float;
	my_float.x_ = 2.25f;
	my_float.y_ = 3.3f;
	my_float.sum();

	Vector2D <double> my_double;
	my_double.x_ = 5.54321;
	my_double.y_ = 3.12345;
	my_double.sum();


}

