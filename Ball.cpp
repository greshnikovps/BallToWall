#include "Ball.h"

using namespace std;

Ball::Ball(int _unitCount, ICanvas* _canvas)
	: canvas(_canvas)
{
	velocities = vector<Velocity>(_unitCount, { -START_VELOCITY, 0 });
	
	coords.resize(_unitCount);
	for (int i = 0; i < _unitCount; i++) 
		coords[i] = { cos(2 * PI / _unitCount * i) + START_X_COORD, sin(2 * PI / _unitCount * i) };

	params.stiffness = SPRING_STIFFNESS;
	params.springlength = 2 * sin(PI / (double)_unitCount);
	params.ballSquare = calcSquare();
}

// принимает промежуток времени и рисует координаты, 
// изменившиеся за это время
void Ball::drawNewCoords(const double& dt)
{
	calcNewCoords(dt);
	canvas->draw(coords);
}

// вычисляет площадь мяча
double Ball::calcSquare() const
{
	double square = 0;
	for (size_t i = 0; i < coords.size(); i++)
		square += coords[i].x * coords[(i + 1) % coords.size()].y;

	for (size_t i = 0; i < coords.size(); i++)
		square -= coords[(i + 1) % coords.size()].x * coords[i].y;
	square /= 2;
	square = abs(square);
	return square;
}

// вычисляет расстояние между двумя точками
double Ball::calcDistance(const Coord& left, const Coord& right)
{
	return sqrt(pow(left.x - right.x, 2) + pow(left.y - right.y, 2));
}

// вычисляет давление изходя из площади круга
double Ball::caclPressure() const
{
	double deltaSquare = 1 - params.ballSquare / calcSquare();
	return - deltaSquare * PRESSURE_FACTOR;
}

Coord Ball::centerMass() const {
	Coord centerCoord = { 0, 0 };
	for (const auto& point : coords) 
		centerCoord = centerCoord + point;
	
	centerCoord = centerCoord * (1 / (double)coords.size());
	return centerCoord;
}

Force Ball::LennardJhonesForce(const Coord& coord) const
{
	double r = coord.x - WALL_X_COORD;
	if (r > LJ_SIGMA)
		return { 0, 0 };
	return { 4 * LJ_EPSILON * (pow(LJ_SIGMA / r, 12) - pow(LJ_SIGMA / r, 6)), 0 };
}

// принимает модуль силы и координаты точки и соседней точки
// вычисляет силу давления оказываемую на точку
Force Ball::calcPressureForce(const double& pressureAbs, 
	const Coord& point, const Coord& neighbour,
	const Coord& centerMassCoord) const 
{
	double length = calcDistance(point, neighbour);

	double a_x = neighbour.x - point.x;
	double a_y = neighbour.y - point.y;
	
	Force pressureForce = {
		//-sign(centerMassCoord.x - point.x) *
		//a_y / sqrt(a_x * a_x + a_y * a_y),

		-(neighbour.y - point.y) / length,
		//sign(centerMassCoord.y - point.y) *
		//a_x / sqrt(a_x * a_x + a_y * a_y)
		(neighbour.x - point.x) / length 
	};
	//cout << "    " << pressureForce.x << " " << pressureForce.y << '\n';
	return pressureForce * pressureAbs;
}

// считает через центр масс
Force Ball::calcPressureForce(const double& pressureAbs,
	const Coord& point, const Coord& centerMassCoord) const
{
	double length = calcDistance(point, centerMassCoord);

	Force pressureForce = { (centerMassCoord.x - point.x) / length,
		(centerMassCoord.y - point.y) / length };

	return pressureForce * pressureAbs;
}

// принимает две координаты концов пружины
// возвращает силу в соответствии с законом гука
Force Ball::calcHookeForce(const Coord& target, const Coord& forceSource) const
{
	double springLength = calcDistance(target, forceSource);
	double ForceAbs = (springLength - params.springlength) * params.stiffness;

	return { ForceAbs * (forceSource.x - target.x) / springLength,
		ForceAbs * (forceSource.y - target.y) / springLength };
}

// принимает промежуток времени и обновляет координаты, 
// изменившиеся за это время
void Ball::calcNewCoords(const double& dt)
{
	Force leftHookeForce = -calcHookeForce(coords.back(), coords[0]);
	Force rightHookeForce = { 0, 0 };
	Coord firstCoord = coords[0];
	
	Coord centerMassCoord = centerMass();

	double pressureAbs = caclPressure();
	Force leftPressureForce = calcPressureForce(pressureAbs, coords[0], 
		coords.back(), centerMassCoord);
	Force rightPressureForce = { 0, 0 };

	for (size_t i = 0; i < coords.size(); i++) {
		
		rightHookeForce = calcHookeForce(coords[i],
			i + 1 == coords.size() ? firstCoord : coords[i + 1]);
		rightPressureForce = calcPressureForce(pressureAbs, coords[i],
			//i + 1 == coords.size() ? firstCoord : coords[i + 1],
			centerMassCoord);

		velocities[i] = velocities[i] + (leftHookeForce + rightHookeForce
			+ rightPressureForce 
			//+ leftPressureForce
			+ LennardJhonesForce(coords[i]) * LJ_FACTOR
			) * dt;

		coords[i] = coords[i] + velocities[i] * dt;

		leftHookeForce = -rightHookeForce;
		leftPressureForce = rightPressureForce;
	}
}