/* Math/Vertex.h
 *
 * A point in 3d space
 */

#pragma once

namespace Math {

	class Vertex {
	public:
		//! Construct a vertex
		Vertex();
		
		//! Construct from another vertex
		Vertex( const Vertex& vtx );
		
		//! Construct from coordinates
		Vertex( float _x, float _y, float _z );
		
		//! Inline accessors
		inline float X() const { return x; }
		inline float Y() const { return y; }
		inline float Z() const { return z; }
		
		//! Inline set functions
		inline void X( float _x ) { x= _x; }
		inline void Y( float _y ) { y= _y; }
		inline void Z( float _z ) { z= _z; }
		
		//! Public members
		float x, y, z;
	}; // end struct Vertex
	
	typedef shared_ptr<Vertex> VertexRef;
	
} // end namespace Math
