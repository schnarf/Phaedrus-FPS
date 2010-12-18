/* World/ResourceManager.h
 * 
 * Responsible for loading anything that comes from the VFS
 * Also tracks references, so each asset only needs to be loaded once
 */
#pragma once

#include "World/Resources.h"

namespace World {


	class ResourceManager {
	public:
		//! Constructor
		ResourceManager();
		//! Non-inline destructor
		~ResourceManager();
		
		//! Loads the texture if necessary and retuns a reference
		shared_ptr<Texture> GetTexture( const string& strFilename );
		//! Loads the mesh if necessary and returns a reference
		shared_ptr<Mesh> GetMesh( const string& strFilename );
	
	private:
		template <typename T>
		class Impl {
		public:
			//! Loads a resource, from cache, if possible, or from disk if necesasry
			shared_ptr<T> Load( const string& strFilename ) {
				// Search for the resource in our map
				map< string, weak_ptr<T> >::iterator pCachedResource= m_resources.find( strFilename );
				// If the resource is not in the map, or if the weak pointer is expired, we have to load it
				if( pCachedResource == m_resources.end() || pCachedResource->second.expired() ) {
					// Try to load the resources
					shared_ptr<T> pResource;
					try {
						pResource.reset( new T(strFilename) );
					} catch( const FileIOException& e ) {	
						return shared_ptr<T>( NULL );
					} // end try to load the resource

					// Insert the resource into our cache map
					m_resources[strFilename]= weak_ptr<T>( pResource );
					return pResource;
				} else {
					// Return our cached resource
					return pCachedResource->second.lock();
				}
			}
		private:
			//! Maps from filenames to resources
			map< string, weak_ptr<T> > m_resources;
		}; // end class Impl

		Impl<Texture> m_textureManager;
		Impl<Mesh> m_meshManager;

	}; // end class ResourceManager

} // end namespace World
