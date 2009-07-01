#include "common.h"
#include "World/Level.h"
#include "World/ResourceManager.h"
#include "System/VFS.h"
#include <OpenGL/gl.h>
#include <boost/tokenizer.hpp>
#include <cstdio>

//==================================================
//! Load a level from a file
//==================================================
World::Level::Level( const string& strFilename ) {
	
	// Load the file from the VFS
	vector<byte> raw;
	Error err= g_VFS.LoadRaw( strFilename, raw );
	assert( err == ERROR_OK );
	
	// From the bytes, turn it into an array of lines
	string text((char*)&raw[0]);
	deque<string> lines;
	boost::char_separator<char> sep("\n");
	boost::tokenizer<boost::char_separator<char> > linetokens(text, sep);
	for( boost::tokenizer<boost::char_separator<char> >::iterator it= linetokens.begin(); it != linetokens.end(); ++it )
		lines.push_back( *it );
		
	// Parse the vertices
	uint uNumVertices;
	sscanf( lines.front().c_str(), "vertices %d", &uNumVertices );
	lines.pop_front();
	m_vertices.resize( uNumVertices );
	for( uint i=0; i<uNumVertices; ++i ) {
		uint j;
		float x, y, z;
		sscanf( lines.front().c_str(), "%u: %f, %f, %f", &j, &x, &y, &z );
		lines.pop_front();
		assert( j == i );
		m_vertices[i]= LevelVertex( x, y, z );
	}
	
	// Parse the textures
	uint uNumTextures;
	sscanf( lines.front().c_str(), "textures %d", &uNumTextures );
	lines.pop_front();
	vector<string> textures(uNumTextures);
	for( uint i=0; i<uNumTextures; ++i ) {
		uint j;
		char name[512];
		sscanf( lines.front().c_str(), "%u: %511s", &j, name );
		lines.pop_front();
		assert( i == j );
		
		textures[i]= name;
	}
	
	// Parse the surfaces
	uint uNumSurfaces;
	sscanf( lines.front().c_str(), "surfaces %u", &uNumSurfaces );
	lines.pop_front();
	m_surfaces.resize( uNumSurfaces );
	for( uint i=0; i<uNumSurfaces; ++i ) {
		uint j;
		uint uNumSurfVtx, uTexture;
		char remainder[512];
		sscanf( lines.front().c_str(), "%u: %u, %u", &j, &uNumSurfVtx, &uTexture );
		lines.pop_front();
		assert( i == j );
		
		m_surfaces[i].uNumVertices= uNumSurfVtx;
		m_surfaces[i].pTexture= g_ResourceManager.GetTexture( textures[uTexture] );
		m_surfaces[i].pVertices.clear();
		m_surfaces[i].textureCoords.clear();
		
		// Read in each vertex
		for( uint k=0; k<uNumSurfVtx; ++k ) {
			uint iVtx;
			float u, v;
			sscanf( lines.front().c_str(), "%u, %f, %f", &iVtx, &u, &v );
			lines.pop_front();
			assert( iVtx < uNumVertices );
			
			m_surfaces[i].pVertices.push_back( &m_vertices[iVtx] );
			m_surfaces[i].textureCoords.push_back( LevelTextureCoords(u, v) );
		}
	}
}


//==================================================
//! Free resources
//==================================================
World::Level::~Level() {
}


//==================================================
//! Render the level (rendering thread)
//==================================================
void World::Level::Render() {
	for( vector<LevelSurface>::iterator it= m_surfaces.begin(); it != m_surfaces.end(); ++it ) {
		it->pTexture->Bind();
		glBegin( GL_POLYGON );
			for( uint iVtx= 0; iVtx<it->uNumVertices; ++iVtx ) {
				glTexCoord2f( it->textureCoords[iVtx].u, it->textureCoords[iVtx].v );
				glVertex3f( it->pVertices[iVtx]->x, it->pVertices[iVtx]->y, it->pVertices[iVtx]->z );
			}
		glEnd();
	}
}