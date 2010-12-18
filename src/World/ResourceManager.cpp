#include "common.h"
#include "World/ResourceManager.h"

//==================================================
//! Constructor
//==================================================
World::ResourceManager::ResourceManager() {

}


//==================================================
//! Loads the texture if necessary and retuns a reference
//==================================================
shared_ptr<World::Texture> World::ResourceManager::GetTexture( const string& strFilename ) {
	return m_textureManager.Load( strFilename );
}


//==================================================
//! Loads the mesh if necessary and returns a reference
//==================================================
shared_ptr<World::Mesh> World::ResourceManager::GetMesh( const string& strFilename ) {
	return m_meshManager.Load( strFilename );
}

//==================================================
//! Non-inline destructor
//==================================================
World::ResourceManager::~ResourceManager() {
	
}