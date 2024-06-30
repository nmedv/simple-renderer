// #define DEBUG

#include "Screen.h"
#include "Matrix.h"
#include "Renderer.h"
#include "Mesh.h"
#include "Timer.h"

#include <iostream>


int printError()
{
	int code = Error::code();

	if (code)
	{
		std::cerr << "error: " << Error::msg() << "\n";
		return code;
	}
	
	return 1;
}


constexpr float PI = 3.1415927f;

float rad(float deg)
{
	return deg * (PI / 180.0f);
}


int main(int argc, char* argv[])
{
	const char* title = "simple-renderer";
	Screen screen = Screen(800, 600, title);
	Renderer renderer;
	renderer.setScreen(&screen);

	Mesh cube ("content/Cube.obj");
	if (!cube.isLoaded())
		return printError();
	
	Matrixf perspective = Matrixf::perspective(0.1f, 1000.0f, rad(85.0f), screen.getAspectRatio());
	Matrixf transform = Matrixf::identity();
	renderer.setVertexProc([&perspective, &transform](const Vec3f& in) {
		return perspective * transform * Vec4f(in.x, in.y, in.z, 1.0f);
	});
	
	int64_t fps;
	int64_t oldtime = 0;
	int64_t newtime;
	int64_t deltatime;
	char perf_title[128] = {"\0"};
	
	Color clearColor;
	Color geomColor = Color(0xFF, 0xFF, 0xFF, 0xFF);
	float deg = 0.0f;

	while (!screen.shouldClose())
	{
		screen.pollEvents();
		screen.clear(clearColor);
		
		deg += 0.002f;
		transform = Matrixf::translate(Vec3f(0, 0, 2.0f)) *
			Matrixf::rotate(deg, Y_AXIS) * Matrixf::rotate(deg, X_AXIS);
		renderer.drawMesh(cube, geomColor);

		screen.flush();

		newtime = Timer::getMicroseconds();
		deltatime = newtime - oldtime;
		if (deltatime)
		{
			fps = 1000000 / deltatime;
			snprintf(perf_title, 128, "%s   FPS: %4lli   ms: %lli   time: %lli", title, fps, deltatime, newtime);
		}
		else
		{
			fps = -1;
			snprintf(perf_title, 128, "%s   FPS: NaN   ms: %lli   time: %lli", title, deltatime, newtime);
		}
		
		screen.setWindowTitle(perf_title);
		oldtime = newtime;

		// break;
	}

	return 0;
}