#pragma once
#include <vector>
#include "common.h"
#include "ICanvas.h"

//debug
#include <iostream>
#include <iomanip>

class Ball {
public:
	Ball(int _unitCount, ICanvas* _canvas);

	// принимает промежуток времени и рисует координаты, 
	// изменившиеся за это время
	void drawNewCoords(const double& dt);
	
private:
	// вычисляет площадь мяча
	double calcSquare() const;

	// вычисляет расстояние между двумя точками
	static double calcDistance(const Coord& left, const Coord& right);

	// вычисляет давление изходя из площади круга
	double caclPressure() const;

	// принимает модуль силы и координаты точки и центра масс
	// вычисляет силу давления оказываемую на точку
	Force calcPressureForce(const double& pressureAbs,
		const Coord& point, const Coord& centerMassCoord) const;

	// принимает модуль силы и координаты точки и соседней точки
	// вычисляет силу давления оказываемую на точку
	Force calcPressureForce(const double& pressureAbs, 
		const Coord& point, const Coord& neighbour, 
		const Coord& centerMassCoord) const;

	// принимает две координаты концов пружины
	// возвращает силу в соответствии с законом гука
	Force calcHookeForce(const Coord& target, const Coord& forceSource) const;

	// принимает промежуток времени и обновляет координаты, 
	// изменившиеся за это время
	void calcNewCoords(const double& dt);

	Coord centerMass() const;

	// Вычисляет потенциал леонарда джонса
	// по координате точки
	Force LennardJhonesForce(const Coord& coord) const;


	Params params;
	ICanvas* canvas;
	std::vector<Coord> coords;
	std::vector<Velocity> velocities;
};

