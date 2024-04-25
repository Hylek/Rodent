#pragma once
#include <string>
#include <sdl2/SDL.h>

class window
{
public:
	window(int width, int height, const std::string& window_name);
	~window();

private:
	SDL_Window* sdl_window_;
};

