#include <memory>

#include "Game.h"

#include <glew/glew.h>
#include <sdl2/SDL.h>

#include "window_manager.h"

game::game()
= default;

game::~game()
{
	SDL_Quit();
}

bool game::init()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION, "SDL_Init Error: %s\n",
			SDL_GetError());

		return false;
	}
	SDL_Log("SDL initialised OK!\n");

	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	window_ = std::make_unique<window_manager>(1280, 720, "Hello, World!");

	glewExperimental = GL_TRUE;
	const GLenum status = glewInit();

	if (status != GLEW_OK)
	{
		SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION, "GLEW failed to start!");

		return false;
	}
	SDL_Log("GLEW initialised OK!");

	return true;
}

void game::run() const
{
	while (!window_->is_window_closed())
	{
		glClearColor(0.0f, 0.15f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		window_->update();
	}
}
