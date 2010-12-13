#pragma once

#if defined(_MSC_VER)
	// We've got to include windows.h before gl.h
	#include <Windows.h>
	#include <GL/GL.h>
	#include <GL/GLU.h>
#elif defined(__APPLE__)
	#include <OpenGL/GL.h>
	#include <OpenGL/GLU.h>
#else
	#error "Unknown platform"
#endif