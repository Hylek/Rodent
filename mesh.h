#pragma once
#include <vector>
#include <glew/glew.h>

#include "transform_component.h"

class mesh
{
public:
	mesh(std::vector<float> vertices, std::vector<unsigned int> indices);
	~mesh();

	void prepare();
	GLuint get_vao() const;
	GLuint get_vbo() const;
	GLuint get_ebo() const;
	int get_indices_count() const;

	transform_component transform;
private:
	std::vector<float> vertices_;
	std::vector<unsigned int> indices_;
	GLuint vao_{}, vbo_{}, ebo_{};
};

