#include "Ball.h"
#include "Canvas.h"
#include <Windows.h>
using namespace std;

int main() {
	double dt = 0.001;
	int unitCount = 20;
	Canvas canvas;
	Ball ball(unitCount, &canvas);
	while (true) {
		ball.drawNewCoords(dt);
		//Sleep(dt);
	}
	return 0;
}