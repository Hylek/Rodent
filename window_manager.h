#pragma once
#include <string>
#include <iostream>
#include <sdl2/SDL.h>

class window_manager
{
public:
	window_manager(const int width, const int height, const std::string& window_name);
	~window_manager();

	void swap_buffers() const;
	void update();
	bool is_window_closed() const;

private:
	std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)> sdl_window_;
	SDL_GLContext sdl_gl_context_;
	bool is_closed_;
};

