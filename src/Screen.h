#ifndef SCREEN_H
#define SCREEN_H

#include <cstdint>


struct Color
{
	Color() : r(0), g(0), b(0), a(0) {}
	Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a) : r(r), g(g), b(b), a(a) {}

	uint8_t r;
	uint8_t g;
	uint8_t b;
	uint8_t a;
};


class Screen
{
public:
	Screen(int width, int height, const char* title);
	~Screen();

	inline bool shouldClose() const { return _shouldClose; }
	void pollEvents();
	void flush();

	inline int getWidth() const { return _bufferWidth; }
	inline int getHeight() const { return _bufferHeight; }
	inline int getSize() const { return _bufferWidth * _bufferHeight; }
	void setWindowTitle(const char* title);

	inline float getAspectRatio() const
	{
		return static_cast<float>(_bufferHeight) / static_cast<float>(_bufferWidth);
	}
	
	inline void setPixel(int x, int y, const Color& color)
	{
		_buffer[y * _bufferWidth + x] = color;
	}

	void clear(const Color& color)
	{
		for (int i = 0; i < _bufferWidth * _bufferHeight; i++)
		{
			_buffer[i] = color;
		}
	}

private:
	bool _shouldClose = false;
	Color* _buffer;
	int _bufferWidth;
	int _bufferHeight;

	using internal_data = struct data {
		void* hwnd;
		void* hbm;
	};

	internal_data _data;
};


#endif