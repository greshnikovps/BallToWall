#include "Canvas.h"

using namespace std;

Canvas::Canvas()
    :
	window(sf::VideoMode(CANVAS_SIZE, CANVAS_SIZE), "Ball To Wall")
{
}

void Canvas::draw(const std::vector<Coord>& coords)
{

    if (circles.empty()) {
        initializeCircles(coords.size());
    }

    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window.close();
    }

    window.clear();
    for (size_t i = 0; i < coords.size(); i++) {
        circles[i].setPosition(SCALE_FACTOR * coords[i].x + CANVAS_SIZE / 2,
            SCALE_FACTOR * coords[i].y + CANVAS_SIZE / 2);
        window.draw(circles[i]);
    }
    window.display();
}

void Canvas::initializeCircles(size_t size)
{
	for (size_t i = 0; i < size; i++) {
		sf::CircleShape shape(CIRCLE_RADIUS);
		shape.setFillColor(sf::Color::Green);
		circles.push_back(shape);
	}
}
