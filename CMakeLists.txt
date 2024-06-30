cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

project(simple-renderer)

add_executable(simple-renderer
	src/Main.cpp
	src/Screen.cpp
	src/Matrix.cpp
	src/Quat.cpp
	src/Renderer.cpp
	src/Mesh.cpp
	src/Utils.cpp
	src/Timer.cpp
)