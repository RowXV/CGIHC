#include "Window.h"

Window::Window()
{
	width = 800;
	height = 600;
	for (size_t i = 0; i < 1024; i++)
	{
		keys[i] = 0;
	}
}
Window::Window(GLint windowWidth, GLint windowHeight)
{
	width = windowWidth;
	height = windowHeight;
	rotax = 0.0f;
	rotay = 0.0f;
	rotaz = 0.0f;
	////////*********************************************------- EJERCICIO 1 GRUA -------*********************************************
	//articulacion1 = 0.0f;
	//articulacion2 = -20.0f;
	//articulacion3 = 170.0f;
	//articulacion4 = 30.0f;
	//articulacion5 = 0.0f;
	//articulacion6 = 0.0f;
	//articulacion7 = 0.0f;
	//articulacion8 = 0.0f;
	//articulacion9 = 0.0f;
	//articulacion10 = 0.0f;
	//articulacion11 = 0.0f;
	////////*********************************************------- EJERCICIO 1 GRUA -------*********************************************

	//////*********************************************------- EJERCICIO 2 PERRO -------*********************************************
	articulacion1 = 20.0f;
	articulacion2 = 20.0f;
	articulacion3 = 20.0f;
	articulacion4 = 20.0f;
	articulacion5 = -40.0f;
	articulacion6 = -40.0f;
	articulacion7 = -40.0f;
	articulacion8 = -40.0f;
	articulacion9 = 0.0f;
	articulacion10 = 0.0f;
	articulacion11 = 35.0f;
	//////*********************************************------- EJERCICIO 2 PERRO -------*********************************************

	for (size_t i = 0; i < 1024; i++)
	{
		keys[i] = 0;
	}
}
int Window::Initialise()
{
	//Inicializaci�n de GLFW
	if (!glfwInit())
	{
		printf("Fall� inicializar GLFW");
		glfwTerminate();
		return 1;
	}
	//Asignando variables de GLFW y propiedades de ventana
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//para solo usar el core profile de OpenGL y no tener retrocompatibilidad
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	//CREAR VENTANA
	mainWindow = glfwCreateWindow(width, height, "Ejercicio 04: Modelado Jer�rquico", NULL, NULL);

	if (!mainWindow)
	{
		printf("Fallo en crearse la ventana con GLFW");
		glfwTerminate();
		return 1;
	}
	//Obtener tama�o de Buffer
	glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);

	//asignar el contexto
	glfwMakeContextCurrent(mainWindow);

	//MANEJAR TECLADO y MOUSE
	createCallbacks();


	//permitir nuevas extensiones
	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK)
	{
		printf("Fall� inicializaci�n de GLEW");
		glfwDestroyWindow(mainWindow);
		glfwTerminate();
		return 1;
	}

	glEnable(GL_DEPTH_TEST); //HABILITAR BUFFER DE PROFUNDIDAD
							 // Asignar valores de la ventana y coordenadas
							 
							 //Asignar Viewport
	glViewport(0, 0, bufferWidth, bufferHeight);
	//Callback para detectar que se est� usando la ventana
	glfwSetWindowUserPointer(mainWindow, this);
}

void Window::createCallbacks()
{
	glfwSetKeyCallback(mainWindow, ManejaTeclado);
	glfwSetCursorPosCallback(mainWindow, ManejaMouse);
}

GLfloat Window::getXChange()
{
	GLfloat theChange = xChange;
	xChange = 0.0f;
	return theChange;
}

GLfloat Window::getYChange()
{
	GLfloat theChange = yChange;
	yChange = 0.0f;
	return theChange;
}

void avanzaPata(GLfloat* y, int index)
{
	//Variable de direcci�n para controlar si aumenta o disminuye
	static bool aumentando = true;

	if (index == 0) 
	{
		if (aumentando) {
			// Si est� aumentando y no ha alcanzado el l�mite superior, aumenta
			if (*y < 20.0) {
				*y += 5.0;
			}
			else {
				// Si alcanza el l�mite superior, cambia la direcci�n
				aumentando = false;
			}
		}
		else {
			// Si est� disminuyendo y no ha alcanzado el l�mite inferior, disminuye
			if (*y > -25.0) {
				*y -= 5.0;
			}
			else {
				// Si alcanza el l�mite inferior, cambia la direcci�n
				aumentando = true;
			}
		}
	}
	else if (index == 1)
	{
		if (aumentando) {
			// Si est� aumentando y no ha alcanzado el l�mite superior, aumenta
			if (*y < -40.0) {
				*y += 5.0;
			}
			else {
				// Si alcanza el l�mite superior, cambia la direcci�n
				aumentando = false;
			}
		}
		else {
			// Si est� disminuyendo y no ha alcanzado el l�mite inferior, disminuye
			if (*y > -85.0) {
				*y -= 5.0;
			}
			else {
				// Si alcanza el l�mite inferior, cambia la direcci�n
				aumentando = true;
			}
		}
	}
}

void Window::ManejaTeclado(GLFWwindow* window, int key, int code, int action, int mode)
{
	Window* theWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));

	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}

	
	if (key == GLFW_KEY_E)
	{
		theWindow->rotax += 10.0;
	}
	if (key == GLFW_KEY_R)
	{
		theWindow->rotay += 10.0; //rotar sobre el eje y 10 grados
	}
	if (key == GLFW_KEY_T)
	{
		theWindow->rotaz += 10.0;
	}

	//////*********************************************------- EJERCICIO 1 GRUA -------*********************************************
	//if (key == GLFW_KEY_F)
	//{

	//	// Variable de direcci�n para controlar si aumenta o disminuye
	//	static bool aumentando = true;

	//	if (aumentando) {
	//		// Si est� aumentando y no ha alcanzado el l�mite superior, aumenta
	//		if (theWindow->articulacion1 < 20.0) {
	//			theWindow->articulacion1 += 5.0;
	//		}
	//		else {
	//			// Si alcanza el l�mite superior, cambia la direcci�n
	//			aumentando = false;
	//		}
	//	}
	//	else {
	//		// Si est� disminuyendo y no ha alcanzado el l�mite inferior, disminuye
	//		if (theWindow->articulacion1 > -40.0) {
	//			theWindow->articulacion1 -= 5.0;
	//		}
	//		else {
	//			// Si alcanza el l�mite inferior, cambia la direcci�n
	//			aumentando = true;
	//		}
	//	}
	//	
	//}

	//if (key == GLFW_KEY_G)
	//{
	//	// Variable de direcci�n para controlar si aumenta o disminuye
	//	static bool aumentando = true;

	//	if (aumentando) {
	//		// Si est� aumentando y no ha alcanzado el l�mite superior, aumenta
	//		if (theWindow->articulacion2 < 80.0) {
	//			theWindow->articulacion2 += 5.0;
	//		}
	//		else {
	//			// Si alcanza el l�mite superior, cambia la direcci�n
	//			aumentando = false;
	//		}
	//	}
	//	else {
	//		// Si est� disminuyendo y no ha alcanzado el l�mite inferior, disminuye
	//		if (theWindow->articulacion2 > -30.0) {
	//			theWindow->articulacion2 -= 5.0;
	//		}
	//		else {
	//			// Si alcanza el l�mite inferior, cambia la direcci�n
	//			aumentando = true;
	//		}
	//	}
	//}
	//if (key == GLFW_KEY_H)
	//{
	//	// Variable de direcci�n para controlar si aumenta o disminuye
	//	static bool aumentando = true;

	//	if (aumentando) {
	//		// Si est� aumentando y no ha alcanzado el l�mite superior, aumenta
	//		if (theWindow->articulacion3 < 160.0) {
	//			theWindow->articulacion3 += 5.0;
	//		}
	//		else {
	//			// Si alcanza el l�mite superior, cambia la direcci�n
	//			aumentando = false;
	//		}
	//	}
	//	else {
	//		// Si est� disminuyendo y no ha alcanzado el l�mite inferior, disminuye
	//		if (theWindow->articulacion3 > 80.0) {
	//			theWindow->articulacion3 -= 5.0;
	//		}
	//		else {
	//			// Si alcanza el l�mite inferior, cambia la direcci�n
	//			aumentando = true;
	//		}
	//	}
	//}
	//if (key == GLFW_KEY_J)
	//{
	//	// Variable de direcci�n para controlar si aumenta o disminuye
	//	static bool aumentando = true;

	//	if (aumentando) {
	//		// Si est� aumentando y no ha alcanzado el l�mite superior, aumenta
	//		if (theWindow->articulacion4 < 60.0) {
	//			theWindow->articulacion4 += 5.0;
	//		}
	//		else {
	//			// Si alcanza el l�mite superior, cambia la direcci�n
	//			aumentando = false;
	//		}
	//	}
	//	else {
	//		// Si est� disminuyendo y no ha alcanzado el l�mite inferior, disminuye
	//		if (theWindow->articulacion4 > 20.0) {
	//			theWindow->articulacion4 -= 5.0;
	//		}
	//		else {
	//			// Si alcanza el l�mite inferior, cambia la direcci�n
	//			aumentando = true;
	//		}
	//	}
	//}
	//if (key == GLFW_KEY_1)
	//{
	//	theWindow->articulacion5 += 10.0;
	//}
	//if (key == GLFW_KEY_2)
	//{
	//	theWindow->articulacion6 += 10.0;
	//}
	//if (key == GLFW_KEY_3)
	//{
	//	theWindow->articulacion7 += 10.0;
	//}
	//if (key == GLFW_KEY_4)
	//{
	//	theWindow->articulacion8 += 10.0;
	//}
	//////*********************************************------- EJERCICIO 1 GRUA -------*********************************************

	////*********************************************------- EJERCICIO 2 PERRO -------*********************************************
	if (key == GLFW_KEY_F)
	{
		avanzaPata(&theWindow->articulacion1,0);
	}
	if (key == GLFW_KEY_G)
	{
		avanzaPata(&theWindow->articulacion2,0);
	}
	if (key == GLFW_KEY_H)
	{
		avanzaPata(&theWindow->articulacion3,0);
	}
	if (key == GLFW_KEY_J)
	{
		avanzaPata(&theWindow->articulacion4,0);
	}
	if (key == GLFW_KEY_V)
	{
		avanzaPata(&theWindow->articulacion5, 1);
	}
	if (key == GLFW_KEY_B)
	{
		avanzaPata(&theWindow->articulacion6, 1);
	}
	if (key == GLFW_KEY_N)
	{
		avanzaPata(&theWindow->articulacion7, 1);
	}
	if (key == GLFW_KEY_M)
	{
		avanzaPata(&theWindow->articulacion8, 1);
	}
	if (key == GLFW_KEY_1)
	{
		static bool aumentando = true;

		if (aumentando) {
			// Si est� aumentando y no ha alcanzado el l�mite superior, aumenta
			if (theWindow->articulacion9 < 0.0) {
				theWindow->articulacion9 += 5.0;
			}
			else {
				// Si alcanza el l�mite superior, cambia la direcci�n
				aumentando = false;
			}
		}
		else {
			// Si est� disminuyendo y no ha alcanzado el l�mite inferior, disminuye
			if (theWindow->articulacion9 > -35.0) {
				theWindow->articulacion9 -= 5.0;
			}
			else {
				// Si alcanza el l�mite inferior, cambia la direcci�n
				aumentando = true;
			}
		}
	}
	if (key == GLFW_KEY_2)
	{
		static bool aumentando = false;

		if (aumentando) {
			// Si es mayor a 0, lo disminuye
			if (theWindow->articulacion10 > 0.0) {
				theWindow->articulacion10 -= 5.0;
			}
			else {
				// Si alcanza el l�mite superior, cambia la direcci�n
				aumentando = false;
			}
		}
		else {
			// Si menor a -35, lo aumenta
			if (theWindow->articulacion10 < 35.0) {
				theWindow->articulacion10 += 5.0;
			}
			else {
				// Si alcanza el l�mite inferior, cambia la direcci�n
				aumentando = true;
			}
		}
	}
	if (key == GLFW_KEY_L)
	{
		static bool aumentando = true;
		
		if (aumentando) {
			// Si est� aumentando y no ha alcanzado el l�mite superior, aumenta
			if (theWindow->articulacion11 < 35.0) {
				theWindow->articulacion11 += 5.0;
			}
			else {
				// Si alcanza el l�mite superior, cambia la direcci�n
				aumentando = false;
			}
		}
		else {
			// Si est� disminuyendo y no ha alcanzado el l�mite inferior, disminuye
			if (theWindow->articulacion11 > -35.0) {
				theWindow->articulacion11 -= 5.0;
			}
			else {
				// Si alcanza el l�mite inferior, cambia la direcci�n
				aumentando = true;
			}
		}

	}
	////*********************************************------- EJERCICIO 2 PERRO -------*********************************************

	if (key == GLFW_KEY_D && action == GLFW_PRESS)
	{
		const char* key_name = glfwGetKeyName(GLFW_KEY_D, 0);
		//printf("se presiono la tecla: %s\n",key_name);
	}

	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
		{
			theWindow->keys[key] = true;
			//printf("se presiono la tecla %d'\n", key);
		}
		else if (action == GLFW_RELEASE)
		{
			theWindow->keys[key] = false;
			//printf("se solto la tecla %d'\n", key);
		}
	}
}

void Window::ManejaMouse(GLFWwindow* window, double xPos, double yPos)
{
	Window* theWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));

	if (theWindow->mouseFirstMoved)
	{
		theWindow->lastX = xPos;
		theWindow->lastY = yPos;
		theWindow->mouseFirstMoved = false;
	}

	theWindow->xChange = xPos - theWindow->lastX;
	theWindow->yChange = theWindow->lastY - yPos;

	theWindow->lastX = xPos;
	theWindow->lastY = yPos;
}


Window::~Window()
{
	glfwDestroyWindow(mainWindow);
	glfwTerminate();

}
