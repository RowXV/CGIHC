//Práctica 2 semestre 2024-2: índices, mesh, proyecciones, transformaciones geométricas
#include <stdio.h>
#include <string.h>
#include<cmath>
#include<vector>
#include <glew.h>
#include <glfw3.h>
//glm
#include<glm.hpp>	//	
#include<gtc\matrix_transform.hpp>
#include<gtc\type_ptr.hpp>
//clases para dar orden y limpieza al código
#include"Mesh.h"
#include"Shader.h"
#include"Window.h"
//Dimensiones de la ventana
const float toRadians = 3.14159265f/180.0; //grados a radianes
Window mainWindow;
std::vector<Mesh*> meshList;
std::vector<MeshColor*> meshColorList;
std::vector<Shader>shaderList;
//Vertex Shader
static const char* vShader = "shaders/shader.vert";
static const char* fShader = "shaders/shader.frag";

static const char* vShaderColor = "shaders/shadercolor.vert";
static const char* fShaderColor = "shaders/shadercolor.frag";
//shaders nuevos se crearían acá
static const char* vShaderR = "shaders/shaderR.vert";
static const char* fShaderR = "shaders/shaderR.frag";
static const char* vShaderV = "shaders/shaderV.vert";
static const char* fShaderV = "shaders/shaderV.frag";
static const char* vShaderA = "shaders/shaderA.vert";
static const char* fShaderA = "shaders/shaderA.frag";
static const char* vShaderC = "shaders/shaderC.vert";
static const char* fShaderC = "shaders/shaderC.frag";
static const char* vShaderVo = "shaders/shaderVo.vert";
static const char* fShaderVo = "shaders/shaderVo.frag";



float angulo = 0.0f;

//color café en RGB : 0.478, 0.255, 0.067

//Pirámide triangular regular
void CreaPiramide()
{
	unsigned int indices[] = { 
		0,1,2,
		1,3,2,
		3,0,2,
		1,0,3
		
	};
	GLfloat vertices[] = {
		-0.5f, -0.5f,0.0f,	//0
		0.5f,-0.5f,0.0f,	//1
		0.0f,0.5f, -0.25f,	//2
		0.0f,-0.5f,-0.5f,	//3

	};
	Mesh *obj1 = new Mesh();
	obj1->CreateMesh(vertices, indices, 12, 12);
	meshList.push_back(obj1);
}

//Vértices de un cubo
void CrearCubo()
{
	unsigned int cubo_indices[] = {
		// front
		0, 1, 2,
		2, 3, 0,
		// right
		1, 5, 6,
		6, 2, 1,
		// back
		7, 6, 5,
		5, 4, 7,
		// left
		4, 0, 3,
		3, 7, 4,
		// bottom
		4, 5, 1,
		1, 0, 4,
		// top
		3, 2, 6,
		6, 7, 3
	};

GLfloat cubo_vertices[] = {
	// front
	-0.5f, -0.5f,  0.5f,
	0.5f, -0.5f,  0.5f,
	0.5f,  0.5f,  0.5f,
	-0.5f,  0.5f,  0.5f,
	// back
	-0.5f, -0.5f, -0.5f,
	0.5f, -0.5f, -0.5f,
	0.5f,  0.5f, -0.5f,
	-0.5f,  0.5f, -0.5f
};
Mesh *cubo = new Mesh();
cubo->CreateMesh(cubo_vertices, cubo_indices,24, 36);
meshList.push_back(cubo);
}

void CrearLetrasyFiguras()
{


	GLfloat vertices_letras[] = {	
			//**************LETRA A -- 144
			//X		Y	 Z		 R		 G		 B

			//Lado IZQ A
			//Triangulo1
			-0.8f,0.0f,0.0f,	0.0f,	0.0f,	1.0f,// B
			-0.8f,0.8f,0.0f,	0.0f,	0.0f,	1.0f,//	A
			-0.7f,0.0f,0.0f,	0.0f,	0.0f,	1.0f,// C
			//Triangulo2
			-0.7f, 0.0f, 0.0f,	0.0f,	0.0f,	1.0f,// C
			-0.8f,0.8f,0.0f,	0.0f,	0.0f,	1.0f,//	A
			-0.7f,0.8f,0.0f,	0.0f,	0.0f,	1.0f,// D

			//Lado DER A
			//Triangulo1
			-0.6f,0.0f,0.0f,	0.0f,	0.0f,	1.0f,// B
			-0.6f,0.8f,0.0f,	0.0f,	0.0f,	1.0f,//	A
			-0.5f,0.0f,0.0f,	0.0f,	0.0f,	1.0f,// C
			//Triangulo2
			-0.5f, 0.0f, 0.0f,	0.0f,	0.0f,	1.0f,// C
			-0.6f,0.8f,0.0f,	0.0f,	0.0f,	1.0f,//	A
			-0.5f,0.8f,0.0f,	0.0f,	0.0f,	1.0f,// D

			//Horizontal Arriba
			//Triangulo1
			-0.7f,0.8f,0.0f,	0.0f,	0.0f,	1.0f,// D
			-0.7f, 0.7f, 0.0f,	0.0f,	0.0f,	1.0f,//	E
			-0.6f,0.7f,0.0f,	0.0f,	0.0f,	1.0f,// I
			//Triangulo2
			-0.7f,0.8f,0.0f,	0.0f,	0.0f,	1.0f,// D
			-0.6f,0.8f,0.0f,	0.0f,	0.0f,	1.0f,//H
			-0.6f,0.7f,0.0f,	0.0f,	0.0f,	1.0f,// I

			//Horizontal Medio
			//Triangulo1
			-0.7f,0.4f,0.0f,	0.0f,	0.0f,	1.0f,// L
			-0.7f,0.3f,0.0f,	0.0f,	0.0f,	1.0f,//	N
			-0.6f,0.3f,0.0f,	0.0f,	0.0f,	1.0f,// O
			//Triangulo2
			-0.7f,0.4f,0.0f,	0.0f,	0.0f,	1.0f,// L
			-0.6f,0.4f,0.0f,	0.0f,	0.0f,	1.0f,//	M
			-0.6f,0.3f,0.0f,	0.0f,	0.0f,	1.0f,// O

			//**************LETRA N -- 108

			//Lado IZQ N
			//Triangulo1
			-0.3f,0.8f,0.0f,	0.0f,	1.0f,	0.0f,// P
			-0.3f,0.0f,0.0f,	0.0f,	1.0f,	0.0f,//	F
			-0.2f,0.0f,0.0f,	0.0f,	1.0f,	0.0f,// R
			//Triangulo2
			-0.3f,0.8f,0.0f,	0.0f,	1.0f,	0.0f,// P
			-0.2f,0.8f,0.0f,	0.0f,	1.0f,	0.0f,//	Q
			-0.2f,0.0f,0.0f,	0.0f,	1.0f,	0.0f,// R

			//Lado DER N
			//Triangulo1
			-0.1f,0.8f,0.0f,	0.0f,	1.0f,	0.0f,// T
			-0.1f,0.0f,0.0f,	0.0f,	1.0f,	0.0f,//	S
			0.0f,0.0f,0.0f,		0.0f,	1.0f,	0.0f,// V
			//Triangulo2
			-0.1f, 0.8f, 0.0f,	0.0f,	1.0f,	0.0f,// T
			0.0f,0.8f,0.0f,		0.0f,	1.0f,	0.0f,//	U
			0.0f,0.0f,0.0f,		0.0f,	1.0f,	0.0f,// V

			//Diagonal
			//Triangulo1
			-0.3f,0.8f,0.0f,	0.0f,	1.0f,	0.0f,//	P
			-0.1f,0.0f,0.0f,	0.0f,	1.0f,	0.0f,//	S
			-0.2f,0.8f,0.0f,	0.0f,	1.0f,	0.0f,//	Q

			//Diagonal
			//Triangulo2
			-0.2f,0.8f,0.0f,	0.0f,	1.0f,	0.0f,//	Q
			-0.1f,0.0f,0.0f,	0.0f,	1.0f,	0.0f,//	S
			0.0f,0.0f,0.0f,		0.0f,	1.0f,	0.0f,// V


			//**************LETRA M -- 144
			//Triangulo1
			0.2f,0.8f,0.0f,		1.0f,	0.0f,	0.0f,// Z
			0.2f,0.0f,0.0f,		1.0f,	0.0f,	0.0f,//	W
			0.3f,0.8f,0.0f,		1.0f,	0.0f,	0.0f,// A1
			//Triangulo2
			0.2f,0.0f,0.0f,		1.0f,	0.0f,	0.0f,//	W
			0.3f,0.0f,0.0f,		1.0f,	0.0f,	0.0f,// B1
			0.3f,0.8f,0.0f,		1.0f,	0.0f,	0.0f,// A1

			//Lado DER M
			//Triangulo1
			0.6f,0.8f,0.0f,		1.0f,	0.0f,	0.0f,// C1
			0.6f,0.0f,0.0f,		1.0f,	0.0f,	0.0f,//	E1
			0.7f,0.0f,0.0f,		1.0f,	0.0f,	0.0f,// F1
			//Triangulo2
			0.6f,0.8f,0.0f,		1.0f,	0.0f,	0.0f,// C1
			0.7f,0.8f,0.0f,		1.0f,	0.0f,	0.0f,//	D1
			0.7f,0.0f,0.0f,		1.0f,	0.0f,	0.0f,// F1

			//Diagonal IZQ
			//Triangulo1
			0.3f,0.8f,0.0f,		1.0f,	0.0f,	0.0f,//	A1
			0.4f,0.2f,0.0f,		1.0f,	0.0f,	0.0f,//	G1
			0.5f,0.2f,0.0f,		1.0f,	0.0f,	0.0f,// H1

			//Triangulo1
			0.2f, 0.8f, 0.0f, 1.0f, 0.0f, 0.0f,// Z
			0.3f, 0.8f, 0.0f, 1.0f, 0.0f, 0.0f,//	A1
			0.4f, 0.2f, 0.0f, 1.0f, 0.0f, 0.0f,//	G1

			//Diagonal DER
			//Triangulo1
			0.6f,0.8f,0.0f,		1.0f,	0.0f,	0.0f,//	C1
			0.4f,0.2f,0.0f,		1.0f,	0.0f,	0.0f,//	G1
			0.5f, 0.2f, 0.0f,	1.0f,	0.0f,	0.0f,// H1	

			//Triangulo2
			0.6f, 0.8f, 0.0f, 1.0f, 0.0f, 0.0f,//	C1
			0.7f,0.8f,0.0f,		1.0f,	0.0f,	0.0f,//	D1
			0.5f, 0.2f, 0.0f, 1.0f, 0.0f, 0.0f,// H1	


			
	};
	MeshColor * letras = new MeshColor();
	letras->CreateMeshColor(vertices_letras,396);
	meshColorList.push_back(letras);

	

	GLfloat vertices_triangulorojo[] = {
		//X			Y			Z			R		G		B
		-1.0f,	-1.0f,		0.5f,			1.0f,	0.0f,	0.0f,
		1.0f,	-1.0f,		0.5f,			1.0f,	0.0f,	0.0f,
		0.0f,	1.0f,		0.5f,			1.0f,	0.0f,	0.0f,
		
	};

	MeshColor* triangulorojo = new MeshColor();
	triangulorojo->CreateMeshColor(vertices_triangulorojo, 18);
	meshColorList.push_back(triangulorojo);


	//	Generacion Triangulo Verde
	GLfloat vertices_trianguloverde[] = {
		//X			Y			Z			R		G		B
		-1.0f,	-1.0f,		0.5f,			0.0f,	0.5f,	0.0f,
		1.0f,	-1.0f,		0.5f,			0.0f,	0.5f,	0.0f,
		0.0f,	1.0f,		0.5f,			0.0f,	0.5f,	0.0f,

	};

	MeshColor* trianguloverde = new MeshColor();
	trianguloverde->CreateMeshColor(vertices_trianguloverde, 18);
	meshColorList.push_back(trianguloverde);

	//	Generacion Triangulo Azul
	GLfloat vertices_trianguloazul[] = {
		//X			Y			Z			R		G		B
		-1.0f,	-1.0f,		0.5f,			0.0f,	0.0f,	1.0f,
		1.0f,	-1.0f,		0.5f,			0.0f,	0.0f,	1.0f,
		0.0f,	1.0f,		0.5f,			0.0f,	0.0f,	1.0f,

	};

	MeshColor* trianguloazul = new MeshColor();
	trianguloazul->CreateMeshColor(vertices_trianguloazul, 18);
	meshColorList.push_back(trianguloazul);

	

	GLfloat vertices_cuadradoverde[] = {
		//X			Y			Z			R		G		B
		-0.5f,	-0.5f,		0.5f,			0.0f,	1.0f,	0.0f,
		0.5f,	-0.5f,		0.5f,			0.0f,	1.0f,	0.0f,
		0.5f,	0.5f,		0.5f,			0.0f,	1.0f,	0.0f,
		-0.5f,	-0.5f,		0.5f,			0.0f,	1.0f,	0.0f,
		0.5f,	0.5f,		0.5f,			0.0f,	1.0f,	0.0f,
		-0.5f,	0.5f,		0.5f,			0.0f,	1.0f,	0.0f,

	};

	MeshColor* cuadradoverde = new MeshColor();
	cuadradoverde->CreateMeshColor(vertices_cuadradoverde, 36);
	meshColorList.push_back(cuadradoverde);


}


void CreateShaders()
{

	Shader *shader1 = new Shader(); //shader para usar índices: objetos: cubo y  pirámide
	shader1->CreateFromFiles(vShader, fShader);
	shaderList.push_back(*shader1);

	Shader *shader2 = new Shader();//shader para usar color como parte del VAO: letras 
	shader2->CreateFromFiles(vShaderColor, fShaderColor);
	shaderList.push_back(*shader2);

	//Shader Rojo
	Shader* shader3 = new Shader(); 
	shader3->CreateFromFiles(vShaderR, fShaderR);
	shaderList.push_back(*shader3);

	//Shader Verde
	Shader* shader4 = new Shader();
	shader4->CreateFromFiles(vShaderV, fShaderV);
	shaderList.push_back(*shader4);

	//Shader Azul
	Shader* shader5 = new Shader();
	shader5->CreateFromFiles(vShaderA, fShaderA);
	shaderList.push_back(*shader5);

	//Shader Cafe
	Shader* shader6 = new Shader(); 
	shader6->CreateFromFiles(vShaderC, fShaderC);
	shaderList.push_back(*shader6);

	//Shader Verde Oscuro
	Shader* shader7 = new Shader(); 
	shader7->CreateFromFiles(vShaderVo, fShaderVo);
	shaderList.push_back(*shader7);
}


int main()
{
	mainWindow = Window(800, 600);
	mainWindow.Initialise();
	//	El orden importa por la lista
	CreaPiramide(); //índice 0 en MeshList
	CrearCubo();//índice 1 en MeshList
	CrearLetrasyFiguras(); //usa MeshColor, índices en MeshColorList
	CreateShaders();
	GLuint uniformProjection = 0;
	GLuint uniformModel = 0;
	//Projection: Matriz de Dimensión 4x4 para indicar si vemos en 2D( orthogonal) o en 3D) perspectiva
	//glm::mat4 projection = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, 0.1f, 100.0f);
	glm::mat4 projection = glm::perspective(glm::radians(60.0f)	,mainWindow.getBufferWidth() / mainWindow.getBufferHeight(), 0.1f, 100.0f);
	
	//Model: Matriz de Dimensión 4x4 en la cual se almacena la multiplicación de las transformaciones geométricas.
	glm::mat4 model(1.0); //fuera del while se usa para inicializar la matriz con una identidad
	
	//Loop mientras no se cierra la ventana
	while (!mainWindow.getShouldClose())
	{
		//Recibir eventos del usuario
		glfwPollEvents();
		//Limpiar la ventana
		glClearColor(1.0f,1.0f,1.0f,0.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Se agrega limpiar el buffer de profundidad
		
		//*********************************EJERCICIO 1*****************************************						
		////Para las letras hay que usar el segundo set de shaders con índice 1 en ShaderList 
		//shaderList[1].useShader();	
		//uniformModel = shaderList[1].getModelLocation();	
		//uniformProjection = shaderList[1].getProjectLocation();	
		//glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		//
		////Letras
		//model = glm::mat4(1.0);
		//model = glm::translate(model, glm::vec3(0.1f, -0.2f, -2.0f));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA y se envían al shader como variables de tipo uniform
		//meshColorList[0]->RenderMeshColor();
		//*********************************EJERCICIO 1*****************************************		
		
		//*********************************EJERCICIO 2*****************************************	
		// 0 Piramide  1 Cubo
		//R , V , A , C , Vo
		//2 , 3 , 4 , 5 , 6 

		////PIRAMIDE VERDE OSCURO IZQUIERDA
		shaderList[6].useShader();
		uniformModel = shaderList[6].getModelLocation();
		uniformProjection = shaderList[6].getProjectLocation();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-1.095f, -0.55f, -1.90f));
		model = glm::scale(model, glm::vec3(0.5f, 0.7f, 0.05f));

		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA y se envían al shader como variables de tipo uniform
		meshList[0]->RenderMesh();


		////PIRAMIDE VERDE OSCURO DERECHA
		shaderList[6].useShader();
		uniformModel = shaderList[6].getModelLocation();
		uniformProjection = shaderList[6].getProjectLocation();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(1.095f, -0.55f, -1.90f));
		model = glm::scale(model, glm::vec3(0.5f, 0.7f, 0.05f));

		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA y se envían al shader como variables de tipo uniform
		meshList[0]->RenderMesh();


		//PIRAMIDE AZUL
		shaderList[4].useShader();
		uniformModel = shaderList[4].getModelLocation();
		uniformProjection = shaderList[4].getProjectLocation();
		
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 0.7f, -1.90f));
		model = glm::scale(model, glm::vec3(1.95f, 0.8f, 0.05f));
		
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA y se envían al shader como variables de tipo uniform
		meshList[0]->RenderMesh();

		//CUBO ROJO
		shaderList[2].useShader();
		uniformModel = shaderList[2].getModelLocation();
		uniformProjection = shaderList[2].getProjectLocation();
		
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -0.4f, -2.5f));
		model = glm::scale(model, glm::vec3(1.55f, 1.5f, 1.0f));
		
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA y se envían al shader como variables de tipo uniform
		meshList[1]->RenderMesh();

		//CUBO VERDE IZQUIERDO
		shaderList[3].useShader();
		uniformModel = shaderList[3].getModelLocation();
		uniformProjection = shaderList[3].getProjectLocation();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-0.35f, 0.0f, -2.0f));
		model = glm::scale(model, glm::vec3(0.45f, 0.45f, 0.05f));
		
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA y se envían al shader como variables de tipo uniform
		meshList[1]->RenderMesh();

		////CUBO VERDE DERECHO
		shaderList[3].useShader();
		uniformModel = shaderList[3].getModelLocation();
		uniformProjection = shaderList[3].getProjectLocation();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.35f, 0.0f, -2.0f));
		model = glm::scale(model, glm::vec3(0.45f, 0.45f, 0.05f));

		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA y se envían al shader como variables de tipo uniform
		meshList[1]->RenderMesh();

		////CUBO VERDE ABAJO
		shaderList[3].useShader();
		uniformModel = shaderList[3].getModelLocation();
		uniformProjection = shaderList[3].getProjectLocation();
		
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -0.95f, -2.0f));
		//model = glm::rotate(model, 41 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.45f, 0.45f, 0.05f));

		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA y se envían al shader como variables de tipo uniform
		meshList[1]->RenderMesh();

		//CUBO CAFE IZQUIERDA
		shaderList[5].useShader();
		uniformModel = shaderList[5].getModelLocation();
		uniformProjection = shaderList[5].getProjectLocation();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-1.15f, -1.05f, -2.0f));
		//model = glm::rotate(model, 41 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.25f, 0.25f, 0.05f));

		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA y se envían al shader como variables de tipo uniform
		meshList[1]->RenderMesh();

		////CUBO CAFE DERECHA
		shaderList[5].useShader();
		uniformModel = shaderList[5].getModelLocation();
		uniformProjection = shaderList[5].getProjectLocation();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(1.15f, -1.05f, -2.0f));
		//model = glm::rotate(model, 41 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.25f, 0.25f, 0.05f));

		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA y se envían al shader como variables de tipo uniform
		meshList[1]->RenderMesh();

		
		glUseProgram(0);
		mainWindow.swapBuffers();

	}
	return 0;
}
// inicializar matriz: glm::mat4 model(1.0);
// reestablecer matriz: model = glm::mat4(1.0);
//Traslación
//model = glm::translate(model, glm::vec3(0.0f, 0.0f, -5.0f));
//////////////// ROTACIÓN //////////////////
//model = glm::rotate(model, 45 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
////////////////  ESCALA ////////////////
//model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
///////////////////// T+R////////////////
/*model = glm::translate(model, glm::vec3(valor, 0.0f, 0.0f));
model = glm::rotate(model, 45 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
model = glm::rotate(model, glm::radians(angulo), glm::vec3(0.0f, 1.0f, 0.0f));
*/
/////////////R+T//////////
/*model = glm::rotate(model, 45 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
model = glm::translate(model, glm::vec3(valor, 0.0f, 0.0f));
*/