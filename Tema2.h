#pragma once

#include <Component/SimpleScene.h>
#include <Core/Engine.h>

#include "Camera.h"


class Tema2 : public SimpleScene
{
public:
	Tema2();
	~Tema2();

	void Init() override;
private:
	void FrameStart() override;
	void Update(float deltaTimeSeconds) override;
	void FrameEnd() override;

	void OnInputUpdate(float deltaTime, int mods) override;
	void OnKeyPress(int key, int mods) override;
	void OnKeyRelease(int key, int mods) override;
	void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
	void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
	void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
	void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
	void OnWindowResize(int width, int height) override;
	void RenderMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix);
	void RenderSimpleMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix);

	bool Coliziune(float xA, float yA, float x, float y);
	bool Coliziune2(float xA, float yA, float x, float y);

	void Restart();

protected:
	Camera::Camera* camera;
	glm::mat4 projectionMatrix;
	glm::mat4 modelMatrix;
	GLenum cullFace;
	GLenum polygonMode;

	float endGame = 0;
	bool end = false;

	float rotateSea = 1;
	float accelerationSea = 20;

	float rotatePropeller = 2;
	float accPropeller = 500;

	float rotateObs = 5;
	float accObs1 = 30;

	float accRotate = 10;
	float auxRotate = 1;
	float auxRotate2 = 3;
	float posZ = 0;
	float posX = 0;
	float posY = 0;

	int life = 2;

	//AVION 
	float rotateAir = 0;
	float angleAir = 0;
	float fuel = 1;
	float fuelS = 0;
	float vFum = 0;
	float vFumX[10];
	int randFum[10];
	float dif = 0;

	//Combustibil:
	float auxFuel = -0.045;
	float reservoir = 1;


	// mouse:
	bool speedMouse = false;
	float pozAir = 0.0f;
	float gravity = 10;

	float birdAcceleration = 0;
	float birdVelocity = 0;

	//OBSTACOLE:
	float obstacoleY[30];
	float obstacoleX[30];
	bool obstacoleC[30];
	float obstacoleUP[30];

	float accObs = 5;
	float vObs = 0;

	float accObsX = 5;
	float vObsX = 0;
	float accObsY = 1;
	float vObsY = 0;

	float obssX[20] = {-24, -19 , -25, -10, - 22.1, 10, 19, 24.75, 5.4 , 17.5, 24.75 };
	float obssY[20] = {0, -17.7, -6.76, 22.75, 15.34, 22.75, 17.7, 3.5, -25.9 , -17.5 , -3.5 };
	float obssZ[20] = {-2, -5, -3, -4, -5, -6, -7, -5, -3, -8, -4};

	// COMBUSTIBIL:
	float combustibilY[50];
	float combustibilX[50];
	bool combustibilC[50];
	float combustibilUP[50];

	float fuelX[50] = {-12, -12.3, -12.5, -12.8, -13,
						-19.8, -19.3, -18.6,
						14.7, 14.2, 13.6, 13.2,
						23, 22.3, 21.7, 21, 20.4, 19.7,
						14.7, 15.2, 15.6,
						-10, -11.2, -12.3, -13.4

						};
	float fuelY[50] = {-20.5, -19.5, -18.4, -17.2, -16.3,
						3.2, 4.5, 5.7,
						-14.7, -13.9, -13, -12,
						0, 0.8, 1.7, 2.3, 3.1, 4,
						14.7, 14, 13.2,
						17, 17.3, 17.1, 16.9
						};

	// NORI:
	float cloudX[70] = {-4.25, -5.4, -10, -13, -17.5, -19, -22.1, -23.5, -25, -24.75,
						-4.25, -5.4, -10, -13, -17.5, -19, -22.1, -23.5, -25, -24.75,
						4.25, 5.4, 10, 13, 17.5, 19, 22.1, 23.5, 25, 24.75,
						4.25, 5.4, 10, 13, 17.5, 19, 22.1, 23.5, 25, 24.75,
						-22, 7.8, -10, 16.7, -20.5, -21.7, 0, -10, -15.5, -17.2,
						0, -10, -15.5, -17.2 ,0, 10, 15.5, 17.2 , 0, 10, 15.5, 17.2,
						-5.4, -22.1, -10, -25, 4.25, 17.5, 13,  24.75};
	float cloudY[70] = {-24.5, -25.9, -22.75, -22.36, -17.5, -17.7, -15.34, -13.5, -6.76, -3.5,
						24.5, 25.9, 22.75, 22.36, 17.5, 17.7, 15.34, 13.5, 6.76, 3.5,
						24.5, 25.9, 22.75, 22.36, 17.5, 17.7, 15.34, 13.5, 6.76, 3.5,
						-24.5, -25.9, -22.75, -22.36, -17.5, -17.7, -15.34, -13.5, -6.76, -3.5,
						0, -22.06, 17.2, 14.2, -12, 5.87, -20, -17.2, -15.4, -10,
						20,17.2, 15.4, 10, 20, 17.2, 15.4, 10, -20, -17.2, -15.4, -10,
						 -25.9, -15.34, 22.75,  6.76, 24.5,  17.5, -22.36, -3.5 };
	float cloudZ[70] = {-6, -4, -7, 3, -5, -2, -5, 1, -1, -3,
						-8, -5, -6, -2, -3, 4, -3, -8, -6, -4,
						-2, -3, -5, -5, 2, 4, -7, -6, -4, -3,
						-10, -5, 4, -3, -6, -1, -3, -4, -2, -4,
						-3, -5, -1, -7, -3, -4, -8, -4, -7, -1, -2,
						2, -4, -7, -3, -1, -5, 3, 2, -2, -1,-5,
						-10, -11, -9, -10, -12, -10, -11, -10};
	

	// Interfata cu utilizatorul:
	bool P = false;
	bool C = true;
	bool R = false;
};