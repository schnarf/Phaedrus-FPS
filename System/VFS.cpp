#include "common.h"
#include "System/VFS.h"
#include "PhysicsFS/physfs.h"

// Global VFS
System::VFS g_VFS;
		
//==================================================
//! Load a file from the VFS into memory
//==================================================
Error System::VFS::LoadRaw( const string& strFilename, vector<byte>& data ) {
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
System::VFS::VFS() {
	// Initialize PhysicsFS
	PHYSFS_init( NULL );
	
	// Hardcoded paths for now
	PHYSFS_addToSearchPath( "/Users/aaron/Desktop/", 1 );
	PHYSFS_addToSearchPath( "/Users/aaron/Documents/Code/GameEngine/Resources/", 1 );
}


//==================================================
//! Non-inline destructor
//==================================================
System::VFS::~VFS() {
	// Deinitialize PhysicsFS
	PHYSFS_deinit();
}
