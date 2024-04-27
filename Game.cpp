#include "game.h"

	// TEST TRIANGLE DATA
	std::vector<float> vertices = {
         0.5f,  0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f,
        -0.5f,  0.5f, 0.0f
    };
    std::vector<unsigned int> indices = {
        0, 1, 3,
        1, 2, 3
    };

    // todo: Move these to external files, and load them in.
	const char *vertex_shader_source = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";

    const char *fragment_shader_source = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
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
	SDL_Log("SDL initialised OK!\n");

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
	SDL_Log("GLEW initialised OK!");

	return true;
}

bool game::start()
{
	// todo: Load int models, compile shaders, set start code/data etc.
	if (load_shaders())
	{
		const auto triangle = std::make_shared<mesh>(vertices, indices);
		triangle->prepare();

		renderer_->add_mesh(triangle);
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
	glClearColor(0.0f, 0.15f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	renderer_->draw(shader_program_id_);

	window_->update();
}

bool game::load_shaders()
{
	const auto vertex_shader = resource_loader::create_shader_direct(vertex_shader_source, shader_type::vertex);
	const auto fragment_shader = resource_loader::create_shader_direct(fragment_shader_source, shader_type::fragment);

	if (!fragment_shader || !vertex_shader)
	{
		return false;
	}

	const auto shader_program = resource_loader::create_shader_program(vertex_shader, fragment_shader);

	if (!shader_program)
	{
		return false;
	}

	shader_program_id_ = shader_program;

	SDL_Log("Shader Program OK");

	return true;
}
