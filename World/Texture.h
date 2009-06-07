#ifndef _WORLD_TEXTURE_H_
#define _WORLD_TEXTURE_H_

#include "common.h"
#include <OpenGL/gl.h>

namespace World {
	
	//! The per-vertex texture coordinates
	struct TextureCoords {
		TextureCoords( float _U, float _V ) : U(_U), V(_V) {}
		float U, V;
	}; // end struct TextureCoords

	class Texture {
	public:
		//! Construct a texture from a file
		Texture( const string& strFilename );
		//! Free resources
		~Texture();
		
		//! Get this texture's filename
		inline string GetFilename() const { return m_strFilename; }
		
		//! Get this texture's id
		inline GLuint GetID() const { return m_id; }
		
		//! Bind this texture for rendering
		inline void Bind() const { glBindTexture( GL_TEXTURE_2D, m_id ); }
	private:	
		//! The filename this texture was loaded from
		string m_strFilename;
		
		//! The OpenGL texture id
		GLuint m_id;
		
		//! The width and height
		uint m_uWidth, m_uHeight;
	};
	
	typedef shared_ptr<Texture> TextureRef;

}; // end namespace World

#endif

