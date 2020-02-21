// Duta Viorel-Ionut, 331CB
#pragma once

#include <string>

#include <include/glm.h>
#include <Core/GPU/Mesh.h>

namespace Object3D
{
	Mesh* Sea(std::string name, glm::vec3 leftBC);
	Mesh* Sea2(std::string name, glm::vec3 leftBC);

	Mesh* Obstacle(std::string name, glm::vec3 leftBC, glm::vec3 color);
	Mesh* Fuel(std::string name, glm::vec3 leftBC);
	Mesh* Airplane(std::string name, glm::vec3 leftBottomCorner, glm::vec3 color);
	Mesh* Propeller(std::string name, glm::vec3 leftBottomCorner);

	Mesh* Cloud(std::string name, glm::vec3 leftBC);
	Mesh* Cloud2(std::string name, glm::vec3 leftBC);
	Mesh* Cloud3(std::string name, glm::vec3 leftBC);

	Mesh* Box(std::string name, glm::vec3 leftBottomCorner, float radius, glm::vec3 color);

	Mesh* FuelBar2(std::string name, float l1, float l2, glm::vec3 leftBC, glm::vec3 color);
	Mesh* FuelBar(std::string name, float aux, float l, glm::vec3 leftBC, glm::vec3 color);
	Mesh* Heart(std::string name, glm::vec3 leftBC, glm::vec3 color);

}
