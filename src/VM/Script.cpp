#include "common.h"
#include "VM/Script.h"
#include "VM/VM.h"
#include "System/VFS.h"

//==================================================
//! Initialize from a script file
//==================================================
VM::Script::Script( const string& strFilename, VM* pVM ) :
	m_pVM(pVM),
	m_strFilename(strFilename) {
	// Load the script. This could throw an exception if it fails
	vector<byte> script;
	g_VFS.LoadRaw( strFilename, script );
	
	// Just reinterpret the string of bytes as chars, appending a NULL terminator first
	script.push_back( '\0' );
	m_code= reinterpret_cast<char*>(&script[0]);
	
	// Now register with the VM
	m_pVM->registerScript( this );
}


//==================================================
//! Get the script's code
//==================================================
const string& VM::Script::GetCode() const {
	return m_code;
}