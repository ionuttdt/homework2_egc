// Duta Viorel-Ionut, 331CB
#include "Object3D.h"

#include <Core/Engine.h>
#include <math.h>
#include <GL/glu.h>
#include <vector>
#include <iostream>

Mesh* Object3D::Sea2(std::string name, glm::vec3 leftBC) {
	glm::vec3 color = glm::vec3(0.3, 0.3, 0.75);
	std::vector<VertexFormat> vertices{};
	std::vector<unsigned short> indices = {};
	
	int dens = 1;
	int y = 0;

	for (int i = 0; i < 9; i++) {
		vertices.push_back(VertexFormat(glm::vec3(1,0 , -i*dens), color));
		vertices.push_back(VertexFormat(glm::vec3(0.97, 0.26 + y, -i * dens), color));
		vertices.push_back(VertexFormat(glm::vec3(0.86, 0.5 + y, -i * dens), color));
		vertices.push_back(VertexFormat(glm::vec3(0.71, 0.71 + y, -i * dens), color));
		vertices.push_back(VertexFormat(glm::vec3(0.5, 0.86 + y, -i * dens), color));
		vertices.push_back(VertexFormat(glm::vec3(0.26, 0.97 + y, -i * dens), color));

		vertices.push_back(VertexFormat(glm::vec3(0, 1, -i * dens), color));
		vertices.push_back(VertexFormat(glm::vec3(-0.26, 0.97 + y, -i * dens), color));
		vertices.push_back(VertexFormat(glm::vec3(-0.5, 0.86 + y, -i * dens), color));
		vertices.push_back(VertexFormat(glm::vec3(-0.71, 0.71 + y, -i * dens), color));
		vertices.push_back(VertexFormat(glm::vec3(-0.86, 0.5 + y, -i * dens), color));
		vertices.push_back(VertexFormat(glm::vec3(-0.97, 0.26 + y, -i * dens), color));

		vertices.push_back(VertexFormat(glm::vec3(-1, 0, -i * dens), color));
		vertices.push_back(VertexFormat(glm::vec3(-0.97, -0.26 + y, -i * dens), color));
		vertices.push_back(VertexFormat(glm::vec3(-0.86, -0.5 + y, -i * dens), color));
		vertices.push_back(VertexFormat(glm::vec3(-0.71, -0.71 + y, -i * dens), color));
		vertices.push_back(VertexFormat(glm::vec3(-0.5, -0.86 + y, -i * dens), color));
		vertices.push_back(VertexFormat(glm::vec3(-0.26, -0.97 + y, -i * dens), color));

		vertices.push_back(VertexFormat(glm::vec3(0, -1, -i * dens), color));
		vertices.push_back(VertexFormat(glm::vec3(0.26, -0.97 + y, -i * dens), color));
		vertices.push_back(VertexFormat(glm::vec3(0.5, -0.86 + y, -i * dens), color));
		vertices.push_back(VertexFormat(glm::vec3(0.71, -0.71 + y, -i * dens), color));
		vertices.push_back(VertexFormat(glm::vec3(0.86, -0.5 + y, -i * dens), color));
		vertices.push_back(VertexFormat(glm::vec3(0.97, -0.26 + y, -i * dens), color));

	}

	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 24; j++) {
			if (j == 23) {

				indices.push_back(24 * i + j );
				indices.push_back(24 * i + 0);
				indices.push_back(24 * i + 24);

				indices.push_back(24 * i + j);
				indices.push_back(24 * i + 24);
				indices.push_back(24 * i + 24 + j);



			}
			else {
				indices.push_back(24 *i + j);
				indices.push_back(24 * i + j + 1);
				indices.push_back(24 * i + j + 24);

				indices.push_back(24 * i + j + 1);
				indices.push_back(24 * i + j + 25);
				indices.push_back(24 * i + j + 24);
			}
		}
	}


	Mesh* sea = new Mesh(name);
	sea->InitFromData(vertices, indices);
	return sea;
}

Mesh* Object3D::Sea(std::string name, glm::vec3 leftBC) {

	glm::vec3 color = glm::vec3(0.3, 0.3, 0.75);
	std::vector<VertexFormat> vertices{
		VertexFormat(glm::vec3(0, 0, 0), color),
		VertexFormat(glm::vec3(0, 0.95, 0), color),
		VertexFormat(glm::vec3(0.5, 0.8, 0), color),
		VertexFormat(glm::vec3(0.8, 0.5, 0), color),
		VertexFormat(glm::vec3(0.95, 0, 0), color),
		VertexFormat(glm::vec3(0.8, -0.5, 0), color),
		VertexFormat(glm::vec3(0.5, -0.8, 0), color),
		VertexFormat(glm::vec3(0, -0.95, 0), color),
		VertexFormat(glm::vec3(-0.5, -0.8, 0), color),
		VertexFormat(glm::vec3(-0.8, -0.5, 0), color),
		VertexFormat(glm::vec3(-0.95, 0, 0), color),
		VertexFormat(glm::vec3(-0.8, 0.5, 0), color),
		VertexFormat(glm::vec3(-0.5, 0.8, 0), color),

				VertexFormat(glm::vec3(0, 0, -3), color),
		VertexFormat(glm::vec3(0, 0.95, -3), color),
		VertexFormat(glm::vec3(0.5, 0.8, -3), color),
		VertexFormat(glm::vec3(0.8, 0.5, -3), color),
		VertexFormat(glm::vec3(0.95, 0, -3), color),
		VertexFormat(glm::vec3(0.8, -0.5, -3), color),
		VertexFormat(glm::vec3(0.5, -0.8, -3), color),
		VertexFormat(glm::vec3(0, -0.95, -3), color),
		VertexFormat(glm::vec3(-0.5, -0.8, -3), color),
		VertexFormat(glm::vec3(-0.8, -0.5, -3), color),
		VertexFormat(glm::vec3(-0.95, 0, -3), color),
		VertexFormat(glm::vec3(-0.8, 0.5, -3), color),
		VertexFormat(glm::vec3(-0.5, 0.8, -3), color),

	};

	std::vector<unsigned short> indices =
	{
		0, 12, 1,
		13, 25, 14
	};

	for (int i = 1; i < 12; i++) {
		indices.push_back(0);
		indices.push_back(i);
		indices.push_back(i + 1);

		indices.push_back(13);
		indices.push_back(13 + i);
		indices.push_back(i + 14);

		indices.push_back(i);
		indices.push_back(i + 13);
		indices.push_back(i + 1);

		indices.push_back(i + 1);
		indices.push_back(i + 13);
		indices.push_back(i + 14);

	}

	indices.push_back(1);
	indices.push_back(14);
	indices.push_back(12);

	indices.push_back(12);
	indices.push_back(14);
	indices.push_back(25);

	Mesh* sea = new Mesh(name);
	sea->InitFromData(vertices, indices);
	return sea;
}

Mesh* Object3D::Cloud2(std::string name, glm::vec3 leftBC) {

	float l1 = 0.5, l2 = 0.6, l3 = 0.4, l4 = 0.3;
	float l11 = 0.5,l5 = -0.5, l6 = 1.05;

	glm::vec3 color = glm::vec3(0.75, 0.65, 0.9);
	std::vector<VertexFormat> vertices
	{
		VertexFormat(glm::vec3(0, 0, 0), color),
		VertexFormat(glm::vec3(l1, 0, 0), color),
		VertexFormat(glm::vec3(0, l1-0.2 , 0), color),
		VertexFormat(glm::vec3(l1, l1 , 0), color),
		VertexFormat(glm::vec3(0, 0, l1), color),
		VertexFormat(glm::vec3(l1, 0, l1), color),
		VertexFormat(glm::vec3(0, l1 - 0.2, l1), color),
		VertexFormat(glm::vec3(l1, l1 , l1), color),

		VertexFormat(glm::vec3(l3, 0, 0), color),
		VertexFormat(glm::vec3(l3 + l2, 0, 0), color),
		VertexFormat(glm::vec3(l3 , l2 , 0), color),
		VertexFormat(glm::vec3(l3 + l2, l2, 0), color),
		VertexFormat(glm::vec3(l3, 0, l2), color),
		VertexFormat(glm::vec3(l3 + l2, 0, l2), color),
		VertexFormat(glm::vec3(l3, l2, l2), color),
		VertexFormat(glm::vec3(l3 + l2, l2, l2), color),

		VertexFormat(glm::vec3(l5, 0, 0), color),
		VertexFormat(glm::vec3(l5 + l4, 0, 0), color),
		VertexFormat(glm::vec3(l5, l4 , 0), color),
		VertexFormat(glm::vec3(l5 + l4, l4, 0), color),
		VertexFormat(glm::vec3(l5, 0, l4), color),
		VertexFormat(glm::vec3(l5 + l4, 0, l4), color),
		VertexFormat(glm::vec3(l5, l4, l4), color),
		VertexFormat(glm::vec3(l5 + l4, l4, l4), color),

		VertexFormat(glm::vec3(l6, 0, 0), color),
		VertexFormat(glm::vec3(l11 + l6, 0.1, 0), color),
		VertexFormat(glm::vec3(0 + l6, l11 , 0), color),
		VertexFormat(glm::vec3(l11 + l6, l11 - 0.1, 0), color),
		VertexFormat(glm::vec3(0 + l6, 0, l11), color),
		VertexFormat(glm::vec3(l11 + l6, 0.1, l11), color),
		VertexFormat(glm::vec3(0 + l6, l11, l11), color),
		VertexFormat(glm::vec3(l11 + l6, l11 - 0.1, l11), color),
	};

	std::vector<unsigned short> indices =
	{
		0, 1, 2,	8, 9, 10,	16, 17, 18,	24, 25, 26,
		1, 3, 2,	9, 11, 10,	17, 19, 18, 25, 27, 26,
		2, 3, 7,	10, 11, 15,	18, 19, 23,	26, 27, 31,
		2, 7, 6,	10, 15, 14,	18, 23, 22,	26, 31, 30,
		1, 7, 3,	9, 15, 11,	17, 23, 19,	25, 31, 27,
		1, 5, 7,	9, 13, 15,	17, 21, 23,	25, 29, 31,
		6, 7, 4,	14, 15, 12,	22, 23, 20, 30, 31, 28,
		7, 5, 4,	15, 13, 12,	23, 21, 20, 31, 29, 28,
		0, 4, 1,	8, 12, 9,	16, 20, 17, 24, 28, 25,
		1, 4, 5,	9, 12, 13,	17, 20, 21, 25, 28, 29,
		2, 6, 4,	10, 14, 12,	18, 22, 20, 26, 30, 28,
		0, 2, 4,	8, 10, 12,	16, 18, 20, 24, 26, 28,
	};

	Mesh* cloud = new Mesh(name);
	cloud->InitFromData(vertices, indices);
	return cloud;
}

Mesh* Object3D::Cloud3(std::string name, glm::vec3 leftBC) {

	float l1 = 0.5, l2 = 0.6, l3 = 0.4, l4 = 0.3;
	float l11 = 0.5, l5 = -0.5, l6 = 1.05;

	glm::vec3 color = glm::vec3(0.75, 0.75, 0.95);
	std::vector<VertexFormat> vertices
	{
		VertexFormat(glm::vec3(0, 0, 0), color),
		VertexFormat(glm::vec3(l1, 0, 0), color),
		VertexFormat(glm::vec3(0, l1 - 0.2 , 0), color),
		VertexFormat(glm::vec3(l1, l1 , 0), color),
		VertexFormat(glm::vec3(0, 0, l1), color),
		VertexFormat(glm::vec3(l1, 0, l1), color),
		VertexFormat(glm::vec3(0, l1 - 0.2, l1), color),
		VertexFormat(glm::vec3(l1, l1 , l1), color),

		VertexFormat(glm::vec3(l3, 0, 0), color),
		VertexFormat(glm::vec3(l3 + l2, 0, 0), color),
		VertexFormat(glm::vec3(l3 , l2 , 0), color),
		VertexFormat(glm::vec3(l3 + l2, l2, 0), color),
		VertexFormat(glm::vec3(l3, 0, l2), color),
		VertexFormat(glm::vec3(l3 + l2, 0, l2), color),
		VertexFormat(glm::vec3(l3, l2, l2), color),
		VertexFormat(glm::vec3(l3 + l2, l2, l2), color),

	};

	std::vector<unsigned short> indices =
	{
		0, 1, 2,	8, 9, 10,	
		1, 3, 2,	9, 11, 10,	
		2, 3, 7,	10, 11, 15,
		2, 7, 6,	10, 15, 14,	
		1, 7, 3,	9, 15, 11,	
		1, 5, 7,	9, 13, 15,
		6, 7, 4,	14, 15, 12,	
		7, 5, 4,	15, 13, 12,
		0, 4, 1,	8, 12, 9,	
		1, 4, 5,	9, 12, 13,	
		2, 6, 4,	10, 14, 12,
		0, 2, 4,	8, 10, 12,	
	};

	Mesh* cloud = new Mesh(name);
	cloud->InitFromData(vertices, indices);
	return cloud;
}

Mesh* Object3D::Cloud(std::string name, glm::vec3 leftBC) {

	float l1 = 0.5, l2 = 0.6, l3 = 1.05, l4 = -0.2, l5 = 0.4;
	glm::vec3 color = glm::vec3(0.75, 0.75, 0.85);
	std::vector<VertexFormat> vertices
	{
		VertexFormat(glm::vec3(0, 0, 0), color),
		VertexFormat(glm::vec3( l1, 0, 0), color),
		VertexFormat(glm::vec3(0, l1 , 0), color),
		VertexFormat(glm::vec3( l1, l1, 0), color),
		VertexFormat(glm::vec3(0, 0, l1), color),
		VertexFormat(glm::vec3( l1, 0, l1), color),
		VertexFormat(glm::vec3(0, l1, l1), color),
		VertexFormat(glm::vec3( l1, l1, l1), color),

		VertexFormat(glm::vec3(l1/1.5, l1/2, 0), color),
		VertexFormat(glm::vec3(0.7 * l2 + l1/1.5, -0.7 * l2 + l1 / 2 , 0), color),
		VertexFormat(glm::vec3(0.7 * l2 + l1/1.5, 0.7 * l2 + l1 / 2, 0), color),
		VertexFormat(glm::vec3(l1/1.5 + 1.4 * l2, 0 + l1 / 2, 0), color),
		VertexFormat(glm::vec3(l1/1.5, 0 + l1 / 2, l2), color),
		VertexFormat(glm::vec3(0.7 * l2 + l1/1.5, -0.7 * l2 + l1 / 2 , l2), color),
		VertexFormat(glm::vec3(0.7 * l2 + l1/1.5, 0.7 * l2 + l1 / 2, l2), color),
		VertexFormat(glm::vec3(l1/1.5 + 1.4 * l2, 0 + l1 / 2, l2), color),

		VertexFormat(glm::vec3(0 + l3, l4, 0), color),
		VertexFormat(glm::vec3(l1 + l3, l4, 0), color),
		VertexFormat(glm::vec3(0 + l3, l1 +l4 , 0), color),
		VertexFormat(glm::vec3(l1 + l3, l1+l4, 0), color),
		VertexFormat(glm::vec3(0 + l3, 0+l4, l1), color),
		VertexFormat(glm::vec3(l1 + l3, 0+l4, l1), color),
		VertexFormat(glm::vec3(0 + l3, l1+l4, l1), color),
		VertexFormat(glm::vec3(l1 + l3, l1+l4, l1), color),

		VertexFormat(glm::vec3(0+ l1 + l3, 0, 0), color),
		VertexFormat(glm::vec3(l5 + l1 + l3, 0, 0), color),
		VertexFormat(glm::vec3(0 + l1 + l3, l5 , 0), color),
		VertexFormat(glm::vec3(l5 + l1 + l3, l5, 0), color),
		VertexFormat(glm::vec3(0 + l1 + l3, 0, l5), color),
		VertexFormat(glm::vec3(l5 + l1 + l3, 0, l5), color),
		VertexFormat(glm::vec3(0 + l1 + l3, l5, l5), color),
		VertexFormat(glm::vec3(l5 + l1 + l3, l5, l5), color),
	};

	std::vector<unsigned short> indices =
	{
		0, 1, 2,	8, 9, 10,	16, 17, 18,	24, 25, 26,
		1, 3, 2,	9, 11, 10,	17, 19, 18, 25, 27, 26,
		2, 3, 7,	10, 11, 15,	18, 19, 23,	26, 27, 31,
		2, 7, 6,	10, 15, 14,	18, 23, 22,	26, 31, 30,
		1, 7, 3,	9, 15, 11,	17, 23, 19,	25, 31, 27,
		1, 5, 7,	9, 13, 15,	17, 21, 23,	25, 29, 31,
		6, 7, 4,	14, 15, 12,	22, 23, 20, 30, 31, 28,
		7, 5, 4,	15, 13, 12,	23, 21, 20, 31, 29, 28,
		0, 4, 1,	8, 12, 9,	16, 20, 17, 24, 28, 25,
		1, 4, 5,	9, 12, 13,	17, 20, 21, 25, 28, 29,
		2, 6, 4,	10, 14, 12,	18, 22, 20, 26, 30, 28,
		0, 2, 4,	8, 10, 12,	16, 18, 20, 24, 26, 28,
	};

	Mesh* cloud = new Mesh(name);
	cloud->InitFromData(vertices, indices);
	return cloud;
}

Mesh* Object3D::Propeller(std::string name, glm::vec3 leftBC) {
	glm::vec3 color = glm::vec3(0.75, 0.75, 0.75);
	std::vector<VertexFormat> vertices;

	vertices.push_back(VertexFormat(glm::vec3(1.03, 0.21, -0.2), color));
	vertices.push_back(VertexFormat(glm::vec3(1.03, 0.21, 0.9), color));
	vertices.push_back(VertexFormat(glm::vec3(1.03, 0.29, -0.2), color));
	vertices.push_back(VertexFormat(glm::vec3(1.03, 0.29, 0.9), color));

	vertices.push_back(VertexFormat(glm::vec3(1.09, 0.21, -0.2), color));
	vertices.push_back(VertexFormat(glm::vec3(1.09, 0.21, 0.9), color));
	vertices.push_back(VertexFormat(glm::vec3(1.09, 0.29, -0.2), color));
	vertices.push_back(VertexFormat(glm::vec3(1.09, 0.29, 0.9), color));

	std::vector<unsigned short> indices =
	{
		0, 1, 2,
		1, 3, 2,
		2, 3, 7,
		2, 7, 6,
		1, 7, 3,
		1, 5, 7,
		6, 7, 4,
		7, 5, 4,
		0, 4, 1,
		1, 4, 5,
		2, 6, 4,
		0, 2, 4,
	};

	Mesh* propeller = new Mesh(name);
	propeller->InitFromData(vertices, indices);
	return propeller;
}


Mesh* Object3D::Airplane(std::string name, glm::vec3 leftBC, glm::vec3 color) {

	float l1 = 2.5, l2 = 5.0, l3 = 10.0;
	float a = 0.2, b = 0.5, c = 1;
	float d = 0.1, e = 0.4, f = 0.3;
	float g = 0.7, h = 0.25, i = 0.8;
	float j = 0.2;

	glm::vec3 color2 = glm::vec3(1, 0, 0);

	color2 = glm::vec3(1.0 ,0.5, 0.0);
	glm::vec3 color3 = glm::vec3(0.5, 0.2, 0.5);
	glm::vec3 color4 = glm::vec3(0.5f, 0.99f, 0.0f);
	glm::vec3 color5 = glm::vec3(0.74, 0.5, 0.56);
	std::vector<VertexFormat> vertices;

	vertices.push_back(VertexFormat(  glm::vec3(0, 0, a), color));
	vertices.push_back(VertexFormat( glm::vec3(0, 0, b), color));
	vertices.push_back(VertexFormat( glm::vec3(0, a, a), color));
	vertices.push_back(VertexFormat( glm::vec3(0, a, b), color));

	vertices.push_back(VertexFormat( glm::vec3(c, 0, 0), color));
	vertices.push_back(VertexFormat( glm::vec3(c, 0, a + b), color));
	vertices.push_back(VertexFormat( glm::vec3(c, b, 0), color));
	vertices.push_back(VertexFormat( glm::vec3(c, b, a + b), color));

	// control
	vertices.push_back(VertexFormat(glm::vec3(d, 0, a+d), color2));
	vertices.push_back(VertexFormat(glm::vec3(d, 0, b - d ), color2));
	vertices.push_back(VertexFormat(glm::vec3(d, e, a + d), color2));
	vertices.push_back(VertexFormat(glm::vec3(d, e, b - d), color2));

	vertices.push_back(VertexFormat(glm::vec3(-a, 0, a + d), color2));
	vertices.push_back(VertexFormat(glm::vec3(-a, 0, b - d), color2));
	vertices.push_back(VertexFormat(glm::vec3(-a, e, a + d), color2));
	vertices.push_back(VertexFormat(glm::vec3(-a, e, b - d), color2));

	//buton elice
	vertices.push_back(VertexFormat(glm::vec3(c + j, a, f), color2));
	vertices.push_back(VertexFormat(glm::vec3(c + j, a, e), color2));
	vertices.push_back(VertexFormat(glm::vec3(c + j, f, f), color2));
	vertices.push_back(VertexFormat(glm::vec3(c + j, f, e), color2));

	vertices.push_back(VertexFormat(glm::vec3(c+d + j, a, f), color2));
	vertices.push_back(VertexFormat(glm::vec3(c+d + j, a, e), color2));
	vertices.push_back(VertexFormat(glm::vec3(c+d + j, f, f), color2));
	vertices.push_back(VertexFormat(glm::vec3(c+d + j, f, e), color2));

	//aripi
	vertices.push_back(VertexFormat(glm::vec3(e, a, -g), color2));
	vertices.push_back(VertexFormat(glm::vec3(e, a, 2*g), color2));
	vertices.push_back(VertexFormat(glm::vec3(e, h, -g), color2));
	vertices.push_back(VertexFormat(glm::vec3(e, h, 2*g), color2));

	vertices.push_back(VertexFormat(glm::vec3(i, a, -g), color2));
	vertices.push_back(VertexFormat(glm::vec3(i, a, 2*g), color2));
	vertices.push_back(VertexFormat(glm::vec3(i, h, -g), color2));
	vertices.push_back(VertexFormat(glm::vec3(i, h, 2*g), color2));

	//bot avion
	vertices.push_back(VertexFormat(glm::vec3(c, 0, 0), color3));
	vertices.push_back(VertexFormat(glm::vec3(c, 0, a + b), color3));
	vertices.push_back(VertexFormat(glm::vec3(c, b, 0), color3));
	vertices.push_back(VertexFormat(glm::vec3(c, b, a + b), color3));

	vertices.push_back(VertexFormat(glm::vec3(c + j, 0, 0), color3));
	vertices.push_back(VertexFormat(glm::vec3(c + j, 0, a + b), color3));
	vertices.push_back(VertexFormat(glm::vec3(c + j, b, 0), color3));
	vertices.push_back(VertexFormat(glm::vec3(c + j, b, a + b), color3));

	// pilor
	vertices.push_back(VertexFormat(glm::vec3(e - d, a - 0.05, a ), color4));
	vertices.push_back(VertexFormat(glm::vec3(e - d, a - 0.05, f + a), color4));
	vertices.push_back(VertexFormat(glm::vec3(e - d, a + f - 0.05, a ), color4));
	vertices.push_back(VertexFormat(glm::vec3(e - d, a + f - 0.05, f + a ), color4));

	vertices.push_back(VertexFormat(glm::vec3(i - d, a - 0.05, a), color4));
	vertices.push_back(VertexFormat(glm::vec3(i - d, a - 0.05, f + a), color4));
	vertices.push_back(VertexFormat(glm::vec3(i - d, a + f - 0.05, a), color4));
	vertices.push_back(VertexFormat(glm::vec3(i - d, a + f - 0.05, f + a), color4));

	vertices.push_back(VertexFormat(glm::vec3(e , a + f +a - 0.05, a + 0.05), color5));
	vertices.push_back(VertexFormat(glm::vec3(e , a + a + f- 0.05, f + a - 0.05), color5));
	vertices.push_back(VertexFormat(glm::vec3(e , a + f - 0.05, a + 0.05), color5));
	vertices.push_back(VertexFormat(glm::vec3(e , a + f - 0.05, f + a - 0.05), color5));

	vertices.push_back(VertexFormat(glm::vec3(i - d - d, a + a +f - 0.05, a + 0.05), color5));
	vertices.push_back(VertexFormat(glm::vec3(i - d - d, a + a + f - 0.05, f + a - 0.05), color5));
	vertices.push_back(VertexFormat(glm::vec3(i - d - d, a + f - 0.05, a + 0.05), color5));
	vertices.push_back(VertexFormat(glm::vec3(i - d - d, a + f - 0.05, f + a - 0.05), color5));


	std::vector<unsigned short> indices =
	{
		0, 1, 2,	8, 9, 10,		32, 33, 34,	48, 49, 50,
		1, 3, 2,	9, 11, 10,		33, 35, 34,	49, 51, 50,
		2, 3, 7,	10, 11, 15,		34, 35, 39,	50, 51, 55,
		2, 7, 6,	10, 15, 14,		34, 39, 38,	50, 55, 54,
		1, 7, 3,	9, 15, 11,		33, 39, 35,	49, 55, 51,
		1, 5, 7,	9, 13, 15,		33, 37, 39,	49, 53, 55,
		6, 7, 4,	14, 15, 12,		38, 39, 36,	54, 55, 52,
		7, 5, 4,	15, 13, 12,		39, 37, 36,	55, 53, 52,
		0, 4, 1,	8, 12, 9,		32, 36, 33,	48, 52, 49,
		1, 4, 5,	9, 12, 13,		33, 36, 37,	49, 52, 53,
		2, 6, 4,	10, 14, 12,		34, 38, 36,	50, 54, 52,
		0, 2, 4,	8, 10, 12,		32, 34, 36,	48, 50, 52,

		16, 17, 18,		24, 25, 26,		40, 41, 42,
		17, 19, 18,		25, 27, 26,		41, 43, 42,
		18, 19, 23,		26, 27, 31,		42, 43,47,
		18, 23, 22,		26, 31, 30,	42,47,46,
		17, 23, 19,		25, 31, 27,	41,47,43,
		17, 21, 23,		25, 29, 31,	41,45,47,
		22, 23, 20,		30, 31, 28,	46,47,44,
		23, 21, 20,		31, 29, 28,	47,45,44,
		16, 20, 17,		24, 28, 25,	40,44,41,
		17, 20, 21,		25, 28, 29,	41,44,45,
		18, 22, 20,		26, 30, 28,	42, 46, 44,
		16, 18, 20,		24, 26, 28,	40,42,44,
		
	};

	Mesh* airplane = new Mesh(name);
	airplane->InitFromData(vertices, indices);
	return airplane;
}

Mesh* Object3D::Obstacle(std::string name, glm::vec3 leftBC, glm::vec3 color) {

	//glm::vec3 color = glm::vec3(0.8, 0.1, 0.2);

	std::vector<VertexFormat> vertices
	{
		VertexFormat(glm::vec3(0, 0, 0), color),

		VertexFormat(glm::vec3(1, 0.6, 0), color),
		VertexFormat(glm::vec3(0.3, 0.6, 0.95), color),
		VertexFormat(glm::vec3(-0.8, 0.6, 0.58), color),
		VertexFormat(glm::vec3(-0.75, 0.6, -0.67), color),
		VertexFormat(glm::vec3(0.31, 0.6, -0.95), color),

		VertexFormat(glm::vec3(0, 2, 0), color),

		VertexFormat(glm::vec3(0.8, 1.4, 0.6), color),
		VertexFormat(glm::vec3(-0.3, 1.4, 0.95), color),
		VertexFormat(glm::vec3(-1, 1.4, 0), color),
		VertexFormat(glm::vec3(-0.3, 1.4, -0.95), color),
		VertexFormat(glm::vec3(0.8, 1.4, -0.6), color),

	};

	std::vector<unsigned short> indices =
	{
		0, 1, 2,	6, 7, 8,
		0, 2, 3,	6, 8, 9,
		0, 3, 4,	6, 9, 10,
		0, 4, 5,	6, 10, 11,
		0, 5, 1,	6, 11, 7,
		1, 2, 7,	7, 8, 2,
		2, 3, 8,	8, 9, 3,
		3, 4, 9,	9, 10, 4,
		4, 5, 10,	10, 11, 5,
		5, 1, 11,	11, 7, 1
	};


	Mesh* obstacle = new Mesh(name);
	obstacle->InitFromData(vertices, indices);
	return obstacle;
}

Mesh* Object3D::FuelBar(std::string name, float aux,float l,glm::vec3 leftBC, glm::vec3 color) {
	std::vector<VertexFormat> vertices
	{
		VertexFormat(glm::vec3(aux, aux, 0) + leftBC, color),
		VertexFormat(glm::vec3(4*l - aux, aux, 0) + leftBC, color),
		VertexFormat(glm::vec3(4*l - aux, l - aux, 0) + leftBC, color),
		VertexFormat(glm::vec3(aux, l - aux, 0) + leftBC, color),
	};

	std::vector<unsigned short> indices =
	{
		0, 1, 2,
		0, 2, 3
	};

	Mesh* fluebar = new Mesh(name);
	fluebar->InitFromData(vertices, indices);
	return fluebar;
}

Mesh* Object3D::FuelBar2(std::string name, float l1, float l2, glm::vec3 leftBC, glm::vec3 color) {

	std::vector<VertexFormat> vertices
	{
		VertexFormat(glm::vec3(0, 0, 0) + leftBC, color),
		VertexFormat(glm::vec3(4*l1 , 0, 0) + leftBC, color),
		VertexFormat(glm::vec3(4*l1 , l2, 0) + leftBC, color),
		VertexFormat(glm::vec3(0, l2, 0) + leftBC, color),
	};

	std::vector<unsigned short> indices =
	{
		0, 1, 2,
		0, 2, 3
	};

	Mesh* fluebar = new Mesh(name);
	fluebar->InitFromData(vertices, indices);
	return fluebar;
}

Mesh* Object3D::Heart(std::string name, glm::vec3 leftBC, glm::vec3 color) {

	std::vector<VertexFormat> vertices
	{
		VertexFormat(glm::vec3(0, 0.05, 0), color),

		VertexFormat(glm::vec3(0.1, 0.15, 0), color),
		VertexFormat(glm::vec3(0.25, 0.2, 0), color),
		VertexFormat(glm::vec3(0.4, 0.15, 0), color),
		VertexFormat(glm::vec3(0.5, 0, 0), color),

		VertexFormat(glm::vec3(0.45, -0.15, 0), color),
		VertexFormat(glm::vec3(0.375, -0.25, 0), color),
		VertexFormat(glm::vec3(0.25, -0.4, 0), color),
		VertexFormat(glm::vec3(0, -0.6, 0), color),

			VertexFormat(glm::vec3(-0.1, 0.15, 0), color),
		VertexFormat(glm::vec3(-0.25, 0.2, 0), color),
		VertexFormat(glm::vec3(-0.4, 0.15, 0), color),
		VertexFormat(glm::vec3(-0.5, 0, 0), color),

		VertexFormat(glm::vec3(-0.45, -0.15, 0), color),
		VertexFormat(glm::vec3(-0.375, -0.25, 0), color),
		VertexFormat(glm::vec3(-0.25, -0.4, 0), color),

	};

	std::vector<unsigned short> indices =
	{
		0, 1, 8,	0, 9, 8,
		1, 2, 8,	9, 10, 8,
		2, 3, 8,	10, 11, 8,
		3, 4, 8,	11, 12, 8,
		4, 5, 8,	12, 13, 8,
		5, 6, 8,	13, 14, 8,
		6, 7, 8,	14, 15, 8
		
	};

	Mesh* heart = new Mesh(name);
	heart->InitFromData(vertices, indices);
	return heart;
}

Mesh* Object3D::Fuel(std::string name, glm::vec3 leftBC) {
	
	glm::vec3 color = glm::vec3(0.2, 0.8, 0.2);

	std::vector<VertexFormat> vertices
	{
		VertexFormat(glm::vec3(0, 0, 0), color),
		VertexFormat(glm::vec3(1, 0, 0), glm::vec3(0.2, 1, 0.2)),
		VertexFormat(glm::vec3(0.5, 0, 0.9), glm::vec3(0.2, 0.9, 0.2)),
		VertexFormat(glm::vec3(0.5, 0.8, 0.5), glm::vec3(0.3, 0.7, 0.3))
	};

	std::vector<unsigned short> indices =
	{
		0, 1, 2,
		0, 3, 2,
		0, 1, 3,
		1, 2, 3
	};

	Mesh* fuel = new Mesh(name);
	fuel->InitFromData(vertices, indices);
	return fuel;
}


Mesh* Object3D::Box(std::string name, glm::vec3 leftBottomCorner, float radius, glm::vec3 color) {

	std::vector<VertexFormat> vertices
	{
		VertexFormat(glm::vec3(0, 0, 1), color),
		VertexFormat(glm::vec3(1, 0, 1), color),
		VertexFormat(glm::vec3(0, 1, 1), color),
		VertexFormat(glm::vec3(1, 1, 1), color),
		VertexFormat(glm::vec3(0, 0, 0), color),
		VertexFormat(glm::vec3(1, 0, 0), color),
		VertexFormat(glm::vec3(0, 1, 0), color),
		VertexFormat(glm::vec3(1, 1, 0), color),
	};

	std::vector<unsigned short> indices =
	{
		0, 1, 2,	
		1, 3, 2,	
		2, 3, 7,
		2, 7, 6,
		1, 7, 3,
		1, 5, 7,
		6, 7, 4,
		7, 5, 4,
		0, 4, 1,
		1, 4, 5,
		2, 6, 4,
		0, 2, 4,
	};

	Mesh* box = new Mesh(name);
	box->InitFromData(vertices, indices);
	return box;
}