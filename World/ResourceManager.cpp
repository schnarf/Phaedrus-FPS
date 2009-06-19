#include "World/Resources.h"
#include "World/ResourceManager.h"
#include "System/VFS.h"

//==================================================
//! Constructor
//==================================================
World::ResourceManager::ResourceManager() {
	
}


//==================================================
//! Loads the texture if necessary and retuns a reference
//==================================================
World::TextureRef World::ResourceManager::GetTexture( const string& strFilename ) {
	// If the texture is already loaded, return it
	for( vector<TextureRef>::iterator it= m_pTextures.begin(); it != m_pTextures.end(); ++it ) {
		if( (*it)->GetFilename() == strFilename ) {
			return *it;
		}
	}
	
	// If we're here, load the texture
	m_pTextures.push_back( TextureRef(new Texture(strFilename)) );
	return m_pTextures.back();
}


//==================================================
//! Loads the mesh if necessary and returns a reference
//==================================================
World::MeshRef World::ResourceManager::GetMesh( const string& strFilename ) {
	// If the mesh is already loaded, return it
	for( vector<MeshRef>::iterator it= m_pMeshes.begin(); it != m_pMeshes.end(); ++it ) {
		if( (*it)->GetFilename() == strFilename ) {
			return *it;
		}
	}
	
	// If we're here, load the texture
	m_pMeshes.push_back( MeshRef(new Mesh(strFilename)) );
	return m_pMeshes.back();

}

//==================================================
//! Non-inline destructor
//==================================================
World::ResourceManager::~ResourceManager() {
	
}