#include "common.h"
#include "System/VFS.h"
#include "physfs.h"

// Global VFS
System::VFS g_VFS;
		
//==================================================
//! Load a file from the VFS into memory, can throw a FileIOException
//==================================================
void System::VFS::LoadRaw( const string& strFilename, vector<byte>& data ) {
	// Check to see if it exists
	if( !PHYSFS_exists(strFilename.c_str()) ) {
		THROW_EXCEPTION( FileReadException() << FileIOExceptionFilename(strFilename) );
	}
	
	// Open the file
	shared_ptr<PHYSFS_file> pFile( PHYSFS_openRead(strFilename.c_str()), PHYSFS_close );
	if( pFile.get() == NULL ) {
		THROW_EXCEPTION( FileReadException() << FileIOExceptionFilename(strFilename) );
	}

	// Try to read the number of bytes, fail if we can't
	PHYSFS_sint64 nBytes= PHYSFS_fileLength( pFile.get() );
	if( nBytes < 0 ) {
		THROW_EXCEPTION( FileReadException() << FileIOExceptionFilename(strFilename) );
	}
	data.resize( unsigned(nBytes) );

	// Try to read the data
	PHYSFS_sint64 nBytesRead= PHYSFS_read( pFile.get(), &data[0], sizeof(byte), data.size() );
	// Check for unexpected length
	if( nBytesRead != nBytes ) {
		data.resize( unsigned(nBytesRead) );
		THROW_EXCEPTION( FileReadException() << FileIOExceptionFilename(strFilename) );
	}
}

	
//==================================================
//! Constructor
//==================================================
System::VFS::VFS() {
	// Initialize PhysicsFS
	PHYSFS_init( NULL );
	
	// Hardcoded paths for now
	PHYSFS_addToSearchPath( "/Users/aaron/Documents/Phaedrus-FPS/Resources/", 1 );
}


//==================================================
//! Non-inline destructor
//==================================================
System::VFS::~VFS() {
	// Deinitialize PhysicsFS
	PHYSFS_deinit();
}
