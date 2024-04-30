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

	void handle_input();
	void update();
	void render();

	bool ok_;
	bool load_shaders() const;
	bool create_program(const std::string& name, const std::shared_ptr<std::string>& vertex_source, const std::shared_ptr<std::string>&
	                    fragment_source) const;
};

