#ifdef _MSC_VER
//#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#endif

#define LITE_GFX_IMPLEMENTATION

#include <litegfx.h>
#include <glfw3.h>
#include <Vec2.h>
using namespace std;

int main() {
	// Inicializamos GLFW
	if (!glfwInit()) {
		cout << "Error: No se ha podido inicializar GLFW" << endl;
		return -1;
	}
	atexit(glfwTerminate);

	// Creamos la ventana
	glfwWindowHint(GLFW_RESIZABLE, true);
	GLFWwindow* window = glfwCreateWindow(800, 600, "Programacion 2D", nullptr, nullptr);
	if (!window) {
		cout << "Error: No se ha podido crear la ventana" << endl;
		return -1;
	}

	// Activamos contexto de OpenGL
	glfwMakeContextCurrent(window);

	// Inicializamos LiteGFX
	lgfx_setup2d(800, 600);

	// Bucle principal
	float x = 0;
	double xposSquare = 0;
	double yposSquare = 0;

	double xposCircle = 0;
	double yposCircle = 0;
	float circleDistance = 50;
	float angleCircle = 0;

	double screenCenterX = 0;
	double screenCenterY = 0;

	double lastTime = glfwGetTime();
	while (!glfwWindowShouldClose(window) && !glfwGetKey(window, GLFW_KEY_ESCAPE)) {
		// Actualizamos delta
		float deltaTime = static_cast<float>(glfwGetTime() - lastTime);
		lastTime = glfwGetTime();

		// Actualizamos tamaño de ventana
		int screenWidth, screenHeight;
		glfwGetWindowSize(window, &screenWidth, &screenHeight);
		lgfx_setviewport(0, 0, screenWidth, screenHeight);
		
		screenCenterX = screenWidth / 2;
		screenCenterY = screenHeight / 2;

		// Actualizacion de logica del programa
		glfwGetCursorPos(window, &xposSquare, &yposSquare);
		float auxY = sin(angleCircle*PI / 180) * circleDistance;
		float auxX = cos(angleCircle*PI / 180) * circleDistance;

		yposCircle = yposSquare - auxY;
		
		xposCircle = xposSquare + auxX;

		Vec2 *centerPos = new Vec2(screenCenterX, screenCenterY);
		Vec2 *squarePos = new Vec2(xposSquare, yposSquare);
		Vec2 *circlePos = new Vec2(xposCircle, yposCircle);
		
		float angleFunc = squarePos->angle(*circlePos);
		float distance = centerPos->distance(*squarePos);

		cout << "Angle Circle: " << angleCircle << " X: " << auxX << " Y: " << auxY << " Angle func: "<< angleFunc<< "Dist: "<<distance<<endl;

		if (angleCircle < 360)
			angleCircle += 32 * deltaTime;
		else
			angleCircle = 0;

		// Pintado
		lgfx_clearcolorbuffer(0, 0, 0);
		lgfx_setcolor(1, 0, 0, 1);
		lgfx_drawrect(centerPos->x -25, centerPos->y - 25, 50, 50);

		lgfx_setcolor(1, 1, 1, 1);
		lgfx_drawrect(squarePos->x - 25, squarePos->y - 25, 50, 50);

		lgfx_setcolor(1, 1, 0, 1);
		lgfx_drawoval(circlePos->x - 10, circlePos->y - 10, 20, 20);

		std::string title = "Distancia: "
			+ std::to_string(distance)
			+ " -- Angulo: "
			+ std::to_string(angleFunc);

		glfwSetWindowTitle(window, title.c_str());



		// Actualizamos ventana y eventos
		glfwSwapBuffers(window);
		glfwPollEvents();
		delete(squarePos);
		delete(circlePos);
		delete(centerPos);
	}

    return 0;
}
