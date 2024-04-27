#pragma once

#include <memory>
#include <glew/glew.h>
#include <sdl2/SDL.h>

#include "renderer.h"
#include "resource_loader.h"
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
	std::unique_ptr<renderer> renderer_;

	unsigned int shader_program_id_{};

	void handle_input();
	void update();
	void render();

	bool ok_{};
	bool load_shaders();
};

