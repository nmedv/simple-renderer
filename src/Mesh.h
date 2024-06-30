#ifndef MESH_H
#define MESH_H

#include "Matrix.h"

#include <cstdint>
#include <vector>


using Triangle = struct {
	int i[3];    // indexes of the vertexes that form a triangle
};


class Mesh
{
public:
	Mesh() : _loaded(false) {}
	Mesh(const char* path) { loadFromFile(path); }

	int loadFromFile(const char* path);
	inline bool isLoaded() { return _loaded; }

	inline const std::vector<Vec3f>& getVerticies() const { return _verticies; }
	inline const std::vector<int>& getIndicies() const { return _indicies; }

private:
	bool _loaded;
	std::vector<Vec3f> _verticies;
	std::vector<int> _indicies;
};


#endif