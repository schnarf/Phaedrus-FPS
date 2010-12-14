#include "common.h"
#include "World/Texture.h"
#include "World/Resources.h"
#include "System/VFS.h"
#include "Render/GL.h"
#include "SDL_image/SDL_image.h"

//==================================================
//! Construct a texture from a file
//==================================================
World::Texture::Texture( const string& strFilename ) :
	m_strFilename( strFilename ) {
	
	// Load the file from the VFS
	vector<byte> raw;
	Error err= g_VFS.LoadRaw( strFilename, raw );
	assert( err == ERROR_OK );
	
	// Load the image
	SDL_Surface* surface;
	SDL_RWops* rwops= SDL_RWFromMem(&raw[0], raw.size());
	assert( rwops != NULL );
	
	// Should do some type detection here
	surface= SDL_LoadBMP_RW( rwops, 1 );
	assert( surface != NULL );
	
	// Get the dimensions
	m_uWidth= surface->w;
	m_uHeight= surface->h;
	
	// Get the number of channels
	uint bpp= surface->format->BytesPerPixel;
	bool bRGB= surface->format->Rmask == 0xff;
	GLenum fmt;
	
	if( bpp == 4 ) {
		if( bRGB ) fmt= GL_RGBA;
		else assert( false );
	} else if( bpp == 3 ) {
		if( bRGB ) fmt= GL_RGB;
		else fmt= GL_RGB;
		//else assert( false );
	} else {
		assert( false );
	}
	
	// Create the OpenGL texture
	glEnable( GL_TEXTURE_2D );
	glGenTextures( 1, &m_id );
	glBindTexture( GL_TEXTURE_2D, m_id );
	glTexImage2D( GL_TEXTURE_2D, 0, bpp, m_uWidth, m_uHeight, 0, fmt, GL_UNSIGNED_BYTE, surface->pixels );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
	// GL_GENERATE_MIPMAP doesn't exist on windows. need to use glGenerateMipmap()?
	//glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);
	
	if( surface ) SDL_FreeSurface( surface );
}


//==================================================
//! Free resources
//==================================================
World::Texture::~Texture() {
	glDeleteTextures( 1, &m_id );
}