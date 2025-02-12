#pragma once

#include <string>
#include <vector>

#include "GLFW/glfw3.h"

class Input
{
public:
	const std::string& GetSemantic();
	void SetSemantic(std::string _semantic);

	const std::string& GetSource();
	void SetSource(std::string _source);

	const GLuint GetOffset();
	void SetOffset(GLuint _offset);
	void SetOffset(std::string _offset);

	const GLuint GetSet();
	void SetSet(GLuint _set);
	void SetSet(std::string _set);

	const std::vector<GLfloat> GetData();
	void SetData(std::vector<GLfloat> _data);

	const GLuint GetDataStride();
	void SetDataStride(GLuint _stride);

private:
	std::string semantic;
	std::string source;
	GLuint offset;
	GLuint set;

	std::vector<GLfloat> data;
	GLuint dataStride;
};