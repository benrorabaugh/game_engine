#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL.h>

#include "movement.h"

int main(int argc, char* argv[]) {
	//Initialize graphics and timer
	if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER) != 0) {
		printf("Failed to initialize SDL: %s\n", SDL_GetError());
		return 1;
	}

	SDL_Window *window = SDL_CreateWindow("Window Title", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 320, 180, 0);

	if (!window) {
		printf("Error creating window: %s\n", SDL_GetError());
		SDL_Quit();
		return 1;
	}
	SDL_MaximizeWindow(window);

	//Change graphics hardware
	Uint32 render_flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
	SDL_Renderer *rend = SDL_CreateRenderer(window, -1, render_flags);
	if (!rend) {
		printf("Error creating renderer: %s\n", SDL_GetError());
		SDL_DestroyWindow(window);
		SDL_Quit();
		return 1;
	}
	
	//Load image into memory
	SDL_Surface* surface = SDL_LoadBMP("f1.bmp");
	if (!surface) {
		printf("Error creating surface\n");
		SDL_DestroyRenderer(rend);
		SDL_DestroyWindow(window);
		SDL_Quit();
		return 1;
	}

	//Load the image data into graphics hardware's memory
	SDL_Texture* tex = SDL_CreateTextureFromSurface(rend, surface);
	SDL_FreeSurface(surface);
	if (!tex) {
		printf("Error creating texture: %s\n", SDL_GetError());
		SDL_DestroyRenderer(rend);
		SDL_DestroyWindow(window);
		SDL_Quit();
		return 1;
	}

	SDL_Rect dest;
	SDL_QueryTexture(tex, NULL, NULL, &dest.w, &dest.h);
	dest.w *= 6;
	dest.h *= 6;
	dest.x = (320 - dest.w) / 2;
	float y_pos = 100;
	float x_pos = 0;
	float v_y = 5;
	float v_x = 1;

	while (dest.x <= 1920) {
		SDL_RenderClear(rend);
		dest.y = 1080 - (int) y_pos;
		dest.x = (int) x_pos;
		SDL_RenderCopy(rend, tex, NULL, &dest);
		SDL_RenderPresent(rend);
		y_pos += v_y;
		x_pos += v_x;
		v_y += -0.3;
		
		if (y_pos < 0 + dest.h) {
			y_pos = 0 + dest.h;
			v_y *= -1;
		}
	}

	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}