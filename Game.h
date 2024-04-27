#pragma once

#include <memory>
#include <glew/glew.h>
#include <sdl2/SDL.h>

#include "window_manager.h"

class game
{
public:
	game();
	~game();
	bool init();
	bool start();
	void run();

private:
	std::unique_ptr<window_manager> window_;

	void handle_input();
	void update();
	void render();
};

