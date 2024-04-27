#include "mesh.h"

mesh::mesh(std::vector<float> vertices, std::vector<unsigned int> indices) :
	vertices_(std::move(vertices)), indices_(std::move(indices))
{
}

mesh::~mesh()
{
	glDeleteVertexArrays(1, &vao_);
	glDeleteBuffers(1, &vbo_);
	glDeleteBuffers(1, &ebo_);
}

void mesh::prepare()
{
	glGenVertexArrays(1, &vao_);
	glGenBuffers(1, &vbo_);
	if (!indices_.empty())
	{
		glGenBuffers(1, &ebo_);
	}

	glBindVertexArray(vao_);

	glBindBuffer(GL_ARRAY_BUFFER, vbo_);
	glBufferData(GL_ARRAY_BUFFER, vertices_.size() * sizeof(float), vertices_.data(), GL_STATIC_DRAW);

	if (!indices_.empty())
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo_);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices_.size() * sizeof(unsigned int), indices_.data(), GL_STATIC_DRAW);
	}

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), static_cast<void*>(nullptr));
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);
	//glBindBuffer(GL_ARRAY_BUFFER, 0);
	if (!indices_.empty())
	{
		//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
}

GLuint mesh::get_vao() const
{
	return vao_;
}

GLuint mesh::get_vbo() const
{
	return vbo_;
}

GLuint mesh::get_ebo() const
{
	return ebo_;
}
