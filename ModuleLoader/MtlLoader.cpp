#include "MtlLoader.h"

#include <vector>

using namespace std;
using namespace glm;

MtlLoader::MtlLoader(FileUtils& _fileUtils)
	: fileUtils(_fileUtils)
{
}

void MtlLoader::LoadMaterials(Model& model, std::string& fileLocation)
{
	Material* newMaterial = nullptr;

	std::string folder = fileUtils.GetFolder(fileLocation);
	vector<string> fileLines = fileUtils.ReadFileAsLines(fileLocation);

	for (size_t i = 0; i < fileLines.size(); i++)
	{
		char* line = (char*)fileLines[i].c_str();

		if (strncmp(line, "newmtl ", 7) == 0)
		{
			if (newMaterial != nullptr)
			{
				model.AddMaterial(*newMaterial);
			}
			newMaterial = &Material();
			newMaterial->name = GetSingleString(fileLines[i]);
		}
		else if (newMaterial == nullptr)
		{
			continue;
		}
		else if (strncmp(line, "Ns ", 3) == 0)
		{
			newMaterial->specularColourWeight = GetSingleFloat(fileLines[i]);
		}
		else if (strncmp(line, "Ka ", 3) == 0)
		{
			newMaterial->ambientColour = GetVector3(fileLines[i]);
		}
		else if (strncmp(line, "Kd ", 3) == 0)
		{
			newMaterial->diffuseColour = GetVector3(fileLines[i]);
		}
		else if (strncmp(line, "Ks ", 3) == 0)
		{
			newMaterial->specularColour = GetVector3(fileLines[i]);
		}
		else if (strncmp(line, "d ", 2) == 0)
		{
			newMaterial->dissolve = GetSingleFloat(fileLines[i]);
		}
		else if (strncmp(line, "illum ", 6) == 0)
		{
			newMaterial->illuminationModel = GetSingleInt(fileLines[i]);
		}
		else if (strncmp(line, "map_Ka ", 7) == 0)
		{
			GetTexture(newMaterial->ambientTextureMap, fileLines[i], folder);
		}
		else if (strncmp(line, "map_Kd ", 7) == 0)
		{
			GetTexture(newMaterial->diffuseTextureMap, fileLines[i], folder);
		}
		else if (strncmp(line, "map_d ", 6) == 0)
		{
			GetTexture(newMaterial->alphaTextureMap, fileLines[i], folder);
		}
	}

	if (newMaterial != nullptr)
	{
		model.AddMaterial(*newMaterial);
	}
}

char* MtlLoader::GetSingleString(std::string& line)
{
	char* value;
	char* remaining;
	value = strtok_s((char*)line.c_str(), " ", &remaining);
	value = strtok_s(remaining, " ", &remaining);

	return value;
}

GLfloat MtlLoader::GetSingleFloat(std::string& line)
{
	return stof(GetSingleString(line));
}

GLuint MtlLoader::GetSingleInt(std::string& line)
{
	return stoi(GetSingleString(line));
}

glm::vec3& MtlLoader::GetVector3(std::string& line)
{
	GLuint value = 0;

	vec3 newVec3 = vec3();

	char* word;
	char* remaining;
	word = strtok_s((char*)line.c_str(), " ", &remaining);
	word = strtok_s(remaining, " ", &remaining);
	while (word != NULL)
	{
		if (value == 0)
		{
			newVec3.x = stof(word);
		}
		else if (value == 1)
		{
			newVec3.y = stof(word);
		}
		else if (value == 2)
		{
			newVec3.z = stof(word);
		}

		value++;
		word = strtok_s(remaining, " ", &remaining);
	}

	return newVec3;
}

void MtlLoader::GetTexture(Texture& texture, std::string& line, std::string& folder)
{
	string textureName = GetSingleString(line);
	string texturePath = folder + textureName;

	GLint width, height, nrChannels;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* c_data = stbi_load(texturePath.c_str(), &width, &height, &nrChannels, 0);

	if (!c_data)
	{
		//TODO Error handling
	}

	texture.SetWidth(width);
	texture.SetHeight(height);
	texture.SetNrChannels(nrChannels);
	texture.SetData(c_data);
}