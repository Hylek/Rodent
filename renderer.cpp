#include "renderer.h"

#include "mesh.h"

void renderer::draw()
{
	if (meshes_.empty()) return;

	// Enables a "wire-frame" mode for drawing.
	// glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	// todo: Alter this to instead use draw lists, to draw in specific batches.
	for (const auto& mesh : meshes_)
	{
		// todo: Allow flexibility for programs to be used depending on mesh to be drawn.
		glUseProgram(get_program("Standard"));
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

void renderer::add_program(const std::string& name, const GLuint program)
{
	shader_programs_[name] = program;
}

GLuint renderer::get_program(const std::string& name)
{
	const auto it = shader_programs_.find(name);
    if (it != shader_programs_.end())
	{
    	return it->second;
    }

    return 0;
}
