#include "World/Resources.h"
#include "World/ResourceManager.h"
#include "PhysicsFS/physfs.h"

World::ResourceManager* World::ResourceManager::m_pResourceManager= NULL;

//==================================================
//! Public accessor
//==================================================
World::ResourceManager* World::ResourceManager::Get() {
	if( m_pResourceManager == NULL ) {
		m_pResourceManager= new ResourceManager();
	}
	
	return m_pResourceManager;
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
//! Constructor
//==================================================
World::ResourceManager::ResourceManager() {
	
}

//==================================================
//! Non-inline destructor
//==================================================
World::ResourceManager::~ResourceManager() {
	
}