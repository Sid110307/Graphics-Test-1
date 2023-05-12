#pragma once

#include <string>
#include <vector>

#include "arrayObject.h"
#include "arrayBuffer.h"
#include "camera.h"
#include "texture.h"

// TODO: Fix possible memory leak (maybe through destructor)
class Mesh
{
public:
	Mesh(std::vector<Vertex> &, std::vector<GLuint> &, std::vector<Texture> &);
	void draw(Shader &, Camera &);

private:
	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;
	std::vector<Texture> textures;

	ArrayObject VAO;
};
