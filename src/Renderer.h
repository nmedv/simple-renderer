#ifndef RENDERER_H
#define RENDERER_H

#include "Screen.h"
#include "Vec.h"
#include "Mesh.h"

#include <functional>


class Renderer
{
	using vertex_proc = std::function<Vec4f(const Vec3f& vec)>;

	enum draw_mode { POINTS, LINES, TRIANGLES, QUADS };

public:

	Renderer() {}
	
	void setScreen(Screen* screen)
	{
		if (screen)
			_screen = screen;
		else
			_screen = nullptr;
	}

	inline void setVertexProc(vertex_proc proc) { _vertexProc = proc; }

	void drawPoint(float x, float y, const Color& color);

	inline void drawPoint(const Vec3f& v, const Color& color)
	{
		drawPoint(v.x, v.y, color);
	}

	void drawLine(float x0, float y0, float x1, float y1, const Color& color);

	inline void drawLine(const Vec3f& v0, const Vec3f& v1, const Color& color)
	{
		drawLine(v0.x, v0.y, v1.x, v1.y, color);
	}

	void drawMesh(const Mesh& mesh, const Color& color);

private:
	void pipeline(const std::vector<Vec3f>& in);

	Screen* _screen;
	std::vector<Vec3f> _storage;
	vertex_proc _vertexProc;
};


#endif