#include "common.h"

int sign(double d) {
	//if (fabs(d) < pow(10, -10))
	//	return 0;
	if (d < 0)
		return -1;
	else
		return 1;
}
Obj2D operator+(const Obj2D& lhs, const Obj2D& rhs) {
	return { lhs.x + rhs.x, lhs.y + rhs.y };
}

Obj2D operator-(const Obj2D& lhs, const Obj2D& rhs) {
	return { lhs.x - rhs.x, lhs.y - rhs.y };
}

Obj2D operator-(const Obj2D& obj2D) {
	return { -obj2D.x, -obj2D.y };
}

Obj2D operator*(const Obj2D& obj2D, const double& number) {
	return { obj2D.x * number, obj2D.y * number };
}