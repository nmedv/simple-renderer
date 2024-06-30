#include "Mesh.h"
#include "Utils.h"

#include <iostream>
#include <fstream>
#include <strstream>


int Mesh::loadFromFile(const char* path)
{
	std::ifstream in(path);
	if (!in.is_open())
	{
		_loaded = false;
		return Error::set(1, "can't open file \"%s\"", path);
	}

	while (!in.eof())
	{
		char line[128];
		in.getline(line, 128);

		char start = line[0];
		Vec3f v;
		std::strstream s;
		s << line;

		if (start == 'v')
		{
			s >> start >> v.x >> v.y >> v.z;
			_verticies.push_back(v);
		}
		else if (start == 'f')
		{
			int f[3];
			s >> start >> f[0] >> f[1] >> f[2];
			_indicies.push_back(f[0] - 1);
			_indicies.push_back(f[1] - 1);
			_indicies.push_back(f[2] - 1);
		}
	}

	_loaded = true;
	return 1;
}