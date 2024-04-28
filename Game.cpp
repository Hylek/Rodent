#include "game.h"

	// TEST DATA
	std::vector<float> vertices = {
         0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
         0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f,
        -0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 1.0f
    };
    std::vector<unsigned int> indices = {
        0, 1, 3,
        1, 2, 3
    };

    // todo: Move these to external files, and load them in.
const char *vertex_shader_source ="#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "layout (location = 1) in vec3 aColor;\n"
    "out vec3 ourColor;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos, 1.0);\n"
    "   ourColor = aColor;\n"
    "}\0";

const char *fragment_shader_source = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "in vec3 ourColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(ourColor, 1.0f);\n"
    "}\n\0";

game::game() : ok_(false)
{
}

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
	SDL_Log("SDL OK");

	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	window_ = std::make_unique<window_manager>(1280, 720, "Hello, World!");
	renderer_ = std::make_unique<renderer>();

	glewExperimental = GL_TRUE;
	const GLenum status = glewInit();

	if (status != GLEW_OK)
	{
		SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION, "GLEW failed to start!");

		return false;
	}
	SDL_Log("GLEW OK");

	return true;
}

bool game::start()
{
	// todo: Load int models, compile shaders, set start code/data etc.
	if (load_shaders())
	{
		const auto rect = std::make_shared<mesh>(vertices, indices);
		rect->prepare();

		renderer_->add_mesh(rect);
	}
	ok_ = true;

	return true;
}

void game::run()
{
	if (!ok_) return;

	// Game Loop
	while (!window_->is_window_closed())
	{
		handle_input();
		update();
		render();
	}
}

void game::handle_input()
{

}

void game::update()
{

}

void game::render()
{
	glClearColor(0.39f, 0.58f, 0.93f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	renderer_->draw();

	window_->update();
}

bool game::load_shaders() const
{
	// todo: Expand this in future to compile and store multiple programs.
	const auto result = create_program("Colour", vertex_shader_source, fragment_shader_source);

	return result;
}

bool game::create_program(const std::string& name, const char* vertex_source, const char* fragment_source) const
{
	const auto vertex_shader = resource_loader::create_shader_direct(vertex_source, vertex);
	const auto fragment_shader = resource_loader::create_shader_direct(fragment_source, fragment);

	if (!fragment_shader || !vertex_shader)
	{
		return false;
	}

	const auto shader_program = resource_loader::create_shader_program(vertex_shader, fragment_shader);

	if (!shader_program)
	{
		return false;
	}

	renderer_->add_program(name, shader_program);

	SDL_Log("Shader Program OK");

	return true;
}
