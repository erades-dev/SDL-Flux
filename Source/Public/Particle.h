#pragma once
#include <SDL.h>

namespace Flux {

struct Particle {
	double x;
	double y;
	double speed;
	double direction;
	SDL_Color color;
	Particle();
	~Particle();
	void update(double deltaTime);
};

} // namespace Flux
