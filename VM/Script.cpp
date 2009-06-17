#include "common.h"
#include "VM/Script.h"
#include "VM/VM.h"
#include "System/VFS.h"

//==================================================
//! Initialize from a script file
//==================================================
VM::Script::Script( string strFilename, VM::VM* pVM ) :
	m_pVM(pVM) {
	// Load the script
	vector<byte> script;
	Error err= System::VFS::Get()->LoadRaw( strFilename, script );
	assert( err == ERROR_OK );
	
	// Just reinterpret the string of bytes as chars
	m_code= reinterpret_cast<char*>(&script[0]);
	// We seem to need a trailing newline...
	m_code+= "\n";
	
	// Now register with the VM
	m_pVM->registerScript( this );
}


//==================================================
//! Get the script's code
//==================================================
const string& VM::Script::GetCode() const {
	return m_code;
}