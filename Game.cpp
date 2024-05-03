#include "game.h"

#include <algorithm>
#include <thread>

#include "resource_loader.h"

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
	if (create_shader_programs())
	{
		testRect_ = std::make_shared<mesh>(vertices, indices);
		testRect_->prepare();
		testRect_->transform.translate(glm::vec3(-0.3f, 0.0f, 0.0f));
		testRect_->transform.rotate(1.0f, glm::vec3(0.0f, 0.0f, 1.0f));
		testRect_->transform.scale(glm::vec3(0.5f, 0.5f, 0.5f));

		renderer_->add_mesh_to_draw_list("Colour", testRect_);
	}

	old_time_ = get_current_time();

	ok_ = true;

	return true;
}

void game::run()
{
	if (!ok_) return;

	// Game Loop
	while (!window_->is_window_closed())
	{
		frame_start_ = std::chrono::high_resolution_clock::now();

		handle_input();
		update();
		render();

		auto frame_end = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double> frame_diff = frame_end - frame_start_;
		delta_ = frame_diff.count();

		const auto remaining_time = (1000 / FPS) - static_cast<int>(1000 * delta_);
		if (remaining_time > 0)
		{
			SDL_Delay(remaining_time);
		}
	}
}

void game::handle_input()
{

}

void game::update()
{
	//glm::mat4 transform = glm::mat4(1.0f);
	//transform = glm::translate(transform, glm::vec3(0.5f, -0.5f, 0.0f));
	//transform = glm::rotate(transform, static_cast<float>(SDL_GetTicks()), glm::vec3(0.0f, 0.0f, 1.0f));

	double time_in_seconds = static_cast<double>(SDL_GetTicks()) / 1000.0;

	std::cout << time_in_seconds << std::endl;

	testRect_->transform.rotate(2 / 1000, glm::vec3(0.0f, 0.0f, 1.0f));

	//auto currentRot = glm::lerp(testRect_->transform, , lerpFactor);
}

void game::render()
{
	glClearColor(0.39f, 0.58f, 0.93f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	renderer_->draw();

	window_->update();
}

double game::get_current_time() const
{
	return std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count() / 1000000.0;
}

bool game::create_shader_programs() const
{
	// todo: Expand this in future to compile and store multiple programs.

	const auto vertex_from_source_file = resource_loader::load_shader_source("data/vertex.shader");
	const auto fragment_from_source_file = resource_loader::load_shader_source("data/fragment.shader");
	const auto result = create_program("Standard", vertex_from_source_file, fragment_from_source_file);

	const auto vtx_source_colour = resource_loader::load_shader_source("data/vertex-colour.shader");
	const auto frag_source_colour = resource_loader::load_shader_source("data/fragment-colour.shader");
	const auto result2 = create_program("Colour", vtx_source_colour, frag_source_colour);

	renderer_->create_draw_list("Standard", result);
	renderer_->create_draw_list("Colour", result2);

	return result;
}

GLuint game::create_program(const std::string& name, const std::shared_ptr<std::string>& vertex_source, const std::shared_ptr<std::string>
                          & fragment_source) const
{
	const auto vertex_shader = resource_loader::create_shader(vertex_source, vertex);
	const auto fragment_shader = resource_loader::create_shader(fragment_source, fragment);

	if (!fragment_shader || !vertex_shader)
	{
		std::cout << "Shader Program " << name << " FAILED" << std::endl;

		return -1;
	}

	const auto shader_program = resource_loader::create_shader_program(vertex_shader, fragment_shader);

	if (!shader_program)
	{
		std::cout << "Shader Program " << name << " FAILED" << std::endl;

		return -1;
	}

	std::cout << "Shader Program " << name << " OK" << std::endl;

	return shader_program;
}
