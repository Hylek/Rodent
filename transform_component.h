#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class transform_component
{
public:
	transform_component();
	~transform_component();

	void translate(const glm::vec3& translation);
	void rotate(float angle, const glm::vec3& axis);
	void scale(const glm::vec3& scale);
	glm::mat4 get_transform() const;


private:
	glm::mat4 transform_{};
};

