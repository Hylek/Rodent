#pragma once
#include <memory>
#include <string>
#include <unordered_map>
#include <glew/glew.h>

#include "mesh.h"

class renderer
{
public:
	renderer();
	~renderer();

	void add_mesh(const std::shared_ptr<mesh>& mesh);
	void add_program(const std::string& name, GLuint program);
	void draw();

private:
	std::vector<std::shared_ptr<mesh>> meshes_;
	std::unordered_map<std::string, GLuint> shader_programs_;

	GLuint get_program(const std::string& name);
};

