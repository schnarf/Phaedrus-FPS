/* System/VFS.h
 *
 * Manages the VFS. Allows packages to be loaded,
 * and raw files to be opened
 */

#ifndef _SYSTEM_VFS_H_
#define _SYSTEM_VFS_H_

namespace System {
	
	class VFS {
	public:
		//! Public accessor
		static VFS* Get();
		
		//! Load a file from the VFS into memory
		Error LoadRaw( const string& strFilename, vector<byte>& data );
		
	private:
		//! Constructor
		VFS();
		//! Non-inline destructor
		~VFS();
		
		//! The singleton
		static VFS* m_pVFS;
	private:
	}; // end class VFS
	
}; // end namespace System

#endif
