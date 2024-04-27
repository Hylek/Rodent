#include "renderer.h"

#include "mesh.h"

void renderer::draw(const unsigned int program) const
{
	if (meshes_.empty()) return;

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	for (const auto& mesh : meshes_)
	{
		glUseProgram(program);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->get_ebo());
        glBindVertexArray(mesh->get_vao());

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

		glBindVertexArray(0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
}

renderer::renderer()
= default;

renderer::~renderer()
= default;

void renderer::add_mesh(const std::shared_ptr<mesh>& mesh)
{
	meshes_.push_back(mesh);
}
