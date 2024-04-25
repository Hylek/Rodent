#include "window_manager.h"

window_manager::window_manager(const int width, const int height, const std::string& window_name) :
		sdl_window_(std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)>(SDL_CreateWindow(window_name.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height,SDL_WINDOW_OPENGL), SDL_DestroyWindow))
{
	if (sdl_window_ == nullptr)
	{
		SDL_LogCritical(SDL_LOG_CATEGORY_VIDEO, "SDL failed to create the window! \n");
	}
	is_closed_ = false;

	sdl_gl_context_ = SDL_GL_CreateContext(sdl_window_.get());

	if (sdl_gl_context_ == nullptr)
	{
		SDL_LogCritical(SDL_LOG_CATEGORY_VIDEO, "SDL failed to create GL Context! \n");
	}
}

window_manager::~window_manager()
{
	SDL_GL_DeleteContext(sdl_gl_context_);
}

void window_manager::swap_buffers() const
{
	SDL_GL_SwapWindow(sdl_window_.get());
}

void window_manager::update()
{
	SDL_GL_SwapWindow(sdl_window_.get());

	SDL_Event e;

	while (SDL_PollEvent(&e))
	{
		if (e.type == SDL_QUIT)
		{
			is_closed_ = true;
		}
	}
}

bool window_manager::is_window_closed() const
{
	return is_closed_;
}
