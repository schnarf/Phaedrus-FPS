#include "common.h"
#include "World/Level.h"
#include "World/ResourceManager.h"
#include "System/VFS.h"
#include "Render/GL.h"
#include <boost/tokenizer.hpp>
#include <cstdio>

//==================================================
//! Load a level from a file
//==================================================
World::Level::Level( const string& strFilename ) {

	// Load the file from the VFS, this can throw an exception
	vector<byte> raw;
	g_pVFS->LoadRaw( strFilename, raw );
	
	// From the bytes, turn it into an array of lines
	string text((char*)&raw[0]);
	deque<string> lines;
	boost::char_separator<char> sep("\n");
	boost::tokenizer<boost::char_separator<char> > linetokens(text, sep);
	for( boost::tokenizer<boost::char_separator<char> >::iterator it= linetokens.begin(); it != linetokens.end(); ++it )
		lines.push_back( *it );
		
	// Parse the vertices
	uint uNumVertices;
	if( sscanf(lines.front().c_str(), "vertices %d", &uNumVertices) != 1 ) {
		THROW_EXCEPTION( FileParseException() );
	}
	lines.pop_front();

	m_vertices.resize( uNumVertices );
	for( uint i=0; i<uNumVertices; ++i ) {
		uint j;
		float x, y, z;
		if( sscanf(lines.front().c_str(), "%u: %f, %f, %f", &j, &x, &y, &z) != 4 ) {
			THROW_EXCEPTION( FileParseException() );
		}
		lines.pop_front();
		
		if( j != i ) THROW_EXCEPTION( FileParseException() );
		
		m_vertices[i]= LevelVertex( x, y, z );
	}
	
	// Parse the textures
	uint uNumTextures;
	if( sscanf(lines.front().c_str(), "textures %d", &uNumTextures) != 1 ) {
		THROW_EXCEPTION( FileParseException() );
	}
	lines.pop_front();

	vector<string> textures(uNumTextures);
	for( uint i=0; i<uNumTextures; ++i ) {
		uint j;
		char name[512];
		if( sscanf(lines.front().c_str(), "%u: %511s", &j, name) != 2 ) {
			THROW_EXCEPTION( FileParseException() );
		}
		lines.pop_front();
		
		if( j != 0 ) THROW_EXCEPTION( FileParseException() );
		
		textures[i]= name;
	}
	
	// Parse the surfaces
	uint uNumSurfaces;
	if( sscanf(lines.front().c_str(), "surfaces %u", &uNumSurfaces) != 1 ) {
		THROW_EXCEPTION( FileParseException() );
	}
	lines.pop_front();
	m_surfaces.resize( uNumSurfaces );
	for( uint i=0; i<uNumSurfaces; ++i ) {
		uint j;
		uint uNumSurfVtx, uTexture;
		char remainder[512];
		if( sscanf(lines.front().c_str(), "%u: %u, %u", &j, &uNumSurfVtx, &uTexture) != 3 ) {
			THROW_EXCEPTION( FileParseException() );
		}
		lines.pop_front();

		if( i != j ) THROW_EXCEPTION( FileParseException() );
		
		m_surfaces[i].uNumVertices= uNumSurfVtx;
		m_surfaces[i].pTexture= g_pResourceManager->GetTexture( textures[uTexture] );
		m_surfaces[i].pVertices.clear();
		m_surfaces[i].textureCoords.clear();
		
		// Read in each vertex
		for( uint k=0; k<uNumSurfVtx; ++k ) {
			uint iVtx;
			float u, v;
			if( sscanf(lines.front().c_str(), "%u, %f, %f", &iVtx, &u, &v) != 3 ) {
				THROW_EXCEPTION( FileParseException() );
			}
			lines.pop_front();

			if( iVtx >= uNumVertices ) THROW_EXCEPTION( FileParseException() );
			
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