#pragma once
#include "Particle.h"

namespace Flux {

class System {
public:
	const static int NPARTICLES = 50000;

private:
	Particle *pParticles;

public:
	System();
	virtual ~System();
	void update(double deltaTime);

	const Particle *const getParticles() {
		return (pParticles);
	};
};

} // namespace Flux