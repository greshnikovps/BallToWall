#pragma once

#include <math.h>
#define _USE_MATH_DEFINES

#define PI 3.14159265358979323846
#define START_X_COORD -2
#define SPRING_STIFFNESS 1000
#define WALL_X_COORD -4
#define START_VELOCITY 0.1
#define SCALE_FACTOR 60
#define CANVAS_SIZE 600
#define CIRCLE_RADIUS 3.f
#define PRESSURE_FACTOR -30
#define LJ_FACTOR 1
#define LJ_SIGMA 0.2
#define LJ_EPSILON 0.5

int sign(double d);

struct Params {
	double stiffness;
	double springlength;
	double ballSquare;
};

struct Obj2D {
	double x;
	double y;
};

Obj2D operator+(const Obj2D& lhs, const Obj2D& rhs);

Obj2D operator-(const Obj2D& lhs, const Obj2D& rhs);

Obj2D operator-(const Obj2D& obj2D);

Obj2D operator*(const Obj2D& obj2D, const double& number);

typedef Obj2D Velocity;
typedef Obj2D Coord;
typedef Obj2D Force;