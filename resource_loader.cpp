#include "resource_loader.h"

resource_loader::resource_loader()
= default;

resource_loader::~resource_loader()
= default;

std::shared_ptr<std::string> resource_loader::load_shader_source(const std::string& path)
{
	// todo: Make assumption that all shader files should end in .shader?
	std::ifstream file;
	file.open(path.c_str());
	if (!file.is_open())
	{
		SDL_LogCritical(SDL_LOG_CATEGORY_RENDER, "Failed to load shader from source!");

		return nullptr;
	}

	std::string content;
	std::string line;
	while (std::getline(file, line))
	{
		content.append(line + "\n");
	}
	file.close();

	return std::make_shared<std::string>(content);
}

GLuint resource_loader::create_shader(const std::shared_ptr<std::string>& source, const shader_type type)
{
	if (!source) return -1;

	const auto shader = glCreateShader(type == shader_type::vertex ? GL_VERTEX_SHADER : GL_FRAGMENT_SHADER);
	const auto source_char = source->c_str();

	glShaderSource(shader, 1, &source_char, nullptr);
	glCompileShader(shader);

	int success;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		char log[512];
		glGetShaderInfoLog(shader, 512, nullptr, log);
		SDL_LogCritical(SDL_LOG_CATEGORY_RENDER, R"(Error compiling shader)", log);

		return -1;
	}

	return shader;
}

GLuint resource_loader::create_shader_direct(const char* source, const shader_type type)
{
	const auto shader = glCreateShader(type == shader_type::vertex ? GL_VERTEX_SHADER : GL_FRAGMENT_SHADER);

	glShaderSource(shader, 1, &source, nullptr);
	glCompileShader(shader);

	int success;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		char log[512];
		glGetShaderInfoLog(shader, 512, nullptr, log);
		SDL_LogCritical(SDL_LOG_CATEGORY_RENDER, R"(Error compiling shader)", log);

		return -1;
	}

	return shader;
}

unsigned resource_loader::create_shader_program(const GLuint vertex_shader, const GLuint fragment_shader)
{
	const auto shader_program = glCreateProgram();
	glAttachShader(shader_program, vertex_shader);
	glAttachShader(shader_program, fragment_shader);
	glLinkProgram(shader_program);

	int success;
	glGetProgramiv(shader_program, GL_LINK_STATUS, &success);
	if (!success)
	{
		char log[512];
		glGetProgramInfoLog(shader_program, 512, nullptr, log);
		SDL_LogCritical(SDL_LOG_CATEGORY_RENDER, R"(Error creating shader program)", log);

		return -1;
	}

	glDeleteShader(vertex_shader);
	glDeleteShader(fragment_shader);

	return shader_program;
}


