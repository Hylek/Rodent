#pragma once

#include <chrono>
#include <memory>
#include <glew/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "renderer.h"
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
	double get_current_time() const;

	// Test objects
	std::shared_ptr<mesh> testRect_;

	std::chrono::high_resolution_clock::time_point frame_start_;
	short FPS = 240;


	double delta_;
	double old_time_;
	bool ok_;
	bool create_shader_programs() const;
	GLuint create_program(const std::string& name, const std::shared_ptr<std::string>& vertex_source, const std::shared_ptr<std::string>&
	                    fragment_source) const;
};

