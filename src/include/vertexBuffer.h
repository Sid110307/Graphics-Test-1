#pragma once

#include <vector>
#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

struct Vertex
{
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec3 color;
	glm::vec2 texture;
};

class VertexBuffer
{
public:
	GLuint id = 0;
	explicit VertexBuffer(std::vector<Vertex> &);

	void bind() const;
	static void unbind();
	void destroy();
};
