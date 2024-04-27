#pragma once
#include <memory>
#include <glew/glew.h>

#include "mesh.h"

class renderer
{
public:
	renderer();
	~renderer();

	void add_mesh(const std::shared_ptr<mesh>& mesh);
	void draw(const unsigned int program) const;

private:
	std::vector<std::shared_ptr<mesh>> meshes_;
};

