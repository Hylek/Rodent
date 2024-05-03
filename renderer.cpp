#include "renderer.h"

#include <utility>
#include <sdl2/SDL_timer.h>

#include "mesh.h"

void renderer::draw()
{
	if (drawing_lists_.empty()) return;

	// Enables a "wire-frame" mode for drawing.
	// glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	for (auto& list : drawing_lists_)
	{
		for (auto j = 0; j < list.meshes.size(); j++)
		{
			const auto& mesh = list.meshes[j];

			glUseProgram(list.shader_program_id);

			const unsigned int transform_loc = glGetUniformLocation(list.shader_program_id, "transform");
			glUniformMatrix4fv(transform_loc, 1, GL_FALSE, glm::value_ptr(mesh->transform.get_transform()));

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->get_ebo());
			glBindVertexArray(mesh->get_vao());

			glDrawElements(GL_TRIANGLES, mesh->get_indices_count(), GL_UNSIGNED_INT, nullptr);

			glBindVertexArray(0);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		}
	}
}

renderer::renderer()
= default;

renderer::~renderer()
= default;

void renderer::create_draw_list(const std::string& draw_list_name, const GLuint shader_program_id)
{
	draw_list new_list;
	new_list.draw_list_name = draw_list_name;
	new_list.shader_program_id = shader_program_id;

	drawing_lists_.push_back(new_list);
}

bool renderer::add_mesh_to_draw_list(const std::string& name, const std::shared_ptr<mesh>& mesh)
{
	for (auto& list : drawing_lists_)
	{
		if (list.draw_list_name == name)
		{
			list.meshes.push_back(mesh);

			return true;
		}
	}
	return false;
}
