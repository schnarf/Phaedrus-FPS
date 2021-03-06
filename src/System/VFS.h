/* System/VFS.h
 *
 * Manages the VFS. Allows packages to be loaded,
 * and raw files to be opened
 */

#pragma once

namespace System {
	
	class VFS {
	public:
		//! Constructor
		VFS();
		//! Non-inline destructor
		~VFS();
		
		//! Load a file from the VFS into memory, can throw a FileIOException
		void LoadRaw( const string& strFilename, vector<byte>& data );
		
	private:
	}; // end class VFS
	
} // end namespace System
