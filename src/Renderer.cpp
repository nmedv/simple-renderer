#include "Renderer.h"

#include <cmath>


void Renderer::drawPoint(float x, float y, const Color& color)
{
	_screen->setPixel(
		static_cast<int>( (x + 1.0f) * 0.5f * _screen->getWidth()  ),
		static_cast<int>( (y + 1.0f) * 0.5f * _screen->getHeight() ),
		color
	);
}


void Renderer::drawLine(float x0, float y0, float x1, float y1, const Color& color)
{
	int width = _screen->getWidth();
	int height = _screen->getHeight();
	int x_start = static_cast<int>( (x0 + 1.0f) * 0.5f * width  );
	int x_end   = static_cast<int>( (x1 + 1.0f) * 0.5f * width  );
	int y_start = static_cast<int>( (y0 + 1.0f) * 0.5f * height );
	int y_end   = static_cast<int>( (y1 + 1.0f) * 0.5f * height );
	int temp;

	int dx = x_end - x_start;
	int dy = y_end - y_start;
	int dx_a = abs(dx);
	int dy_a = abs(dy);
	int error, derr;

	if (dx_a >= dy_a)
	{
		if (dx < 0)
		{
			temp = x_end;
			x_end = x_start;
			x_start = temp;
			temp = y_end;
			y_end = y_start;
			y_start = temp;
		}

		error = 0;
		derr = (dy_a + 1);
		int diry = y_end - y_start;
		if (diry > 0) diry =  1;
		if (diry < 0) diry = -1;

		int y = y_start;
		for (int x = x_start; x <= x_end; x++)
		{
			if (x >= 0 && x < width && y >= 0 && y < height)
				_screen->setPixel(x, y, color);
			else
				break;

			error += derr;
			if (error > dx_a + 1)
			{
				y += diry;
				error -= dx_a + 1;
			}
		}
	}
	else
	{
		if (dy < 0)
		{
			temp = x_end;
			x_end = x_start;
			x_start = temp;
			temp = y_end;
			y_end = y_start;
			y_start = temp;
		}

		error = 0;
		derr = (dx_a + 1);
		int dirx = x_end - x_start;
		if (dirx > 0) dirx =  1;
		if (dirx < 0) dirx = -1;

		int x = x_start;
		for (int y = y_start; y <= y_end; y++)
		{
			if (x >= 0 && x < width && y >= 0 && y < height)
				_screen->setPixel(x, y, color);
			else
				break;

			error += derr;
			if (error > dy_a + 1)
			{
				x += dirx;
				error -= dy_a + 1;
			}
		}
	}
}


void Renderer::drawMesh(const Mesh& mesh, const Color& color)
{
	const std::vector<Vec3f>& vb = mesh.getVerticies();
	pipeline(vb);

	const std::vector<int>& ib = mesh.getIndicies();
	size_t ib_size = ib.size();
	ib_size -= ib_size % 3;
	for (int i = 0; i < ib_size; i += 3)
	{
		Vec3f& v1 = _storage[ib[i]];
		Vec3f& v2 = _storage[ib[i + 1]];
		Vec3f& v3 = _storage[ib[i + 2]];

		drawLine(v1, v2, color);
		drawLine(v2, v3, color);
		drawLine(v3, v1, color);
	}
}


void Renderer::pipeline(const std::vector<Vec3f>& in)
{
	size_t in_size = in.size();
	if (_storage.size() < in_size)
		_storage.resize(in_size);

	for (int i = 0; i < in_size; i++)
	{
		Vec4f o = _vertexProc(in[i]);
		if (o.w)
			_storage[i] = Vec3f(o.x / o.w, o.y / o.w, o.z / o.w);
		else
			_storage[i] = Vec3f(o.x, o.y, o.z);
	}
}