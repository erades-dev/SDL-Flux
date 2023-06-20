#include "../Public/Screen.h"
// #include <math.h>

namespace Flux {

Screen::Screen()
	: window(NULL), renderer(NULL), texture(NULL), buffer1(NULL), buffer2(NULL) {
}

bool Screen::init() {
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		return (false);
	}
	window = SDL_CreateWindow(
		"Particle fire",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		WIDTH,
		HEIGHT,
		SDL_WINDOW_SHOWN);
	if (!window) {
		SDL_Quit();
		return (false);
	}
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);
	texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ABGR8888, SDL_TEXTUREACCESS_STATIC, WIDTH, HEIGHT);
	buffer1 = new SDL_Color[BUFFERSIZE];
	buffer2 = new SDL_Color[BUFFERSIZE];
	clear(buffer1);
	clear(buffer2);
	return (true);
}

void Screen::update() {
	SDL_UpdateTexture(texture, NULL, buffer1, WIDTH * sizeof(SDL_Color));
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, texture, NULL, NULL);
	SDL_RenderPresent(renderer);
}

void Screen::clear(SDL_Color *buffer) {
	memset(buffer, 0, BUFFERSIZE * sizeof(SDL_Color));
}

void Screen::fill() {
	SDL_Color bgColor{100, 100, 0, 255};
	for (int y = 0; y < Screen::HEIGHT; y++) {
		for (int x = 0; x < Screen::WIDTH; x++) {
			setPixel(x, y, bgColor);
		}
	}
}

void Screen::boxBlur() {
	SDL_Color *temp = buffer1;
	buffer1 = buffer2;
	buffer2 = temp;
	for (int y = 0; y < HEIGHT; y++) {
		for (int x = 0; x < WIDTH; x++) {
			SDL_Color colorSum{0, 0, 0, 255};
			for (int row = -1; row < 2; row++) {
				for (int col = -1; col < 2; col++) {
					int curX = x + col;
					int curY = y + row;
					if (curX >= 0 && curX < WIDTH && curY >= 0 && curY < HEIGHT) {
						SDL_Color colorCur = buffer2[curX + (curY * WIDTH)];
						colorSum.r += colorCur.r;
						colorSum.g += colorCur.g;
						colorSum.b += colorCur.b;
					}
				}
			}
			colorSum.r /= 9;
			colorSum.g /= 9;
			colorSum.b /= 9;
			setPixel(x, y, colorSum);
		}
	}
}

void Screen::setPixel(int x, int y, SDL_Color color) {
	// x += WIDTH / 2;
	// y += HEIGHT / 2;
	int index = x + y * WIDTH;
	if (x < 0 || x > WIDTH - 1 || y < 0 || y > HEIGHT - 1)
		return;
	buffer1[index] = color;
}

SDL_Color Screen::toColor(Uint8 red, Uint8 green, Uint8 blue) {
	SDL_Color color{
		color.r = red,
		color.g = green,
		color.b = blue,
		color.a = 255};
	return (color);
}

bool Screen::processEvents() {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT) {
			return (false);
		}
	}
	return (true);
}

void Screen::close() {
	delete[] buffer1;
	delete[] buffer2;
	SDL_DestroyRenderer(renderer);
	SDL_DestroyTexture(texture);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

} // namespace Flux
