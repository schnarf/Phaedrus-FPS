#include "common.h"
#include "VM/Script.h"
#include "VM/VM.h"
#include "System/VFS.h"

//==================================================
//! Initialize from a script file
//==================================================
VM::Script::Script( string strFilename, VM::VM* pVM ) :
	m_pVM(pVM),
	m_strFilename(strFilename) {
	// Load the script
	vector<byte> script;
	Error err= g_VFS.LoadRaw( strFilename, script );
	assert( err == ERROR_OK );
	
	// Just reinterpret the string of bytes as chars
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