#pragma once

#include "Mesh.h"

#include <vector>

class Object
{
public:
	Object(GLuint& _program);
	void Init();
	void Update();

	void SetName(std::string& _name);
	std::string& GetName();

	void AddMesh(Mesh& mesh);
	std::vector<Mesh>& GetMeshes();

private:
	std::string name;
	std::vector<Mesh> meshes;

	GLuint& program;
};