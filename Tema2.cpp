#include "Tema2.h"
#include "Object3D.h"
#include "Transform3D.h"

#include <vector>
#include <iostream>
#include <time.h>
#include <stdlib.h>

#include <Core/Engine.h>


using namespace std;

Tema2::Tema2()
{
}

Tema2::~Tema2()
{
}

void Tema2::Init()
{
	cullFace = GL_BACK;
	
	polygonMode = GL_FILL;

	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	camera = new Camera::Camera();

	//glm::ivec2 resolution = window->GetResolution();
	auto camera = GetSceneCamera();
	//camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
	//camera->SetPosition(glm::vec3(0, 0, -1));
	//camera->SetPosition(glm::vec3(0, 0, 50));
	//camera->Set(glm::vec3(0, 15, 4), glm::vec3(0, 0, -25), glm::vec3(0, 0, -2));
//	camera->position = glm::vec3(0, 8, 5);

	{
		Shader* shader = new Shader("ShaderSea");
		shader->AddShader("Source/Laboratoare/Tema2/Shaders/VertexShader.glsl", GL_VERTEX_SHADER);
		shader->AddShader("Source/Laboratoare/Tema2/Shaders/FragmentShader.glsl", GL_FRAGMENT_SHADER);
		shader->CreateAndLink();
		shaders[shader->GetName()] = shader;
	}



	glm::vec3 corner = glm::vec3(0, 0, 0);
	glm::vec3 corner2 = glm::vec3(0, 0, 0.01);

	Mesh* square = Object3D::Box("box", corner, 100, glm::vec3(0.75, 0.75, 0.95));
	AddMeshToList(square);

	Mesh* airplane = Object3D::Airplane("airplane", corner, glm::vec3(1, 1, 0));
	AddMeshToList(airplane);

	Mesh* propeller = Object3D::Propeller("propeller", corner);
	AddMeshToList(propeller);

	Mesh* fuel = Object3D::Fuel("fuel", corner);
	AddMeshToList(fuel);

	Mesh* cloud = Object3D::Cloud("cloud", corner);
	AddMeshToList(cloud);

	Mesh* cloud2 = Object3D::Cloud2("cloud2", corner);
	AddMeshToList(cloud2);

	Mesh* cloud3 = Object3D::Cloud3("cloud3", corner);
	AddMeshToList(cloud3);

	Mesh* fuelbar1 = Object3D::FuelBar2("fuelbar1",1, 1, corner, glm::vec3(1,1,1));
	AddMeshToList(fuelbar1);
	Mesh* fuelbar2 = Object3D::FuelBar2("fuelbar2", 0.95f, 0.8f, corner2, glm::vec3(0, 1, 0.5));
	AddMeshToList(fuelbar2);

	Mesh* obstacle = Object3D::Obstacle("obstacle", corner, glm::vec3(0.8, 0.1, 0.2));
	AddMeshToList(obstacle);

	Mesh* fum = Object3D::Obstacle("fum", corner, glm::vec3(0.55, 0.55, 0.55));
	AddMeshToList(fum);

	Mesh* par = Object3D::Obstacle("par", corner, glm::vec3(0.15, 0.1, 0.1));
	AddMeshToList(par);

	Mesh* heart = Object3D::Heart("heart",  corner, glm::vec3(1, 0, 0));
	AddMeshToList(heart);

	Mesh* sea = Object3D::Sea2("sea", corner);
	AddMeshToList(sea);

	projectionMatrix = glm::perspective(RADIANS(60), window->props.aspectRatio, 0.01f, 200.0f);

	//glm::ivec2 resolution = window->GetResolution();
	//auto camera = GetSceneCamera();
	//camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
	
	//camera->SetRotation(glm::vec3(0, 0, 0));
	//camera->Update();
	//GetCameraInput()->SetActive(true);

	srand(time(NULL));

	posZ = -12;
	posX = -4;
	posY = -1;
	rotateSea = 1;
	vFum = 0;
	dif = 0;

	for (int i = 0; i < 50; i++) {
		
		combustibilC[i] = false;
	}

	for (int i = 0; i < 10; i++) {
		randFum[i] = rand() % 4 + 1;
		for (int j = 0; j < 5; j++) {
			combustibilX[i*5 + j] = 20 + i*20 + j;

		}
	}

	for (int i = 0; i < 10; i++) {

		float randY = rand() % 5 - 1.5 + (rand() % 5) / 5.0f;
		for (int j = 0; j < 5; j++) {
			combustibilY[i * 5 + j] = randY;
		}
	}

	for (int i = 0; i < 20; i++) {
		obstacoleC[i] = false;
		obstacoleX[i] = 20 + i * 10;
		obstacoleY[i] = rand() % 5 - 2 + (rand() % 5)/5.0f;
		obstacoleUP[i] = 0;
	}

	for (int i = 20; i < 30; i++) {
		obstacoleY[i] = false;
		obstacoleX[i] = (i - 19)* 15 + 2;
		obstacoleY[i] = rand() % 5 - 2 + (rand() % 5) / 5.0f;
		obstacoleUP[i] = 0;
	}

}

void Tema2::FrameStart()
{
	glClearColor(0.9, 0.7, 0.5, 1);
	//glClearColor(0, 0, 0, 1);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::ivec2 resolution = window->GetResolution();
	glViewport(0, 0, resolution.x, resolution.y);


}

void Tema2::Update(float deltaTimeSeconds)
{

	posZ = -12;
	posX = -4;
	posY = -1;


	if (P) {
		deltaTimeSeconds = 0;
	}
	
	if (end) {
		endGame += 5 * deltaTimeSeconds;
		rotateAir = -50;
		deltaTimeSeconds = 0;
	}
	vObsY += accObsY * deltaTimeSeconds;
	if (!speedMouse) {
		rotateSea += 2 * accelerationSea * deltaTimeSeconds;
		rotatePropeller += 2 * accPropeller * deltaTimeSeconds;
		rotateObs +=  (1.5 + dif )* accObs1 * deltaTimeSeconds;
		reservoir += 2* auxFuel * deltaTimeSeconds;

		vObsX += (2 + dif) * accObsX * deltaTimeSeconds;
	}
	else {
		rotateSea += accelerationSea * deltaTimeSeconds;
		rotatePropeller += accPropeller * deltaTimeSeconds;
		rotateObs += (1 + dif) * accObs1 * deltaTimeSeconds;
		reservoir += auxFuel * deltaTimeSeconds;

		vObsX += (1.3f + dif )*accObsX * deltaTimeSeconds;

	}

	if (rotateSea > 150) {
		dif = 0.1;
	}
	else if (rotateSea > 300) {
		dif = 0.2;
	}
	else
		dif = 0.35;


	if (reservoir < 0) {
		end = true;
	}
		

	if (C == false) {
		float cameraX = 0, cameraY = 0;
		if (!speedMouse) {
			cameraX = -0.2;
		//	cameraY = 1;
		}

		camera->position = glm::vec3(posX -0.5 + cameraX, posY + pozAir + cameraY + 1, posZ + 0.25);
		camera->forward = glm::vec3(2, 0, 0);
		camera->up = glm::vec3(0, 1, 0);
		camera->right = glm::vec3(0, 0, 1);
		
		modelMatrix = glm::mat4(1);
		modelMatrix *=
			glm::rotate(modelMatrix, RADIANS(90), glm::vec3(0, 1, 0))
			*glm::translate(modelMatrix, glm::vec3(2 , -6 - pozAir/2, +10))
			* glm::rotate(modelMatrix, RADIANS(auxRotate * rotateSea), glm::vec3(0, 0, 1))
		//	* glm::rotate(modelMatrix, RADIANS(90), glm::vec3(0, 1, 0))

			//* glm::rotate(modelMatrix, RADIANS(auxRotate * rotateSea), glm::vec3(0, 0, 1))
			//	*	 glm::translate(modelMatrix, glm::vec3(0, -10, 0))
			* glm::scale(modelMatrix, glm::vec3(5, 5, 3))
			//* glm::rotate(modelMatrix, RADIANS(25) , glm::vec3(1, 0, 0))
			;
		//Transform3D::Scale(, 3, 3);n
		RenderSimpleMesh(meshes["sea"], shaders["ShaderSea"], modelMatrix);

		// COMBUSTIBIL
		modelMatrix = glm::mat4(1);
		modelMatrix *= glm::translate(modelMatrix, glm::vec3(9.5 + cameraX, 6.7 + pozAir + posY +cameraY, posZ + 9.9 ))
			* glm::rotate(modelMatrix, RADIANS(270), glm::vec3(0, 1, 0));
		RenderMesh(meshes["fuelbar1"], shaders["VertexColor"], modelMatrix);
		modelMatrix = glm::mat4(1);
		modelMatrix *= glm::translate(modelMatrix, glm::vec3(9.5 + cameraX, 6.7 + pozAir + posY + cameraY, posZ + 9.9))
			* glm::translate(modelMatrix, glm::vec3(0, 0.1f, 0.1f))
			* glm::scale(modelMatrix, glm::vec3(1, 1, reservoir))
			* glm::rotate(modelMatrix, RADIANS(270), glm::vec3(0, 1, 0));
		RenderMesh(meshes["fuelbar2"], shaders["VertexColor"], modelMatrix);

		for (int i = life; i < 5; i++) {
			modelMatrix = glm::mat4(1);
			modelMatrix *= glm::translate(modelMatrix, glm::vec3(10.3 +cameraX, 6.2 + pozAir + posY + cameraY,  i * 1.2 + posZ + 8.3))
				* glm::rotate(modelMatrix, RADIANS(90), glm::vec3(0,  1, 0));
			RenderMesh(meshes["heart"], shaders["VertexColor"], modelMatrix);
		}
	}
	else {

		float cameraZ = 0;
		if (!speedMouse) {
			cameraZ = 1;
		}

		camera->position = glm::vec3(0, -1, 0 + cameraZ);
		camera->forward = glm::vec3(0, 0, -2);
		camera->up = glm::vec3(0, 1, 0);
		camera->right = glm::vec3(1, 0, 0);
		

	modelMatrix = glm::mat4(1);
	modelMatrix *=
		glm::translate(modelMatrix, glm::vec3(0, -8, 7))
		* glm::rotate(modelMatrix, RADIANS(auxRotate * rotateSea), glm::vec3(0, 0, 1))
		* glm::scale(modelMatrix, glm::vec3(5, 5, 3))
		 ;
	RenderSimpleMesh(meshes["sea"], shaders["ShaderSea"], modelMatrix);

	modelMatrix = glm::mat4(1);
	modelMatrix *=
		glm::translate(modelMatrix, glm::vec3( + 2, -8, 7))
		* glm::rotate(modelMatrix, RADIANS(auxRotate * rotateSea), glm::vec3(0, 0, 1))
		* glm::scale(modelMatrix, glm::vec3(5, 5, 3))
		;
	RenderSimpleMesh(meshes["sea"], shaders["ShaderSea"], modelMatrix);

	modelMatrix = glm::mat4(1);
	modelMatrix *=
		glm::translate(modelMatrix, glm::vec3(-2, -8, 7))
		* glm::rotate(modelMatrix, RADIANS(auxRotate * rotateSea), glm::vec3(0, 0, 1))
		* glm::scale(modelMatrix, glm::vec3(5, 5, 3))
		;
	RenderSimpleMesh(meshes["sea"], shaders["ShaderSea"], modelMatrix);

		// COMBUSTIBIL
		modelMatrix = glm::mat4(1);
		modelMatrix *= glm::translate(modelMatrix, glm::vec3(10, 5.5, -14 + cameraZ));
		RenderMesh(meshes["fuelbar1"], shaders["VertexColor"], modelMatrix);
		modelMatrix = glm::mat4(1);
		modelMatrix *= glm::translate(modelMatrix, glm::vec3(10, 5.5, -14 + cameraZ))
		* glm::translate(modelMatrix, glm::vec3(0.1f, 0.1f, 0))
		* glm::scale(modelMatrix, glm::vec3( reservoir, 1, 1));
		RenderMesh(meshes["fuelbar2"], shaders["VertexColor"], modelMatrix);

		for (int i = life; i < 5; i++) {
			modelMatrix = glm::mat4(1);
			modelMatrix *= glm::translate(modelMatrix, glm::vec3(8.5 + i * 1.2, 5, -14 + cameraZ));
			RenderMesh(meshes["heart"], shaders["VertexColor"], modelMatrix);
		}
	}

// ================================== AVION =================================


	modelMatrix = glm::mat4(1);
//	RenderSimpleMesh(meshes["airplane"], shaders["VertexColor"], modelMatrix);
	modelMatrix *= glm::translate(modelMatrix, glm::vec3(posX, posY, posZ))
		* glm::translate(modelMatrix, glm::vec3(0, pozAir - endGame, 0))
		* glm::rotate(modelMatrix, RADIANS(rotateAir), glm::vec3(0, 0, 1))
		* glm::scale(modelMatrix, glm::vec3(1, 1, 1))
		* glm::scale(modelMatrix, glm::vec3(0.9, 0.9, 0.9))
		;
	RenderMesh(meshes["airplane"], shaders["VertexColor"], modelMatrix);
	modelMatrix = glm::mat4(1);
	modelMatrix *=
		glm::translate(modelMatrix, glm::vec3(posX, posY, posZ))
		* glm::translate(modelMatrix, glm::vec3(0.20, pozAir - endGame, 0))
		* glm::scale(modelMatrix, glm::vec3(0.9, 0.9, 0.9))
		* glm::rotate(modelMatrix, RADIANS(rotateAir), glm::vec3(0, 0, 1))

		* glm::translate(modelMatrix, glm::vec3(1.06, 0.25, 0.35))
		* glm::rotate(modelMatrix, RADIANS(rotatePropeller ), glm::vec3(1, 0, 0))
		* glm::translate(modelMatrix, glm::vec3(-1.06,- 0.25, -0.35))
		;
	
	RenderMesh(meshes["propeller"], shaders["VertexColor"], modelMatrix);

	vFum += 2 * deltaTimeSeconds;

	if (vFum > 2)
		vFum = 0;


	if (!speedMouse && !end) {
		for (int i = 0; i < 6; i++) {
			
			if (vFumX[i] > 1) {
				vFumX[i] = 0;
			}

			vFumX[i] += (i + 1)/6.f * randFum[i] * deltaTimeSeconds;


			modelMatrix = glm::mat4(1);
			modelMatrix *= glm::translate(modelMatrix, glm::vec3(posX, posY, posZ + 0.3))
				* glm::translate(modelMatrix, glm::vec3(0 - vFumX[i], pozAir  + vFumX[i]*(i+ 1)/10.f, 0.1))
			//	* glm::rotate(modelMatrix, RADIANS(rotateAir), glm::vec3(0, 0, 1))
				* glm::scale(modelMatrix, glm::vec3(0.12, 0.12, 0.12))
				;
			RenderMesh(meshes["fum"], shaders["VertexColor"], modelMatrix);
		}
	}

	modelMatrix = glm::mat4(1);
	modelMatrix *= glm::translate(modelMatrix, glm::vec3(posX, posY, posZ + 0.3))
		* glm::translate(modelMatrix, glm::vec3(0 + 0.4 - rotateAir / 100.f , pozAir + rotateAir/100.f + 0.5 - endGame, 0))
		* glm::scale(modelMatrix, glm::vec3(0.17, 0.17, 0.15))
		;
	RenderMesh(meshes["par"], shaders["VertexColor"], modelMatrix);
	int semn = 1;
	for (int i = 0; i < 6; i++) {

		if (i % 3 == 0)
			semn = 0;
		else if (i % 3 == 1)
			semn = 1;
		else
			semn = -0.5;
		modelMatrix = glm::mat4(1);
		modelMatrix *= glm::translate(modelMatrix, glm::vec3(posX, posY, posZ + 0.3))
			* glm::translate(modelMatrix, glm::vec3(0 + 0.4 - rotateAir / 100.f - vFumX[i]/10.f, pozAir + rotateAir / 100.f + 0.5 - endGame + semn*(i + 1)*vFumX[i] / 50.f, 0))
			* glm::scale(modelMatrix, glm::vec3(0.1, 0.1, 0.1))
			;
		RenderMesh(meshes["par"], shaders["VertexColor"], modelMatrix);
	}

// ==========================================================================

// ================================== NORI =================================
	float obsY = -19;

	for (int i = 0; i < 70; i++) {
		modelMatrix = glm::mat4(1);
		modelMatrix = modelMatrix
			* glm::translate(modelMatrix, glm::vec3(0, obsY, 0))
			* glm::rotate(modelMatrix, RADIANS(auxRotate * rotateObs), glm::vec3(0, 0, 1))
			* glm::translate(modelMatrix, glm::vec3(cloudX[i], cloudY[i], posZ + 0.25 + cloudZ[i]))
			* glm::rotate(modelMatrix, RADIANS(-auxRotate * rotateObs), glm::vec3(0, 0, 1))
			* glm::rotate(modelMatrix, RADIANS(auxRotate * rotateObs), glm::vec3(1, 0, 0))
			;
		if(i % 4 == 0)
			RenderMesh(meshes["cloud2"], shaders["VertexColor"], modelMatrix);
		else if (i % 3 == 0) {
			RenderMesh(meshes["cloud3"], shaders["VertexColor"], modelMatrix);
		}
		else
			RenderMesh(meshes["cloud"], shaders["VertexColor"], modelMatrix);
	}
// ==========================================================================

// ============================ COMBUSTIBIL =================================

	for (int i = 0; i < 50; i++) {

		if (combustibilX[i] - vObsX * 0.75f < 15 && combustibilX[i] - vObsX * 0.75f > 7) {
			combustibilUP[i] += accObsY * deltaTimeSeconds;

		}
		else if (combustibilX[i] - vObsX * 0.75f < 7 && combustibilX[i] - vObsX * 0.75f > -2) {
			combustibilUP[i] -= accObsY * deltaTimeSeconds;
		}
		else if (combustibilX[i] - vObsX * 0.75f < -2 && combustibilX[i] - vObsX * 0.75f > -5) {
			combustibilUP[i] += accObsY * deltaTimeSeconds;

		}
		else if (combustibilX[i] - vObsX * 0.75f < -5 && combustibilX[i] - vObsX * 0.75f > -15) {
			combustibilUP[i] -= accObsY * deltaTimeSeconds;

		}
		else {
			combustibilUP[i] = 0;
		}

		modelMatrix = glm::mat4(1);
		modelMatrix = modelMatrix
			* glm::translate(modelMatrix, glm::vec3(combustibilX[i] - vObsX*0.75f,combustibilY[i] + combustibilUP[i], posZ + 0.25))
			//* glm::scale(modelMatrix, glm::vec3(0.5, 0.5, 0.5))
			* glm::rotate(modelMatrix, RADIANS(auxRotate * rotateObs), glm::vec3(1, 0, 0))
			;

		if (combustibilX[i] - vObsX*0.75f < -20) {
			combustibilX[i] += 200;
			combustibilC[i] = false;
		}

		if (Coliziune2(posX, posY + pozAir, combustibilX[i] - vObsX*0.75f, combustibilY[i] + combustibilUP[i]) && !combustibilC[i]) {
			combustibilC[i] = true;
			if(reservoir <= 0.95)
				reservoir += 0.06;
			if (life == 5) {
				end = true;
			}
		}
		else if (!combustibilC[i] && combustibilX[i] - vObsX * 0.75f < 20) {
			RenderMesh(meshes["fuel"], shaders["VertexColor"], modelMatrix);
		}

	
	}

// ==========================================================================

// ============================== BOLOVANI ===================================
	for (int i = 0; i < 30; i++) {
		//obstacoleUP[30];
		//cout << " "<< obstacoleX[i] - vObsX << endl;

		if (obstacoleX[i] - vObsX < 25 && obstacoleX[i] - vObsX > 20) {
			obstacoleUP[i] = 0;
		}
		else if (obstacoleX[i] - vObsX < 20 && obstacoleX[i] - vObsX > 0) {
			obstacoleUP[i] += accObsY * deltaTimeSeconds;
		//	cout << "1 " << +obstacoleUP[i] << endl;
		}
		else if (obstacoleX[i] - vObsX < 0 && obstacoleX[i] - vObsX > -20) {
			obstacoleUP[i] -= 1.5*accObsY * deltaTimeSeconds;
		//	cout << "2 " << +obstacoleUP[i] << endl;

		}
		else if (obstacoleX[i] - vObsX < -20) {
			obstacoleUP[i] = 0;
		//	cout << "3 " << +obstacoleUP[i] << endl;
		}
		else if (obstacoleX[i] - vObsX > 25) {
			obstacoleUP[i] = -10;
		}
	}

	for (int i = 0; i < 30; i++) {

		if (i % 6 == 0) {

			modelMatrix = glm::mat4(1);
			modelMatrix = modelMatrix
				* glm::translate(modelMatrix, glm::vec3(obstacoleX[i] - vObsX, obstacoleY[i] + 0.8*obstacoleUP[i] , posZ - 4))
				* glm::scale(modelMatrix, glm::vec3(0.5, 0.5, 0.5))
				* glm::rotate(modelMatrix, RADIANS(auxRotate * rotateObs), glm::vec3(1, 0, 0))
				;
			if(obstacoleX[i] - vObsX < 25)
				RenderMesh(meshes["obstacle"], shaders["VertexColor"], modelMatrix);
		}

		if (i % 7 == 0) {

			modelMatrix = glm::mat4(1);
			modelMatrix = modelMatrix
				* glm::translate(modelMatrix, glm::vec3(obstacoleX[i] - vObsX , obstacoleY[i] + 0.9 * obstacoleUP[i] + 2, posZ - 7))
				* glm::scale(modelMatrix, glm::vec3(0.5, 0.5, 0.5))
				* glm::rotate(modelMatrix, RADIANS(auxRotate * rotateObs), glm::vec3(1, 0, 0))
				;
			if(obstacoleX[i] - vObsX < 25)
				RenderMesh(meshes["obstacle"], shaders["VertexColor"], modelMatrix);
		}


		modelMatrix = glm::mat4(1);
		modelMatrix = modelMatrix
			* glm::translate(modelMatrix, glm::vec3(obstacoleX[i] - vObsX, obstacoleY[i] + obstacoleUP[i], posZ +0.25))
			* glm::scale(modelMatrix, glm::vec3(0.5, 0.5, 0.5))
			* glm::rotate(modelMatrix, RADIANS(auxRotate * rotateObs), glm::vec3(1, 0, 0))
			;

		
		if (obstacoleX[i] - vObsX < -25) {
			obstacoleX[i] += 200;
			obstacoleUP[i] = 0;
			obstacoleC[i] = false;
		}

		if (Coliziune(posX, posY + pozAir, obstacoleX[i] - vObsX, obstacoleY[i] + obstacoleUP[i]) && !obstacoleC[i]) {
			obstacoleC[i] = true;
			life++;
			if (life == 5) {
				end = true;
			}
		}
		else if(!obstacoleC[i] && obstacoleX[i] - vObsX < 25) {
			RenderMesh(meshes["obstacle"], shaders["VertexColor"], modelMatrix);
		}

		
	}



	//for (int i = 0; i < 11; i++) {
	//	modelMatrix = glm::mat4(1);
	//	modelMatrix = modelMatrix
	//		* glm::translate(modelMatrix, glm::vec3(0, obsY, 0))
	//		* glm::rotate(modelMatrix, RADIANS( auxRotate * rotateObs), glm::vec3(0, 0, 1))
	//		* glm::translate(modelMatrix, glm::vec3(1.15*obssX[i], 1.15 * obssY[i], obssZ[i]))
	//		* glm::translate(modelMatrix, glm::vec3(0, 0, posZ + 0.25))
	//		* glm::scale(modelMatrix, glm::vec3(0.5, 0.5, 0.5))
	//		;
	//	RenderMesh(meshes["obstacle"], shaders["VertexColor"], modelMatrix);
	//}
// ==========================================================================
	
}

bool Tema2::Coliziune(float xA, float yA, float x, float y) {
	bool ans = false;

	if (xA > x -0.5 && xA + 0.2 < x + 0.5 && yA < y + 0.6 && y < yA )
		ans = true;
	else if (xA + 0.2 > x - 0.5 && xA < x + 0.5 &&  y < yA +1 && yA +1 < y + 0.6 )
		ans = true;
	else if (xA + 0.2 < x - 0.5 && x < xA + 0.8 && yA < y + 0.6 && y < yA)
		ans = true;
	else if (xA + 0.2 < x -0.5 && x < xA + 0.8 && y < yA + 1 && yA + 1 < y + 0.6)
		ans = true;
	return ans;
}

bool Tema2::Coliziune2(float xA, float yA, float x, float y) {
	bool ans = false;

	if (xA > x - 0.5 && xA < x + 0.5 && yA < y + 1 && y < yA)
		ans = true;
	else if (xA > x - 0.5 && xA < x + 0.5 && y < yA + 1 && yA + 1 < y + 1)
		ans = true;
	else if (xA < x - 0.5 && x < xA + 1 && yA < y + 1 && y < yA)
		ans = true;
	else if (xA < x - 0.5 && x < xA + 1 && y < yA + 1 && yA + 1 < y + 1)
		ans = true;
	return ans;
}

void Tema2::RenderSimpleMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix)
{
	if (!mesh || !shader || !shader->GetProgramID())
		return;

	// render an object using the specified shader and the specified position
	glUseProgram(shader->program);

	// TODO : get shader location for uniform mat4 "Model"
	int location = glGetUniformLocation(shader->GetProgramID(), "Model");
	// TODO : set shader uniform "Model" to modelMatrix
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(modelMatrix));

	// TODO : get shader location for uniform mat4 "View"
	location = glGetUniformLocation(shader->GetProgramID(), "View");
	// TODO : set shader uniform "View" to viewMatrix
	glm::mat4 viewMatrix = GetSceneCamera()->GetViewMatrix();

	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(viewMatrix));
	// TODO : get shader location for uniform mat4 "Projection"
	location = glGetUniformLocation(shader->GetProgramID(), "Projection");
	// TODO : set shader uniform "Projection" to projectionMatrix
	glm::mat4 projectionMatrix = GetSceneCamera()->GetProjectionMatrix();
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

	// TODO : get shader location for float  "Projection"
	location = glGetUniformLocation(shader->GetProgramID(), "Time");
	glUniform1f(location, Engine::GetElapsedTime());

	// Draw the object
	glBindVertexArray(mesh->GetBuffers()->VAO);
	glDrawElements(mesh->GetDrawMode(), static_cast<int>(mesh->indices.size()), GL_UNSIGNED_SHORT, 0);
}


void Tema2::RenderMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix)
{
	if (!mesh || !shader || !shader->program)
		return;

	// render an object using the specified shader and the specified position
	shader->Use();
	glUniformMatrix4fv(shader->loc_view_matrix, 1, GL_FALSE, glm::value_ptr(camera->GetViewMatrix()));
	glUniformMatrix4fv(shader->loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
	glUniformMatrix4fv(shader->loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

	mesh->Render();
}

void Tema2::FrameEnd()
{
	//DrawCoordinatSystem();
}

void Tema2::OnInputUpdate(float deltaTime, int mods)
{

}

void Tema2::Restart() {
	end = false;
	endGame =  0;
	rotateSea = 1;
	accelerationSea = 20;

	rotatePropeller = 2;
	accPropeller = 500;

	rotateObs = 5;
	accObs1 = 30;

	accRotate = 10;
	auxRotate = 1;
	auxRotate2 = 3;
	 posZ = 0;
	 posX = 0;
	 posY = 0;

	 life = 2;

	//AVION 
	 rotateAir = 0;
	 angleAir = 0;
	 fuel = 1;
	 fuelS = 0;

	//Combustibil:
	 auxFuel = -0.045;
	 reservoir = 1;


	// mouse:
	 speedMouse = false;
	 pozAir = 0.0f;
	 gravity = 10;

	 birdAcceleration = 0;
	 birdVelocity = 0;

	//OBSTACOLE:
	 accObs = 5;
	 vObs = 0;

	 accObsX = 5;
	 vObsX = 0;
	 accObsY = 1;
	 vObsY = 0;
}

void Tema2::OnKeyPress(int key, int mods)
{
	if (key == GLFW_KEY_P) {
		if (P == false)
			P = true;
		else
			P = false;
	}

	if (key == GLFW_KEY_R) {
		
		Restart();
		Init();
	}

	if (key == GLFW_KEY_S) {

	}

	if (key == GLFW_KEY_C) {
		if (C == false) {
			C = true;
		}
		else {
			C = false;
		}
	}
	/*	if (C) {
		/*forward = glm::vec3(0, 0, -2);
		up = glm::vec3(0, 1, 0);

	camera->position = glm::vec3(posX, posY + pozAir, posZ);
	camera->forward = glm::vec3(0, 0, -2);
	camera->up = glm::vec3(0, 1, 0);

	camera->RotateThirdPerson_OZ(DEGREES(0.01));

}
	else {
	camera->position = glm::vec3(0, -1, 0);
	camera->forward = glm::vec3(0, 0, -2);
	camera->up = glm::vec3(0, 1, 0);
	}
	*/

}

void Tema2::OnKeyRelease(int key, int mods)
{

}

void Tema2::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	// add mouse move event
	
	//cout << "x:" << mouseX << endl;
	if (end) {
		
	}
	else if(P) {

	}
	else {
		if (mouseX < window->GetResolution().x / 2) {
			speedMouse = true;
		}
		else {
			speedMouse = false;
		}

		if (deltaY == 0)
			rotateAir = 0;
		else if (deltaY < 0)
			rotateAir = 8;
		else
			rotateAir = -10;

		if (mouseY < 50) {
			pozAir = 5;
		}
		else if (mouseY > 400) {
			pozAir = 0;
			rotateAir = 0;

		}
		else {
			pozAir = (mouseY - 400.0f) * (-5.0f) / 350.0f;
		}
	}

}

void Tema2::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button press event
}

void Tema2::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button release event
}

void Tema2::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}

void Tema2::OnWindowResize(int width, int height)
{
}