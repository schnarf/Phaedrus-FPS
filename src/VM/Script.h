/* VM/Script.h
 *
 * Virtual Machine script object. Internally corresponds to lua scripts.
 */
 
#pragma once

namespace VM {

	class VM;
	
	class Script {
	public:
		//! Get the script's code
		const string& GetCode() const;
		
		//! Get the script's name
		const string& GetName() const { return m_strFilename; }
	private:
		string m_code;
		VM* m_pVM;
		string m_strFilename;

		//! Initialize from a script file
		Script( const string& strFilename, VM* pVM );

		//! Only the VM can create scriptss
		friend class VM;
	}; // end class Script

} // end namespace VM

