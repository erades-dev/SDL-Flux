#pragma once
#include <SDL.h>
#include <iostream>

namespace Flux {
class Screen {
public:
	const static int WIDTH = 800;
	const static int HEIGHT = 600;
	const static int BUFFERSIZE = WIDTH * HEIGHT;
	SDL_Color *buffer1;

private:
	SDL_Window *window;
	SDL_Renderer *renderer;
	SDL_Texture *texture;
	SDL_Color *buffer2;

public:
	Screen();
	bool init();
	void update();
	void clear(SDL_Color* buffer);
	void fill();
	void boxBlur();
	void setPixel(int x, int y, SDL_Color color);
	bool processEvents();
	void close();
	static SDL_Color toColor(Uint8 red, Uint8 green, Uint8 blue);
};
} // namespace Flux
