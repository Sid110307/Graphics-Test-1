#include "include/mesh.h"

Mesh::Mesh(std::vector<Vertex> &_vertices, std::vector<GLuint> &_indices, std::vector<Texture> &_textures)
		: vertices(_vertices), indices(_indices), textures(_textures)
{
	VAO.bind();
	VertexBuffer VBO(vertices);
	ArrayBuffer IBO(indices);
	IBO.bind();

	ArrayObject::linkAttribute(VBO, 0, 3, GL_FLOAT, sizeof(Vertex), nullptr);
	ArrayObject::linkAttribute(VBO, 1, 3, GL_FLOAT, sizeof(Vertex), (void*) (3 * sizeof(GLfloat)));
	ArrayObject::linkAttribute(VBO, 2, 3, GL_FLOAT, sizeof(Vertex), (void*) (6 * sizeof(GLfloat)));
	ArrayObject::linkAttribute(VBO, 3, 2, GL_FLOAT, sizeof(Vertex), (void*) (8 * sizeof(GLfloat)));

	ArrayObject::unbind();
	VertexBuffer::unbind();
	ArrayBuffer::unbind();
}

void Mesh::draw(Shader &shader, Camera &camera)
{
	shader.activate();
	VAO.bind();

	GLuint diffuse = 0, specular = 0;
	for (GLuint i = 0; i < textures.size(); i++)
	{
		std::string num, type = textures[i].textureType;
		if (type == "diffuse") num = std::to_string(diffuse++);
		else if (type == "specular") num = std::to_string(specular++);

		textures[i].textureUniform(shader, (type + num).c_str(), i);
		textures[i].bind();
	}

	glUniform3f(glGetUniformLocation(shader.id, "cameraPosition"), camera.position.x, camera.position.y,
				camera.position.z);
	camera.createMatrix(shader, "camMatrix");

	glDrawElements(GL_TRIANGLES, (int) indices.size(), GL_UNSIGNED_INT, nullptr);
}
