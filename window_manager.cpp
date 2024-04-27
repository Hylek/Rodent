#include "window_manager.h"

window_manager::window_manager(const int width, const int height, const std::string& window_name) :
		sdl_window_(std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)>
			(SDL_CreateWindow(window_name.c_str(), SDL_WINDOWPOS_CENTERED, 
				SDL_WINDOWPOS_CENTERED, width, height,SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE),
				SDL_DestroyWindow))
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

	glViewport(0, 0, width, height);
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

	const std::unique_ptr<SDL_Event> e(new SDL_Event);

	while (SDL_PollEvent(e.get()))
	{
		process_events(*e);
	}
}

bool window_manager::is_window_closed() const
{
	return is_closed_;
}

void window_manager::process_events(const SDL_Event& e)
{
	if (e.type == SDL_QUIT)
	{
		is_closed_ = true;
	}

	if (e.type == SDL_WINDOWEVENT)
	{
		if(e.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
		{
			const int new_width = e.window.data1;
			const int new_height = e.window.data2;

			glViewport(0, 0, new_width, new_height);

			// todo: Adjust projection matrix once implemented?
		}
	}
}
