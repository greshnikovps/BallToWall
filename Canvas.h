#pragma once
#include <vector>
#include "common.h"
#include "ICanvas.h"
#include <iostream>
#include <SFML/Graphics.hpp>

class Canvas : public ICanvas {
public:
	Canvas();
	virtual void draw(const std::vector<Coord>& coords) override;
private:
	void initializeCircles(size_t size);

	std::vector<sf::CircleShape> circles;
	sf::RenderWindow window;// (sf::VideoMode(CANVAS_SIZE, CANVAS_SIZE), "Ball To Wall");
};