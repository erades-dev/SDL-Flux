#include <stdlib.h>
#include "Particle.h"

namespace Flux {

Particle::Particle()
	: x(0.5), y(0.35) {
	direction = ((2 * M_PI * rand()) / RAND_MAX);
	speed = (1.4 * rand()) / RAND_MAX;
	speed *= speed * speed;

	color = {
		color.r = 255,
		color.g = 255,
		color.b = 255,
		color.a = 255};
}

Particle::~Particle() {
}

void Particle::update(double timeDelta) {
	direction += timeDelta * 1.4;
	double xspeed = speed * cos(direction);
	double yspeed = speed * sin(direction);
	x += xspeed * timeDelta;
	y += yspeed * timeDelta;
}

} // namespace Flux
