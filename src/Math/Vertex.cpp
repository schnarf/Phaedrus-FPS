#include "common.h"
#include "Math/Vertex.h"

//==================================================
//! Construct a vertex
//==================================================
Math::Vertex::Vertex() :
	x(0.0),
	y(0.0),
	z(0.0) {
}

//==================================================
//! Construct from another vertex
//==================================================
Math::Vertex::Vertex( const Vertex& vtx ) :
	x(vtx.X()),
	y(vtx.Y()),
	z(vtx.Z()) {
}

//==================================================
//! Construct from coordinates
//==================================================
Math::Vertex::Vertex( float _x, float _y, float _z ) :
	x(_x),
	y(_y),
	z(_z) {
}