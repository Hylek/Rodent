#pragma once
#include <memory>
#include <string>
#include <fstream>
#include <glew/glew.h>

#include "sdl2/SDL.h"

enum shader_type
{
	vertex, fragment
};

class resource_loader
{
public:
	resource_loader();
	~resource_loader();

	static std::shared_ptr<std::string> load_shader_source(const std::string& path);
	static GLuint create_shader(const std::shared_ptr<std::string>& source, const shader_type type);
	static GLuint create_shader_direct(const char* source, shader_type type);
	static unsigned int create_shader_program(GLuint vertex_shader, GLuint fragment_shader);
private:
};

