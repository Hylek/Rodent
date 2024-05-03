#pragma once
#include <memory>
#include <string>
#include <unordered_map>
#include <glew/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "mesh.h"

struct draw_list
{
	std::string draw_list_name;
	GLuint shader_program_id;
	std::vector<std::shared_ptr<mesh>> meshes;
};

class renderer
{
public:
	renderer();
	~renderer();

	void add_mesh(const std::shared_ptr<mesh>& mesh);
	void add_program(const std::string& name, GLuint program);
	void create_draw_list(const std::string& draw_list_name, GLuint shader_program_id);
	bool add_mesh_to_draw_list(const std::string& name, const std::shared_ptr<mesh>& mesh);
	void draw();

private:
	std::vector<draw_list> drawing_lists_;
};

