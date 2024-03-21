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
	////////*********************************************------- EJERCICIO 1 -------*********************************************
	chasis = 0.0f;
	cofre = 0.0f;
	llantaDIz = 0.0f;
	llantaDDe = 0.0f;
	llantaTIz = 0.0f;
	llantaTDe = 0.0f;
	
	////////*********************************************------- EJERCICIO 1 -------*********************************************

	for (size_t i = 0; i < 1024; i++)
	{
		keys[i] = 0;
	}
}
int Window::Initialise()
{
	//Inicialización de GLFW
	if (!glfwInit())
	{
		printf("Falló inicializar GLFW");
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
	mainWindow = glfwCreateWindow(width, height, "Practica 05: Optimización y Carga de Modelos", NULL, NULL);

	if (!mainWindow)
	{
		printf("Fallo en crearse la ventana con GLFW");
		glfwTerminate();
		return 1;
	}
	//Obtener tamaño de Buffer
	glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);

	//asignar el contexto
	glfwMakeContextCurrent(mainWindow);

	//MANEJAR TECLADO y MOUSE
	createCallbacks();


	//permitir nuevas extensiones
	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK)
	{
		printf("Falló inicialización de GLEW");
		glfwDestroyWindow(mainWindow);
		glfwTerminate();
		return 1;
	}

	glEnable(GL_DEPTH_TEST); //HABILITAR BUFFER DE PROFUNDIDAD
							 // Asignar valores de la ventana y coordenadas
							 
							 //Asignar Viewport
	glViewport(0, 0, bufferWidth, bufferHeight);
	//Callback para detectar que se está usando la ventana
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

	////*********************************************------- EJERCICIO 1 -------*********************************************
	static bool zPresionado = false; // Para cambiar la direccion de las llantas

	if (key == GLFW_KEY_Z && action == GLFW_PRESS )
	{
		// Cambiar el estado cada vez que se presiona 'Z'
		zPresionado = !zPresionado;
	}

	//Llantas Izquierdas
	if (key == GLFW_KEY_V && zPresionado == true)
	{
		theWindow->llantaTIz += 5.0;
	}
	else if (key == GLFW_KEY_V)
	{

		theWindow->llantaTIz -= 5.0;
	}

	if (key == GLFW_KEY_B && zPresionado== true)
	{
		theWindow->llantaDIz += 5.0;
	}
	else if (key == GLFW_KEY_B)
	{

		theWindow->llantaDIz -= 5.0;
	}

	//Llantas Derechas
	if (key == GLFW_KEY_N && zPresionado == true)
	{
		theWindow->llantaTDe += 5.0;
	}
	else if (key == GLFW_KEY_N)
	{

		theWindow->llantaTDe -= 5.0;
	}

	if (key == GLFW_KEY_M && zPresionado == true)
	{
		theWindow->llantaDDe += 5.0;
	}
	else if (key == GLFW_KEY_M)
	{

		theWindow->llantaDDe -= 5.0;
	}

	if (key == GLFW_KEY_H)
	{
		static bool aumentando = true;
		if (aumentando) {
			// Si está aumentando y no ha alcanzado el límite superior, aumenta
			if (theWindow->cofre < 0.0) {
				theWindow->cofre += 5.0;
			}
			else {
				// Si alcanza el límite superior, cambia la dirección
				aumentando = false;
			}
		}
		else {
			// Si está disminuyendo y no ha alcanzado el límite inferior, disminuye
			if (theWindow->cofre > -35.0) {
				theWindow->cofre -= 5.0;
			}
			else {
				// Si alcanza el límite inferior, cambia la dirección
				aumentando = true;
			}
		}
	}
	
	if (key == GLFW_KEY_LEFT)
	{
		theWindow->chasis -= 0.1;
		theWindow->llantaTIz += 10.0;
		theWindow->llantaTDe += 10.0;
		theWindow->llantaDIz += 10.0;
		theWindow->llantaDDe += 10.0;
	}

	if (key == GLFW_KEY_RIGHT)
	{
		theWindow->chasis += 0.1;
		theWindow->llantaTIz -= 10.0;
		theWindow->llantaTDe -= 10.0;
		theWindow->llantaDIz -= 10.0;
		theWindow->llantaDDe -= 10.0;
	}
	
	////*********************************************------- EJERCICIO 1 -------*********************************************

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
