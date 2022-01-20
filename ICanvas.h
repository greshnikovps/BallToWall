#pragma once

#include <vector>
#include "common.h"

class ICanvas {
public:
	virtual void draw(const std::vector<Coord>& coords) = 0;

	virtual ~ICanvas() {}
};