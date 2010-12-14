/* World/Level.h
 *
 * Loads a level from disk, contains all its geometry
 * and other information
 */

#pragma once

#include "World/Resources.h"

namespace World {

	class Texture;
	
	struct LevelVertex {
		LevelVertex( float _x, float _y, float _z ) : x(_x), y(_y), z(_z) {}
		LevelVertex() : x(0.0f), y(0.0f), z(0.0f) {}
		//! Position coordinates
		float x, y, z;
	}; // end struct LevelVertex
	
	struct LevelTextureCoords {
		LevelTextureCoords( float _u, float _v ) : u(_u), v(_v) {}
		//! Texture coordinates
		float u, v;
	}; // end struct LevelTextureCoords
	
	struct LevelSurface {
		uint uNumVertices;
		vector<LevelVertex*> pVertices;
		vector<LevelTextureCoords> textureCoords;
		
		//! The texture used by this surface
		TextureRef pTexture;
	}; // end struct LevelSurface

	class Level {
	public:
		//! Load a level from a file
		Level( const string& strFilename );
		//! Free resources
		~Level();
		
		//! Render the level (rendering thread)
		void Render();
	private:
		//! The vertices for geometry
		vector<LevelVertex> m_vertices;
		
		//! All the surfaces in the level
		vector<LevelSurface> m_surfaces;
	}; // end class Level
	
} // end namespace World
