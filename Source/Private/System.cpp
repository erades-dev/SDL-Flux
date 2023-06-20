#include "../Public/System.h"
// #include "../Public/Particle.h"

namespace Flux {

System::System() {
	pParticles = new Particle[NPARTICLES];
}

System::~System() {
	delete[] pParticles;
}
void System::update(double deltaTime) {
	int i = 0;
	while (i < NPARTICLES) {
		pParticles[i].update(deltaTime);
		i++;
	}
}
} // namespace Flux