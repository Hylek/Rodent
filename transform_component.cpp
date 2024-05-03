#include "transform_component.h"

transform_component::transform_component()
{
	transform_ = glm::mat4(1.0f);
}

transform_component::~transform_component()
= default;

void transform_component::translate(const glm::vec3& translation)
{
	transform_ = glm::translate(transform_, translation);
}

void transform_component::rotate(float angle, const glm::vec3& axis)
{
	transform_ = glm::rotate(transform_, angle, axis);
}

void transform_component::scale(const glm::vec3& scale)
{
	transform_ = glm::scale(transform_, scale);
}

glm::mat4 transform_component::get_transform() const
{
	return transform_;
}
