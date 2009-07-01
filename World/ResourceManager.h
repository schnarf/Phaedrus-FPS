/* World/ResourceManager.h
 * 
 * Responsible for loading anything that comes from the VFS
 * Also tracks references, so each asset only needs to be loaded once
 */

#ifndef _WORLD_RESOURCEMANAGER_H_
#define _WORLD_RESOURCEMANAGER_H_

#include "common.h"
#include "World/Resources.h"

namespace World {

	class ResourceManager {
	public:
		//! Constructor
		ResourceManager();
		
		//! Non-inline destructor
		~ResourceManager();
		
		//! Loads the texture if necessary and retuns a reference
		TextureRef GetTexture( const string& strFilename );
		
		//! Loads the mesh if necessary and returns a reference
		MeshRef GetMesh( const string& strFilename );
	private:
		//! Resources
		vector<TextureRef> m_pTextures;
		vector<MeshRef> m_pMeshes;
	}; // end class ResourceManager

}; // end namespace World

#endif
