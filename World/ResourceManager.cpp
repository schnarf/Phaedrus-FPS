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
//! Load a file from the VFS into memory
//==================================================
Error World::ResourceManager::LoadRaw( const string& strFilename, vector<byte>& data ) {
	// Check to see if it exists
	if( !PHYSFS_exists(strFilename.c_str()) ) {
		return ERROR_FILE_DOES_NOT_EXIST;
	}
	
	// Open the file, allocate, and read
	PHYSFS_file* file= PHYSFS_openRead( strFilename.c_str() );
	data.resize( PHYSFS_fileLength(file) );
	PHYSFS_read( file, &data[0], sizeof(byte), data.size() );
	PHYSFS_close( file );
	
	return ERROR_OK;
}


//==================================================
//! Constructor
//==================================================
World::ResourceManager::ResourceManager() {
	// Initialize PhysicsFS
	PHYSFS_init( NULL );
	
	// Hardcoded paths for now
	PHYSFS_addToSearchPath( "/Users/aaron/Desktop/", 1 );
	PHYSFS_addToSearchPath( "/Users/aaron/Documents/ioquake3/baseq3/pak0/", 1 );
}

//==================================================
//! Non-inline destructor
//==================================================
World::ResourceManager::~ResourceManager() {
	// Deinitialize PhysicsFS
	PHYSFS_deinit();
}