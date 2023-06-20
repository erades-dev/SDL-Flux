#include "Screen.h"
#include "System.h"

using namespace Flux;

// float map(float value, float start1, float stop1, float start2, float stop2) {
//	float outgoing = start2 + (stop2 - start2) * ((value - start1) / (stop1 - start1));
//	return (outgoing);
// }

// double clamp1(double x, double a, double b) {
//	if (x < a)
//		return a;
//	else if (x > b)
//		return b;
//	else
//		return (x);
// }

Uint64 timeLast = SDL_GetTicks64();
int main(int argc, char **args) {
	srand((unsigned int)time(NULL));
	System system;
	Screen screen;
	if (!screen.init()) {
		std::cout << "Error initializing Screen" << std::endl;
	}
	while (true) {
		Uint64 timeElapsed = SDL_GetTicks64();
		float timeDelta = (timeElapsed - timeLast) / 1000.0f;
		timeLast = timeElapsed;
		SDL_Color color{
			color.r = (unsigned char)((1 + sin(timeElapsed * 0.0001)) * 128),
			color.g = (unsigned char)((1 + cos(timeElapsed * 0.0002)) * 128),
			color.b = (unsigned char)((1 + sin(timeElapsed * 0.0003)) * 128)};
		// Particle system.
		{
			system.update(timeDelta);
			const Particle *particles = system.getParticles();
			for (size_t i = 0; i < system.NPARTICLES; i++) {
				int screenX = (int)((double)Screen::WIDTH * particles[i].x);
				int screenY = (int)((double)Screen::WIDTH * particles[i].y);
				screen.setPixel(screenX, screenY, color);
			}
		}
		screen.update();
		screen.boxBlur();
		// screen.clear(screen.buffer1);
		if (!screen.processEvents()) {
			break;
		}
	}
	screen.close();
	return (0);
}
